// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadder.h for the primary calling header

#include "Vadder__pch.h"
#include "Vadder___024root.h"

void Vadder___024root___ico_sequent__TOP__0(Vadder___024root* vlSelf);

void Vadder___024root___eval_ico(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vadder___024root___ico_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

VL_INLINE_OPT void Vadder___024root___ico_sequent__TOP__0(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___ico_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
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

void Vadder___024root___eval_triggers__ico(Vadder___024root* vlSelf);

bool Vadder___024root___eval_phase__ico(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_phase__ico\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vadder___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vadder___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vadder___024root___eval_act(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vadder___024root___nba_sequent__TOP__0(Vadder___024root* vlSelf);

void Vadder___024root___eval_nba(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vadder___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vadder___024root___nba_sequent__TOP__0(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___nba_sequent__TOP__0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.enable) {
            vlSelfRef.adder__DOT__resultFormatted = 
                ((0x807fffffU & vlSelfRef.adder__DOT__resultFormatted) 
                 | (0x7f800000U & (((0U == (IData)(vlSelfRef.adder__DOT__effectiveOperation))
                                     ? ((0x1000000U 
                                         & vlSelfRef.adder__DOT__mantissaSum)
                                         ? ((0xfeU 
                                             == (IData)(vlSelfRef.adder__DOT__base))
                                             ? 0xffU
                                             : ((IData)(1U) 
                                                + (IData)(vlSelfRef.adder__DOT__base)))
                                         : ((0x800000U 
                                             & vlSelfRef.adder__DOT__mantissaSum)
                                             ? (IData)(vlSelfRef.adder__DOT__base)
                                             : 0U))
                                     : (((0U == vlSelfRef.adder__DOT__mantissaDiff) 
                                         | ((IData)(vlSelfRef.adder__DOT__leadingZero) 
                                            >= (IData)(vlSelfRef.adder__DOT__base)))
                                         ? 0U : ((IData)(vlSelfRef.adder__DOT__base) 
                                                 - (IData)(vlSelfRef.adder__DOT__leadingZero)))) 
                                   << 0x17U)));
            vlSelfRef.adder__DOT__resultFormatted = 
                ((0xff800000U & vlSelfRef.adder__DOT__resultFormatted) 
                 | (0x7fffffU & ((0U == (IData)(vlSelfRef.adder__DOT__effectiveOperation))
                                  ? ((0x1000000U & vlSelfRef.adder__DOT__mantissaSum)
                                      ? ((0xfeU == (IData)(vlSelfRef.adder__DOT__base))
                                          ? 0U : (vlSelfRef.adder__DOT__mantissaSum 
                                                  >> 1U))
                                      : vlSelfRef.adder__DOT__mantissaSum)
                                  : ((0U == vlSelfRef.adder__DOT__mantissaDiff)
                                      ? 0U : (((IData)(vlSelfRef.adder__DOT__leadingZero) 
                                               >= (IData)(vlSelfRef.adder__DOT__base))
                                               ? (0xffffffU 
                                                  & VL_SHIFTL_III(24,24,8, vlSelfRef.adder__DOT__mantissaDiff, 
                                                                  (0xffU 
                                                                   & ((IData)(vlSelfRef.adder__DOT__base) 
                                                                      - (IData)(1U)))))
                                               : (0xffffffU 
                                                  & VL_SHIFTL_III(24,24,6, vlSelfRef.adder__DOT__mantissaDiff, (IData)(vlSelfRef.adder__DOT__leadingZero))))))));
            vlSelfRef.adder__DOT__resultFormatted = 
                ((0x7fffffffU & vlSelfRef.adder__DOT__resultFormatted) 
                 | (((0U == (IData)(vlSelfRef.adder__DOT__effectiveOperation))
                      ? (vlSelfRef.adder__DOT__operandOneFormatted 
                         >> 0x1fU) : (((0x7fffffffU 
                                        & vlSelfRef.operandOne) 
                                       != (0x7fffffffU 
                                           & vlSelfRef.operandTwo)) 
                                      && (1U & ((IData)(vlSelfRef.adder__DOT__magDiffer)
                                                 ? 
                                                (vlSelfRef.adder__DOT__operandOneFormatted 
                                                 >> 0x1fU)
                                                 : 
                                                (~ 
                                                 (vlSelfRef.adder__DOT__operandOneFormatted 
                                                  >> 0x1fU)))))) 
                    << 0x1fU));
        }
    } else {
        vlSelfRef.adder__DOT__resultFormatted = (0x807fffffU 
                                                 & vlSelfRef.adder__DOT__resultFormatted);
        vlSelfRef.adder__DOT__resultFormatted = (0xff800000U 
                                                 & vlSelfRef.adder__DOT__resultFormatted);
        vlSelfRef.adder__DOT__resultFormatted = (0x7fffffffU 
                                                 & vlSelfRef.adder__DOT__resultFormatted);
    }
    vlSelfRef.result = vlSelfRef.adder__DOT__resultFormatted;
}

void Vadder___024root___eval_triggers__act(Vadder___024root* vlSelf);

bool Vadder___024root___eval_phase__act(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_phase__act\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vadder___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vadder___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vadder___024root___eval_phase__nba(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_phase__nba\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vadder___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder___024root___dump_triggers__ico(Vadder___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder___024root___dump_triggers__nba(Vadder___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder___024root___dump_triggers__act(Vadder___024root* vlSelf);
#endif  // VL_DEBUG

void Vadder___024root___eval(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vadder___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("../../rtl/adder.sv", 3, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vadder___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vadder___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("../../rtl/adder.sv", 3, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vadder___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("../../rtl/adder.sv", 3, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vadder___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vadder___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vadder___024root___eval_debug_assertions(Vadder___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_debug_assertions\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelfRef.rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((vlSelfRef.enable & 0xfeU))) {
        Verilated::overWidthError("enable");}
    if (VL_UNLIKELY((vlSelfRef.operation & 0xf8U))) {
        Verilated::overWidthError("operation");}
}
#endif  // VL_DEBUG
