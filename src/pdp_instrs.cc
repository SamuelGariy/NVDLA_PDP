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

namespace ilang
{

    // Define PDP instructions relevant to configuration registers
    void DefinePDPInstrs(Ila &m)
    {
        // m.AddInit(m.state(NVDLA_CSC_S_STATUS_0) == BvConst(0, 2));
        // m.AddInit(m.state(NVDLA_CSC_S_STATUS_1) == BvConst(0, 2));

        auto csb_addr = Extract(Concat(m.input("csb_addr"), BvConst(0, 2)), 11, 0);
        auto csb_valid = (m.state("csb_rdy") == BvConst(1, 1)) & (m.input("csb_vld") == BvConst(1, 1));
        auto csb_write = m.input("csb_write") == BvConst(1, 1);
        auto group0_unset = m.state(GetVarName("group0_", NVDLA_PDP_D_OP_ENABLE)) == BvConst(0, 1);
        auto group1_unset = m.state(GetVarName("group1_", NVDLA_PDP_D_OP_ENABLE)) == BvConst(0, 1);
        auto producer = m.state(NVDLA_PDP_S_PRODUCER);
        auto consumer = m.state(NVDLA_PDP_S_CONSUMER);
        auto pdp_state = m.state("pdp_state");
        auto stride = m.state("pdp_stride");
       // auto inputarr[NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT][NVDLA_PDP_D_DATA_CUBE_IN_WIDTH];
        //auto outputarr[NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT][NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT] auto counter = BvConst(0, 5);
        // auto input = m.input("pdp_input")

        // Initialize both the PRODUCER and CONSUMER states to be 0
        m.AddInit(m.state(NVDLA_PDP_S_PRODUCER) == BvConst(0, 1));
        m.AddInit(m.state(NVDLA_PDP_S_CONSUMER) == BvConst(0, 1));
        // Status: 3
        // 1: Config/Start
        // 2: Load data
        // 3: Calculate max pool
        // 4: Store output

        // CSB set producer
        { // 0004
            auto instr = m.NewInstr("Set_Producer");
            instr.SetDecode(csb_addr == 0x004 & csb_valid & csb_write);

            instr.SetUpdate(producer, Extract(m.input("csb_data"), 0, 0));
        }

        // Set Start Group

        { // PDP Set Start Group 0 (addr:008)
            auto instr = m.NewInstr("set_start_group0");
            instr.SetDecode(csb_addr == 0x008 & csb_valid & csb_write & producer == BvConst(0, 1) & group0_unset);
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_OP_ENABLE)), Extract(m.input("csb_data"), 0, 0));
            instr.SetUpdate(pdp_state, LOAD);
        }

        { // PDP Set Start Group 1 (addr:008)
            auto instr = m.NewInstr("set_start_group1");
            instr.SetDecode(csb_addr == 0x008 & csb_valid & csb_write & producer == BvConst(1, 1) & group1_unset);
            instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_PDP_D_OP_ENABLE)), Extract(m.input("csb_data"), 0, 0));
            instr.SetUpdate(pdp_state, LOAD);
        }

        // PDP operations
        //  Load input data
        {
            auto instr = m.NewInstr("load_input");
            instr.SetDecode(pdp_state == LOAD);

            // set input height and width
            instr.SetUpdate(m.state(NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT), BvConst(4, NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH));
                instr.SetUpdate(m.state(NVDLA_PDP_D_DATA_CUBE_IN_WIDTH), BvConst(4, NVDLA_PDP_D_DATA_CUBE_IN_WIDTH_WIDTH));

                //  set kernel height and width
                instr.SetUpdate(m.state(NVDLA_PDP_D_RECIP_KERNEL_HEIGHT), BvConst(2, NVDLA_PDP_D_RECIP_KERNEL_HEIGHT_WIDTH));
                    instr.SetUpdate(m.state(NVDLA_PDP_D_RECIP_KERNEL_WIDTH), BvConst(2, NVDLA_PDP_D_RECIP_KERNEL_WIDTH_WIDTH));
                // set stride
                //instr.SetUpdate(pdp_stride, BvConst(2, 2));
                //pdp_stride = BvConst(2,2);

                // set output
                instr.SetUpdate(m.state(NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT), BvConst(2, NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT_WIDTH));
                    instr.SetUpdate(m.state(NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH), BvConst(2, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH));

            //             for (auto i = 0; i < NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT; i++)
            // {
            //     // for (auto j = 0; j < NVDLA_PDP_D_DATA_CUBE_IN_WIDTH; j++)
            //     // {
            //     //     instr.SetUpdate(inputarr[i][j], Extract(m.input("pdp_input" + (std::to_string(counter))), 31, 0));
            //     //     //   instr.SetUpdate(m.state("pdp_input" + (std::to_string(counter))), );
            //     //     counter = counter + BvConst(1, 5)
            //     // }
            // }
        }

        instr.SetUpdate(pdp_state, MAXPOOL);
    }

    { // PDP Set Start Group 0 (addr:008)
        auto instr = m.NewInstr("max_pool");
        instr.SetDecode(pdp_state == MAXPOOL);

        auto mem_ptr = MemConst(0, {}, 4, 32).get();
        for (auto output_i = 0; output_i < NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT; output_i++)
        {
            for (int output_j = 0; output_j < outputHeight_Width; output_j++)
            {
                for (int kernel_i = 0; kernel_i < 2; kernel_i++)
                {
                    for (int kernel_j = 0; kernel_j < 2; kernel_j++)
                    {
                        // load from memory and read
                        auto i = output_j * 2 + kernel_i;
                        auto j = output_i * 2 + kernel_j;
                        auto curr = m.input("pdp_input", (std::to_string(i)) + "_" + (std::to_string(j)));
                        auto mem_addr = i + j;
                        auto max = Load(ExprRef(mem_ptr), BvConst(mem_addr, 4));

                        instr.SetUpdate(max, Ite(curr > max, curr, max));
                        // outputarr[output_i][output_j]

                        auto new_mem = ExprRef(mem_ptr).Store(BvConst(mem_addr, 4), max);
                        mem_ptr = new_mem.get();
                    }
                }

                // instr.SetUpdate(inputarr[i][j],Extract(m.input("pdp_input"+ (std::to_string(counter))), 31, 0 ));
                // instr.SetUpdate(m.state("pdp_input"+ (std::to_string(counter))), );
                // counter = counter + BvConst(1,5)
            }
        }
        instr.SetUpdate(pdp_state, STORE);
    }

    { // PDP Set Start Group 0 (addr:008)
        auto instr = m.NewInstr("store");
        instr.SetDecode(pdp_state == STORE);

    //     auto counter = 0 for (auto i = 0; i < NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT; i++)
    //     {
    //         for (auto j = 0; j < NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH; j++)
    //         {
    //             auto curr = BvConst(outputarr[i][j], 32)
    //                             instr.SetUpdate(m.state("pdp_output" + (std::to_string(counter))), curr);
    //             counter = counter + BvConst(1, 5)
    //         }
    //     }
    // }
    instr.SetUpdate(pdp_state, START);

} // namespace ilang