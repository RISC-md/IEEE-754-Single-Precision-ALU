import alu_pkg::*;

module multiplier( // Module performs multiplicaton on two single-precision floats
	input logic clk,
	input logic rst_n,

	input logic [DATA_WIDTH-1:0] operandOne,
	input logic [DATA_WIDTH-1:0] operandTwo,
	input alu_operations_e operation,

	input logic validIn,
	input logic readyIn,

	output logic validOut,
	output logic readyOut,
	
	output logic [DATA_WIDTH-1:0] result	
);
