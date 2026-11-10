import alu_pkg::*;

module top(
	input clk,
	input rst_n,
	input enable,

	input logic [DATA_WIDTH-1:0] operandOne,
	input logic [DATA_WIDTH-1:0] operandTwo,
	input alu_operations_e operation,

	output logic [DATA_WIDTH-1:0] result,
	output exception_flag_t flags
);
	logic [DATA_WIDTH-1:0] operandOneSync;
	logic [DATA_WIDTH-1:0] operandTwoSync;
	alu_operations_e operationSync1;
	logic enableSync1;
	
	logic [DATA_WIDTH-1:0] adderResult;
	logic [DATA_WIDTH-1:0] multiplierResult;

	exception_flag_t adderFlags;
	exception_flag_t multiplierFlags;

	logic [DATA_WIDTH-1:0] resultFlop;
	exception_flag_t flagFlop;

	alu_operations_e operationSync2;
	logic enableSync2;

	adder adderInst(.clk(clk), .rst_n(rst_n), .enable(enableSync1), .operandOne(operandOneSync), .operandTwo(operandTwoSync), .operation(operationSync1), .result(adderResult), .flags(adderFlags));

	multiplier multiplierInst(.clk(clk), .rst_n(rst_n), .enable(enableSync1), .operandOne(operandOneSync), .operandTwo(operandTwoSync), .operation(operationSync1), .result(multiplierResult), .flags(multiplierFlags));
	
	always_ff @(posedge clk or negedge rst_n) begin 
		if (!rst_n) begin 
			operationSync2 <= ADD;
			enableSync2 <= 1'b0;
		end else begin 
			operationSync2 <= operationSync1;
			enableSync2 <= enableSync1;
		end
	end

	always_ff @(posedge clk or negedge rst_n) begin 
		if (!rst_n) begin 
			operandOneSync <= '0;
			operandTwoSync <= '0;
			operationSync1 <= ADD;
			enableSync1 <= 1'b0;
		end else begin 
			operandOneSync <= operandOne;
			operandTwoSync <= operandTwo;
			operationSync1 <= operation;
			enableSync1 <= enable;
		end
	end

	always_ff @(posedge clk or negedge rst_n) begin
		if (!rst_n) begin
			resultFlop <= '0;
			flagFlop <= '0;
		end else if (enableSync2) begin 
			case(operationSync2) 
				ADD, SUB : begin
				       	resultFlop <= adderResult;
			       	       	flagFlop <= adderFlags;	       
				end
				MUL : begin 
					resultFlop <= multiplierResult;
					flagFlop <= multiplierFlags;
				end
			endcase
		end
	end

	assign result = resultFlop;
	assign flags = flagFlop;
endmodule
