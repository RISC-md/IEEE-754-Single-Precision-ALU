// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadder.h for the primary calling header

#include "Vadder__pch.h"
#include "Vadder___024root.h"

VL_ATTR_COLD void Vadder___024root___eval_static(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_static\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vadder___024root___eval_initial(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_initial\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

VL_ATTR_COLD void Vadder___024root___eval_final(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_final\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder___024root___dump_triggers__stl(Vadder___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vadder___024root___eval_phase__stl(Vadder___024root* vlSelf);

VL_ATTR_COLD void Vadder___024root___eval_settle(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_settle\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vadder___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("../../rtl/adder.sv", 3, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vadder___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder___024root___dump_triggers__stl(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___dump_triggers__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vadder___024root___stl_sequent__TOP__0(Vadder___024root* vlSelf);
VL_ATTR_COLD void Vadder___024root____Vm_traceActivitySetAll(Vadder___024root* vlSelf);

VL_ATTR_COLD void Vadder___024root___eval_stl(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vadder___024root___stl_sequent__TOP__0(vlSelf);
        Vadder___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD void Vadder___024root___stl_sequent__TOP__0(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___stl_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.result = vlSelfRef.adder__DOT__resultFormatted;
    vlSelfRef.adder__DOT__magDiffer = ((0x7fffffffU 
                                        & vlSelfRef.operandOne) 
                                       > (0x7fffffffU 
                                          & vlSelfRef.operandTwo));
    vlSelfRef.adder__DOT__operandOneFormatted = 0U;
    vlSelfRef.adder__DOT__operandTwoFormatted = 0U;
    vlSelfRef.adder__DOT__prependedMantissaOne = 0U;
    vlSelfRef.adder__DOT__prependedMantissaTwo = 0U;
    vlSelfRef.adder__DOT__effectiveOperation = 0U;
    if (vlSelfRef.enable) {
        vlSelfRef.adder__DOT__operandOneFormatted = 
            ((0x7fffffffU & vlSelfRef.adder__DOT__operandOneFormatted) 
             | (0x80000000U & vlSelfRef.operandOne));
        vlSelfRef.adder__DOT__operandTwoFormatted = 
            ((0x7fffffffU & vlSelfRef.adder__DOT__operandTwoFormatted) 
             | (0x80000000U & vlSelfRef.operandTwo));
        vlSelfRef.adder__DOT__operandOneFormatted = 
            ((0x807fffffU & vlSelfRef.adder__DOT__operandOneFormatted) 
             | (0x7f800000U & vlSelfRef.operandOne));
        vlSelfRef.adder__DOT__operandTwoFormatted = 
            ((0x807fffffU & vlSelfRef.adder__DOT__operandTwoFormatted) 
             | (0x7f800000U & vlSelfRef.operandTwo));
        vlSelfRef.adder__DOT__operandOneFormatted = 
            ((0xff800000U & vlSelfRef.adder__DOT__operandOneFormatted) 
             | (0x7fffffU & vlSelfRef.operandOne));
        vlSelfRef.adder__DOT__operandTwoFormatted = 
            ((0xff800000U & vlSelfRef.adder__DOT__operandTwoFormatted) 
             | (0x7fffffU & vlSelfRef.operandTwo));
        vlSelfRef.adder__DOT__prependedMantissaOne 
            = ((0U == (0xffU & (vlSelfRef.adder__DOT__operandOneFormatted 
                                >> 0x17U))) ? (0x7fffffU 
                                               & vlSelfRef.adder__DOT__operandOneFormatted)
                : (0x800000U | (0x7fffffU & vlSelfRef.adder__DOT__operandOneFormatted)));
        vlSelfRef.adder__DOT__prependedMantissaTwo 
            = ((0U == (0xffU & (vlSelfRef.adder__DOT__operandTwoFormatted 
                                >> 0x17U))) ? (0x7fffffU 
                                               & vlSelfRef.adder__DOT__operandTwoFormatted)
                : (0x800000U | (0x7fffffU & vlSelfRef.adder__DOT__operandTwoFormatted)));
        vlSelfRef.adder__DOT__effectiveOperation = 
            ((1U & (((vlSelfRef.adder__DOT__operandOneFormatted 
                      ^ vlSelfRef.adder__DOT__operandTwoFormatted) 
                     >> 0x1fU) ^ (1U == (IData)(vlSelfRef.operation))))
              ? 1U : 0U);
    }
    vlSelfRef.adder__DOT__biggerMantissa = ((IData)(vlSelfRef.adder__DOT__magDiffer)
                                             ? vlSelfRef.adder__DOT__prependedMantissaOne
                                             : vlSelfRef.adder__DOT__prependedMantissaTwo);
    vlSelfRef.adder__DOT__effectiveExponentOne = ((0U 
                                                   == 
                                                   (0xffU 
                                                    & (vlSelfRef.adder__DOT__operandOneFormatted 
                                                       >> 0x17U)))
                                                   ? 1U
                                                   : 
                                                  (0xffU 
                                                   & (vlSelfRef.adder__DOT__operandOneFormatted 
                                                      >> 0x17U)));
    vlSelfRef.adder__DOT__effectiveExponentTwo = ((0U 
                                                   == 
                                                   (0xffU 
                                                    & (vlSelfRef.adder__DOT__operandTwoFormatted 
                                                       >> 0x17U)))
                                                   ? 1U
                                                   : 
                                                  (0xffU 
                                                   & (vlSelfRef.adder__DOT__operandTwoFormatted 
                                                      >> 0x17U)));
    vlSelfRef.adder__DOT____VdfgRegularize_h23828683_0_4 
        = ((IData)(vlSelfRef.adder__DOT__effectiveExponentOne) 
           >= (IData)(vlSelfRef.adder__DOT__effectiveExponentTwo));
    vlSelfRef.adder__DOT__base = ((IData)(vlSelfRef.adder__DOT____VdfgRegularize_h23828683_0_4)
                                   ? (IData)(vlSelfRef.adder__DOT__effectiveExponentOne)
                                   : (IData)(vlSelfRef.adder__DOT__effectiveExponentTwo));
    vlSelfRef.adder__DOT__smallerMantissa = (0xffffffU 
                                             & VL_SHIFTR_III(24,24,8, 
                                                             ((IData)(vlSelfRef.adder__DOT__magDiffer)
                                                               ? vlSelfRef.adder__DOT__prependedMantissaTwo
                                                               : vlSelfRef.adder__DOT__prependedMantissaOne), 
                                                             (0xffU 
                                                              & ((IData)(vlSelfRef.adder__DOT____VdfgRegularize_h23828683_0_4)
                                                                  ? 
                                                                 ((IData)(vlSelfRef.adder__DOT__effectiveExponentOne) 
                                                                  - (IData)(vlSelfRef.adder__DOT__effectiveExponentTwo))
                                                                  : 
                                                                 ((IData)(vlSelfRef.adder__DOT__effectiveExponentTwo) 
                                                                  - (IData)(vlSelfRef.adder__DOT__effectiveExponentOne))))));
    vlSelfRef.adder__DOT__mantissaSum = (0x1ffffffU 
                                         & (vlSelfRef.adder__DOT__biggerMantissa 
                                            + vlSelfRef.adder__DOT__smallerMantissa));
    vlSelfRef.adder__DOT__mantissaDiff = (0xffffffU 
                                          & (vlSelfRef.adder__DOT__biggerMantissa 
                                             - vlSelfRef.adder__DOT__smallerMantissa));
    vlSelfRef.adder__DOT__leadingZero = 0x18U;
    if ((1U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0x17U;
    }
    if ((2U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0x16U;
    }
    if ((4U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0x15U;
    }
    if ((8U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0x14U;
    }
    if ((0x10U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0x13U;
    }
    if ((0x20U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0x12U;
    }
    if ((0x40U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0x11U;
    }
    if ((0x80U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0x10U;
    }
    if ((0x100U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0xfU;
    }
    if ((0x200U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0xeU;
    }
    if ((0x400U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0xdU;
    }
    if ((0x800U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0xcU;
    }
    if ((0x1000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0xbU;
    }
    if ((0x2000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0xaU;
    }
    if ((0x4000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 9U;
    }
    if ((0x8000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 8U;
    }
    if ((0x10000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 7U;
    }
    if ((0x20000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 6U;
    }
    if ((0x40000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 5U;
    }
    if ((0x80000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 4U;
    }
    if ((0x100000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 3U;
    }
    if ((0x200000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 2U;
    }
    if ((0x400000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 1U;
    }
    if ((0x800000U & vlSelfRef.adder__DOT__mantissaDiff)) {
        vlSelfRef.adder__DOT__leadingZero = 0U;
    }
}

VL_ATTR_COLD void Vadder___024root___eval_triggers__stl(Vadder___024root* vlSelf);

VL_ATTR_COLD bool Vadder___024root___eval_phase__stl(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_phase__stl\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vadder___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vadder___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder___024root___dump_triggers__ico(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___dump_triggers__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder___024root___dump_triggers__act(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___dump_triggers__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder___024root___dump_triggers__nba(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___dump_triggers__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vadder___024root____Vm_traceActivitySetAll(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root____Vm_traceActivitySetAll\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void Vadder___024root___ctor_var_reset(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___ctor_var_reset\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst_n = VL_RAND_RESET_I(1);
    vlSelf->enable = VL_RAND_RESET_I(1);
    vlSelf->operandOne = VL_RAND_RESET_I(32);
    vlSelf->operandTwo = VL_RAND_RESET_I(32);
    vlSelf->operation = VL_RAND_RESET_I(3);
    vlSelf->result = VL_RAND_RESET_I(32);
    vlSelf->adder__DOT__operandOneFormatted = VL_RAND_RESET_I(32);
    vlSelf->adder__DOT__operandTwoFormatted = VL_RAND_RESET_I(32);
    vlSelf->adder__DOT__resultFormatted = VL_RAND_RESET_I(32);
    vlSelf->adder__DOT__base = VL_RAND_RESET_I(8);
    vlSelf->adder__DOT__prependedMantissaOne = VL_RAND_RESET_I(24);
    vlSelf->adder__DOT__prependedMantissaTwo = VL_RAND_RESET_I(24);
    vlSelf->adder__DOT__leadingZero = VL_RAND_RESET_I(6);
    vlSelf->adder__DOT__effectiveOperation = VL_RAND_RESET_I(3);
    vlSelf->adder__DOT__magDiffer = VL_RAND_RESET_I(1);
    vlSelf->adder__DOT__mantissaSum = VL_RAND_RESET_I(25);
    vlSelf->adder__DOT__mantissaDiff = VL_RAND_RESET_I(24);
    vlSelf->adder__DOT__biggerMantissa = VL_RAND_RESET_I(24);
    vlSelf->adder__DOT__smallerMantissa = VL_RAND_RESET_I(24);
    vlSelf->adder__DOT__effectiveExponentOne = VL_RAND_RESET_I(8);
    vlSelf->adder__DOT__effectiveExponentTwo = VL_RAND_RESET_I(8);
    vlSelf->adder__DOT____VdfgRegularize_h23828683_0_4 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
