// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vadder.h for the primary calling header

#ifndef VERILATED_VADDER___024ROOT_H_
#define VERILATED_VADDER___024ROOT_H_  // guard

#include "verilated.h"


class Vadder__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vadder___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(enable,0,0);
    VL_IN8(operation,2,0);
    CData/*7:0*/ adder__DOT__base;
    CData/*5:0*/ adder__DOT__leadingZero;
    CData/*2:0*/ adder__DOT__effectiveOperation;
    CData/*0:0*/ adder__DOT__magDiffer;
    CData/*7:0*/ adder__DOT__effectiveExponentOne;
    CData/*7:0*/ adder__DOT__effectiveExponentTwo;
    CData/*0:0*/ adder__DOT____VdfgRegularize_h23828683_0_4;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
    CData/*0:0*/ __VactContinue;
    VL_IN(operandOne,31,0);
    VL_IN(operandTwo,31,0);
    VL_OUT(result,31,0);
    IData/*31:0*/ adder__DOT__operandOneFormatted;
    IData/*31:0*/ adder__DOT__operandTwoFormatted;
    IData/*31:0*/ adder__DOT__resultFormatted;
    IData/*23:0*/ adder__DOT__prependedMantissaOne;
    IData/*23:0*/ adder__DOT__prependedMantissaTwo;
    IData/*24:0*/ adder__DOT__mantissaSum;
    IData/*23:0*/ adder__DOT__mantissaDiff;
    IData/*23:0*/ adder__DOT__biggerMantissa;
    IData/*23:0*/ adder__DOT__smallerMantissa;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vadder__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vadder___024root(Vadder__Syms* symsp, const char* v__name);
    ~Vadder___024root();
    VL_UNCOPYABLE(Vadder___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
