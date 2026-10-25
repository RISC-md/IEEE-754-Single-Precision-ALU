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

bool isNaN(uint32_t x) { 
	return ((x >> 23) & 0xFF) == 0xFF && (x & 0x7FFFFF) != 0; 
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

	while (sim_time <= 200000004) {
		dut->operandOne = any32(rng);
		dut->operandTwo = any32(rng);
		dut->operation = opDist(rng);
		tick();
		uint32_t expectedFlags;
		uint32_t expected = reference(dut->operandOne, dut->operandTwo, dut->operation, expectedFlags);
		bool resultMatches = (dut->result == expected) || (isNaN(dut->result) && isNaN(expected));
		if (!resultMatches) {
			printf("t=%llu, operation=%u, operand one=%08X, operand two=%08X\n",
                	      (unsigned long long)sim_time, dut->operation, dut->operandOne, dut->operandTwo);
        		printf("  MISMATCH: expected=%08X got=%08X\n", expected, dut->result);
        		errors++;
		}
		if (dut->flags != expectedFlags) {
			printf("t=%llu, operation=%u, operand one=%08X, operand two=%08X\n",
               		      (unsigned long long)sim_time, dut->operation, dut->operandOne, dut->operandTwo);
        		printf("  FLAG MISMATCH: expected=%02X got=%02X\n", expectedFlags, (unsigned)dut->flags);
        		errors++;
		}
	}
	printf("tests=%llu errors=%d\n", (unsigned long long)((sim_time - 6) / 2), errors);
	trace->close();
	dut->final();
   	delete dut;
    	return errors != 0;	
}
