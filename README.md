# IEEE-754-Single-Precision-ALU

Based off of the IEEE 754 standard, this ALU currently supports addition, subtraction, and multiplication of 32-bit signed floats!

## Design
<img width="1226" height="584" alt="image" src="https://github.com/user-attachments/assets/34428239-e8dd-4f28-a23b-7e70ee68d367" />

I chose to go with a single cycle approach where each part of the result, sign, exponent, and mantissa, were computed in parallel as this is a stand alone ALU and not a part of a bigger system such as a CPU.

### Tradeoff

A tradeoff with using the single cycle design is that some most computation occurs combinationally which could possibly lead to a long critical path which could furthermore lead to closing timing at lower than ideal clock frequencies. This overall would slow down computation by however many magnitudes a pipelined IEEE 754 ALU's clock frequency would be proportional to the current single cycle design's closing time.

### Resource Utilization

| Resource        | Used | Available | Utilization |
|-----------------|-----:|----------:|------------:|
| Slice LUTs      | 1137 |    14,600 |       7.79% |
| Flip-Flops      |  187 |    29,200 |       0.64% |
| DSP48E1         |    2 |        80 |       2.50% |

### Timing/Power

| Timing / Power            | Result                         |
|---------------------------|--------------------------------|
| Clock                     | 47 MHz (single-cycle units)    |
| Worst negative slack      | +0.166 ns                      |
| Worst hold slack          | +0.200 ns                      |
| Total on-chip power       | 0.077 W                        |

Closed timing at 47.619 MHz. This is somewhat the speed I expected for a design that requires so much computation and wasn't pipelined to accommodate that fact.

## Verification

I used the C++ library Verilator to unit test each module using around 100 million random tests as well as having directed cases for NaN, infinity, 0, and maximum values as these values, even with 100 million randomly generated cases, may not occur so I added them to ensure full coverage.

All tests use floats with 0 optimization (-O0) and no -ffast-math, in order to, fully comply with the IEEE 754 specification and ensure literal correctness with no optimization.

## Implementation

This design was implemented on an Arty S7-25.

## Repository Structure
```text

IEEE-754-Single-Precision-ALU/
├── .gitignore
├── rtl/
│   ├── alu_pkg.sv              # Shared parameters, ALU operation enum, operand struct, exception flags struct
│   ├── adder.sv                # Adder/subtractor logic
│   └── multiplier.sv           # Multiplier logic
└── tests/
    ├── cpp/
    │   ├── tb_adder.cpp        # Directed and 100M random tested against C++ -O0 and no -ffast-math float reference
    │   └── tb_multiplier.cpp   # Directed and 100M random tested against C++ -O0 and no -ffast-math float reference
    ├── adderTests/
    │   └── build.sh            # Build script to run Verilator testbench on adder.sv
    └── multiplierTests/
        └── build.sh            # Build script to run Verilator testbench on adder.sv
```
