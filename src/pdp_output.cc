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

// File: pdp_output.cc

#include <ilang/ilang++.h>

#include <pdp_config.h>

namespace ilang
{

    // Define PDP outputs
    void DefinePDPOutput(Ila &m)
    {

        // /****************************************************************************/
        // // ********************** TO CSB ******************************************//
        // /***************************************************************************/

        m.NewBvState("pdp2csb_rdy", 1);
        m.NewBvState("pdp2csb_data_vld", 1); // true when output is valid
          
        // to RAM  
        m.NewMemState("pdp_output_1", PDP_OUTPUT_ADDR_WIDTH, PDP_INT_16_WIDTH); // 2^13- holds 8191 output

        
    
    }

} // namespace ilang