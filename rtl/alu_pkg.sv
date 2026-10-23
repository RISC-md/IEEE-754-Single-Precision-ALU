package alu_operations_pkg; // Package as these are all more or less shared between each operation file and the top file

	parameter int DATA_WIDTH = 32; // Width of operands and result
	parameter int EXPONENT_WIDTH = 8; // Width of the whole number 2^n part of the operands and result
	parameter int MANTISSA_WIDTH = 23; // Width of the decimals of the operands and result
	parameter int BIAS = 127; // For shifting negative numbers per IEEE 754 spec 
	
	parameter int EXPONENT_WIDTH_NEW = EXPONENT_WIDTH - 1;
	parameter int MANTISSA_WIDTH_NEW = MANTISSA_WIDTH - 1;

	// enum to represent ALU operations
	typedef enum logic [2:0] {
		ADD = 3'b000,
		SUB = 3'b001,
		MUL = 3'b010,
		DIV = 3'b011,
		SQRT = 3'b100	
	} alu_operations_e;
	
	// Struct to demonstrate different pieces of the operands
	typedef struct packed {
		logic sign;
		logic [EXPONENT_WIDTH-1:0] exponent;
		logic [EXPONENT_WIDTH-1:0] mantissa;
	} operand_format_t;
end package;
