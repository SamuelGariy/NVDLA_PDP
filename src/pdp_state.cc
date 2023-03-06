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
        // /****************************************************************************/
        // // ********************** CONFIG REGISTER STATES ***************************//
        // /***************************************************************************/

        // 0xd000 - Idle status of two register groups
        m.NewBvState(NVDLA_PDP_S_STATUS_0, NVDLA_PDP_S_STATUS_WIDTH);
        m.NewBvState(NVDLA_PDP_S_STATUS_1, NVDLA_PDP_S_STATUS_WIDTH);

        // 0xd004 - Pointer for CSB master and data path to access groups
        m.NewBvState(NVDLA_PDP_S_PRODUCER, NVDLA_PDP_S_PRODUCER_WIDTH);
        m.NewBvState(NVDLA_PDP_S_CONSUMER, NVDLA_PDP_S_CONSUMER_WIDTH);

        // 0xd008 - Set it to 1 to kick off operation for current register group
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_OP_ENABLE), NVDLA_PDP_D_OP_ENABLE_WIDTH);

        // 0xd00c Input data cube’s width
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_WIDTH), NVDLA_PDP_D_DATA_CUBE_IN_WIDTH_WIDTH);

        // 0xd010 Input data cube’s height
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT), NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH);

        // 0xd014 Input data cube’s channel
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL), NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL_WIDTH);

        // 0xd018 Output data cube’s width
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH), NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH);

        // 0xd01c Output data cube’s height
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT), NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT_WIDTH);

        // 0xd020 Output data cube’s channel
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL), NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL_WIDTH);

        // 0xd024 Split number
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_POOLING_METHOD), NVDLA_PDP_POOLING_METHOD_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_FLYING_MODE), NVDLA_PDP_FLYING_MODE_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_SPLIT_NUM), NVDLA_PDP_SPLIT_NUM_WIDTH);

        // 0xd028 - Option to flush input NaN to zero
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_NAN_FLUSH_TO_ZERO), NVDLA_PDP_D_NAN_FLUSH_TO_ZERO_WIDTH);

        // 0xd02c - Partial width for first, last and middle partitions of input cube
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST), NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID), NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST), NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST_WIDTH);

        // 0xd030 - Partial width for first, last and middle partitions of output cube
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST), NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID), NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST), NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST_WIDTH);

        // 0xd034 - Kernel width and kernel stride
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_KERNEL_WIDTH), NVDLA_PDP_D_KERNEL_WIDTH_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_KERNEL_HEIGHT), NVDLA_PDP_D_KERNEL_HEIGHT_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_HEIGHT), NVDLA_PDP_D_KERNEL_STRIDE_HEIGHT_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_WIDTH), NVDLA_PDP_D_KERNEL_STRIDE_WIDTH_WIDTH);

        // 0xd038 - Reciprocal of pooling kernel width, set to actual value * (2^16)
        // when INT8/INT16 format enabled. and set to actual value for fp16 precision
        // mode with fp17 data format.
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_RECIP_KERNEL_WIDTH), NVDLA_PDP_D_RECIP_KERNEL_WIDTH_WIDTH);

        // 0xd03c - Reciprocal of pooling kernel height, set to actual value * (2^16)
        // when INT8/INT16 format enabled. and set to actual value for fp16 precision
        // mode with fp17 data format.
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_RECIP_KERNEL_HEIGHT), NVDLA_PDP_D_RECIP_KERNEL_HEIGHT_WIDTH);

        // 0xd040 - Left/right/top/bottom padding size
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PAD_LEFT), NVDLA_PDP_D_PAD_LEFT_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PAD_TOP), NVDLA_PDP_D_PAD_TOP_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PAD_RIGHT), NVDLA_PDP_D_PAD_RIGHT_WIDTH);
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PAD_BOTTOM), NVDLA_PDP_D_PAD_BOTTOM_WIDTH);

        // 0xd044 - Padding_value*1
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_1_CFG), NVDLA_PDP_D_POOLING_PADDING_VALUE_1_CFG_WIDTH);

        // 0xd048 - Padding_value*2
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_2_CFG), NVDLA_PDP_D_POOLING_PADDING_VALUE_2_CFG_WIDTH);

        // 0xd04c - Padding_value*3
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_3_CFG), NVDLA_PDP_D_POOLING_PADDING_VALUE_3_CFG_WIDTH);

        // 0xd050 - Padding_value*4
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_4_CFG), NVDLA_PDP_D_POOLING_PADDING_VALUE_4_CFG_WIDTH);

        // 0xd054 - Padding_value*5
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_5_CFG), NVDLA_PDP_D_POOLING_PADDING_VALUE_5_CFG_WIDTH);

        // 0xd058 - Padding_value*6
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_6_CFG), NVDLA_PDP_D_POOLING_PADDING_VALUE_6_CFG_WIDTH);

        // 0xd05c - Padding_value*7
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_7_CFG), NVDLA_PDP_D_POOLING_PADDING_VALUE_7_CFG_WIDTH);

        // 0xd060 - Lower 32bits of input data address
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_SRC_BASE_ADDR_LOW), NVDLA_PDP_D_SRC_BASE_ADDR_LOW_WIDTH);

        // 0xd064 - Higher 32bits of input data address when axi araddr is 64bits
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_SRC_BASE_ADDR_HIGH), NVDLA_PDP_D_SRC_BASE_ADDR_HIGH_WIDTH);

        // 0xd068 - Line stride of input cube
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_SRC_LINE_STRIDE), NVDLA_PDP_D_SRC_LINE_STRIDE_WIDTH);

        // 0xd06c - Surface stride of input cube
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_SRC_SURFACE_STRIDE), NVDLA_PDP_D_SRC_SURFACE_STRIDE_WIDTH);

        // 0xd070 - Lower 32bits of output data address
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DST_BASE_ADDR_LOW), NVDLA_PDP_D_DST_BASE_ADDR_LOW_WIDTH);

        // 0xd074 - Higher 32bits of output data address when axi awaddr is 64bits
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DST_BASE_ADDR_HIGH), NVDLA_PDP_D_DST_BASE_ADDR_HIGH_WIDTH);

        // 0xd078 - Line stride of output cube
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DST_LINE_STRIDE), NVDLA_PDP_D_DST_LINE_STRIDE_WIDTH);

        // 0xd07c - Surface stride of output cube
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DST_SURFACE_STRIDE), NVDLA_PDP_D_DST_SURFACE_STRIDE_WIDTH);

        // 0xd080 - RAM type of destination cube
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DST_RAM_CFG), NVDLA_PDP_D_DST_RAM_CFG_WIDTH);

        // 0xd084 - Precision of input data
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_DATA_FORMAT), NVDLA_PDP_D_DATA_FORMAT_WIDTH);

        // 0xd088 - Input infinity element number
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_INF_INPUT_NUM), NVDLA_PDP_D_INF_INPUT_NUM_WIDTH);

        // 0xd08c - Input NaN element number
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_NAN_INPUT_NUM), NVDLA_PDP_D_NAN_INPUT_NUM_WIDTH);

        // 0xd090 - Output NaN element number
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_NAN_OUTPUT_NUM), NVDLA_PDP_D_NAN_OUTPUT_NUM_WIDTH);

        // 0xd094 - Enable/disable performance counting
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PERF_ENABLE), NVDLA_PDP_D_PERF_ENABLE_WIDTH);

        // 0xd098 - Counting stalls of write requests
        m.NewBvState(GetVarName("group0_", NVDLA_PDP_D_PERF_WRITE_STALL), NVDLA_PDP_D_PERF_WRITE_STALL_WIDTH);

        // /****************************************************************************/
        // // ********************** ADDITIONAL STATES *********************************//
        // /***************************************************************************/

        // PDP_ILA states
        m.NewBvState("pdp_state", 3);

        // share line buffer
      //  m.NewMemState("pdp_share_line_buffer", PDP_SHARE_LINE_ADDR_WIDTH, PDP_INT_16_WIDTH);

        // buffer storing last kernel values for split width
     //   m.NewMemState("pdp_split_width_buffer", PDP_SPLIT_WIDTH_BUFFER_ADDR_WIDTH, PDP_INT_16_WIDTH);

        // Padding value in use
        m.NewBvState("pdp_padding_value", PDP_INT_16_WIDTH);

        // pooling_stage_split_width
        m.NewBvState("pdp_pooling_stage_split_width", 2);

        // input height computed
      //  m.NewBvState("input_height_marker", NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH);

        // input kernel computed
        m.NewBvState("kernel_height_marker", NVDLA_PDP_D_KERNEL_HEIGHT_WIDTH);

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