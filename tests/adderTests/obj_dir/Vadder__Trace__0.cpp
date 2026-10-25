// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vadder__Syms.h"


void Vadder___024root__trace_chg_0_sub_0(Vadder___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vadder___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root__trace_chg_0\n"); );
    // Init
    Vadder___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vadder___024root*>(voidSelf);
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vadder___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vadder___024root__trace_chg_0_sub_0(Vadder___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root__trace_chg_0_sub_0\n"); );
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelfRef.__Vm_traceActivity[1U])) {
        bufp->chgIData(oldp+0,(vlSelfRef.adder__DOT__operandOneFormatted),32);
        bufp->chgIData(oldp+1,(vlSelfRef.adder__DOT__operandTwoFormatted),32);
        bufp->chgCData(oldp+2,((0xffU & ((IData)(vlSelfRef.adder__DOT____VdfgRegularize_h23828683_0_4)
                                          ? ((IData)(vlSelfRef.adder__DOT__effectiveExponentOne) 
                                             - (IData)(vlSelfRef.adder__DOT__effectiveExponentTwo))
                                          : ((IData)(vlSelfRef.adder__DOT__effectiveExponentTwo) 
                                             - (IData)(vlSelfRef.adder__DOT__effectiveExponentOne))))),8);
        bufp->chgCData(oldp+3,(vlSelfRef.adder__DOT__base),8);
        bufp->chgIData(oldp+4,(vlSelfRef.adder__DOT__prependedMantissaOne),24);
        bufp->chgIData(oldp+5,(vlSelfRef.adder__DOT__prependedMantissaTwo),24);
        bufp->chgCData(oldp+6,(vlSelfRef.adder__DOT__leadingZero),6);
        bufp->chgCData(oldp+7,(vlSelfRef.adder__DOT__effectiveOperation),3);
        bufp->chgBit(oldp+8,(vlSelfRef.adder__DOT__magDiffer));
        bufp->chgIData(oldp+9,(vlSelfRef.adder__DOT__mantissaSum),25);
        bufp->chgIData(oldp+10,(vlSelfRef.adder__DOT__mantissaDiff),24);
        bufp->chgIData(oldp+11,(vlSelfRef.adder__DOT__biggerMantissa),24);
        bufp->chgIData(oldp+12,(vlSelfRef.adder__DOT__smallerMantissa),24);
        bufp->chgIData(oldp+13,((0xffffffU & VL_SHIFTL_III(24,24,6, vlSelfRef.adder__DOT__mantissaDiff, (IData)(vlSelfRef.adder__DOT__leadingZero)))),24);
        bufp->chgIData(oldp+14,((0xffffffU & VL_SHIFTL_III(24,24,8, vlSelfRef.adder__DOT__mantissaDiff, 
                                                           (0xffU 
                                                            & ((IData)(vlSelfRef.adder__DOT__base) 
                                                               - (IData)(1U)))))),24);
        bufp->chgCData(oldp+15,(vlSelfRef.adder__DOT__effectiveExponentOne),8);
        bufp->chgCData(oldp+16,(vlSelfRef.adder__DOT__effectiveExponentTwo),8);
    }
    bufp->chgBit(oldp+17,(vlSelfRef.clk));
    bufp->chgBit(oldp+18,(vlSelfRef.rst_n));
    bufp->chgBit(oldp+19,(vlSelfRef.enable));
    bufp->chgIData(oldp+20,(vlSelfRef.operandOne),32);
    bufp->chgIData(oldp+21,(vlSelfRef.operandTwo),32);
    bufp->chgCData(oldp+22,(vlSelfRef.operation),3);
    bufp->chgIData(oldp+23,(vlSelfRef.result),32);
    bufp->chgIData(oldp+24,(vlSelfRef.adder__DOT__resultFormatted),32);
    bufp->chgBit(oldp+25,(((0x7fffffffU & vlSelfRef.operandOne) 
                           == (0x7fffffffU & vlSelfRef.operandTwo))));
}

void Vadder___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root__trace_cleanup\n"); );
    // Init
    Vadder___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vadder___024root*>(voidSelf);
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
