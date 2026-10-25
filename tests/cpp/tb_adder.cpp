#include "Vadder.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <cstdint>
#include <cstring>
#include <cfenv>
#include <cmath>
#include <random>
#include <cstdio>

Vadder* dut;
VerilatedVcdC* trace;
vluint64_t sim_time = 0;

int errors = 0;

std::mt19937 rng(12345);
std::uniform_int_distribution<uint32_t> any32;
std::uniform_int_distribution<int> opDist(0, 1);

struct TestCase { uint32_t a, b; int op; };

const TestCase directed[] = {
        // Infinity combinations
        {0x7F800000, 0x7F800000, 1},   // +inf - +inf  -> NaN, invalid
        {0x7F800000, 0xFF800000, 0},   // +inf + -inf  -> NaN, invalid
        {0xFF800000, 0xFF800000, 1},   // -inf - -inf  -> NaN, invalid
        {0x7F800000, 0x7F800000, 0},   // +inf + +inf  -> +inf
        {0x7F800000, 0xFF800000, 1},   // +inf - -inf  -> +inf
        {0x3F800000, 0x7F800000, 1},   // 1.0 - +inf   -> -inf

        // NaNs
        {0x7F800001, 0x3F800000, 0},   // sNaN + 1.0   -> NaN, invalid
        {0x7FC00000, 0x3F800000, 0},   // qNaN + 1.0   -> NaN, no flags
        {0x7F800001, 0x7F800000, 0},   // sNaN + +inf  -> NaN, invalid
        {0x7FC00000, 0x7F800000, 1},   // qNaN - +inf  -> NaN, no flags

        // Signed zeros
        {0x00000000, 0x00000000, 0},   // +0 + +0 -> +0
        {0x80000000, 0x80000000, 0},   // -0 + -0 -> -0
        {0x00000000, 0x80000000, 0},   // +0 + -0 -> +0
        {0x80000000, 0x00000000, 0},   // -0 + +0 -> +0
        {0x3F800000, 0x3F800000, 1},   // 1.0 - 1.0 -> +0
};

bool isNaN(uint32_t x) {
	return ((x >> 23) & 0xFF) == 0xFF && (x & 0x7FFFFFFF) != 0;
}

uint32_t reference(uint32_t operandOne, uint32_t operandTwo, int operation, uint32_t& expectedFlags) {
	float one, two;
        volatile float foperandOne, foperandTwo;
        memcpy(&one, &operandOne, 4);
        memcpy(&two, &operandTwo, 4);

	foperandOne = one;
	foperandTwo = two;

	feclearexcept(FE_ALL_EXCEPT);
        volatile float result = (operation == 1) ? foperandOne - foperandTwo : foperandOne + foperandTwo;
	int raised = fetestexcept(FE_ALL_EXCEPT);

	expectedFlags =
                ((raised & FE_INVALID)   ? 1u << 4 : 0) |
                ((raised & FE_DIVBYZERO) ? 1u << 3 : 0) |
                ((raised & FE_OVERFLOW)  ? 1u << 2 : 0) |
                ((raised & FE_UNDERFLOW) ? 1u << 1 : 0) |
                ((raised & FE_INEXACT)   ? 1u << 0 : 0);

        float resultFinal = result;
        uint32_t bits;
        memcpy(&bits, &resultFinal, 4);
        return bits;
}

void tick() {
	dut->clk = 0;
	dut->eval();
	sim_time++;
	dut->clk = 1;
	dut->eval();
	sim_time++;
}

void reset() {
	dut->rst_n = 0;
	dut->operation = 0;
	dut->operandOne = 0;
	dut->operandTwo = 0;
	dut->enable = 0;
	for (int i = 0; i < 3; i++) {
		tick();
	}
	dut->rst_n = 1;
}

void runTest(uint32_t a, uint32_t b, int op) {
        dut->operandOne = a;
        dut->operandTwo = b;
        dut->operation = op;
        tick();

        uint32_t expectedFlags;
        uint32_t expected = reference(a, b, op, expectedFlags);
        bool resultMatches = (dut->result == expected) || (isNaN(dut->result) && isNaN(expected));

        if (!resultMatches || dut->flags != expectedFlags) {
                printf("op=%d a=%08X b=%08X  expected=%08X flags=%02X  got=%08X flags=%02X\n",
                       op, a, b, expected, expectedFlags, dut->result, (unsigned)dut->flags);
                errors++;
        }
}

int main(int argc, char** argv) {
	fesetround(FE_TOWARDZERO);
	Verilated::commandArgs(argc, argv);
    	Verilated::traceEverOn(true);

	dut = new Vadder;
	trace = new VerilatedVcdC;
    	dut->trace(trace, 5);
    	trace->open("adder.vcd");
	reset();

	dut->enable = 1;
	
	for (const TestCase& t : directed) {
        	runTest(t.a, t.b, t.op);
	}

	while (sim_time <= 200000004) {
		runTest(any32(rng), any32(rng), opDist(rng));
	}
	printf("tests=%llu errors=%d\n", (unsigned long long)((sim_time - 6) / 2), errors);
	trace->close();
	dut->final();
   	delete dut;
    	return errors != 0;	
}
