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

uint32_t reference(uint32_t operandOne, uint32_t operandTwo, int operation) {
        float foperandOne, foperandTwo;
        memcpy(&foperandOne, &operandOne, 4);
        memcpy(&foperandTwo, &operandTwo, 4);
        volatile float result = (operation == 1) ? foperandOne - foperandTwo : foperandOne + foperandTwo;
        float resultFinal = result;
        uint32_t bits;
        memcpy(&bits, &resultFinal, 4);
        return bits;
}

void tick() {
	dut->clk = 0;
	dut->eval();
	trace->dump(sim_time++);
	dut->clk = 1;
	dut->eval();
	trace->dump(sim_time++);
}

uint32_t randomFinite() {
    uint32_t x;
    do { x = any32(rng); } while (((x >> 23) & 0xFF) == 0xFF);
    return x;
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
		dut->operandOne = randomFinite();
		dut->operandTwo = randomFinite();
		dut->operation = opDist(rng);
		tick();
		uint32_t expected = reference(dut->operandOne, dut->operandTwo, dut->operation);
		if (dut->result != expected) {
			printf("t=%llu, operation=%u, operand one=%08X, operand two=%08X\n",
                	(unsigned long long)sim_time, dut->operation, dut->operandOne, dut->operandTwo);
        		printf("  MISMATCH: expected=%08X got=%08X\n", expected, dut->result);
        		errors++;
		}
	}
	printf("tests=%llu errors=%d\n", (unsigned long long)((sim_time - 6) / 2), errors);
	trace->close();
	dut->final();
   	delete dut;
    	return errors != 0;	
}
