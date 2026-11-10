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
	logic [DATA_WIDTH-1:0] adderResult;
	logic [DATA_WIDTH-1:0] multiplierResult;
	//logic [DATA_WIDTH-1:0] dividerResult;

	exception_flag_t adderFlags;
	exception_flag_t multiplierFlags;
	//exception_flag_t dividerFlags;

	//logic adderDone;
	//logic multiplierDone;
	//logic dividerDone;

	logic [DATA_WIDTH-1:0] resultFlop;
	exception_flag_t flagFlop;
	//logic doneFlop;

	//logic ready;
	//logic processing;

	adderInst adder(.clk(clk), .rst_n(rst_n), .enable(enable), .operandOne(operandOne), .operandTwo(operandTwo), .operation(operation), .result(adderResult), .flags(adderFlags));

	multiplierInst multiplier(.clk(clk), .rst_n(rst_n), .enable(enable), .operandOne(operandOne), .operandTwo(operandTwo), .operation(operation), .result(multiplierResult), .flags(multiplierFlags));

	// dividerInst divider(.clk(clk), .rst_n(rst_n), .enable(enable), .operandOne(operandOne), .operandTwo(operandTwo), .operation(operation), .result(dividerResult), .flags(dividerFlags), .done(dividerDone));
	always_ff @(posedge clk or negedge rst_n) begin
		if (!rst_n) begin
			resultFlop <= '0;
			flagFlop <= '0;
		end else if (enable) begin 
			case(operation) 
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
