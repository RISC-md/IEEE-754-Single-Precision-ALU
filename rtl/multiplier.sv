import alu_pkg::*;

module multiplier( // Module performs multiplicaton on two single-precision floats
	input logic clk,
	input logic rst_n,
	input logic enable,

	input logic [DATA_WIDTH-1:0] operandOne,
	input logic [DATA_WIDTH-1:0] operandTwo,
	input alu_operations_e operation,
	
	output logic [DATA_WIDTH-1:0] result,
	output exception_flag_t flags,

	output logic done	
);
	localparam int EXTENDED_WIDTH = EXPONENT_WIDTH + 2;
	localparam int MANTISSA_PRODUCT_WIDTH = MANTISSA_WIDTH * 2 + 2;

	operand_format_t operandOneFormatted;
       	operand_format_t operandTwoFormatted;
	operand_format_t resultFormatted;

	logic [EXTENDED_WIDTH-1:0] exponent;

	logic [MANTISSA_WIDTH:0] prependedMantissaOne;
	logic [MANTISSA_WIDTH:0] prependedMantissaTwo;

	logic [MANTISSA_PRODUCT_WIDTH-1:0] prependedMantissaProduct;

	logic [MANTISSA_PRODUCT_WIDTH-1:0] normalizedMantissaProduct;
	
	always_ff @(posedge clk or negedge rst_n) begin // Block for determining sign of result
		if (!rst_n) begin 
			resultFormatted.sign <= 0;
		end else if (enable) begin
			if (operation == MUL) begin
				resultFormatted.sign <= operandOneFormatted.sign ^ operandTwoFormatted.sign;
			end
		end
	end

	always_ff @(posedge clk or negedge rst_n) begin // Block for determining exponent of result
		if (!rst_n) begin 
			resultFormatted.exponent <= '0;
		end else if (enable) begin 
			if (operation == MUL) begin 
				if (prependedMantissaProduct[MANTISSA_PRODUCT_WIDTH-1]) begin 
					if (exponent >= $signed(10'd254)) begin 
						resultFormatted.exponent <= 8'hFF;
					end else begin
						resultFormatted.exponent <= exponent[EXPONENT_WIDTH-1:0] + 1'b1;
					end
				end else begin 
					if (exponent >= $signed(10'd254)) begin 
						resultFormatted.exponent <= 8'hFF;
					end else if (exponent < $signed(10'd1) begin 
						resultFormatted.exponent <= 8'h00;
					end else begin	
						resultFormatted.exponent <= exponent[EXPONENT_WIDTH-1:0];
					end
				end
			end
		end
	end

	always_ff @(posedge clk or negedge rst_n) begin // Block for determining mantissa of result
		if (!rst_n) begin 
			resultFormatted.mantissa <= '0;
		end else if (enable) begin
			if (operation == MUL) begin
				resultFormatted.mantissa <= normalizedMantissaProduct[MANTISSA_PRODUCT_WIDTH - 3 -: MANTISSA_WIDTH];
			end
		end
	end

	always_comb begin // Block for formatting data
		operandOneFormatted = '0;
		operandTwoFormatted = '0;
		exponent = '0;
		prependedMantissaOne = '0;
		prependedMantissaTwo = '0;
		prependedMantissaProduct = '0;
		normalizedMantissaProduct = '0;
		if (enable) begin
			operandOneFormatted.sign = operandOne[DATA_WIDTH - 1];
			operandTwoFormatted.sign = operandTwo[DATA_WIDTH - 1];

			operandOneFormatted.exponent = operandOne[DATA_WIDTH - 2 -: EXPONENT_WIDTH];
			operandTwoFormatted.exponent = operandTwo[DATA_WIDTH - 2 -: EXPONENT_WIDTH];

			operandOneFormatted.mantissa = operandOne[DATA_WIDTH - 2 - EXPONENT_WIDTH -: MANTISSA_WIDTH];
			operandTwoFormatted.mantissa = operandTwo[DATA_WIDTH - 2 - EXPONENT_WIDTH -: MANTISSA_WIDTH];

			exponent = operandOneFormatted.exponent + operandTwoFormatted.exponent - BIAS;

			prependedMantissaOne = (operandOneFormatted.exponent == '0) ? {1'b0, operandOneFormatted.mantissa} : {1'b1, operandOneFormatted.mantissa};
                        prependedMantissaTwo = (operandTwoFormatted.exponent == '0) ? {1'b0, operandTwoFormatted.mantissa} : {1'b1, operandTwoFormatted.mantissa};

			prependedMantissaProduct = prependedMantissaOne * prependedMantissaTwo;

			normalizedMantissaProduct = prependedMantissaProduct[MANTISSA_PRODUCT_WIDTH-1] ? prependedMantissaProduct >> 1 : prependedMantissaProduct;

		end
	end	

	assign result = {resultFormatted.sign, resultFormatted.exponent, resultFormatted.mantissa};
endmodule
