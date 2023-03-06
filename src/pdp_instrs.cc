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

    // Return 16-bit representation of int8
    ExprRef int8_to_int16(ExprRef num)
    {
        auto bv7_unsigned = num & BvConst(0x7F, PDP_INT_16_WIDTH);
        auto bv = Ite(SelectBit(num, 7) == 0, bv7_unsigned, bv7_unsigned | BvConst(0xFF80, PDP_INT_16_WIDTH));
        return bv;
    }

    // // sign extends 8 bits to 16 bits
    // ExprRef int8_to_int16(ExprRef bv16, ExprRef data_type)
    // {
    //     auto bv7_unsigned = bv16 & BvConst(0x7F, PDP_INT_16_WIDTH);

    //     // update weight based on datatype
    //     auto bv = Ite(data_type == INT16, bv16,
    //                   Ite(data_type == INT8, Ite(SelectBit(bv16, 7) == 0, bv7_unsigned, bv7_unsigned | BvConst(0xFF80, PDP_INT_16_WIDTH)),
    //                       BvConst(0, PDP_INT_16_WIDTH)));

    //     return bv;
    // }

    // Convert bit vector  to int
    //  int bv_to_int(ExprRef bv)
    //  {
    //      curr = BvConst(0, PDP_INT_16_WIDTH);
    //      for(auto i = 0; i < SHRT_MAX; i++ ){

    //     }

    //     return bv;
    // }

    // Define PDP instructions relevant to configuration registers
    void DefinePDPInstrs(Ila &m)
    {
        // /****************************************************************************/
        // // ********************** INITIALIZING *********************************//
        // /***************************************************************************/

        // Initialize both the PRODUCER and CONSUMER states to be 0
        m.AddInit(m.state(NVDLA_PDP_S_PRODUCER) == BvConst(0, NVDLA_PDP_S_PRODUCER_WIDTH));
        m.AddInit(m.state(NVDLA_PDP_S_CONSUMER) == BvConst(0, NVDLA_PDP_S_CONSUMER_WIDTH));

        m.AddInit(m.state(NVDLA_PDP_S_STATUS_0) == BvConst(0, NVDLA_PDP_S_STATUS_WIDTH));
        m.AddInit(m.state(NVDLA_PDP_S_STATUS_1) == BvConst(0, NVDLA_PDP_S_STATUS_WIDTH));

        m.AddInit(m.state(GetVarName("group0_", NVDLA_PDP_D_OP_ENABLE)) == BvConst(0, NVDLA_PDP_D_OP_ENABLE_WIDTH));

        // Initialize output signals
        m.AddInit(m.state("pdp2csb_rdy") == BvConst(1, 1));
        m.AddInit(m.state("pdp2csb_data_vld") == SIG_FALSE);

        // /****************************************************************************/
        // // ********************** GLOBAL VARIABLES *********************************//
        // /***************************************************************************/

        // csb  - pdp variables
        auto pdp_csb_addr = Extract(m.input("csb2pdp_addr"), 11, 0);
        auto pdp_csb_valid = (m.state("pdp2csb_rdy") == SIG_TRUE) & (m.input("csb2pdp_vld") == SIG_TRUE);
        auto pdp_csb_write = m.input("csb2pdp_write") == SIG_TRUE;
        auto pdp_group0_unset = m.state(GetVarName("group0_", NVDLA_PDP_D_OP_ENABLE)) == BvConst(0, 1);
        auto pdp_producer = m.state(NVDLA_PDP_S_PRODUCER);
        auto pdp_consumer = m.state(NVDLA_PDP_S_CONSUMER);
        auto pdp_state = m.state("pdp_state");

        // sdp - pdp involved variables
        // TODO : Fill with other valid states inputs

        // /****************************************************************************/
        // // ***************** REGISTER CONFIGURATION INSTRUCTIONS ********************//
        // /***************************************************************************/

        { // PDP set producer - addr = 0x004
            auto instr = m.NewInstr("set_producer");
            instr.SetDecode(pdp_csb_addr == 0x004 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(pdp_producer, Extract(m.input("csb2pdp_data"), NVDLA_PDP_S_PRODUCER_WIDTH - 1, 0));
        }

        { // PDP set start group 0 - addr = 0x008
            auto instr = m.NewInstr("set_start_group0");
            instr.SetDecode(pdp_csb_addr == 0x008 & pdp_csb_valid & pdp_csb_write & pdp_producer == BvConst(0, 1) & pdp_group0_unset);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_OP_ENABLE)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_OP_ENABLE_WIDTH - 1, 0));
            instr.SetUpdate(pdp_state, START);
        }

        { // PDP set input data cube's width - addr = 0x00c
            auto instr = m.NewInstr("set_cube_in_width");
            instr.SetDecode(pdp_csb_addr == 0x00c & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_WIDTH)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_DATA_CUBE_IN_WIDTH_WIDTH - 1, 0));
        }

        { // PDP set input data cube's height - addr = 0x010
            auto instr = m.NewInstr("set_cube_in_height");
            instr.SetDecode(pdp_csb_addr == 0x010 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH - 1, 0));
        }

        { // PDP set input data cube's channel - addr = 0x014
            auto instr = m.NewInstr("set_cube_in_channel");
            instr.SetDecode(pdp_csb_addr == 0x014 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL_WIDTH - 1, 0));
        }

        { // PDP set output data cube's width - addr = 0x0018
            auto instr = m.NewInstr("set_cube_out_width");
            instr.SetDecode(pdp_csb_addr == 0x018 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH - 1, 0));
        }

        { // PDP set output data cube's height - addr = 0x01c
            auto instr = m.NewInstr("set_cube_out_height");
            instr.SetDecode(pdp_csb_addr == 0x01c & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT_WIDTH - 1, 0));
        }

        { // PDP set output data cube's channel - addr = 0x020
            auto instr = m.NewInstr("set_cube_out_channel");
            instr.SetDecode(pdp_csb_addr == 0x020 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL_WIDTH - 1, 0));
        }

        { // PDP set split number and pooling method and operation mode - addr = 0x024
            auto instr = m.NewInstr("set_split_number");
            instr.SetDecode(pdp_csb_addr == 0x024 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_POOLING_METHOD)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_POOLING_METHOD_WIDTH - 1, 0));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_FLYING_MODE)), SelectBit(m.input("csb2pdp_data"), NVDLA_PDP_FLYING_MODE_START_BIT));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_SPLIT_NUM)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_SPLIT_NUM_WIDTH_END_BIT, NVDLA_PDP_SPLIT_NUM_WIDTH_START_BIT));
        }

        { // PDP set option to flush input NaN to zero - addr = 0x028
            auto instr = m.NewInstr("set_nan_flush_to_zero");
            instr.SetDecode(pdp_csb_addr == 0x028 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_NAN_FLUSH_TO_ZERO)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_NAN_FLUSH_TO_ZERO_WIDTH - 1, 0));
        }

        { // PDP set partial width for first, last and middle partitions of input cube - addr = 0x02c
            auto instr = m.NewInstr("set_partial_width_in");
            instr.SetDecode(pdp_csb_addr == 0x02c & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST_WIDTH - 1, 0));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID_END_BIT, NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID_START_BIT));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST_END_BIT, NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST_START_BIT));
        }

        { // PDP set partial width for first, last and middle partitions of output cube - addr = 0x030
            auto instr = m.NewInstr("set_partial_width_out");
            instr.SetDecode(pdp_csb_addr == 0x030 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST_WIDTH - 1, 0));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID_END_BIT, NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID_START_BIT));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST_END_BIT, NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST_START_BIT));
        }

        { // PDP set kernel width and kernel stride - addr = 0x034
            auto instr = m.NewInstr("set_kernel_width_height");
            instr.SetDecode(pdp_csb_addr == 0x034 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_WIDTH)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_KERNEL_WIDTH_WIDTH - 1, 0));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_HEIGHT)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_KERNEL_HEIGHT_END_BIT, NVDLA_PDP_D_KERNEL_HEIGHT_START_BIT));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_HEIGHT)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_KERNEL_STRIDE_HEIGHT_END_BIT, NVDLA_PDP_D_KERNEL_STRIDE_HEIGHT_START_BIT));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_WIDTH)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_KERNEL_STRIDE_WIDTH_END_BIT, NVDLA_PDP_D_KERNEL_STRIDE_WIDTH_START_BIT));
        }

        { // PDP set reciprocal of pooling kernel width - addr = 0x038
            auto instr = m.NewInstr("set_kernel_width_reciprocal");
            instr.SetDecode(pdp_csb_addr == 0x038 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_RECIP_KERNEL_WIDTH)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_RECIP_KERNEL_WIDTH_WIDTH - 1, 0));
        }

        { // PDP set reciprocal of pooling kernel height - addr = 0x03c
            auto instr = m.NewInstr("set_kernel_height_reciprocal");
            instr.SetDecode(pdp_csb_addr == 0x03c & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_RECIP_KERNEL_HEIGHT)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_RECIP_KERNEL_HEIGHT_WIDTH - 1, 0));
        }

        { // PDP set left/right/top/bottom padding size - addr = 0x040
            auto instr = m.NewInstr("set_padding_size");
            instr.SetDecode(pdp_csb_addr == 0x040 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_LEFT)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PAD_LEFT_WIDTH - 1, 0));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_TOP)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PAD_TOP_END_BIT, NVDLA_PDP_D_PAD_TOP_START_BIT));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_RIGHT)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PAD_RIGHT_END_BIT, NVDLA_PDP_D_PAD_RIGHT_START_BIT));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_BOTTOM)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PAD_BOTTOM_END_BIT, NVDLA_PDP_D_PAD_BOTTOM_START_BIT));
        }

        { // PDP set Padding_value*1 - addr = 0x044
            auto instr = m.NewInstr("set_padding_value_1x");
            instr.SetDecode(pdp_csb_addr == 0x044 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_1_CFG)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_POOLING_PADDING_VALUE_1_CFG_WIDTH - 1, 0));
        }

        { // PDP set Padding_value*2 - addr = 0x048
            auto instr = m.NewInstr("set_padding_value_2x");
            instr.SetDecode(pdp_csb_addr == 0x048 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_2_CFG)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_POOLING_PADDING_VALUE_2_CFG_WIDTH - 1, 0));
        }

        { // PDP set Padding_value*3 - addr = 0x04c
            auto instr = m.NewInstr("set_padding_value_3x");
            instr.SetDecode(pdp_csb_addr == 0x04c & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_3_CFG)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_POOLING_PADDING_VALUE_3_CFG_WIDTH - 1, 0));
        }

        { // PDP set Padding_value*4 - addr = 0x050
            auto instr = m.NewInstr("set_padding_value_4x");
            instr.SetDecode(pdp_csb_addr == 0x050 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_4_CFG)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_POOLING_PADDING_VALUE_4_CFG_WIDTH - 1, 0));
        }

        { // PDP set Padding_value*5 - addr = 0x054
            auto instr = m.NewInstr("set_padding_value_5x");
            instr.SetDecode(pdp_csb_addr == 0x054 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_5_CFG)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_POOLING_PADDING_VALUE_5_CFG_WIDTH - 1, 0));
        }

        { // PDP set Padding_value*6 - addr = 0x058
            auto instr = m.NewInstr("set_padding_value_6x");
            instr.SetDecode(pdp_csb_addr == 0x058 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_6_CFG)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_POOLING_PADDING_VALUE_6_CFG_WIDTH - 1, 0));
        }

        { // PDP set Padding_value*7 - addr = 0x05c
            auto instr = m.NewInstr("set_padding_value_7x");
            instr.SetDecode(pdp_csb_addr == 0x05c & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_7_CFG)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_POOLING_PADDING_VALUE_7_CFG_WIDTH - 1, 0));
        }

        { // PDP set lower 32bits of input data address - addr = 0x060
            auto instr = m.NewInstr("set_source_address_low");
            instr.SetDecode(pdp_csb_addr == 0x060 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_SRC_BASE_ADDR_LOW)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_SRC_BASE_ADDR_LOW_END_BIT, NVDLA_PDP_D_SRC_BASE_ADDR_LOW_START_BIT));
        }

        { // PDP set higher 32bits of input data address - addr = 0x064
            auto instr = m.NewInstr("set_source_address_high");
            instr.SetDecode(pdp_csb_addr == 0x064 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_SRC_BASE_ADDR_HIGH)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_SRC_BASE_ADDR_HIGH_WIDTH - 1, 0));
        }

        { // PDP set line stride of input cube - addr = 0x068
            auto instr = m.NewInstr("set_source_line_stride");
            instr.SetDecode(pdp_csb_addr == 0x068 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_SRC_LINE_STRIDE)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_SRC_LINE_STRIDE_END_BIT, NVDLA_PDP_D_SRC_LINE_STRIDE_START_BIT));
        }

        { // PDP set surface stride of input cube - addr = 0x06c
            auto instr = m.NewInstr("set_source_surface_stride");
            instr.SetDecode(pdp_csb_addr == 0x06c & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_SRC_SURFACE_STRIDE)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_SRC_SURFACE_STRIDE_END_BIT, NVDLA_PDP_D_SRC_SURFACE_STRIDE_START_BIT));
        }

        { // PDP set lower 32bits of output data address - addr = 0x070
            auto instr = m.NewInstr("set_destination_address_low");
            instr.SetDecode(pdp_csb_addr == 0x070 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DST_BASE_ADDR_LOW)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_DST_BASE_ADDR_LOW_END_BIT, NVDLA_PDP_D_DST_BASE_ADDR_LOW_START_BIT));
        }

        { // PDP set higher 32bits of output data address - addr = 0x074
            auto instr = m.NewInstr("set_destination_address_high");
            instr.SetDecode(pdp_csb_addr == 0x074 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DST_BASE_ADDR_HIGH)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_DST_BASE_ADDR_HIGH_WIDTH - 1, 0));
        }

        { // PDP set line stride of output cube - addr = 0x078
            auto instr = m.NewInstr("set_destination_line_stride");
            instr.SetDecode(pdp_csb_addr == 0x078 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DST_LINE_STRIDE)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_DST_LINE_STRIDE_END_BIT, NVDLA_PDP_D_DST_LINE_STRIDE_START_BIT));
        }

        { // PDP set surface stride of output cube - addr = 0x07c
            auto instr = m.NewInstr("set_destination_surface_stride");
            instr.SetDecode(pdp_csb_addr == 0x07c & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_SRC_SURFACE_STRIDE)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_SRC_SURFACE_STRIDE_END_BIT, NVDLA_PDP_D_SRC_SURFACE_STRIDE_START_BIT));
        }

        { // PDP set RAM type of destination cube - addr = 0x080
            auto instr = m.NewInstr("set_ram_type");
            instr.SetDecode(pdp_csb_addr == 0x080 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DST_RAM_CFG)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_DST_RAM_CFG_WIDTH - 1, 0));
        }

        { // PDP set precision of input data - addr = 0x084
            auto instr = m.NewInstr("set_input_data_format");
            instr.SetDecode(pdp_csb_addr == 0x084 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_FORMAT)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_DATA_FORMAT_WIDTH - 1, 0));
        }

        { // PDP set input infinity element number- addr = 0x088
            auto instr = m.NewInstr("set_infinity_input_number");
            instr.SetDecode(pdp_csb_addr == 0x088 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_INF_INPUT_NUM)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_INF_INPUT_NUM_WIDTH - 1, 0));
        }

        { // PDP set input NaN element number - addr = 0x08c
            auto instr = m.NewInstr("set_nan_input_number");
            instr.SetDecode(pdp_csb_addr == 0x08c & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_NAN_INPUT_NUM)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_NAN_INPUT_NUM_WIDTH - 1, 0));
        }

        { // PDP set output NaN element number - addr = 0x090
            auto instr = m.NewInstr("set_nan_output_number");
            instr.SetDecode(pdp_csb_addr == 0x090 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_NAN_OUTPUT_NUM)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_NAN_OUTPUT_NUM_WIDTH - 1, 0));
        }

        { // PDP set performance counting (enable/disable) - addr = 0x094
            auto instr = m.NewInstr("set_perf_count_enable");
            instr.SetDecode(pdp_csb_addr == 0x094 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PERF_ENABLE)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PERF_ENABLE_WIDTH - 1, 0));
        }

        { // PDP set counting stalls of write requests - addr = 0x098
            auto instr = m.NewInstr("set_perf_write_stall");
            instr.SetDecode(pdp_csb_addr == 0x098 & pdp_csb_valid & pdp_csb_write);

            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PERF_WRITE_STALL)), Extract(m.input("csb2pdp_data"), NVDLA_PDP_D_PERF_WRITE_STALL_WIDTH - 1, 0));
        }

        // // /****************************************************************************/
        // // // ***************************** PDP STATE CONTROL ***************************//
        // // /***************************************************************************/
        {
            // start to load
            auto instr = m.NewInstr("pdp_start_to_load");
            auto group0_ready = pdp_consumer == BvConst(0, 1) & m.state(GetVarName("group0_", NVDLA_PDP_D_OP_ENABLE)) == SIG_TRUE;
            instr.SetDecode(pdp_state == START & group0_ready);

            instr.SetUpdate(m.state("pdp_state"), LOAD);
        }

        // // /****************************************************************************/
        // // // ***************** PDP OPERATIONS INSTRUCTIONS ***************************//
        // // /***************************************************************************/

        
        {
            // PDP operations
            //  Load input variables

            auto instr = m.NewInstr("load_prepooling_variables");
            instr.SetDecode(pdp_state == LOAD);

            // update padding value
            instr.SetUpdate(m.state("pdp_padding_value"), Extract(m.state(GetVarName("group0_", NVDLA_PDP_D_POOLING_PADDING_VALUE_1_CFG)), PDP_INT_16_WIDTH - 1, 0));

            // update output variables
            // update output channel
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL)), Extract(m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL)), NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL_WIDTH - 1, 0));

            // update output height
            auto output_var = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT)) - SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_HEIGHT)), NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH) + SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_BOTTOM)), NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH) + SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_TOP)), NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH);
            output_var = (output_var / SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_HEIGHT)), NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT_WIDTH)) + 1;
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT)), output_var);

            // update output width
            output_var = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_WIDTH)) - SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_WIDTH)), NVDLA_PDP_D_DATA_CUBE_IN_WIDTH_WIDTH) + SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_LEFT)), NVDLA_PDP_D_DATA_CUBE_IN_WIDTH_WIDTH) + SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_RIGHT)), NVDLA_PDP_D_DATA_CUBE_IN_WIDTH_WIDTH);
            output_var = (output_var / SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_WIDTH)), NVDLA_PDP_D_DATA_CUBE_IN_WIDTH_WIDTH)) + 1;
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH)), output_var);

            // update first width
            output_var = m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST)) - SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_WIDTH)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST_WIDTH) + SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_LEFT)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST_WIDTH) + SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_RIGHT)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST_WIDTH);
            output_var = (output_var / SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_WIDTH)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_FIRST_WIDTH)) + 1;
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST)), output_var);

            //  update mid width
            output_var = m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID)) - SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_WIDTH)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID_WIDTH) + SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_LEFT)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID_WIDTH) + SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_RIGHT)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID_WIDTH);
            output_var = (output_var / SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_WIDTH)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_MID_WIDTH)) + 1;
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID)), output_var);

            // // update last width
            output_var = m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST)) - SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_WIDTH)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST_WIDTH) + SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_LEFT)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST_WIDTH) + SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_RIGHT)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST_WIDTH);
            output_var = (output_var / SExt(m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_WIDTH)), NVDLA_PDP_D_PARTIAL_WIDTH_IN_LAST_WIDTH)) + 1;
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST)), output_var);

            // update next state
            instr.SetUpdate(m.state("pdp_state"), Ite(m.state(GetVarName("group0_", NVDLA_PDP_POOLING_METHOD)) == PDP_MAXPOOL, MAXPOOL,
                                                      Ite(m.state(GetVarName("group0_", NVDLA_PDP_POOLING_METHOD)) == PDP_MINPOOL, MINPOOL, AVGPOOL)));

            // // update_pooling_stage (for split_width)
            instr.SetUpdate(m.state("pdp_pooling_stage_split_width"), SPLIT_STAGE_1);
        }




        {
            // max - pooling instruction
            auto instr = m.NewInstr("max_pool");
            instr.SetDecode(pdp_state == MAXPOOL);
            // instr.SetUpdate(m.state("pdp_state"), MAXPOOL);
            // pdp_state = MAXPOOL;

            // variables needed for max pooling
            auto input_height = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT));
            auto output_channel = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL));

            auto output_height = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT));
            auto output_width = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH));
            auto kernel_height = m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_HEIGHT));
            auto kernel_width = m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_WIDTH));
            auto stride_height = m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_HEIGHT));
            auto stride_width = m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_WIDTH));
            auto pdp_padding_value = m.state("pdp_padding_value");

            auto padding_left = m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_LEFT));
            auto padding_right = m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_RIGHT));
            auto padding_top = m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_TOP));
            auto padding_bottom = m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_BOTTOM));

            auto output_width_first = m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST));
            auto output_width_mid = m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID));
            auto output_width_last = m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST));

            auto data_format = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_FORMAT));
            auto mode = Ite(m.state(GetVarName("group0_", NVDLA_PDP_FLYING_MODE)) == BvConst(0, NVDLA_PDP_FLYING_MODE_WIDTH), PDP_FLYING, Ite(m.state(GetVarName("group0_", NVDLA_PDP_SPLIT_NUM)) > BvConst(0, NVDLA_PDP_SPLIT_NUM_WIDTH), PDP_OFF_FLYING_SPLIT, PDP_OFF_FLYING_NO_SPLIT));
            auto split_stage = m.state("pdp_pooling_stage_split_width");

            // update output width in use depending on mode
            output_width = Ite(mode == PDP_OFF_FLYING_NO_SPLIT, SExt(output_width_first, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH), Ite(mode == PDP_OFF_FLYING_SPLIT, Ite(split_stage == SPLIT_STAGE_1, SExt(output_width_first, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH), Ite(split_stage == SPLIT_STAGE_2, SExt(output_width_mid, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH), SExt(output_width_last, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH))), output_width));

            auto share_buffer_ptr = MemConst(0, {}, PDP_SHARE_LINE_ADDR_WIDTH, PDP_INT_16_WIDTH).get();
 

            for (auto output_j = 0; output_j < PDP_OUTPUT_MAX; output_j++)
            {
            
                auto max = BvConst(0, PDP_INT_16_WIDTH);

                for (int kernel_j = 0; kernel_j < PDP_KERNEL_MAX; kernel_j++)
                {
                   
                //    auto input_in_marker = BvConst(kernel_j,NVDLA_PDP_D_KERNEL_WIDTH_WIDTH) < kernel_width ? kernel_j : PDP_KERNEL_MAX - 1;
                    auto input_in = m.input(GetVarName("pdp_input_", std::to_string(output_j) + std::to_string(kernel_j)));
                    auto sign_ext_input = Ite(data_format == INT8, int8_to_int16(input_in), input_in);
                    auto curr = Ite(BvConst(kernel_j,NVDLA_PDP_D_KERNEL_WIDTH_WIDTH) < kernel_width,sign_ext_input, BvConst(0,PDP_INT_16_WIDTH));
                    max = Ite(sign_ext_input > max, sign_ext_input, max);
                }
              
                // update memory and increment memory pointer
                auto new_share_buffer = ExprRef(share_buffer_ptr).Store(BvConst(output_j, PDP_SHARE_LINE_ADDR_WIDTH),max);
                share_buffer_ptr = new_share_buffer.get();
            }

            // // load to buffer
            instr.SetUpdate(m.state("pdp_output"), ExprRef(share_buffer_ptr));
            instr.SetUpdate(m.state("pdp2csb_data_vld"),  SIG_TRUE);

            instr.SetUpdate(m.state("pdp_state"), Ite(m.input("pdp_last_input_batch") == BoolConst(true), START, MAXPOOL));
            instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_OP_ENABLE)), Ite(m.input("pdp_last_input_batch") == BoolConst(true), SIG_FALSE, SIG_TRUE));
        }











        // {
        //     // max - pooling instruction
        //     auto instr = m.NewInstr("max_pool");
        //     instr.SetDecode(pdp_state == MAXPOOL);
        //     // instr.SetUpdate(m.state("pdp_state"), MAXPOOL);
        //     // pdp_state = MAXPOOL;

        //     // variables needed for max pooling
        //     auto input_height = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT));
        //     auto output_channel = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL));

        //     auto output_height = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT));
        //     auto output_width = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH));
        //     auto kernel_height = m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_HEIGHT));
        //     auto kernel_width = m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_WIDTH));
        //     auto stride_height = m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_HEIGHT));
        //     auto stride_width = m.state(GetVarName("group0_", NVDLA_PDP_D_KERNEL_STRIDE_WIDTH));
        //     auto pdp_padding_value = m.state("pdp_padding_value");

        //     auto padding_left = m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_LEFT));
        //     auto padding_right = m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_RIGHT));
        //     auto padding_top = m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_TOP));
        //     auto padding_bottom = m.state(GetVarName("group0_", NVDLA_PDP_D_PAD_BOTTOM));

        //     auto output_width_first = m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST));
        //     auto output_width_mid = m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID));
        //     auto output_width_last = m.state(GetVarName("group0_", NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST));

        //     auto data_format = m.state(GetVarName("group0_", NVDLA_PDP_D_DATA_FORMAT));
        //     auto mode = Ite(m.state(GetVarName("group0_", NVDLA_PDP_FLYING_MODE)) == BvConst(0, NVDLA_PDP_FLYING_MODE_WIDTH), PDP_FLYING, Ite(m.state(GetVarName("group0_", NVDLA_PDP_SPLIT_NUM)) > BvConst(0, NVDLA_PDP_SPLIT_NUM_WIDTH), PDP_OFF_FLYING_SPLIT, PDP_OFF_FLYING_NO_SPLIT));
        //     auto split_stage = m.state("pdp_pooling_stage_split_width");

        //     // update output width in use depending on mode
        //     output_width = Ite(mode == PDP_OFF_FLYING_NO_SPLIT, SExt(output_width_first, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH), Ite(mode == PDP_OFF_FLYING_SPLIT, Ite(split_stage == SPLIT_STAGE_1, SExt(output_width_first, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH), Ite(split_stage == SPLIT_STAGE_2, SExt(output_width_mid, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH), SExt(output_width_last, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH))), output_width));

        //     // share line buffer
        //     auto share_buffer_ptr = MemConst(0, {}, PDP_SHARE_LINE_ADDR_WIDTH, PDP_INT_16_WIDTH).get();

        //     // for use in split width
        //     auto split_buffer_ptr = MemConst(0, {}, PDP_SPLIT_WIDTH_BUFFER_ADDR_WIDTH, PDP_INT_16_WIDTH).get();

        //     for (auto output_j = 0; output_j < PDP_OUTPUT_MAX; output_j++)
        //     {
        //         // skip output_update when operation is over
        //         auto skip_output_bv = Ite(BvConst(output_j, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH) < output_width, BoolConst(false), BoolConst(true));
        //         auto actual_output_j = Ite(skip_output_bv, output_width - 1, BvConst(output_j, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH));
        //         auto max = BvConst(0, PDP_INT_16_WIDTH);

        //         for (int kernel_j = 0; kernel_j < PDP_KERNEL_MAX; kernel_j++)
        //         {
        //             // auto curr = BvConst(0, PDP_INT_16_WIDTH);
        //             auto kernel_j_bv = BvConst(kernel_j, PDP_INT_16_WIDTH);
        //             auto actual_kernel_j = Ite(kernel_j_bv < SExt(kernel_width, PDP_INT_16_WIDTH), kernel_j_bv, SExt(kernel_width, PDP_INT_16_WIDTH) - 1);
        //             auto j = SExt(actual_output_j, PDP_INT_16_WIDTH) * SExt(stride_width, PDP_INT_16_WIDTH) + actual_kernel_j;
        //             auto input_j_marker = output_j + kernel_j;
        //             auto input_j_marker_bv = BvConst(input_j_marker, PDP_INT_16_WIDTH);
        //             auto input_in_marker = input_j_marker < PDP_OUTPUT_MAX ? input_j_marker : PDP_OUTPUT_MAX - 1;
        //             auto input_in = m.input(GetVarName("pdp_input_", std::to_string(input_in_marker)));
        //             auto sign_ext_input = Ite(data_format == INT8, int8_to_int16(input_in), input_in);

        //             auto curr = Ite(input_j_marker_bv == j, sign_ext_input, BvConst(0, PDP_INT_16_WIDTH));

        //             max = Ite(curr > max, curr, max);
        //         }
        //         auto curr_max = Load(m.state("pdp_share_line_buffer"), BvConst(output_j, PDP_SHARE_LINE_ADDR_WIDTH));

        //         skip_output_bv = Ite(max > curr_max, skip_output_bv, BoolConst(true));

        //         // update memory and increment memory pointer
        //         auto new_share_buffer = ExprRef(share_buffer_ptr).Store(BvConst(output_j, PDP_SHARE_LINE_ADDR_WIDTH), Ite(skip_output_bv, curr_max, max));
        //         share_buffer_ptr = new_share_buffer.get();
        //     }

        //     // // load to buffer
        //     instr.SetUpdate(m.state("pdp_share_line_buffer"), ExprRef(share_buffer_ptr));

            // auto kernel_height_marker = m.state("kernel_height_marker");
            // //   auto input_height_marker = m.state("input_height_marker");

    

            // kernel_height_marker = kernel_height_marker + 1;

            //     // check if output is ready
            // auto output_ready = Ite(kernel_height_marker == kernel_height, BoolConst(true), BoolConst(false));
            // kernel_height_marker = Ite(output_ready, BvConst(0, NVDLA_PDP_D_KERNEL_HEIGHT_WIDTH), kernel_height_marker);
            // instr.SetUpdate(m.state("kernel_height_marker"), kernel_height_marker);

            // //     // update output if ready
            // instr.SetUpdate(m.state("pdp2csb_data_vld"), Ite(output_ready, SIG_TRUE, m.state("pdp2csb_data_vld")));
            // instr.SetUpdate(m.state("pdp_output"), Ite(output_ready, m.state("pdp_share_line_buffer"), m.state("pdp_output")));

            // //     // reset share line buffer if output is ready
            // instr.SetUpdate(m.state("pdp_share_line_buffer"), Ite(output_ready, MemConst(0, {}, PDP_SHARE_LINE_ADDR_WIDTH, PDP_INT_16_WIDTH), m.state("pdp_share_line_buffer")));

            // instr.SetUpdate(m.state("pdp_state"), Ite(m.input("pdp_last_input_batch") == BoolConst(true), START, MAXPOOL));
            // instr.SetUpdate(m.state(GetVarName("group0_", NVDLA_PDP_D_OP_ENABLE)), Ite(m.input("pdp_last_input_batch") == BoolConst(true), SIG_FALSE, SIG_TRUE));
        //}

        // {
        //     // Max pooling option
        //     auto instr = m.NewInstr("max_pool");
        //     instr.SetDecode(pdp_state == LOAD);
        //     instr.SetUpdate(m.state("pdp_state"), MAXPOOL);
        //     pdp_state = MAXPOOL;

        //     auto input_height = m.state(NVDLA_PDP_D_DATA_CUBE_IN_HEIGHT);
        //     auto output_channel = m.state(NVDLA_PDP_D_DATA_CUBE_IN_CHANNEL);

        //     auto output_height = m.state(NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT);
        //     auto output_width = m.state(NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH);
        //     auto kernel_height = m.state(NVDLA_PDP_D_KERNEL_HEIGHT);
        //     auto kernel_width = m.state(NVDLA_PDP_D_KERNEL_WIDTH);
        //     auto stride_height = m.state(NVDLA_PDP_D_KERNEL_STRIDE_HEIGHT);
        //     auto stride_width = m.state(NVDLA_PDP_D_KERNEL_STRIDE_WIDTH);
        //     auto pdp_padding_value = m.state("pdp_padding_value");

        //     auto padding_left = m.state(NVDLA_PDP_D_PAD_LEFT);
        //     auto padding_right = m.state(NVDLA_PDP_D_PAD_RIGHT);
        //     auto padding_top = m.state(NVDLA_PDP_D_PAD_TOP);
        //     auto padding_bottom = m.state(NVDLA_PDP_D_PAD_BOTTOM);

        //     auto output_width_first = m.state(NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST);
        //     auto output_width_mid = m.state(NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID);
        //     auto output_width_last = m.state(NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST);

        //     auto data_format = m.state(NVDLA_PDP_D_DATA_FORMAT);

        //     auto mem_ptr = MemConst(0, {}, PDP_OUTPUT_ADDR_WIDTH, PDP_INT_16_WIDTH).get();
        //     auto output_k = output_channel - output_channel;
        //     auto skip1 = output_k < output_channel;
        //     // auto output_k = output_channel - output_channel;

        //     //  while(output_k < output_channel)
        //     // for (auto output_k = output_channel - output_channel; (output_channel - output_k) != BvConst(0,output_channel.bit_width());)
        //     // while(output_k < output_channel)
        //     // auto channel_continue = Ite(output_channel > BvConst(0,1),BoolConst(true),BoolConst(false));

        //     // chan loop variables
        //     auto channel_cond = Ite(output_channel > BvConst(0, 1), LOOP_TRUE_BV, LOOP_FALSE_BV);
        //     bool chan_loop_cond = channel_cond.bit_width() == LOOP_TRUE;
        //     auto chan_loop_bv = BvConst(0, NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL_WIDTH);

        //     // chan loop
        //     for (auto output_k = 0; output_k < OUTPUT; output_k++)

        //     for (auto output_k = 0; chan_loop_cond; output_k++)
        //     {
        //         // height loop variables
        //         auto height_cond = Ite(output_height > BvConst(0, 1), LOOP_TRUE_BV, LOOP_FALSE_BV);
        //         bool height_loop_cond = height_cond.bit_width() == LOOP_TRUE;
        //         auto height_loop_bv = BvConst(0, NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT_WIDTH);

        //         // height loop
        //         for (auto output_i = 0; height_loop_cond; output_i++)
        //         {

        //             // width loop variables
        //             auto width_cond = Ite(output_width > BvConst(0, 1), LOOP_TRUE_BV, LOOP_FALSE_BV);
        //             bool width_loop_cond = width_cond.bit_width() == LOOP_TRUE;
        //             auto width_loop_bv = BvConst(0, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH);

        //             // width loop
        //             for (auto output_j = 0; width_loop_cond; output_j++)
        //             {
        //                 auto mem_addr = BvConst(output_i, NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT_WIDTH) * output_width + BvConst(output_j, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH);
        //                 // auto max = Load(ExprRef(mem_ptr), BvConst(mem_addr, PDP_OUTPUT_ADDR_WIDTH));
        //                 auto max = Load(ExprRef(mem_ptr), mem_addr);

        //                 // kernel height loop variables
        //                 auto kernel_height_cond = Ite(kernel_height > BvConst(0, 1), LOOP_TRUE_BV, LOOP_FALSE_BV);
        //                 bool kernel_height_loop_cond = kernel_height_cond.bit_width() == LOOP_TRUE;
        //                 auto kernel_height_loop_bv = BvConst(0, NVDLA_PDP_D_KERNEL_HEIGHT_WIDTH);

        //                 // kernel height loop
        //                 for (auto kernel_i = 0; kernel_height_loop_cond; kernel_i++)
        //                 {
        //                     // kernel width loop variables
        //                     auto kernel_width_cond = Ite(kernel_width > BvConst(0, 1), LOOP_TRUE_BV, LOOP_FALSE_BV);
        //                     bool kernel_width_loop_cond = kernel_width_cond.bit_width() == LOOP_TRUE;
        //                     auto kernel_width_loop_bv = BvConst(0, NVDLA_PDP_D_KERNEL_WIDTH_WIDTH);

        //                     // kernel width loop
        //                     for (auto kernel_j = 0; kernel_width_loop_cond; kernel_j++)
        //                     {
        //                         // load from memory and read
        //                         // assumes they don't stride out of input (kernel and stride fit perfectly)

        //                         auto i = BvConst(output_i, NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT_WIDTH) * stride_height + BvConst(kernel_i, NVDLA_PDP_D_KERNEL_HEIGHT_WIDTH);
        //                         auto actual_i = i;
        //                         auto curr = BvConst(SHRT_MIN, PDP_INT_16_WIDTH);
        //                         auto skip_input = BoolConst(false);

        //                         // update if there is vertical padding
        //                         actual_i = Ite(padding_top > 0, Ite(i < padding_top, BvConst(0, PDP_INT_16_WIDTH), Ite((i - padding_top) < input_height, i - padding_top, Ite(padding_bottom > 0, input_height - 1, i))), i);
        //                         skip_input = Ite(padding_top > 0, Ite(i < padding_top, BoolConst(true), Ite(padding_bottom > 0, BoolConst(true), BoolConst(false))), BoolConst(false));
        //                         curr = Ite(skip_input, pdp_padding_value, curr);

        //                         auto j = BvConst(output_j, NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH_WIDTH) * stride_width + BvConst(kernel_j, NVDLA_PDP_D_KERNEL_WIDTH_WIDTH);
        //                         auto actual_j = j;

        //                         // update if there is horizontal padding
        //                         actual_j = Ite(padding_left > 0, Ite(i < padding_left, BvConst(0, PDP_INT_16_WIDTH), Ite((i - padding_left) < input_height, i - padding_left, Ite(padding_bottom > 0, input_height - 1, i))), i);
        //                         skip_input = Ite(padding_left > 0, Ite(i < padding_left, BoolConst(true), Ite(padding_right > 0, BoolConst(true), skip_input)), skip_input);

        //                         // auto input_curr = int8_to_int_16(m.inputGetVarName("pdp_input_chan_", (std::to_string(k)) + "_" + (std::to_string(i)) + "_" + (std::to_string(j))), data_format);
        //                         auto input_curr = SExt(m.input(GetVarName("pdp_input_chan_", (std::to_string(output_k)) + "_" + (std::to_string(i)) + "_" + (std::to_string(j)))), 16);

        //                         curr = Ite(skip_input, pdp_padding_value, input_curr);

        //                         // auto mem_addr = output_j + output_i;
        //                         // auto max = Load(ExprRef(mem_ptr), BvConst(mem_addr, 4));

        //                         instr.SetUpdate(max, Ite(curr > max, curr, max));
        //                         // outputarr[output_i][output_j]

        //                         // auto new_mem = ExprRef(mem_ptr).Store(BvConst(mem_addr, 4), max);
        //                         // mem_ptr = new_mem.get();

        //                         // kernel width loop update
        //                         kernel_width_loop_bv = kernel_width_loop_bv + 1;
        //                         kernel_width_cond = new auto(Ite(kernel_width_loop_bv < kernel_width, LOOP_TRUE_BV, LOOP_FALSE_BV));
        //                         kernel_width_loop_cond = kernel_width_cond.bit_width() == LOOP_TRUE;
        //                     }

        //                     // kernel height loop update
        //                     kernel_height_loop_bv = kernel_height_loop_bv + 1;
        //                     kernel_height_cond = new auto(Ite(kernel_height_loop_bv < kernel_height, LOOP_TRUE_BV, LOOP_FALSE_BV));
        //                     kernel_height_loop_cond = kernel_height_cond.bit_width() == LOOP_TRUE;
        //                 }

        //                 auto new_mem = ExprRef(mem_ptr).Store(BvConst(mem_addr, PDP_OUTPUT_ADDR_WIDTH), max);
        //                 mem_ptr = new_mem.get();

        //                 // width loop update
        //                 width_loop_bv = width_loop_bv + 1;
        //                 width_cond = new auto(Ite(width_loop_bv < output_width, LOOP_TRUE_BV, LOOP_FALSE_BV));
        //                 width_loop_cond = width_cond.bit_width() == LOOP_TRUE;
        //                 // instr.SetUpdate(inputarr[i][j],Extract(m.input("pdp_input"+ (std::to_string(counter))), 31, 0 ));
        //                 // instr.SetUpdate(m.state("pdp_input"+ (std::to_string(counter))), );
        //                 // counter = counter + BvConst(1,5)
        //             }

        //             // height loop update
        //             height_loop_bv = height_loop_bv + 1;
        //             height_cond = new auto(Ite(height_loop_bv < output_height, LOOP_TRUE_BV, LOOP_FALSE_BV));
        //             height_loop_cond = height_cond.bit_width() == LOOP_TRUE;
        //         }

        //         // chan loop update
        //         chan_loop_bv = chan_loop_bv + 1;
        //         channel_cond = new auto(Ite(chan_loop_bv < output_channel, LOOP_TRUE_BV, LOOP_FALSE_BV));
        //         chan_loop_cond = channel_cond.bit_width() == LOOP_TRUE;
        //     }
        //     instr.SetUpdate(pdp_state, Ite(m.input("pdp_input_done"), START, LOAD));
        // }

        // {
        //     // Min pooling option
        //     auto instr = m.NewInstr("min_pool");
        //     instr.SetDecode(pdp_state == LOAD);
        //     instr.SetUpdate(m.state("pdp_state"), MINPOOL);
        //     pdp_state = MINPOOL;

        //     auto output_channel = m.state(NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL);
        //     auto output_height = m.state(NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT);
        //     auto output_width = m.state(NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH);
        //     auto kernel_height = m.state(NVDLA_PDP_D_KERNEL_HEIGHT);
        //     auto kernel_width = m.state(NVDLA_PDP_D_KERNEL_WIDTH);
        //     auto stride_height = m.state(NVDLA_PDP_D_KERNEL_STRIDE_HEIGHT);
        //     auto stride_width = m.state(NVDLA_PDP_D_KERNEL_STRIDE_WIDTH);
        //     auto pdp_padding_value = m.state("pdp_padding_value");

        //     auto output_width_first = m.state(NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST);
        //     auto output_width_mid = m.state(NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID);
        //     auto output_width_last = m.state(NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST);

        //     auto data_format = m.state(NVDLA_PDP_D_DATA_FORMAT);

        //     auto mem_ptr = MemConst(0, {}, PDP_OUTPUT_ADDR_WIDTH, PDP_INT_16_WIDTH).get();
        //     for (auto output_k = 0; output_k < output_channel; output_k++)
        //     {
        //         for (auto output_i = 0; output_i < output_height; output_i++)
        //         {
        //             for (auto output_j = 0; output_j < output_width; output_j++)
        //             {
        //                 auto mem_addr = output_i * output_width + output_j;
        //                 auto min = Load(ExprRef(mem_ptr), BvConst(mem_addr, PDP_OUTPUT_ADDR_WIDTH));
        //                 for (auto kernel_i = 0; kernel_i < kernel_height; kernel_i++)
        //                 {
        //                     for (auto kernel_j = 0; kernel_j < kernel_width; kernel_j++)
        //                     {
        //                         // load from memory and read
        //                         // assumes they don't stride out of input (kernel and stride fit perfectly)

        //                         auto i = output_i * stride_height + kernel_i;
        //                         auto actual_i = i;
        //                         auto curr = BvConst(SHRT_MAX, PDP_INT_16_WIDTH);
        //                         auto skip_input = BoolConst(false);

        //                         // update if there is vertical padding
        //                         actual_i = Ite(padding_top > 0, Ite(i < padding_top, 0, Ite((i - padding_top) < input_height, i - padding_top, Ite(padding_bottom > 0, input_height - 1, i))), i);
        //                         skip_input = Ite(padding_top > 0, Ite(i < padding_top, true, Ite(padding_bottom > 0, true, false)), false);
        //                         curr = Ite(skip_input, pdp_padding_value, curr);

        //                         auto j = output_j * stride_width + kernel_j;
        //                         auto actual_j = j;

        //                         // update if there is horizontal padding
        //                         actual_j = Ite(padding_left > 0, Ite(i < padding_left, 0, Ite((i - padding_left) < input_height, i - padding_left, Ite(padding_bottom > 0, input_height - 1, i))), i);
        //                         skip_input = Ite(padding_left > 0, Ite(i < padding_left, true, Ite(padding_right > 0, true, skip_input)), skip_input);

        //                         auto input_curr = int8_to_int_16(GetVarName("pdp_input_chan_", (std::to_string(k)) + "_" + (std::to_string(i)) + "_" + (std::to_string(j))), data_format);
        //                         curr = Ite(skip_input, pdp_padding_value, input_curr);

        //                         // auto mem_addr = output_j + output_i;
        //                         // auto min = Load(ExprRef(mem_ptr), BvConst(mem_addr, 4));

        //                         instr.SetUpdate(min, Ite(curr < min, curr, min));
        //                         // outputarr[output_i][output_j]

        //                         // auto new_mem = ExprRef(mem_ptr).Store(BvConst(mem_addr, 4), min);
        //                         // mem_ptr = new_mem.get();
        //                     }
        //                 }

        //                 auto new_mem = ExprRef(mem_ptr).Store(BvConst(mem_addr, PDP_OUTPUT_ADDR_WIDTH), min);
        //                 mem_ptr = new_mem.get();
        //                 // instr.SetUpdate(inputarr[i][j],Extract(m.input("pdp_input"+ (std::to_string(counter))), 31, 0 ));
        //                 // instr.SetUpdate(m.state("pdp_input"+ (std::to_string(counter))), );
        //                 // counter = counter + BvConst(1,5)
        //             }
        //         }
        //         instr.SetUpdate(pdp_state, Ite(m.input("pdp_input_done"), START, LOAD));
        //     }
        // }

        // {
        //     // average pooling option
        //     auto instr = m.NewInstr("avg_pool");
        //     instr.SetDecode(pdp_state == LOAD);
        //     instr.SetUpdate(m.state("pdp_state"), AVGPOOL);
        //     pdp_state = AVGPOOL;

        //     auto output_channel = m.state(NVDLA_PDP_D_DATA_CUBE_OUT_CHANNEL);
        //     auto output_height = m.state(NVDLA_PDP_D_DATA_CUBE_OUT_HEIGHT);
        //     auto output_width = m.state(NVDLA_PDP_D_DATA_CUBE_OUT_WIDTH);
        //     auto kernel_height = m.state(NVDLA_PDP_D_KERNEL_HEIGHT);
        //     auto kernel_width = m.state(NVDLA_PDP_D_KERNEL_WIDTH);
        //     auto stride_height = m.state(NVDLA_PDP_D_KERNEL_STRIDE_HEIGHT);
        //     auto stride_width = m.state(NVDLA_PDP_D_KERNEL_STRIDE_WIDTH);
        //     auto pdp_padding_value = m.state("pdp_padding_value");

        //     auto output_width_first = m.state(NVDLA_PDP_D_PARTIAL_WIDTH_OUT_FIRST);
        //     auto output_width_mid = m.state(NVDLA_PDP_D_PARTIAL_WIDTH_OUT_MID);
        //     auto output_width_last = m.state(NVDLA_PDP_D_PARTIAL_WIDTH_OUT_LAST);

        //     auto data_format = m.state(NVDLA_PDP_D_DATA_FORMAT);

        //     auto mem_ptr = MemConst(0, {}, PDP_OUTPUT_ADDR_WIDTH, PDP_INT_16_WIDTH).get();
        //     for (auto output_k = 0; output_k < output_channel; output_k++)
        //     {
        //         for (auto output_i = 0; output_i < output_height; output_i++)
        //         {
        //             for (auto output_j = 0; output_j < output_width; output_j++)
        //             {
        //                 auto sum = BvConst(0, PDP_INT_16_WIDTH);
        //                 auto mem_addr = output_i * output_width + output_j;
        //                 auto avg = Load(ExprRef(mem_ptr), BvConst(mem_addr, PDP_OUTPUT_ADDR_WIDTH));
        //                 for (auto kernel_i = 0; kernel_i < kernel_height; kernel_i++)
        //                 {
        //                     for (auto kernel_j = 0; kernel_j < kernel_width; kernel_j++)
        //                     {
        //                         // load from memory and read
        //                         // assumes they don't stride out of input (kernel and stride fit perfectly)

        //                         auto i = output_i * stride_height + kernel_i;
        //                         auto actual_i = i;
        //                         auto curr = BvConst(SHRT_MIN, PDP_INT_16_WIDTH);
        //                         auto skip_input = BoolConst(false);

        //                         // update if there is vertical padding
        //                         actual_i = Ite(padding_top > 0, Ite(i < padding_top, 0, Ite((i - padding_top) < input_height, i - padding_top, Ite(padding_bottom > 0, input_height - 1, i))), i);
        //                         skip_input = Ite(padding_top > 0, Ite(i < padding_top, true, Ite(padding_bottom > 0, true, false)), false);
        //                         curr = Ite(skip_input, pdp_padding_value, curr);

        //                         auto j = output_j * stride_width + kernel_j;
        //                         auto actual_j = j;

        //                         // update if there is horizontal padding
        //                         actual_j = Ite(padding_left > 0, Ite(i < padding_left, 0, Ite((i - padding_left) < input_height, i - padding_left, Ite(padding_bottom > 0, input_height - 1, i))), i);
        //                         skip_input = Ite(padding_left > 0, Ite(i < padding_left, true, Ite(padding_right > 0, true, skip_input)), skip_input);

        //                         auto input_curr = int8_to_int_16(GetVarName("pdp_input_chan_", (std::to_string(k)) + "_" + (std::to_string(i)) + "_" + (std::to_string(j))), data_format);
        //                         curr = Ite(skip_input, pdp_padding_value, input_curr);

        //                         // auto mem_addr = output_j + output_i;
        //                         // auto min = Load(ExprRef(mem_ptr), BvConst(mem_addr, 4));

        //                         sum = sum + curr;
        //                     }
        //                 }
        //                 avg = sum / kernel_elements;
        //                 // outputarr[output_i][output_j]

        //                 auto new_mem = ExprRef(mem_ptr).Store(BvConst(mem_addr, PDP_OUTPUT_ADDR_WIDTH), avg);
        //                 mem_ptr = new_mem.get();

        //                 // instr.SetUpdate(inputarr[i][j],Extract(m.input("pdp_input"+ (std::to_string(counter))), 31, 0 ));
        //                 // instr.SetUpdate(m.state("pdp_input"+ (std::to_string(counter))), );
        //                 // counter = counter + BvConst(1,5)
        //             }
        //         }
        //         instr.SetUpdate(pdp_state, Ite(m.input("pdp_input_done"), START, LOAD));
        //     }
        // }

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