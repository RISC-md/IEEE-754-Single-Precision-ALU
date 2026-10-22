import alu_pkg::*;

module multiplier(
	input logic [DATA_WIDTH-1:0] operandOne,
	input logic [DATA_WIDTH-1:0] operandTwo,
	input alu_operations_e operation,
	
	output logic [DATA_WIDTH-1:0] result	
);
