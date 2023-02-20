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
    ExprRef int8_to_int16(ExprRef bv16, ExprRef data_type)
    {
        auto bv7_unsigned = bv16 & BvConst(0x7F, PDP_INT_16_WIDTH);

        // update weight based on datatype
        auto bv = Ite(data_type == INT16, bv16,
                      Ite(data_type == INT8, Ite(SelectBit(bv16, 7) == 0, bv7_unsigned, bv7_unsigned | BvConst(0xFF80, PDP_INT_16_WIDTH)),
                          BvConst(0, PDP_INT_16_WIDTH)));

        return bv;
    }

    // Define PDP instructions relevant to configuration registers
    void DefinePDPInstrs(Ila &m)
    {
        // m.AddInit(m.state(NVDLA_CSC_S_STATUS_0) == BvConst(0, 2));
        // m.AddInit(m.state(NVDLA_CSC_S_STATUS_1) == BvConst(0, 2));

        auto csb_addr = Extract(Concat(m.input("csb_addr"), BvConst(0, 2)), 11, 0);
        auto csb_valid = (m.state("csb_rdy") == BvConst(1, 1)) & (m.input("csb_vld") == BvConst(1, 1));
        auto csb_write = m.input("csb_write") == BvConst(1, 1);
        auto group0_unset = m.state(GetVarName("group0_", NVDLA_PDP_D_OP_ENABLE)) == BvConst(0, 1);
        // auto group1_unset = m.state(GetVarName("group1_", NVDLA_PDP_D_OP_ENABLE)) == BvConst(0, 1);
        auto producer = m.state(NVDLA_PDP_S_PRODUCER);
        auto consumer = m.state(NVDLA_PDP_S_CONSUMER);
        // auto padding = 0

        // Initialize both the PRODUCER and CONSUMER states to be 0
        m.AddInit(m.state(NVDLA_PDP_S_PRODUCER) == BvConst(0, 1));
        m.AddInit(m.state(NVDLA_PDP_S_CONSUMER) == BvConst(0, 1));

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

        // { // PDP Set Start Group 1 (addr:008)
        //     auto instr = m.NewInstr("set_start_group1");
        //     instr.SetDecode(csb_addr == 0x008 & csb_valid & csb_write & producer == BvConst(1, 1) & group1_unset);
        //     instr.SetUpdate(m.state(GetVarName("group1_", NVDLA_PDP_D_OP_ENABLE)), Extract(m.input("csb_data"), 0, 0));
        //     instr.SetUpdate(pdp_state, LOAD);
        // }

        {
            // PDP operations
            //  Load input data

            auto instr = m.NewInstr("load_input");
            instr.SetDecode(pdp_state == LOAD);

            // set input height and width
            // instr.SetUpdate(m.state(NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT), BvConst(4, NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH));
            //    instr.SetUpdate(m.state(NVDLA_PDP_D_DATA_CUBE_IN_WIDTH), BvConst(4, NVDLA_PDP_D_DATA_CUBE_IN_WIDTH_WIDTH));

            //  set kernel height and width
            instr.SetUpdate(m.state(NVDLA_PDP_D_POOLING_KERNEL_CFG_HEIGHT), m.input(NVDLA_PDP_D_POOLING_KERNEL_CFG_HEIGHT));
            instr.SetUpdate(m.state(NVDLA_PDP_D_POOLING_KERNEL_CFG_WIDTH), m.input(NVDLA_PDP_D_POOLING_KERNEL_CFG_WIDTH));

            // set stride
            instr.SetUpdate(m.state(NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_HEIGHT), m.input(NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_HEIGHT));
            instr.SetUpdate(m.state(NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_WIDTH), m.input(NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_WIDTH));

            // set padding size
            instr.SetUpdate(m.state(NVDLA_PDP_D_POOLING_PADDING_CFG_BOTTOM), m.input(NVDLA_PDP_D_POOLING_PADDING_CFG_BOTTOM));
            instr.SetUpdate(m.state(NVDLA_PDP_D_POOLING_PADDING_CFG_LEFT), m.input(NVDLA_PDP_D_POOLING_PADDING_CFG_LEFT));
            instr.SetUpdate(m.state(NVDLA_PDP_D_POOLING_PADDING_CFG_RIGHT), m.input(NVDLA_PDP_D_POOLING_PADDING_CFG_RIGHT));
            instr.SetUpdate(m.state(NVDLA_PDP_D_POOLING_PADDING_CFG_TOP), m.input(NVDLA_PDP_D_POOLING_PADDING_CFG_TOP));

            // set padding value
            instr.SetUpdate(m.state("pdp_padding_value"), m.input("pdp_padding_value"));

            // set output
            auto output_height = (PDP_INPUT_HEIGHT - m.state(NVDLA_PDP_D_POOLING_KERNEL_CFG_HEIGHT) + m.state(NVDLA_PDP_D_POOLING_PADDING_CFG_BOTTOM) + m.state(NVDLA_PDP_D_POOLING_PADDING_CFG_TOP));
            output_height = (output_height / m.state(NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_HEIGHT)) + 1;

            auto output_width = (PDP_INPUT_WIDTH - m.state(NVDLA_PDP_D_POOLING_KERNEL_CFG_WIDTH) + m.state(NVDLA_PDP_D_POOLING_PADDING_CFG_LEFT) + m.state(NVDLA_PDP_D_POOLING_PADDING_CFG_RIGHT));
            output_width = (output_width / m.state(NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_WIDTH)) + 1;

            instr.SetUpdate(m.state(NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT), output_height);
            instr.SetUpdate(m.state(NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH), output_width);

            //             for (auto i = 0; i < NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT; i++)
            // {
            //     // for (auto j = 0; j < NVDLA_PDP_D_DATA_CUBE_IN_WIDTH; j++)
            //     // {
            //     //     instr.SetUpdate(inputarr[i][j], Extract(m.input("pdp_input" + (std::to_string(counter))), 31, 0));
            //     //     //   instr.SetUpdate(m.state("pdp_input" + (std::to_string(counter))), );
            //     //     counter = counter + BvConst(1, 5)
            //     // }
            // }
            instr.SetUpdate(pdp_state, Ite(m.input("pdp_operation") == PDP_MAXPOOL, MAXPOOL,
                                           Ite(m.input("pdp_operation") == PDP_MINPOOL, MINPOOL, PDP_AVGPOOL)));
        }

        {
            // Max pooling option
            auto instr = m.NewInstr("max_pool");
            instr.SetDecode(pdp_state == MAXPOOL);
            auto outputHeight_Width = m.state(NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT);
            auto kernel_height = m.state("kernel height");
            auto kernel_width = m.state("kernel_width");
            auto stride = m.state("stride");

            auto mem_ptr = MemConst(0, {}, OUTPUT_ADDR_WIDTH, OUTPUT_BIT_WIDTH).get();
            for (auto output_i = 0; output_i < outputHeight_Width; output_i++)
            {
                for (auto output_j = 0; output_j < outputHeight_Width; output_j++)
                {
                    auto mem_addr = output_i * outputHeight_Width + output_j;
                    auto max = Load(ExprRef(mem_ptr), BvConst(mem_addr, 4));
                    for (auto kernel_i = 0; kernel_i < kernel_height; kernel_i++)
                    {
                        for (auto kernel_j = 0; kernel_j < kernel_width; kernel_j++)
                        {
                            // load from memory and read
                            // assumes they don't stride out of input (kernel and stride fit perfectly)
                            auto i = output_j * stride + kernel_i;
                            auto j = output_i * stride + kernel_j;
                            auto curr = m.input("pdp_input" + (std::to_string(i)) + "_" + (std::to_string(j)));
                            // auto mem_addr = output_j + output_i;
                            // auto max = Load(ExprRef(mem_ptr), BvConst(mem_addr, 4));

                            instr.SetUpdate(max, Ite(curr > max, curr, max));
                            // outputarr[output_i][output_j]

                            // auto new_mem = ExprRef(mem_ptr).Store(BvConst(mem_addr, 4), max);
                            // mem_ptr = new_mem.get();
                        }
                    }

                    auto new_mem = ExprRef(mem_ptr).Store(BvConst(mem_addr, 4), max);
                    mem_ptr = new_mem.get();
                    // instr.SetUpdate(inputarr[i][j],Extract(m.input("pdp_input"+ (std::to_string(counter))), 31, 0 ));
                    // instr.SetUpdate(m.state("pdp_input"+ (std::to_string(counter))), );
                    // counter = counter + BvConst(1,5)
                }
            }
            instr.SetUpdate(pdp_state, Ite(m.input("pdp_input_done"), START, LOAD));
        }

        {
            // Min pooling option
            auto instr = m.NewInstr("min_pool");
            instr.SetDecode(pdp_state == MINPOOL);
            auto outputHeight_Width = m.state("output_height");
            auto kernel_height = m.state("kernel height");
            auto kernel_width = m.state("kernel_width");
            auto stride = m.state("stride");

            auto mem_ptr = MemConst(0, {}, OUTPUT_ADDR_WIDTH, OUTPUT_BIT_WIDTH).get();
            for (auto output_i = 0; output_i < outputHeight_Width; output_i++)
            {
                for (int output_j = 0; output_j < outputHeight_Width; output_j++)
                {
                    auto mem_addr = output_i * outputHeight_Width + output_j;
                    auto min = Load(ExprRef(mem_ptr), BvConst(mem_addr, 4));
                    for (int kernel_i = 0; kernel_i < kernel_height; kernel_i++)
                    {
                        for (int kernel_j = 0; kernel_j < kernel_width; kernel_j++)
                        {
                            // load from memory and read
                            // assumes they don't stride out of input (kernel and stride fit perfectly)
                            auto i = output_i * stride + kernel_i;
                            auto j = output_j * stride + kernel_j;

                            auto curr = m.input("pdp_input" + (std::to_string(i)) + "_" + (std::to_string(j)));
                            // auto mem_addr = output_i + output_j;
                            // auto max = Load(ExprRef(mem_ptr), BvConst(mem_addr, 4));

                            instr.SetUpdate(min, Ite(curr < min, curr, min));
                            // outputarr[output_i][output_j]

                            auto new_mem = ExprRef(mem_ptr).Store(BvConst(mem_addr, 4), max);
                            mem_ptr = new_mem.get();
                        }
                    }
                    auto new_mem = ExprRef(mem_ptr).Store(BvConst(mem_addr, 4), min);
                    mem_ptr = new_mem.get();

                    // instr.SetUpdate(inputarr[i][j],Extract(m.input("pdp_input"+ (std::to_string(counter))), 31, 0 ));
                    // instr.SetUpdate(m.state("pdp_input"+ (std::to_string(counter))), );
                    // counter = counter + BvConst(1,5)
                }
            }
            instr.SetUpdate(pdp_state, Ite(m.input("pdp_input_done"), START, LOAD));
        }

        {
            // average pooling option
            auto instr = m.NewInstr("avg_pool");
            instr.SetDecode(pdp_state == AVGPOOL);
            auto outputHeight_Width = m.state("output_height");
            auto kernel_height = m.state("kernel height");
            auto kernel_width = m.state("kernel_width");
            auto stride = m.state("stride");
            auto kernel_elements = kernel_width * kernel_height;

            auto mem_ptr = MemConst(0, {}, OUTPUT_ADDR_WIDTH, OUTPUT_BIT_WIDTH).get();
            for (auto output_i = 0; output_i < outputHeight_Width; output_i++)
            {
                for (int output_j = 0; output_j < outputHeight_Width; output_j++)
                {
                    auto sum = 0;
                    auto mem_addr = output_i * outputHeight_Width + output_j;
                    auto avg = Load(ExprRef(mem_ptr), BvConst(mem_addr, 4));
                    for (int kernel_i = 0; kernel_i < kernel_height; kernel_i++)
                    {

                        for (int kernel_j = 0; kernel_j < kernel_width; kernel_j++)
                        {
                            // load from memory and read
                            // assumes they don't stride out of input (kernel and stride fit perfectly)
                            auto i = output_j * stride + kernel_i;
                            auto j = output_i * stride + kernel_j;
                            auto curr = m.input("pdp_input" + (std::to_string(i)) + "_" + (std::to_string(j)));
                            //  auto mem_addr = i + j;
                            //  auto avg = Load(ExprRef(mem_ptr), BvConst(mem_addr, 4));
                            //   auto sum =
                            sum = sum + curr;
                        }
                    }
                    avg = sum / kernel_elements;
                    // outputarr[output_i][output_j]

                    auto new_mem = ExprRef(mem_ptr).Store(BvConst(mem_addr, 4), avg);
                    mem_ptr = new_mem.get();

                    // instr.SetUpdate(inputarr[i][j],Extract(m.input("pdp_input"+ (std::to_string(counter))), 31, 0 ));
                    // instr.SetUpdate(m.state("pdp_input"+ (std::to_string(counter))), );
                    // counter = counter + BvConst(1,5)
                }
            }
            instr.SetUpdate(pdp_state, Ite(m.input("pdp_input_done"), START, LOAD));
        }

        // { // PDP Set Start Group 0 (addr:008)
        //     auto instr = m.NewInstr("store");
        //     instr.SetDecode(pdp_state == STORE);

        //     //     auto counter = 0 for (auto i = 0; i < NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT; i++)
        //     //     {
        //     //         for (auto j = 0; j < NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH; j++)
        //     //         {
        //     //             auto curr = BvConst(outputarr[i][j], 32)
        //     //                             instr.SetUpdate(m.state("pdp_output" + (std::to_string(counter))), curr);
        //     //             counter = counter + BvConst(1, 5)
        //     //         }
        //     //     }
        //     // }
        //     instr.SetUpdate(pdp_state, START);
        // }
    }

} // namespace ilang