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

namespace ilang {

void DefinePDPInput(Ila& m) {
    // CSB MMIO
    // Total should be 63 bits, omit 8 bits for now
    m.NewBvInput("csb_addr", 22); // need to offset for 2 bit
    m.NewBvInput("csb_data", 32);
    m.NewBvInput("csb_write", 1);
    // m.NewBvInput("csb_other", 8);
    m.NewBvInput("csb_vld", 1);

    //input
     for (int i = 0; i < 16; i++) {
        // Primary inputs
        m.NewBvInput(GetVarName("pdp_input", (std::to_string(i))), 32);
     }

    // Control Signals
    // m.NewBvInput("pending_clr", 1);
    // m.NewBvInput("sg2dl_vld", 1);
    // m.NewBvInput("sg2wt_vld", 1);
    // m.NewBvInput("fifo_clr", 1);
    // m.NewBvInput("done", 1);
}


} // namespace ilang