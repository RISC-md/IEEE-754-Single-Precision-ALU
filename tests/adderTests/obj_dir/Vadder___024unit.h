// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vadder.h for the primary calling header

#ifndef VERILATED_VADDER___024UNIT_H_
#define VERILATED_VADDER___024UNIT_H_  // guard

#include "verilated.h"


class Vadder__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vadder___024unit final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vadder__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vadder___024unit(Vadder__Syms* symsp, const char* v__name);
    ~Vadder___024unit();
    VL_UNCOPYABLE(Vadder___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
