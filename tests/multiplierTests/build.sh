#!/usr/bin/env bash
# Build and run the adder testbench with Verilator.
#
# Usage (from anywhere):
#   ./build.sh          build, then run the tests
#   ./build.sh build    build only
#   ./build.sh clean    delete build output and waveforms
#
# Exits nonzero if the build fails or any test mismatches.
 
set -euo pipefail
 
# Always work from this script's directory (tests/adderTests)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"
 
RTL_DIR="$SCRIPT_DIR/../../rtl"
TB="$SCRIPT_DIR/../cpp/tb_multiplier.cpp"
 
MODE="${1:-run}"
 
case "$MODE" in
    clean)
        rm -rf obj_dir multiplier.vcd
        echo "Cleaned obj_dir and multiplier.vcd"
        exit 0
        ;;
    build|run)
        ;;
    *)
        echo "Usage: $0 [run|build|clean]"
        exit 1
        ;;
esac
 
verilator --cc --exe --build -j 0 -Wall -Wno-fatal --trace \
    --top-module multiplier \
    -CFLAGS "-frounding-math" \
    -MAKEFLAGS "OPT_FAST=-O0 OPT_SLOW=-O0 OPT_GLOBAL=-O0" \
    "$RTL_DIR/alu_pkg.sv" "$RTL_DIR/multiplier.sv" "$TB"
 
if [ "$MODE" = "run" ]; then
    ./obj_dir/Vmultiplier
fi
