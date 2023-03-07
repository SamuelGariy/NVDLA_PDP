#include <systemc>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>

#include "nlohmann/json.hpp"
#include <pdp.h>

using json = nlohmann::json;

#define GET_JSON_INT(json_val, default_val) (!(json_val.is_null()) ? json_val.get<int>() : default_val)
#define GET_JSON_INT_FROM_HEX_STR(json_val, default_val) (!(json_val.is_null()) ? (std::stoi(json_val.get<std::string>().c_str(), nullptr, 16)) : default_val)
#define GET_JSON_BOOL(json_val, default_val) (!(json_val.is_null()) ? json_val.get<bool>() : default_val)

std::string file_in;
std::string file_out;

#define PDP_KERNEL_MAX 16

// Module for reading inputs into ILA model
SC_MODULE(Source)
{
  sc_in<bool> clk{"clk"};

  // CSB inputs
  sc_out<sc_biguint<16>> pdp_csb2pdp_addr;
  sc_out<sc_biguint<32>> pdp_csb2pdp_data;
  sc_out<sc_biguint<1>> pdp_csb2pdp_write;
  sc_out<sc_biguint<1>> pdp_csb2pdp_vld;

  // PDP control signals
  sc_out<bool> pdp_pdp_last_input_batch;

  // PDP array inputs

  sc_out<sc_biguint<16>> pdp_pdp_input_0[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_1[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_2[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_3[PDP_KERNEL_MAX];

  sc_out<sc_biguint<16>> pdp_pdp_input_4[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_5[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_6[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_7[PDP_KERNEL_MAX];

  sc_out<sc_biguint<16>> pdp_pdp_input_8[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_9[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_10[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_11[PDP_KERNEL_MAX];

  sc_out<sc_biguint<16>> pdp_pdp_input_12[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_13[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_14[PDP_KERNEL_MAX];
  sc_out<sc_biguint<16>> pdp_pdp_input_15[PDP_KERNEL_MAX];

  sc_out<sc_biguint<1>> input_done;

  SC_CTOR(Source)
  {
    SC_THREAD(source_input);
    sensitive << clk.pos();
  }

  void source_input()
  {
    // reset the ports

    // CSB inputs
    pdp_csb2pdp_addr = 0;
    pdp_csb2pdp_data = 0;
    pdp_csb2pdp_write = 0;
    pdp_csb2pdp_vld = 0;

    // PDP control signals
    pdp_pdp_last_input_batch = false;

    std::fill(pdp_pdp_input_0, pdp_pdp_input_0 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_1, pdp_pdp_input_1 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_2, pdp_pdp_input_2 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_3, pdp_pdp_input_3 + PDP_KERNEL_MAX, 0);

    std::fill(pdp_pdp_input_4, pdp_pdp_input_4 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_5, pdp_pdp_input_5 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_6, pdp_pdp_input_6 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_7, pdp_pdp_input_7 + PDP_KERNEL_MAX, 0);

    std::fill(pdp_pdp_input_8, pdp_pdp_input_8 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_9, pdp_pdp_input_9 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_10, pdp_pdp_input_10 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_11, pdp_pdp_input_11 + PDP_KERNEL_MAX, 0);

    std::fill(pdp_pdp_input_12, pdp_pdp_input_12 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_13, pdp_pdp_input_13 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_14, pdp_pdp_input_14 + PDP_KERNEL_MAX, 0);
    std::fill(pdp_pdp_input_15, pdp_pdp_input_15 + PDP_KERNEL_MAX, 0);

    input_done = 0;

    // read program fragment from file
    std::ifstream fin;
    fin.open(file_in, ios::in);

    json cmd_seq;
    cmd_seq = json::parse(fin);

    // Pass the command to the ports
    for (size_t i = 0; i < cmd_seq["program fragment"].size(); i++)
    {
      pdp_csb2pdp_addr = GET_JSON_INT_FROM_HEX_STR(cmd_seq["program fragment"][i]["pdp_csb2pdp_addr"], 0);
      pdp_csb2pdp_data = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_csb2pdp_data"], 0);
      pdp_csb2pdp_write = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_csb2pdp_write"], 0);
      pdp_csb2pdp_vld = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_csb2pdp_vld"], 0);

      pdp_pdp_last_input_batch = GET_JSON_BOOL(cmd_seq["program fragment"][i]["pdp_pdp_last_input_batch"], false);

      // Read in array data
      for (size_t j = 0; j < PDP_KERNEL_MAX; j++)
      {

        pdp_pdp_input_0[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_0_" + std::to_string(j)], 0);
        pdp_pdp_input_1[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_1_" + std::to_string(j)], 0);
        pdp_pdp_input_2[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_2_" + std::to_string(j)], 0);
        pdp_pdp_input_3[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_3_" + std::to_string(j)], 0);

        pdp_pdp_input_4[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_4_" + std::to_string(j)], 0);
        pdp_pdp_input_5[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_5_" + std::to_string(j)], 0);
        pdp_pdp_input_6[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_6_" + std::to_string(j)], 0);
        pdp_pdp_input_7[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_7_" + std::to_string(j)], 0);

        pdp_pdp_input_8[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_8_" + std::to_string(j)], 0);
        pdp_pdp_input_9[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_9_" + std::to_string(j)], 0);
        pdp_pdp_input_10[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_10_" + std::to_string(j)], 0);
        pdp_pdp_input_11[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_11_" + std::to_string(j)], 0);

        pdp_pdp_input_12[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_12_" + std::to_string(j)], 0);
        pdp_pdp_input_13[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_13_" + std::to_string(j)], 0);
        pdp_pdp_input_14[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_14_" + std::to_string(j)], 0);
        pdp_pdp_input_15[j] = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_15_" + std::to_string(j)], 0);
      }

      wait(10, SC_NS);
    }

    input_done = 1;
    std::cout << "read_file" << std::flush;
  }
};

// Link input data to SystemC model
SC_MODULE(testbench)
{
  pdp pdp_inst;
  Source src;

  sc_clock clk;

  sc_signal<sc_biguint<16>> pdp_csb2pdp_addr_signal;
  sc_signal<sc_biguint<32>> pdp_csb2pdp_data_signal;
  sc_signal<sc_biguint<1>> pdp_csb2pdp_write_signal;
  sc_signal<sc_biguint<1>> pdp_csb2pdp_vld_signal;

  sc_signal<bool> pdp_pdp_last_input_batch;

  sc_signal<sc_biguint<16>> pdp_pdp_input_0_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_1_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_2_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_3_signal[PDP_KERNEL_MAX];

  sc_signal<sc_biguint<16>> pdp_pdp_input_4_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_5_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_6_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_7_signal[PDP_KERNEL_MAX];

  sc_signal<sc_biguint<16>> pdp_pdp_input_8_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_9_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_10_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_11_signal[PDP_KERNEL_MAX];

  sc_signal<sc_biguint<16>> pdp_pdp_input_12_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_13_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_14_signal[PDP_KERNEL_MAX];
  sc_signal<sc_biguint<16>> pdp_pdp_input_15_signal[PDP_KERNEL_MAX];

  sc_signal<sc_biguint<1>> input_done;

  SC_CTOR(testbench) : clk("clk", 1, SC_NS),
                       pdp_inst("pdp_inst"),
                       src("source")
  {
    // Read in signals from the prog_frag file
    src.clk(clk);

    src.pdp_csb2pdp_addr(pdp_csb2pdp_addr_signal);
    src.pdp_csb2pdp_data(pdp_csb2pdp_data_signal);
    src.pdp_csb2pdp_write(pdp_csb2pdp_write_signal);
    src.pdp_csb2pdp_vld(pdp_csb2pdp_vld_signal);

    src.pdp_pdp_last_input_batch(pdp_pdp_last_input_batch_signal);

    for (size_t i = 0; i < PDP_KERNEL_MAX; i++)
    {

      src.pdp_pdp_input_0[i](pdp_pdp_input_0_signal[i]);
      src.pdp_pdp_input_1[i](pdp_pdp_input_1_signal[i]);
      src.pdp_pdp_input_2[i](pdp_pdp_input_2_signal[i]);
      src.pdp_pdp_input_3[i](pdp_pdp_input_3_signal[i]);

      src.pdp_pdp_input_4[i](pdp_pdp_input_4_signal[i]);
      src.pdp_pdp_input_5[i](pdp_pdp_input_5_signal[i]);
      src.pdp_pdp_input_6[i](pdp_pdp_input_6_signal[i]);
      src.pdp_pdp_input_7[i](pdp_pdp_input_7_signal[i]);

      src.pdp_pdp_input_8[i](pdp_pdp_input_8_signal[i]);
      src.pdp_pdp_input_9[i](pdp_pdp_input_9_signal[i]);
      src.pdp_pdp_input_10[i](pdp_pdp_input_10_signal[i]);
      src.pdp_pdp_input_11[i](pdp_pdp_input_11_signal[i]);

      src.pdp_pdp_input_12[i](pdp_pdp_input_12_signal[i]);
      src.pdp_pdp_input_13[i](pdp_pdp_input_13_signal[i]);
      src.pdp_pdp_input_14[i](pdp_pdp_input_14_signal[i]);
      src.pdp_pdp_input_15[i](pdp_pdp_input_15_signal[i]);
    }

    src.input_done(input_done);

    // Link with the pdp.h SystemC model

    pdp_inst.pdp_csb2pdp_addr_in(pdp_csb2pdp_addr_signal);
    pdp_inst.pdp_csb2pdp_data_in(pdp_csb2pdp_data_signal);
    pdp_inst.pdp_csb2pdp_write_in(pdp_csb2pdp_write_signal);
    pdp_inst.pdp_csb2pdp_vld_in(pdp_csb2pdp_vld_signal);

    pdp_inst.pdp_pdp_last_input_batch_in(pdp_pdp_last_input_batch_signal);

    pdp_inst.pdp_pdp_input_0_0_in(pdp_pdp_input_0_signal[0]);
    pdp_inst.pdp_pdp_input_0_1_in(pdp_pdp_input_0_signal[1]);
    pdp_inst.pdp_pdp_input_0_2_in(pdp_pdp_input_0_signal[2]);
    pdp_inst.pdp_pdp_input_0_3_in(pdp_pdp_input_0_signal[3]);
    pdp_inst.pdp_pdp_input_0_4_in(pdp_pdp_input_0_signal[4]);
    pdp_inst.pdp_pdp_input_0_5_in(pdp_pdp_input_0_signal[5]);
    pdp_inst.pdp_pdp_input_0_6_in(pdp_pdp_input_0_signal[6]);
    pdp_inst.pdp_pdp_input_0_7_in(pdp_pdp_input_0_signal[7]);
    pdp_inst.pdp_pdp_input_0_8_in(pdp_pdp_input_0_signal[8]);
    pdp_inst.pdp_pdp_input_0_9_in(pdp_pdp_input_0_signal[9]);
    pdp_inst.pdp_pdp_input_0_10_in(pdp_pdp_input_0_signal[10]);
    pdp_inst.pdp_pdp_input_0_11_in(pdp_pdp_input_0_signal[11]);
    pdp_inst.pdp_pdp_input_0_12_in(pdp_pdp_input_0_signal[12]);
    pdp_inst.pdp_pdp_input_0_13_in(pdp_pdp_input_0_signal[13]);
    pdp_inst.pdp_pdp_input_0_14_in(pdp_pdp_input_0_signal[14]);
    pdp_inst.pdp_pdp_input_0_15_in(pdp_pdp_input_0_signal[15]);

    pdp_inst.pdp_pdp_input_1_0_in(pdp_pdp_input_1_signal[0]);
    pdp_inst.pdp_pdp_input_1_1_in(pdp_pdp_input_1_signal[1]);
    pdp_inst.pdp_pdp_input_1_2_in(pdp_pdp_input_1_signal[2]);
    pdp_inst.pdp_pdp_input_1_3_in(pdp_pdp_input_1_signal[3]);
    pdp_inst.pdp_pdp_input_1_4_in(pdp_pdp_input_1_signal[4]);
    pdp_inst.pdp_pdp_input_1_5_in(pdp_pdp_input_1_signal[5]);
    pdp_inst.pdp_pdp_input_1_6_in(pdp_pdp_input_1_signal[6]);
    pdp_inst.pdp_pdp_input_1_7_in(pdp_pdp_input_1_signal[7]);
    pdp_inst.pdp_pdp_input_1_8_in(pdp_pdp_input_1_signal[8]);
    pdp_inst.pdp_pdp_input_1_9_in(pdp_pdp_input_1_signal[9]);
    pdp_inst.pdp_pdp_input_1_10_in(pdp_pdp_input_1_signal[10]);
    pdp_inst.pdp_pdp_input_1_11_in(pdp_pdp_input_1_signal[11]);
    pdp_inst.pdp_pdp_input_1_12_in(pdp_pdp_input_1_signal[12]);
    pdp_inst.pdp_pdp_input_1_13_in(pdp_pdp_input_1_signal[13]);
    pdp_inst.pdp_pdp_input_1_14_in(pdp_pdp_input_1_signal[14]);
    pdp_inst.pdp_pdp_input_1_15_in(pdp_pdp_input_1_signal[15]);

    pdp_inst.pdp_pdp_input_2_0_in(pdp_pdp_input_2_signal[0]);
    pdp_inst.pdp_pdp_input_2_1_in(pdp_pdp_input_2_signal[1]);
    pdp_inst.pdp_pdp_input_2_2_in(pdp_pdp_input_2_signal[2]);
    pdp_inst.pdp_pdp_input_2_3_in(pdp_pdp_input_2_signal[3]);
    pdp_inst.pdp_pdp_input_2_4_in(pdp_pdp_input_2_signal[4]);
    pdp_inst.pdp_pdp_input_2_5_in(pdp_pdp_input_2_signal[5]);
    pdp_inst.pdp_pdp_input_2_6_in(pdp_pdp_input_2_signal[6]);
    pdp_inst.pdp_pdp_input_2_7_in(pdp_pdp_input_2_signal[7]);
    pdp_inst.pdp_pdp_input_2_8_in(pdp_pdp_input_2_signal[8]);
    pdp_inst.pdp_pdp_input_2_9_in(pdp_pdp_input_2_signal[9]);
    pdp_inst.pdp_pdp_input_2_10_in(pdp_pdp_input_2_signal[10]);
    pdp_inst.pdp_pdp_input_2_11_in(pdp_pdp_input_2_signal[11]);
    pdp_inst.pdp_pdp_input_2_12_in(pdp_pdp_input_2_signal[12]);
    pdp_inst.pdp_pdp_input_2_13_in(pdp_pdp_input_2_signal[13]);
    pdp_inst.pdp_pdp_input_2_14_in(pdp_pdp_input_2_signal[14]);
    pdp_inst.pdp_pdp_input_2_15_in(pdp_pdp_input_2_signal[15]);

    pdp_inst.pdp_pdp_input_3_0_in(pdp_pdp_input_3_signal[0]);
    pdp_inst.pdp_pdp_input_3_1_in(pdp_pdp_input_3_signal[1]);
    pdp_inst.pdp_pdp_input_3_2_in(pdp_pdp_input_3_signal[2]);
    pdp_inst.pdp_pdp_input_3_3_in(pdp_pdp_input_3_signal[3]);
    pdp_inst.pdp_pdp_input_3_4_in(pdp_pdp_input_3_signal[4]);
    pdp_inst.pdp_pdp_input_3_5_in(pdp_pdp_input_3_signal[5]);
    pdp_inst.pdp_pdp_input_3_6_in(pdp_pdp_input_3_signal[6]);
    pdp_inst.pdp_pdp_input_3_7_in(pdp_pdp_input_3_signal[7]);
    pdp_inst.pdp_pdp_input_3_8_in(pdp_pdp_input_3_signal[8]);
    pdp_inst.pdp_pdp_input_3_9_in(pdp_pdp_input_3_signal[9]);
    pdp_inst.pdp_pdp_input_3_10_in(pdp_pdp_input_3_signal[10]);
    pdp_inst.pdp_pdp_input_3_11_in(pdp_pdp_input_3_signal[11]);
    pdp_inst.pdp_pdp_input_3_12_in(pdp_pdp_input_3_signal[12]);
    pdp_inst.pdp_pdp_input_3_13_in(pdp_pdp_input_3_signal[13]);
    pdp_inst.pdp_pdp_input_3_14_in(pdp_pdp_input_3_signal[14]);
    pdp_inst.pdp_pdp_input_3_15_in(pdp_pdp_input_3_signal[15]);

    pdp_inst.pdp_pdp_input_4_0_in(pdp_pdp_input_4_signal[0]);
    pdp_inst.pdp_pdp_input_4_1_in(pdp_pdp_input_4_signal[1]);
    pdp_inst.pdp_pdp_input_4_2_in(pdp_pdp_input_4_signal[2]);
    pdp_inst.pdp_pdp_input_4_3_in(pdp_pdp_input_4_signal[3]);
    pdp_inst.pdp_pdp_input_4_4_in(pdp_pdp_input_4_signal[4]);
    pdp_inst.pdp_pdp_input_4_5_in(pdp_pdp_input_4_signal[5]);
    pdp_inst.pdp_pdp_input_4_6_in(pdp_pdp_input_4_signal[6]);
    pdp_inst.pdp_pdp_input_4_7_in(pdp_pdp_input_4_signal[7]);
    pdp_inst.pdp_pdp_input_4_8_in(pdp_pdp_input_4_signal[8]);
    pdp_inst.pdp_pdp_input_4_9_in(pdp_pdp_input_4_signal[9]);
    pdp_inst.pdp_pdp_input_4_10_in(pdp_pdp_input_4_signal[10]);
    pdp_inst.pdp_pdp_input_4_11_in(pdp_pdp_input_4_signal[11]);
    pdp_inst.pdp_pdp_input_4_12_in(pdp_pdp_input_4_signal[12]);
    pdp_inst.pdp_pdp_input_4_13_in(pdp_pdp_input_4_signal[13]);
    pdp_inst.pdp_pdp_input_4_14_in(pdp_pdp_input_4_signal[14]);
    pdp_inst.pdp_pdp_input_4_15_in(pdp_pdp_input_4_signal[15]);

    pdp_inst.pdp_pdp_input_5_0_in(pdp_pdp_input_5_signal[0]);
    pdp_inst.pdp_pdp_input_5_1_in(pdp_pdp_input_5_signal[1]);
    pdp_inst.pdp_pdp_input_5_2_in(pdp_pdp_input_5_signal[2]);
    pdp_inst.pdp_pdp_input_5_3_in(pdp_pdp_input_5_signal[3]);
    pdp_inst.pdp_pdp_input_5_4_in(pdp_pdp_input_5_signal[4]);
    pdp_inst.pdp_pdp_input_5_5_in(pdp_pdp_input_5_signal[5]);
    pdp_inst.pdp_pdp_input_5_6_in(pdp_pdp_input_5_signal[6]);
    pdp_inst.pdp_pdp_input_5_7_in(pdp_pdp_input_5_signal[7]);
    pdp_inst.pdp_pdp_input_5_8_in(pdp_pdp_input_5_signal[8]);
    pdp_inst.pdp_pdp_input_5_9_in(pdp_pdp_input_5_signal[9]);
    pdp_inst.pdp_pdp_input_5_10_in(pdp_pdp_input_5_signal[10]);
    pdp_inst.pdp_pdp_input_5_11_in(pdp_pdp_input_5_signal[11]);
    pdp_inst.pdp_pdp_input_5_12_in(pdp_pdp_input_5_signal[12]);
    pdp_inst.pdp_pdp_input_5_13_in(pdp_pdp_input_5_signal[13]);
    pdp_inst.pdp_pdp_input_5_14_in(pdp_pdp_input_5_signal[14]);
    pdp_inst.pdp_pdp_input_5_15_in(pdp_pdp_input_5_signal[15]);

    pdp_inst.pdp_pdp_input_6_0_in(pdp_pdp_input_6_signal[0]);
    pdp_inst.pdp_pdp_input_6_1_in(pdp_pdp_input_6_signal[1]);
    pdp_inst.pdp_pdp_input_6_2_in(pdp_pdp_input_6_signal[2]);
    pdp_inst.pdp_pdp_input_6_3_in(pdp_pdp_input_6_signal[3]);
    pdp_inst.pdp_pdp_input_6_4_in(pdp_pdp_input_6_signal[4]);
    pdp_inst.pdp_pdp_input_6_5_in(pdp_pdp_input_6_signal[5]);
    pdp_inst.pdp_pdp_input_6_6_in(pdp_pdp_input_6_signal[6]);
    pdp_inst.pdp_pdp_input_6_7_in(pdp_pdp_input_6_signal[7]);
    pdp_inst.pdp_pdp_input_6_8_in(pdp_pdp_input_6_signal[8]);
    pdp_inst.pdp_pdp_input_6_9_in(pdp_pdp_input_6_signal[9]);
    pdp_inst.pdp_pdp_input_6_10_in(pdp_pdp_input_6_signal[10]);
    pdp_inst.pdp_pdp_input_6_11_in(pdp_pdp_input_6_signal[11]);
    pdp_inst.pdp_pdp_input_6_12_in(pdp_pdp_input_6_signal[12]);
    pdp_inst.pdp_pdp_input_6_13_in(pdp_pdp_input_6_signal[13]);
    pdp_inst.pdp_pdp_input_6_14_in(pdp_pdp_input_6_signal[14]);
    pdp_inst.pdp_pdp_input_6_15_in(pdp_pdp_input_6_signal[15]);

    pdp_inst.pdp_pdp_input_7_0_in(pdp_pdp_input_7_signal[0]);
    pdp_inst.pdp_pdp_input_7_1_in(pdp_pdp_input_7_signal[1]);
    pdp_inst.pdp_pdp_input_7_2_in(pdp_pdp_input_7_signal[2]);
    pdp_inst.pdp_pdp_input_7_3_in(pdp_pdp_input_7_signal[3]);
    pdp_inst.pdp_pdp_input_7_4_in(pdp_pdp_input_7_signal[4]);
    pdp_inst.pdp_pdp_input_7_5_in(pdp_pdp_input_7_signal[5]);
    pdp_inst.pdp_pdp_input_7_6_in(pdp_pdp_input_7_signal[6]);
    pdp_inst.pdp_pdp_input_7_7_in(pdp_pdp_input_7_signal[7]);
    pdp_inst.pdp_pdp_input_7_8_in(pdp_pdp_input_7_signal[8]);
    pdp_inst.pdp_pdp_input_7_9_in(pdp_pdp_input_7_signal[9]);
    pdp_inst.pdp_pdp_input_7_10_in(pdp_pdp_input_7_signal[10]);
    pdp_inst.pdp_pdp_input_7_11_in(pdp_pdp_input_7_signal[11]);
    pdp_inst.pdp_pdp_input_7_12_in(pdp_pdp_input_7_signal[12]);
    pdp_inst.pdp_pdp_input_7_13_in(pdp_pdp_input_7_signal[13]);
    pdp_inst.pdp_pdp_input_7_14_in(pdp_pdp_input_7_signal[14]);
    pdp_inst.pdp_pdp_input_7_15_in(pdp_pdp_input_7_signal[15]);

    pdp_inst.pdp_pdp_input_8_0_in(pdp_pdp_input_8_signal[0]);
    pdp_inst.pdp_pdp_input_8_1_in(pdp_pdp_input_8_signal[1]);
    pdp_inst.pdp_pdp_input_8_2_in(pdp_pdp_input_8_signal[2]);
    pdp_inst.pdp_pdp_input_8_3_in(pdp_pdp_input_8_signal[3]);
    pdp_inst.pdp_pdp_input_8_4_in(pdp_pdp_input_8_signal[4]);
    pdp_inst.pdp_pdp_input_8_5_in(pdp_pdp_input_8_signal[5]);
    pdp_inst.pdp_pdp_input_8_6_in(pdp_pdp_input_8_signal[6]);
    pdp_inst.pdp_pdp_input_8_7_in(pdp_pdp_input_8_signal[7]);
    pdp_inst.pdp_pdp_input_8_8_in(pdp_pdp_input_8_signal[8]);
    pdp_inst.pdp_pdp_input_8_9_in(pdp_pdp_input_8_signal[9]);
    pdp_inst.pdp_pdp_input_8_10_in(pdp_pdp_input_8_signal[10]);
    pdp_inst.pdp_pdp_input_8_11_in(pdp_pdp_input_8_signal[11]);
    pdp_inst.pdp_pdp_input_8_12_in(pdp_pdp_input_8_signal[12]);
    pdp_inst.pdp_pdp_input_8_13_in(pdp_pdp_input_8_signal[13]);
    pdp_inst.pdp_pdp_input_8_14_in(pdp_pdp_input_8_signal[14]);
    pdp_inst.pdp_pdp_input_8_15_in(pdp_pdp_input_8_signal[15]);

    pdp_inst.pdp_pdp_input_9_0_in(pdp_pdp_input_9_signal[0]);
    pdp_inst.pdp_pdp_input_9_1_in(pdp_pdp_input_9_signal[1]);
    pdp_inst.pdp_pdp_input_9_2_in(pdp_pdp_input_9_signal[2]);
    pdp_inst.pdp_pdp_input_9_3_in(pdp_pdp_input_9_signal[3]);
    pdp_inst.pdp_pdp_input_9_4_in(pdp_pdp_input_9_signal[4]);
    pdp_inst.pdp_pdp_input_9_5_in(pdp_pdp_input_9_signal[5]);
    pdp_inst.pdp_pdp_input_9_6_in(pdp_pdp_input_9_signal[6]);
    pdp_inst.pdp_pdp_input_9_7_in(pdp_pdp_input_9_signal[7]);
    pdp_inst.pdp_pdp_input_9_8_in(pdp_pdp_input_9_signal[8]);
    pdp_inst.pdp_pdp_input_9_9_in(pdp_pdp_input_9_signal[9]);
    pdp_inst.pdp_pdp_input_9_10_in(pdp_pdp_input_9_signal[10]);
    pdp_inst.pdp_pdp_input_9_11_in(pdp_pdp_input_9_signal[11]);
    pdp_inst.pdp_pdp_input_9_12_in(pdp_pdp_input_9_signal[12]);
    pdp_inst.pdp_pdp_input_9_13_in(pdp_pdp_input_9_signal[13]);
    pdp_inst.pdp_pdp_input_9_14_in(pdp_pdp_input_9_signal[14]);
    pdp_inst.pdp_pdp_input_9_15_in(pdp_pdp_input_9_signal[15]);

    pdp_inst.pdp_pdp_input_10_0_in(pdp_pdp_input_10_signal[0]);
    pdp_inst.pdp_pdp_input_10_1_in(pdp_pdp_input_10_signal[1]);
    pdp_inst.pdp_pdp_input_10_2_in(pdp_pdp_input_10_signal[2]);
    pdp_inst.pdp_pdp_input_10_3_in(pdp_pdp_input_10_signal[3]);
    pdp_inst.pdp_pdp_input_10_4_in(pdp_pdp_input_10_signal[4]);
    pdp_inst.pdp_pdp_input_10_5_in(pdp_pdp_input_10_signal[5]);
    pdp_inst.pdp_pdp_input_10_6_in(pdp_pdp_input_10_signal[6]);
    pdp_inst.pdp_pdp_input_10_7_in(pdp_pdp_input_10_signal[7]);
    pdp_inst.pdp_pdp_input_10_8_in(pdp_pdp_input_10_signal[8]);
    pdp_inst.pdp_pdp_input_10_9_in(pdp_pdp_input_10_signal[9]);
    pdp_inst.pdp_pdp_input_10_10_in(pdp_pdp_input_10_signal[10]);
    pdp_inst.pdp_pdp_input_10_11_in(pdp_pdp_input_10_signal[11]);
    pdp_inst.pdp_pdp_input_10_12_in(pdp_pdp_input_10_signal[12]);
    pdp_inst.pdp_pdp_input_10_13_in(pdp_pdp_input_10_signal[13]);
    pdp_inst.pdp_pdp_input_10_14_in(pdp_pdp_input_10_signal[14]);
    pdp_inst.pdp_pdp_input_10_15_in(pdp_pdp_input_10_signal[15]);

    pdp_inst.pdp_pdp_input_11_0_in(pdp_pdp_input_11_signal[0]);
    pdp_inst.pdp_pdp_input_11_1_in(pdp_pdp_input_11_signal[1]);
    pdp_inst.pdp_pdp_input_11_2_in(pdp_pdp_input_11_signal[2]);
    pdp_inst.pdp_pdp_input_11_3_in(pdp_pdp_input_11_signal[3]);
    pdp_inst.pdp_pdp_input_11_4_in(pdp_pdp_input_11_signal[4]);
    pdp_inst.pdp_pdp_input_11_5_in(pdp_pdp_input_11_signal[5]);
    pdp_inst.pdp_pdp_input_11_6_in(pdp_pdp_input_11_signal[6]);
    pdp_inst.pdp_pdp_input_11_7_in(pdp_pdp_input_11_signal[7]);
    pdp_inst.pdp_pdp_input_11_8_in(pdp_pdp_input_11_signal[8]);
    pdp_inst.pdp_pdp_input_11_9_in(pdp_pdp_input_11_signal[9]);
    pdp_inst.pdp_pdp_input_11_10_in(pdp_pdp_input_11_signal[10]);
    pdp_inst.pdp_pdp_input_11_11_in(pdp_pdp_input_11_signal[11]);
    pdp_inst.pdp_pdp_input_11_12_in(pdp_pdp_input_11_signal[12]);
    pdp_inst.pdp_pdp_input_11_13_in(pdp_pdp_input_11_signal[13]);
    pdp_inst.pdp_pdp_input_11_14_in(pdp_pdp_input_11_signal[14]);
    pdp_inst.pdp_pdp_input_11_15_in(pdp_pdp_input_11_signal[15]);

    pdp_inst.pdp_pdp_input_12_0_in(pdp_pdp_input_12_signal[0]);
    pdp_inst.pdp_pdp_input_12_1_in(pdp_pdp_input_12_signal[1]);
    pdp_inst.pdp_pdp_input_12_2_in(pdp_pdp_input_12_signal[2]);
    pdp_inst.pdp_pdp_input_12_3_in(pdp_pdp_input_12_signal[3]);
    pdp_inst.pdp_pdp_input_12_4_in(pdp_pdp_input_12_signal[4]);
    pdp_inst.pdp_pdp_input_12_5_in(pdp_pdp_input_12_signal[5]);
    pdp_inst.pdp_pdp_input_12_6_in(pdp_pdp_input_12_signal[6]);
    pdp_inst.pdp_pdp_input_12_7_in(pdp_pdp_input_12_signal[7]);
    pdp_inst.pdp_pdp_input_12_8_in(pdp_pdp_input_12_signal[8]);
    pdp_inst.pdp_pdp_input_12_9_in(pdp_pdp_input_12_signal[9]);
    pdp_inst.pdp_pdp_input_12_10_in(pdp_pdp_input_12_signal[10]);
    pdp_inst.pdp_pdp_input_12_11_in(pdp_pdp_input_12_signal[11]);
    pdp_inst.pdp_pdp_input_12_12_in(pdp_pdp_input_12_signal[12]);
    pdp_inst.pdp_pdp_input_12_13_in(pdp_pdp_input_12_signal[13]);
    pdp_inst.pdp_pdp_input_12_14_in(pdp_pdp_input_12_signal[14]);
    pdp_inst.pdp_pdp_input_12_15_in(pdp_pdp_input_12_signal[15]);

    pdp_inst.pdp_pdp_input_13_0_in(pdp_pdp_input_13_signal[0]);
    pdp_inst.pdp_pdp_input_13_1_in(pdp_pdp_input_13_signal[1]);
    pdp_inst.pdp_pdp_input_13_2_in(pdp_pdp_input_13_signal[2]);
    pdp_inst.pdp_pdp_input_13_3_in(pdp_pdp_input_13_signal[3]);
    pdp_inst.pdp_pdp_input_13_4_in(pdp_pdp_input_13_signal[4]);
    pdp_inst.pdp_pdp_input_13_5_in(pdp_pdp_input_13_signal[5]);
    pdp_inst.pdp_pdp_input_13_6_in(pdp_pdp_input_13_signal[6]);
    pdp_inst.pdp_pdp_input_13_7_in(pdp_pdp_input_13_signal[7]);
    pdp_inst.pdp_pdp_input_13_8_in(pdp_pdp_input_13_signal[8]);
    pdp_inst.pdp_pdp_input_13_9_in(pdp_pdp_input_13_signal[9]);
    pdp_inst.pdp_pdp_input_13_10_in(pdp_pdp_input_13_signal[10]);
    pdp_inst.pdp_pdp_input_13_11_in(pdp_pdp_input_13_signal[11]);
    pdp_inst.pdp_pdp_input_13_12_in(pdp_pdp_input_13_signal[12]);
    pdp_inst.pdp_pdp_input_13_13_in(pdp_pdp_input_13_signal[13]);
    pdp_inst.pdp_pdp_input_13_14_in(pdp_pdp_input_13_signal[14]);
    pdp_inst.pdp_pdp_input_13_15_in(pdp_pdp_input_13_signal[15]);

    pdp_inst.pdp_pdp_input_14_0_in(pdp_pdp_input_14_signal[0]);
    pdp_inst.pdp_pdp_input_14_1_in(pdp_pdp_input_14_signal[1]);
    pdp_inst.pdp_pdp_input_14_2_in(pdp_pdp_input_14_signal[2]);
    pdp_inst.pdp_pdp_input_14_3_in(pdp_pdp_input_14_signal[3]);
    pdp_inst.pdp_pdp_input_14_4_in(pdp_pdp_input_14_signal[4]);
    pdp_inst.pdp_pdp_input_14_5_in(pdp_pdp_input_14_signal[5]);
    pdp_inst.pdp_pdp_input_14_6_in(pdp_pdp_input_14_signal[6]);
    pdp_inst.pdp_pdp_input_14_7_in(pdp_pdp_input_14_signal[7]);
    pdp_inst.pdp_pdp_input_14_8_in(pdp_pdp_input_14_signal[8]);
    pdp_inst.pdp_pdp_input_14_9_in(pdp_pdp_input_14_signal[9]);
    pdp_inst.pdp_pdp_input_14_10_in(pdp_pdp_input_14_signal[10]);
    pdp_inst.pdp_pdp_input_14_11_in(pdp_pdp_input_14_signal[11]);
    pdp_inst.pdp_pdp_input_14_12_in(pdp_pdp_input_14_signal[12]);
    pdp_inst.pdp_pdp_input_14_13_in(pdp_pdp_input_14_signal[13]);
    pdp_inst.pdp_pdp_input_14_14_in(pdp_pdp_input_14_signal[14]);
    pdp_inst.pdp_pdp_input_14_15_in(pdp_pdp_input_14_signal[15]);

    pdp_inst.pdp_pdp_input_15_0_in(pdp_pdp_input_15_signal[0]);
    pdp_inst.pdp_pdp_input_15_1_in(pdp_pdp_input_15_signal[1]);
    pdp_inst.pdp_pdp_input_15_2_in(pdp_pdp_input_15_signal[2]);
    pdp_inst.pdp_pdp_input_15_3_in(pdp_pdp_input_15_signal[3]);
    pdp_inst.pdp_pdp_input_15_4_in(pdp_pdp_input_15_signal[4]);
    pdp_inst.pdp_pdp_input_15_5_in(pdp_pdp_input_15_signal[5]);
    pdp_inst.pdp_pdp_input_15_6_in(pdp_pdp_input_15_signal[6]);
    pdp_inst.pdp_pdp_input_15_7_in(pdp_pdp_input_15_signal[7]);
    pdp_inst.pdp_pdp_input_15_8_in(pdp_pdp_input_15_signal[8]);
    pdp_inst.pdp_pdp_input_15_9_in(pdp_pdp_input_15_signal[9]);
    pdp_inst.pdp_pdp_input_15_10_in(pdp_pdp_input_15_signal[10]);
    pdp_inst.pdp_pdp_input_15_11_in(pdp_pdp_input_15_signal[11]);
    pdp_inst.pdp_pdp_input_15_12_in(pdp_pdp_input_15_signal[12]);
    pdp_inst.pdp_pdp_input_15_13_in(pdp_pdp_input_15_signal[13]);
    pdp_inst.pdp_pdp_input_15_14_in(pdp_pdp_input_15_signal[14]);
    pdp_inst.pdp_pdp_input_15_15_in(pdp_pdp_input_15_signal[15]);

    SC_THREAD(run);
  }

  // Run the SystemC simuation and log outputs
  void run()
  {
    pdp_inst.instr_log.open("instr_log_conv.txt", ofstream::out | ofstream::trunc);
    pdp_inst.instr_update_log.open("instr_update_log_conv.txt", ios::out | ios::trunc);

    std::cout << "start running" << std::endl;
    std::cout << "*********** simulation start ***********" << std::endl;
    std::cout << "*********** check 0 ***********" << std::endl;
    wait(10, SC_NS);
    std::cout << "*********** check 1 ***********" << std::endl;
    // Log final outputs
    std::ofstream fout;
    std::cout << "*********** check 2 ***********" << std::endl;
    fout.open(file_out, ios::out | ios::trunc);
  std::cout << "*********** check 3 ***********" << std::endl;
    int instr_no = 0;
std::cout << "*********** check 4 ***********" << std::endl;
    while (input_done == 0)
    {
    
      fout << std::dec << instr_no++ << " ";
      // output
      for (int i = 0; i < 16; i++)
      {

        fout << std::dec << (sc_dt::sc_bigint<16>)pdp_inst.pdp_pdp_output[i] << " ";

      }
      fout << std::endl;

    

      wait(10, SC_NS);
    }
    wait(1000, SC_NS);

    fout.close();

    std::cout << "outputs have been stored at " << file_out << std::endl;

    wait(100000, SC_NS);
    std::cout << '\n'
              << std::endl;
    std::cout << "************* sc_stop **************" << std::endl;

    pdp_inst.instr_log.close();
    sc_stop();
  }
};

int sc_main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cout << "Usage: ./pdp [prog_frag_in_path] [result_out_dump_path]" << std::endl;
    return 0;
  }
  else
  {
    file_in = argv[1];
    file_out = argv[2];
  }

  // Begin simulation
  std::cout << "test start" << std::endl;
  testbench tb("tb");

  sc_start();

  return 0;
}
