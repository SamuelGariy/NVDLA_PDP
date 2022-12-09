// =============================================================================
// MIT License
//
// Copyright (c) 2022 Princeton University
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// =============================================================================

// File: pdp_instrs.cc

#include <ilang/ilang++.h>

#include <pdp_config.h>

namespace ilang {


// Define PDP instructions relevant to configuration registers
void DefinePDPInstrs(Ila& m) {
    // m.AddInit(m.state(NVDLA_CSC_S_STATUS_0) == BvConst(0, 2));
    // m.AddInit(m.state(NVDLA_CSC_S_STATUS_1) == BvConst(0, 2));

    auto csb_addr = Extract(Concat(m.input("csb_addr"), BvConst(0,2)), 11, 0);
    auto csb_valid = (m.state("csb_rdy") == BvConst(1,1)) & (m.input("csb_vld") == BvConst(1,1));
    auto csb_write = m.input("csb_write") == BvConst(1,1);
    auto group0_unset = m.state(GetVarName("group0_", NVDLA_PDP_D_OP_ENABLE)) == BvConst(0,1);
    auto group1_unset = m.state(GetVarName("group1_", NVDLA_PDP_D_OP_ENABLE)) == BvConst(0,1);
    auto producer = m.state(NVDLA_PDP_S_PRODUCER);
    auto consumer = m.state(NVDLA_PDP_S_CONSUMER);
    auto pdp_state = m.state("pdp_state");


  // Initialize both the PRODUCER and CONSUMER states to be 0
    m.AddInit(m.state(NVDLA_SDP_S_PRODUCER) == BvConst(0, 1));
    m.AddInit(m.state(NVDLA_SDP_S_CONSUMER) == BvConst(0, 1));
    // Status: 3
    // 1: IDLE
    // 2: Producer (op_enable) and Consumer
    // 3: Producer (op_enable) but not consumer

    // CSB MMIO
    { // 0004
        auto instr = m.NewInstr("Set_Producer");
        instr.SetDecode(csb_addr == 0x004 & csb_valid & csb_write);

        instr.SetUpdate(producer, Extract(m.input("csb_data"), 0, 0));
    }


// assuming a 2by 2 pooling kernel and a 4 by 2^n input plane and stride of 2





// CSB MMIO
    // { // 000c
    //     auto instr = m.NewInstr("D_DATA_CUBE_IN_WIDTH_group_0");
    //     instr.SetDecode(csb_addr == 0x00c & csb_valid & csb_write);

    //     instr.SetUpdate(NVDLA_PDP_D_DATA, Extract(m.input("csb_data"), 12, 0));
    // }

    //  { // 000c
    //     auto instr = m.NewInstr("D_DATA_CUBE_IN_HEIGHT_group1");
    //     instr.SetDecode(csb_addr == 0x004 & csb_valid & csb_write);

    //     instr.SetUpdate(producer, Extract(m.input("csb_data"), 0, 0));
    // }
    //  { // 000c
    //     auto instr = m.NewInstr("Set_Output_Height");
    //     instr.SetDecode(csb_addr == 0x004 & csb_valid & csb_write);

    //     instr.SetUpdate(producer, Extract(m.input("csb_data"), 0, 0));
    // }

    //  { // 000c
    //     auto instr = m.NewInstr("Set_Output_Width");
    //     instr.SetDecode(csb_addr == 0x004 & csb_valid & csb_write);

    //     instr.SetUpdate(producer, Extract(m.input("csb_data"), 0, 0));
    // }








}


} // namespace ilang