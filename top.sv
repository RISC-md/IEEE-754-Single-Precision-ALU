import alu_pkg::*;

module top(
	input [DATA_WIDTH-1:0] logic operandOne,
	input [DATA_WIDTH-1:0] logic operandTwo,
	input alu_operations_e operation,

	output [DATA_WIDTH-1:0] logic result
);
