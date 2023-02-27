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
        // /****************************************************************************/
        // // ********************** FROM CSB ******************************************//
        // /***************************************************************************/
        m.NewBvInput("csb2pdp_addr", 16);
        m.NewBvInput("csb2pdp_data", 32);
        m.NewBvInput("csb2pdp_write", 1); // 0 - read request; 1  write request
        m.NewBvInput("csb2pdp_vld", 1);

      

        // /****************************************************************************/
        // // ********************* INPUT DATA FROM SDP or PDMA*************************//
        // /***************************************************************************/

        for (auto i = 0; i < PDP_INPUT_CHANNEL_MAX; i++)
        {
            for (auto j = 0; j < PDP_INPUT_HEIGHT_MAX; j++)
            {
                for (auto k = 0; k < PDP_INPUT_WIDTH_MAX; k++)
                {
                    m.NewBvInput(GetVarName("pdp_input_chan_", (std::to_string(i)) + "_" + (std::to_string(j)) + "_" + (std::to_string(k))), PDP_INT_16_WIDTH);
                }
            }
        }

// Control Signals
         m.NewBvInput("pdp_input_done", 1); // is it last pdp input

        // Control Signals
        // m.NewBvInput("pending_clr", 1);
        // m.NewBvInput("sg2dl_vld", 1);
        // m.NewBvInput("sg2wt_vld", 1);
        // m.NewBvInput("fifo_clr", 1);
        // m.NewBvInput("done", 1);
    }

} // namespace ilang