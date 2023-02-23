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

// File: pdp_input.cc

#include <ilang/ilang++.h>

#include <pdp_config.h>

namespace ilang
{

    void DefinePDPInput(Ila &m)
    {
        // From CSB
        m.NewBvInput("csb2pdp_addr", 22);
        m.NewBvInput("csb2pdp_data", 32);
        m.NewBvInput("csb2pdp_write", 1);
        m.NewBvInput("csb2pdp_vld", 1);

        // input for pooling
        // m.NewBvInput(NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT,NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH);
        // m.NewBvInput(NVDLA_PDP_D_DATA_CUBE_IN_WIDTH,NVDLA_PDP_D_DATA_CUBE_IN_WIDTH_WIDTH );

        m.NewBvInput("pdp_input_done", 1); // is it last pdp input

        // Kernel width and kernel stride

        m.NewBvInput(NVDLA_PDP_D_POOLING_KERNEL_CFG_HEIGHT, NVDLA_PDP_D_POOLING_KERNEL_CFG_HEIGHT_WIDTH);
        m.NewBvInput(NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_HEIGHT, NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_HEIGHT_WIDTH);
        m.NewBvInput(NVDLA_PDP_D_POOLING_KERNEL_CFG_WIDTH, NVDLA_PDP_D_POOLING_KERNEL_CFG_WIDTH_WIDTH);
        m.NewBvInput(NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_WIDTH, NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_WIDTH_WIDTH);

        // Padding Sizes
        m.NewBvInput(NVDLA_PDP_D_POOLING_PADDING_CFG_BOTTOM, NVDLA_PDP_D_POOLING_PADDING_CFG_BOTTOM_WIDTH);
        m.NewBvInput(NVDLA_PDP_D_POOLING_PADDING_CFG_LEFT, NVDLA_PDP_D_POOLING_PADDING_CFG_LEFT_WIDTH);
        m.NewBvInput(NVDLA_PDP_D_POOLING_PADDING_CFG_RIGHT, NVDLA_PDP_D_POOLING_PADDING_CFG_RIGHT_WIDTH);
        m.NewBvInput(NVDLA_PDP_D_POOLING_PADDING_CFG_TOP, NVDLA_PDP_D_POOLING_PADDING_CFG_TOP_WIDTH );

        //Padding value
        m.NewBvInput("pdp_padding_value", PDP_INT_16_WIDTH );

        //precision of input data
        m.NewBvInput(NVDLA_PDP_D_DATA_FORMAT,NVDLA_PDP_D_DATA_FORMAT_WIDTH);

        m.NewBvInput("pdp_operation", 2); // max/min/avg pooling

        for (auto i = 0; i < PDP_INPUT_HEIGHT; i++)
        {
            // Primary inputs
            for (auto j = 0; h < PDP_INPUT_WIDTH; i++)
            {
                m.NewBvInput(GetVarName("pdp_input", (std::to_string(i)) + "_" + (std::to_string(j))), PDP_INT_16_WIDTH);
            }
        }

        // Control Signals
        // m.NewBvInput("pending_clr", 1);
        // m.NewBvInput("sg2dl_vld", 1);
        // m.NewBvInput("sg2wt_vld", 1);
        // m.NewBvInput("fifo_clr", 1);
        // m.NewBvInput("done", 1);
    }

} // namespace ilang