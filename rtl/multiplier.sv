import alu_pkg::*;

module multiplier( // Module performs multiplicaton on two single-precision floats
	input logic clk,
	input logic rst_n,
	input logic enable,

	input logic [DATA_WIDTH-1:0] operandOne,
	input logic [DATA_WIDTH-1:0] operandTwo,
	input alu_operations_e operation,
	
	output logic [DATA_WIDTH-1:0] result,
	output exception_flag_t flags	
);
	localparam int EXTENDED_WIDTH = EXPONENT_WIDTH + 2;
	localparam int MANTISSA_PRODUCT_WIDTH = MANTISSA_WIDTH * 2 + 2;

	operand_format_t operandOneFormatted;
       	operand_format_t operandTwoFormatted;
	operand_format_t resultFormatted;

	logic signed [EXTENDED_WIDTH-1:0] exponent;

	logic [MANTISSA_WIDTH:0] prependedMantissaOne;
	logic [MANTISSA_WIDTH:0] prependedMantissaTwo;

	logic [MANTISSA_PRODUCT_WIDTH-1:0] prependedMantissaProduct;

	logic [MANTISSA_PRODUCT_WIDTH-1:0] normalizedMantissaProduct;
	logic [MANTISSA_PRODUCT_WIDTH-1:0] denormalizedMantissaProduct;

	logic isZeroOne;
	logic isZeroTwo;
	
	logic signed [EXTENDED_WIDTH-1:0] effectiveExponentOne;
	logic signed [EXTENDED_WIDTH-1:0] effectiveExponentTwo;

	logic signed [EXTENDED_WIDTH-1:0] leadingZeroOne;
	logic signed [EXTENDED_WIDTH-1:0] leadingZeroTwo;

	logic [MANTISSA_WIDTH:0] normalizedSignificandOne;
	logic [MANTISSA_WIDTH:0] normalizedSignificandTwo;

	logic signed [EXTENDED_WIDTH-1:0] adjustedExponentOne;
	logic signed [EXTENDED_WIDTH-1:0] adjustedExponentTwo;

	assign isZeroOne = operandOne[DATA_WIDTH-2:0] == '0;
	assign isZeroTwo = operandTwo[DATA_WIDTH-2:0] == '0;

	assign effectiveExponentOne = operandOneFormatted.exponent == '0 ? 1 : EXTENDED_WIDTH'(operandOneFormatted.exponent);
	assign effectiveExponentTwo = operandTwoFormatted.exponent == '0 ? 1 : EXTENDED_WIDTH'(operandTwoFormatted.exponent);

	assign normalizedSignificandOne = prependedMantissaOne << leadingZeroOne;
	assign normalizedSignificandTwo = prependedMantissaTwo << leadingZeroTwo;

	assign adjustedExponentOne = effectiveExponentOne - leadingZeroOne;
	assign adjustedExponentTwo = effectiveExponentTwo - leadingZeroTwo;

	logic isInfinityOne;
	logic isInfinityTwo;

	logic isSpecial;
	logic isSpecialLatch;

	logic [DATA_WIDTH-1:0] specialResult;
	logic [DATA_WIDTH-1:0] specialResultLatch;

	logic isNaNOne;
	logic isNaNTwo;

	logic isNaNOneSignaling;
	logic isNaNTwoSignaling;

	assign isNaNOne = (operandOneFormatted.exponent == 8'hFF) && (operandOneFormatted.mantissa != '0);
	assign isNaNTwo = (operandTwoFormatted.exponent == 8'hFF) && (operandTwoFormatted.mantissa != '0);

	assign isNaNOneSignaling = (operandOneFormatted.exponent == 8'hFF) && (operandOneFormatted.mantissa != '0) && (operandOneFormatted.mantissa[MANTISSA_WIDTH-1] == 1'b0);
	assign isNaNTwoSignaling = (operandTwoFormatted.exponent == 8'hFF) && (operandTwoFormatted.mantissa != '0) && (operandTwoFormatted.mantissa[MANTISSA_WIDTH-1] == 1'b0);

	assign isInfinityOne = (operandOneFormatted.exponent == 8'hFF) && (operandOneFormatted.mantissa == '0);
	assign isInfinityTwo = (operandTwoFormatted.exponent == 8'hFF) && (operandTwoFormatted.mantissa == '0);

	exception_flag_t nextFlags;

	always_ff @(posedge clk or negedge rst_n) begin 
		if (!rst_n) begin 
			flags <= '0;
		end else if (enable) begin 
			flags <= nextFlags;
		end
	end

	always_ff @(posedge clk or negedge rst_n) begin 
		if (!rst_n) begin 
			isSpecialLatch <= 0;
			specialResultLatch <= '0;
		end else if (enable) begin 
			isSpecialLatch <= isSpecial;
			specialResultLatch <= specialResult;
		end
	end
	
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
					if (exponent >= 10'sd254) begin 
						resultFormatted.exponent <= 8'hFE;
					end else if (exponent <= -1) begin
						resultFormatted.exponent <= 8'h00;
					end else begin
						resultFormatted.exponent <= exponent[EXPONENT_WIDTH-1:0] + 1'b1;
					end
				end else begin 
					if (exponent > 10'sd254) begin 
						resultFormatted.exponent <= 8'hFE;
					end else if (exponent < 10'sd1) begin 
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
				if ((prependedMantissaProduct[MANTISSA_PRODUCT_WIDTH-1] && exponent >= 10'sd254) || (!prependedMantissaProduct[MANTISSA_PRODUCT_WIDTH-1] && exponent > 10'sd254)) begin	
					resultFormatted.mantissa <= '1;
				end else if (exponent <= 0) begin 
					resultFormatted.mantissa <= denormalizedMantissaProduct[MANTISSA_PRODUCT_WIDTH - 3 -: MANTISSA_WIDTH];
				end else begin
					resultFormatted.mantissa <= normalizedMantissaProduct[MANTISSA_PRODUCT_WIDTH - 3 -: MANTISSA_WIDTH];
				end
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
		denormalizedMantissaProduct = '0;
		if (enable) begin
			operandOneFormatted.sign = operandOne[DATA_WIDTH - 1];
			operandTwoFormatted.sign = operandTwo[DATA_WIDTH - 1];

			operandOneFormatted.exponent = operandOne[DATA_WIDTH - 2 -: EXPONENT_WIDTH];
			operandTwoFormatted.exponent = operandTwo[DATA_WIDTH - 2 -: EXPONENT_WIDTH];

			operandOneFormatted.mantissa = operandOne[DATA_WIDTH - 2 - EXPONENT_WIDTH -: MANTISSA_WIDTH];
			operandTwoFormatted.mantissa = operandTwo[DATA_WIDTH - 2 - EXPONENT_WIDTH -: MANTISSA_WIDTH];

			if (isZeroOne || isZeroTwo) begin
				exponent = '0;
			end else begin 
				exponent = adjustedExponentOne + adjustedExponentTwo - BIAS;
			end

			prependedMantissaOne = (operandOneFormatted.exponent == '0) ? {1'b0, operandOneFormatted.mantissa} : {1'b1, operandOneFormatted.mantissa};
                        prependedMantissaTwo = (operandTwoFormatted.exponent == '0) ? {1'b0, operandTwoFormatted.mantissa} : {1'b1, operandTwoFormatted.mantissa};

			prependedMantissaProduct = normalizedSignificandOne * normalizedSignificandTwo;

			normalizedMantissaProduct = prependedMantissaProduct[MANTISSA_PRODUCT_WIDTH-1] ? prependedMantissaProduct >> 1 : prependedMantissaProduct;
			denormalizedMantissaProduct = prependedMantissaProduct >> (1 - exponent);

		end
	end

	always_comb begin
        	leadingZeroOne = EXTENDED_WIDTH'(MANTISSA_WIDTH + 1);
        	leadingZeroTwo = EXTENDED_WIDTH'(MANTISSA_WIDTH + 1);
        	for (int i = 0; i <= MANTISSA_WIDTH; i++) begin
			if (prependedMantissaOne[i]) begin
		       		leadingZeroOne = EXTENDED_WIDTH'(MANTISSA_WIDTH - i);
			end

			if (prependedMantissaTwo[i]) begin
				leadingZeroTwo = EXTENDED_WIDTH'(MANTISSA_WIDTH - i);
			end
        	end
	end

	always_comb begin
	        int dropShift;
        	if (exponent <= 0) begin
        		dropShift = 1 - exponent;
		end else begin
        		dropShift = prependedMantissaProduct[MANTISSA_PRODUCT_WIDTH-1];
		end

		nextFlags = '0;

		nextFlags.invalid = isNaNOneSignaling || isNaNTwoSignaling || (isInfinityOne && isZeroTwo) || (isInfinityTwo && isZeroOne);

		nextFlags.overflow = !isSpecial && ((prependedMantissaProduct[MANTISSA_PRODUCT_WIDTH-1] && exponent >= 10'sd254) || (!prependedMantissaProduct[MANTISSA_PRODUCT_WIDTH-1] && exponent > 10'sd254));
		
		nextFlags.inexact  = !isSpecial && (nextFlags.overflow || (((prependedMantissaProduct >> (dropShift + MANTISSA_WIDTH)) << (dropShift + MANTISSA_WIDTH)) != prependedMantissaProduct));

		nextFlags.underflow = !isSpecial && !nextFlags.overflow && ((prependedMantissaProduct[MANTISSA_PRODUCT_WIDTH-1] && exponent <= -1) || 
			              (!prependedMantissaProduct[MANTISSA_PRODUCT_WIDTH-1] && exponent <= 0)) && nextFlags.inexact;
	end

	always_comb begin 
		isSpecial = 0;
		specialResult = 0;

		if (operandOneFormatted.exponent == 8'hFF || operandTwoFormatted.exponent == 8'hFF) begin 
			isSpecial = 1;
		end

		if(isNaNOne || isNaNTwo || (isInfinityOne && isZeroTwo) || (isInfinityTwo && isZeroOne)) begin 
			specialResult = 32'h7FC0_0000;
		end else begin 
			specialResult = {operandOneFormatted.sign ^ operandTwoFormatted.sign, 8'hFF, 23'b0};
		end
	end

	assign result = isSpecialLatch ? specialResultLatch : {resultFormatted.sign, resultFormatted.exponent, resultFormatted.mantissa};
endmodule
