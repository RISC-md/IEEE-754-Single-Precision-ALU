#include "Vmultiplier.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <cstdint>
#include <cstring>
#include <cfenv>
#include <cmath>
#include <random>
#include <cstdio>

Vmultiplier* dut;
VerilatedVcdC* trace;
vluint64_t sim_time = 0;

int errors = 0;

std::mt19937 rng(12345);
std::uniform_int_distribution<uint32_t> any32;
std::uniform_int_distribution<int> opDist(0, 1);

struct TestCase { 
	uint32_t a, b;
};

const TestCase directed[] = {
        {0x3F800000, 0x3F800000},   // 1.0 * 1.0   = 1.0
        {0x3FC00000, 0x3FC00000},   // 1.5 * 1.5   = 2.25 (carry)
        {0x40000000, 0x3F000000},   // 2.0 * 0.5   = 1.0
        {0xBF800000, 0x40400000},   // -1.0 * 3.0  = -3.0
        {0x7F000000, 0x7F000000},   // 2^127 * 2^127 -> overflow, max finite
        {0x20000000, 0x20000000},   // 2^-63 * 2^-63 = 2^-126, smallest normal
        {0x1F800000, 0x1F800000},   // 2^-64 * 2^-64 = 2^-128 -> denormal result
	{0x0C000000, 0x0C000000},   // 2^-103 * 2^-103 -> truncates to +0
	{0x00400000, 0x40000000},   // 2^-127 * 2.0      = 2^-126  -> 00800000
	{0x00000001, 0x7F000000},   // 2^-149 * 2^127    = 2^-22   -> 34800000
	{0x007FFFFF, 0x40000000},   // largest denormal * 2.0       -> 00FFFFFE
	{0x00000001, 0x00000001},   // denormal * denormal          -> +0
	{0x00000000, 0x3F800000},   // +0 * 1.0  -> +0
	{0x80000000, 0x40400000}  // -0 * 3.0  -> -0
};

bool isNaN(uint32_t x) {
	return ((x >> 23) & 0xFF) == 0xFF && (x & 0x7FFFFF) != 0;
}

uint32_t randomNormal() {
        uint32_t x, e;
        do { 
		x = any32(rng); 
		e = (x >> 23) & 0xFF; 
	} while (e == 0xFF);
        return x;
}

uint32_t reference(uint32_t operandOne, uint32_t operandTwo, int operation, uint32_t& expectedFlags) {
	float one, two;
        volatile float foperandOne, foperandTwo;
        memcpy(&one, &operandOne, 4);
        memcpy(&two, &operandTwo, 4);

	foperandOne = one;
	foperandTwo = two;

	feclearexcept(FE_ALL_EXCEPT);
        volatile float result = foperandOne * foperandTwo;
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

        if (!resultMatches) {
                printf("op=%d a=%08X b=%08X  expected=%08X  got=%08X\n",
                       op, a, b, expected, dut->result);
                errors++;
        }
}

int main(int argc, char** argv) {
	fesetround(FE_TOWARDZERO);
	Verilated::commandArgs(argc, argv);
    	Verilated::traceEverOn(true);

	dut = new Vmultiplier;
	trace = new VerilatedVcdC;
    	dut->trace(trace, 5);
    	trace->open("multiplier.vcd");
	reset();

	dut->enable = 1;
	
	for (const TestCase& t : directed) {
        	runTest(t.a, t.b, 2);
	}

	while (sim_time <= 200000004) {
		runTest(randomNormal(), randomNormal(), 2);
	}
	printf("tests=%llu errors=%d\n", (unsigned long long)((sim_time - 6) / 2), errors);
	trace->close();
	dut->final();
   	delete dut;
    	return errors != 0;	
}
