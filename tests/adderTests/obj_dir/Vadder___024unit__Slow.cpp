// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadder.h for the primary calling header

#include "Vadder__pch.h"
#include "Vadder__Syms.h"
#include "Vadder___024unit.h"

void Vadder___024unit___ctor_var_reset(Vadder___024unit* vlSelf);

Vadder___024unit::Vadder___024unit(Vadder__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vadder___024unit___ctor_var_reset(this);
}

void Vadder___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vadder___024unit::~Vadder___024unit() {
}
