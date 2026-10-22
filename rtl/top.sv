import alu_pkg::*;

module top(
	input clk,
	input rst_n,

	input logic [DATA_WIDTH-1:0] operandOne,
	input logic [DATA_WIDTH-1:0] operandTwo,
	input alu_operations_e operation,

	input validIn,
	input readyIn,

	output validOut,
	output readyOut,

	output logic [DATA_WIDTH-1:0] result
);
