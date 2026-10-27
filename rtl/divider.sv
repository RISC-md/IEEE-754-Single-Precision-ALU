import alu_pkg::*;

module divider( // Module performs division on two single-precision floats
        input logic clk,
        input logic rst_n,
        input logic enable,

        input logic [DATA_WIDTH-1:0] operandOne,
        input logic [DATA_WIDTH-1:0] operandTwo,
        input alu_operations_e operation,

        output logic [DATA_WIDTH-1:0] result,
        output exception_flag_t flags;
);

        operand_format_t operandOneFormatted;
        operand_format_t operandTwoFormatted;
        operand_format_t resultFormatted;

        always_ff @(posedge clk or negedge rst_n) begin // Block for determing sign of result
                if (!rst_n) begin
                        resultFormatted.sign <= 0;
                end else if (enable) begin
                        resultFormatted.sign <= operandOneFormatted.sign ^ operandTwoFormatted.sign;
                end
        end

        always_comb begin // Block for formatting data
                operandOneFormatted = '0;
                operandTwoFormatted = '0;
                if (enable) begin
                        operandOneFormatted.sign = operandOne[DATA_WIDTH - 1];
                        operandTwoFormatted.sign = operandTwo[DATA_WIDTH - 1];

                        operandOneFormatted.exponent = operandOne[DATA_WIDTH - 2 -: EXPONENT_WIDTH];
                        operandTwoFormatted.exponent = operandTwo[DATA_WIDTH - 2 -: EXPONENT_WIDTH];

                        operandOneFormatted.mantissa = operandOne[DATA_WIDTH - 2 - EXPONENT_WIDTH -: MANTISSA_WIDTH];
                        operandTwoFormatted.mantissa = operandTwo[DATA_WIDTH - 2 - EXPONENT_WIDTH -: MANTISSA_WIDTH];
                end
        end

        assign result {resultFormatted.sign, resultFormatted.exponent, resultFormatted.mantissa};
endmodule
