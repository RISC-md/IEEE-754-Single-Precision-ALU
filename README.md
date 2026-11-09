# IEEE-754-Single-Precision-ALU

Based off of the IEEE 754 standard, this ALU currently supports addition, subtraction, and multiplication of 32-bit signed floats!

## Design

I chose to go with a single cycle approach where each part of the result, sign, exponent, and mantissa, were computed in parallel as this is a stand alone ALU and not a part of a bigger system such as a CPU.

### Tradeoff

A tradeoff with using the single cycle design is that some most computation occurs combinationally which could possibly lead to a long critical path which could furthermore lead to closing timing at lower than ideal clock frequencies. This overall would slow down computation by however many magnitudes a pipelined IEEE 754 ALU's clock frequency would be proportional to the current single cycle design's closing time.

### Resource Utilization

Will get numbers later today.

### Timing

Will get number later today.

## Verification

I used the C++ library Verilator to unit test each module using around 100 million random tests as well as having directed cases for NaN, infinity, 0, and maximum values as these values, even with 100 million randomly generated cases, may not occur so I added them to ensure full coverage.

All tests

## Implementation

I will be implementing my desing on an Arty S7-25 later today.

## Repository Structure

IEEE-754-Single-Precision-ALU/
├── .gitignore
├── rtl/
│   ├── alu\_pkg.sv             # Shared parameters, ALU operation enum, operand struct, exception flags struct
│   ├── adder.sv                # Adder/subtractor logic
│   └── multiplier.sv           # Multiplier logic
└── tests/
    ├── cpp/
    │   ├── tb\_adder.cpp        # Directed and 100M random tested against C++ -O0 and no -ffast-math float reference
    │   └── tb\_multiplier.cpp   # Directed and 100M random tested against C++ -O0 and no -ffast-math float reference
    ├── adderTests/
    │   └── build.sh            # Build script to run Verilator testbench on adder.sv
    └── multiplierTests/
        └── build.sh            # Build script to run Verilator testbench on multiplier.sv
