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

// File: pdp_state.cc

#include <ilang/ilang++.h>

#include <pdp_config.h>

namespace ilang
{

    // Define PDP states
    void DefinePDPState(Ila &m)
    {
        // Config Registers

        // d000 done
        m.NewBvState(NVDLA_PDP_S_STATUS_0, NVDLA_PDP_S_STATUS_WIDTH);
        m.NewBvState(NVDLA_PDP_S_STATUS_1, NVDLA_PDP_S_STATUS_WIDTH);

        // d004 done
        m.NewBvState(NVDLA_PDP_S_PRODUCER, NVDLA_PDP_S_PRODUCER_WIDTH);
        m.NewBvState(NVDLA_PDP_S_CONSUMER, NVDLA_PDP_S_CONSUMER_WIDTH);


        //states
        m.NewBvState("pdp_state", 3);

        // for pooling calculations : kernwl and stride 
        m.NewBvState(NVDLA_PDP_D_POOLING_KERNEL_CFG_HEIGHT, NVDLA_PDP_D_POOLING_KERNEL_CFG_HEIGHT_WIDTH);
        m.NewBvState(NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_HEIGHT, NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_HEIGHT_WIDTH);
        m.NewBvState(NVDLA_PDP_D_POOLING_KERNEL_CFG_WIDTH, NVDLA_PDP_D_POOLING_KERNEL_CFG_WIDTH_WIDTH);
        m.NewBvState(NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_WIDTH, NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_WIDTH_WIDTH);

        // Padding Sizes
        m.NewBvState(NVDLA_PDP_D_POOLING_PADDING_CFG_BOTTOM, NVDLA_PDP_D_POOLING_PADDING_CFG_BOTTOM_WIDTH);
        m.NewBvState(NVDLA_PDP_D_POOLING_PADDING_CFG_LEFT, NVDLA_PDP_D_POOLING_PADDING_CFG_LEFT_WIDTH);
        m.NewBvState(NVDLA_PDP_D_POOLING_PADDING_CFG_RIGHT, NVDLA_PDP_D_POOLING_PADDING_CFG_RIGHT_WIDTH);
        m.NewBvState(NVDLA_PDP_D_POOLING_PADDING_CFG_TOP, NVDLA_PDP_D_POOLING_PADDING_CFG_TOP_WIDTH );

        //Padding value
        m.NewBvState("pdp_padding_value", PDP_INT_16_WIDTH );

        // Input precision
        m.NewBvState(NVDLA_PDP_D_DATA_FORMAT,NVDLA_PDP_D_DATA_FORMAT_WIDTH);

        //Output dimensions
        m.NewBvState(NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT, NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT_WIDTH);
        m.NewBvState(NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH);


        // for (auto i = 0; i < 2; i++)
        // {
        //     // d008 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_OP_ENABLE, NVDLA_PDP_D_OP_ENABLE_WIDTH);

        //     // d000c done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DATA_CUBE_IN_WIDTH, NVDLA_PDP_D_DATA_CUBE_IN_WIDTH_WIDTH);

        //     // d010 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT, NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH);

        //     // d014 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL, NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL_WIDTH);

        //     // d018 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH);

        //     // d01c done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT, NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT_WIDTH);

        //     // d020 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL, NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL_WIDTH);

        //     // d024 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_OPERATION_MODE_CFG, NVDLA_PDP_D_OPERATION_MODE_CFG_WIDTH);

        //     // d028 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_NAN_FLUSH_TO_ZERO, NVDLA_PDP_D_NAN_FLUSH_TO_ZERO_WIDTH);

        //     // d02c done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST, NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST_WIDTH);
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID, NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID_WIDTH);
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST, NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST_WIDTH);

        //     // d030 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST, NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST_WIDTH);
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID, NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID_WIDTH);
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST, NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST_WIDTH);

        //     // d034 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_KERNEL_CFG_HEIGHT, NVDLA_PDP_D_POOLING_KERNEL_CFG_HEIGHT_WIDTH);
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_HEIGHT, NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_HEIGHT_WIDTH);
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_KERNEL_CFG_WIDTH, NVDLA_PDP_D_POOLING_KERNEL_CFG_WIDTH_WIDTH);
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_WIDTH, NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_WIDTH_WIDTH);

        //     // d03c done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_RECIP_KERNEL_WIDTH, NVDLA_PDP_D_RECIP_KERNEL_WIDTH_WIDTH);

        //     // d03c done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_RECIP_KERNEL_HEIGHT, NVDLA_PDP_D_RECIP_KERNEL_HEIGHT_WIDTH);

        //     // d040 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_PADDING_CFG_BOTTOM, NVDLA_PDP_D_POOLING_PADDING_CFG_BOTTOM_WIDTH);
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_PADDING_CFG_LEFT, NVDLA_PDP_D_POOLING_PADDING_CFG_LEFT_WIDTH);
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_PADDING_CFG_RIGHT, NVDLA_PDP_D_POOLING_PADDING_CFG_RIGHT_WIDTH);
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_PADDING_CFG_TOP, NVDLA_PDP_D_POOLING_PADDING_CFG_TOP_WIDTH);

        //     // d044 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_PADDING_VALUE_1_CFG, NVDLA_PDP_D_POOLING_PADDING_VALUE_1_CFG_WIDTH);

        //     // d048 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_PADDING_VALUE_2_CFG, NVDLA_PDP_D_POOLING_PADDING_VALUE_2_CFG_WIDTH);

        //     // d04c done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_PADDING_VALUE_3_CFG, NVDLA_PDP_D_POOLING_PADDING_VALUE_3_CFG_WIDTH);

        //     // d050 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_PADDING_VALUE_4_CFG, NVDLA_PDP_D_POOLING_PADDING_VALUE_4_CFG_WIDTH);

        //     // d054 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_PADDING_VALUE_5_CFG, NVDLA_PDP_D_POOLING_PADDING_VALUE_5_CFG_WIDTH);

        //     // d058 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_PADDING_VALUE_6_CFG, NVDLA_PDP_D_POOLING_PADDING_VALUE_6_CFG_WIDTH);

        //     // d05c done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_POOLING_PADDING_VALUE_7_CFG, NVDLA_PDP_D_POOLING_PADDING_VALUE_7_CFG_WIDTH);

        //     // d060 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_SRC_BASE_ADDR_LOW, NVDLA_PDP_D_SRC_BASE_ADDR_LOW_WIDTH);

        //     // d064 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_SRC_BASE_ADDR_HIGH, NVDLA_PDP_D_SRC_BASE_ADDR_HIGH_WIDTH);

        //     // d068 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_SRC_LINE_STRIDE, NVDLA_PDP_D_SRC_LINE_STRIDE_WIDTH);

        //     // d06c done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_SRC_SURFACE_STRIDE, NVDLA_PDP_D_SRC_SURFACE_STRIDE_WIDTH);

        //     // d070 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DST_BASE_ADDR_LOW, NVDLA_PDP_D_DST_BASE_ADDR_LOW_WIDTH);

        //     // d074 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DST_BASE_ADDR_HIGH, NVDLA_PDP_D_DST_BASE_ADDR_HIGH_WIDTH);

        //     // d078 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DST_LINE_STRIDE, NVDLA_PDP_D_DST_LINE_STRIDE_WIDTH);

        //     // d07c done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DST_SURFACE_STRIDE, NVDLA_PDP_D_DST_SURFACE_STRIDE_WIDTH);

        //     // d080 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DST_RAM_CFG, NVDLA_PDP_D_DST_RAM_CFG_WIDTH);

        //     // d084 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_DATA_FORMAT, NVDLA_PDP_D_DATA_FORMAT_WIDTH);

        //     // d088 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_INF_INPUT_NUM, NVDLA_PDP_D_INF_INPUT_NUM_WIDTH);

        //     // d08c done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_NAN_INPUT_NUM, NVDLA_PDP_D_NAN_INPUT_NUM_WIDTH);

        //     // d090 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_NAN_OUTPUT_NUM, NVDLA_PDP_D_NAN_OUTPUT_NUM_WIDTH);

        //     // d094 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_PERF_ENABLE, NVDLA_PDP_D_PERF_ENABLE_WIDTH);

        //     // d098 done
        //     m.NewBvState("group" + (std::to_string(i)) + "_" + NVDLA_PDP_D_PERF_WRITE_STALL, NVDLA_PDP_D_PERF_WRITE_STALL_WIDTH);
        // }


  
 
 
    }

} // namespace ilang