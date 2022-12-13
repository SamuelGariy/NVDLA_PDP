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

// File: pdp_config.h

#ifndef NVDLA_PDP_CONFIG_H__
#define NVDLA_PDP_CONFIG_H__

namespace ilang {

inline std::string GetVarName(const std::string& var_name0, const std::string& var_name1) {
 
  return var_name0 + var_name1;
}

/**********************************************************************/
// ********************** CONFIG REGISTERS ***************************//
/**********************************************************************/
// 0xd000 - Idle status of two register groups
#define NVDLA_PDP_S_STATUS_0 "s_status0" // read_only
#define NVDLA_PDP_S_STATUS_1 "s_status1" // read_only
#define NVDLA_PDP_S_STATUS_WIDTH 2

// 0xd004 - Pointer for CSB master and data path to access groups
#define NVDLA_PDP_S_PRODUCER "s_producer"
#define NVDLA_PDP_S_PRODUCER_WIDTH 1
#define NVDLA_PDP_S_CONSUMER "s_consumer"
#define NVDLA_PDP_S_CONSUMER_WIDTH 1

// 0xd008 - Set it to 1 to kick off operation for current register group
#define NVDLA_PDP_D_OP_ENABLE "d_op_en_trigger"
#define NVDLA_PDP_D_OP_ENABLE_WIDTH 1

// 0xd00c Input data cube’s width
#define NVDLA_PDP_D_DATA_CUBE_IN_WIDTH "d_cube_in_width"
#define NVDLA_PDP_D_DATA_CUBE_IN_WIDTH_WIDTH 13

// 0xd010 Input data cube’s height
#define NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT "d_cube_in_height"
#define NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH 13

// 0xd014 Input data cube’s channel
#define NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL "d_cube_in_channel"
#define NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL_WIDTH 13

// 0xd018 Output data cube’s width
#define NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH "d_cube_out_width"
#define NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH 13
	
// 0xd01c Output data cube’s height
#define NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT "d_cube_out_height"
#define NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT_WIDTH 13

//0xd020 Output data cube’s channel
#define NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL "d_cube_out_channel"
#define NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL_WIDTH 13

// 0xd024 Split number
#define NVDLA_PDP_D_OPERATION_MODE_CFG "d_split_num"
#define NVDLA_PDP_D_OPERATION_MODE_CFG_WIDTH 8

// 0xd028 - Option to flush input NaN to zero
#define NVDLA_PDP_D_NAN_FLUSH_TO_ZERO "d_nan_to_zero"
#define NVDLA_PDP_D_NAN_FLUSH_TO_ZERO_WIDTH 1

// 0xd02c - Partial width for first, last and middle partitions of input cube
#define NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST "d_partial_width_in_first"
#define NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST_WIDTH 10
#define NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID "d_partial_width_in_mid"
#define NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID_WIDTH 10
#define NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST "d_partial_width_in_last"
#define NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST_WIDTH 10

// 0xd030 - Partial width for first, last and middle partitions of output cube
#define NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST "d_partial_width_out_first"
#define NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST_WIDTH 10
#define NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID "d_partial_width_out_mid"
#define NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID_WIDTH 10
#define NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST "d_partial_width_out_last"
#define NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST_WIDTH 10

// 0xd034 - Kernel width and kernel stride
#define NVDLA_PDP_D_POOLING_KERNEL_CFG_HEIGHT "d_kernel_height"
#define NVDLA_PDP_D_POOLING_KERNEL_CFG_HEIGHT_WIDTH 4
#define NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_HEIGHT "d_kernel_stride_height"
#define NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_HEIGHT_WIDTH 4
#define NVDLA_PDP_D_POOLING_KERNEL_CFG_WIDTH "d_kernel_width"
#define NVDLA_PDP_D_POOLING_KERNEL_CFG_WIDTH_WIDTH 4
#define NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_WIDTH "d_kernel_stride_width"
#define NVDLA_PDP_D_POOLING_KERNEL_CFG_STRIDE_WIDTH_WIDTH 4

// 0xd038 - Reciprocal of pooling kernel width, set to actual value * (2^16) 
// when INT8/INT16 format enabled. and set to actual value for fp16 precision
// mode with fp17 data format.
#define NVDLA_PDP_D_RECIP_KERNEL_WIDTH "d_recip_kernel_width"
#define NVDLA_PDP_D_RECIP_KERNEL_WIDTH_WIDTH 17

// 0xd03c - Reciprocal of pooling kernel height, set to actual value * (2^16)
// when INT8/INT16 format enabled. and set to actual value for fp16 precision
// mode with fp17 data format.
#define NVDLA_PDP_D_RECIP_KERNEL_HEIGHT "d_recip_kernel_height"
#define NVDLA_PDP_D_RECIP_KERNEL_HEIGHT_WIDTH 17

// 0xd040 - Left/right/top/bottom padding size
#define NVDLA_PDP_D_POOLING_PADDING_CFG_BOTTOM "d_pad_bottom"
#define NVDLA_PDP_D_POOLING_PADDING_CFG_BOTTOM_WIDTH 3
#define NVDLA_PDP_D_POOLING_PADDING_CFG_LEFT "d_pad_left"
#define NVDLA_PDP_D_POOLING_PADDING_CFG_LEFT_WIDTH 3
#define NVDLA_PDP_D_POOLING_PADDING_CFG_RIGHT "d_pad_right"
#define NVDLA_PDP_D_POOLING_PADDING_CFG_RIGHT_WIDTH 3
#define NVDLA_PDP_D_POOLING_PADDING_CFG_TOP "d_pad_top"
#define NVDLA_PDP_D_POOLING_PADDING_CFG_TOP_WIDTH 3

// 0xd044 - Padding_value*1
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_1_CFG "d_pad_value_1x"
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_1_CFG_WIDTH 19

// 0xd048 - Padding_value*2
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_2_CFG "d_pad_value_2x"
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_2_CFG_WIDTH 19

// 0xd04c - Padding_value*3
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_3_CFG "d_pad_value_3x"
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_3_CFG_WIDTH 19

// 0xd050 - Padding_value*4
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_4_CFG "d_pad_value_4x"
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_4_CFG_WIDTH 19

// 0xd054 - Padding_value*5
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_5_CFG "d_pad_value_5x"
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_5_CFG_WIDTH 19

// 0xd058 - Padding_value*6
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_6_CFG "d_pad_value_6x"
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_6_CFG_WIDTH 19

// 0xd05c - Padding_value*7
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_7_CFG "d_pad_value_7x"
#define NVDLA_PDP_D_POOLING_PADDING_VALUE_7_CFG_WIDTH 19

// 0xd060 - Lower 32bits of input data address
#define NVDLA_PDP_D_SRC_BASE_ADDR_LOW "d_src_base_addr_low"
#define NVDLA_PDP_D_SRC_BASE_ADDR_LOW_WIDTH 27

// 0xd064 - Higher 32bits of input data address when axi araddr is 64bits
#define NVDLA_PDP_D_SRC_BASE_ADDR_HIGH "d_src_base_addr_high"
#define NVDLA_PDP_D_SRC_BASE_ADDR_HIGH_WIDTH 32

// 0xd068 - Line stride of input cube
#define NVDLA_PDP_D_SRC_LINE_STRIDE "d_src_line_stride"
#define NVDLA_PDP_D_SRC_LINE_STRIDE_WIDTH 27

// 0xd06c - Surface stride of input cube
#define NVDLA_PDP_D_SRC_SURFACE_STRIDE "d_src_surface_stride"
#define NVDLA_PDP_D_SRC_SURFACE_STRIDE_WIDTH 27

// 0xd070 - Lower 32bits of output data address
#define NVDLA_PDP_D_DST_BASE_ADDR_LOW "d_dst_base_addr_low"
#define NVDLA_PDP_D_DST_BASE_ADDR_LOW_WIDTH 27

// 0xd074 - Higher 32bits of output data address when axi awaddr is 6
#define NVDLA_PDP_D_DST_BASE_ADDR_HIGH "d_dst_base_addr_high"
#define NVDLA_PDP_D_DST_BASE_ADDR_HIGH_WIDTH 27

// 0xd078 - Line stride of output cube
#define NVDLA_PDP_D_DST_LINE_STRIDE "d_dst_line_stride"
#define NVDLA_PDP_D_DST_LINE_STRIDE_WIDTH 27

// 0xd07c - Surface stride of output cube
#define NVDLA_PDP_D_DST_SURFACE_STRIDE "d_dst_surface_stride"
#define NVDLA_PDP_D_DST_SURFACE_STRIDE_WIDTH 27

// 0xd080 - RAM type of destination cube
#define NVDLA_PDP_D_DST_RAM_CFG "d_dst_ram_type"
#define NVDLA_PDP_D_DST_RAM_CFG_WIDTH 1

// 0xd084 - Precision of input data
#define NVDLA_PDP_D_DATA_FORMAT "d_input_data"
#define NVDLA_PDP_D_DATA_FORMAT_WIDTH 2

// 0xd088 - Input infinity element number
#define NVDLA_PDP_D_INF_INPUT_NUM "d_inf_input_num"
#define NVDLA_PDP_D_INF_INPUT_NUM_WIDTH 32

// 0xd08c - Input NaN element number
#define NVDLA_PDP_D_NAN_INPUT_NUM "d_nan_input_num"
#define NVDLA_PDP_D_NAN_INPUT_NUM_WIDTH 32

// 0xd090 - Output NaN element number
#define NVDLA_PDP_D_NAN_OUTPUT_NUM "d_nan_output_num"
#define NVDLA_PDP_D_NAN_OUTPUT_NUM_WIDTH 32

// 0xd094 - Enable/disable performance counting   
#define NVDLA_PDP_D_PERF_ENABLE "d_dma_en"                         //NOT SURE               
#define NVDLA_PDP_D_PERF_ENABLE_WIDTH 1

// 0xd098 - Counting stalls of write requests
#define NVDLA_PDP_D_PERF_WRITE_STALL "d_perf_write_stall"
#define NVDLA_PDP_D_PERF_WRITE_STALL_WIDTH 32

// // states
#define START BvConst(0,2)
#define LOAD BvConst(1,2)
#define MAXPOOL BvConst(2,2)
#define STORE BvConst(3,2)

} // namespace ilang

#endif // NVDLA_PDP_CONFIG_H__