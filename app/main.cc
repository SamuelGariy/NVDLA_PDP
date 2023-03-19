// =============================================================================
// MIT License
//
// Copyright (c) 2019 Princeton University
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

// File: main.cc
#include <pdp.h>

#include <ilang/ilang++.h>
#include <ilang/util/log.h>
#include <iostream>
//#include <ilang/vtarget-out/vtarget_gen.h>
using namespace std;

using namespace ilang;
//TODO: Update main.cc and start testing

int main(int argc, char* argv[]) {
  SetToStdErr(1);

  cout << "start";
  // get the ILA model
  auto pdp = GetPDPIla("pdp");

  ILA_INFO << "#instr: " << pdp.instr_num();
  for (size_t i = 0; i < pdp.instr_num(); i++) {
    ILA_INFO << pdp.instr(i);
  }

  ILA_INFO << "#state: " << pdp.state_num();
  // auto total = 0;
  for (size_t i = 0; i < pdp.state_num(); i++) {
    ILA_INFO << pdp.state(i);
    // total += pdp.state(i).bit_width();
  }
  // cout << "\n";
  // cout << total;
  // cout << "\n";

  ILA_INFO << "#input: " << pdp.input_num();
  for (size_t i = 0; i < pdp.input_num(); i++) {
    ILA_INFO << pdp.input(i);
  }

 std::vector<std::string> pdp_design_files = {
   "NV_NVDLA_pdp_top.v"
 };

//  auto vtg_cfg = SetConfiguration();

//  verify_csc(csc, vtg_cfg, csc_design_files);

  //ExportSysCSim(pdp, "./sim_model", false); 
  ExportSysCSim(pdp, "./sim_model");  

  return 0;
}

