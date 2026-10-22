package alu_operations_pkg;

	parameter int DATA_WIDTH = 32;
	parameter int EXPONENT_WIDTH = 8;
	parameter int MANTISSA_WIDTH = 23;
	parameter int BIAS = 12;

	typedef enum logic [2:0] {
		ADD = 3'b000,
		SUB = 3'b001,
		MUL = 3'b010,
		DIV = 3'b011,
		SQRT = 3'b100	
	} alu_operations_e;

	typedef struct packed {
		logic sign;
		logic [EXPONENT_WIDTH-1:0] exponent;
		logic [EXPONENT_WIDTH-1:0] mantissa;
	} operand_partitions_t;
end package;
