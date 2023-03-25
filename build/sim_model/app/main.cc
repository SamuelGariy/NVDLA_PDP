#include <pdp.h>

#include <systemc>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

#define GET_JSON_INT(json_val, default_val) (!(json_val.is_null()) ? json_val.get<int>() : default_val)
#define GET_JSON_INT_FROM_HEX_STR(json_val, default_val) (!(json_val.is_null()) ? (std::stoi(json_val.get<std::string>().c_str(), nullptr, 16)) : default_val)
#define GET_JSON_BOOL(json_val, default_val) (!(json_val.is_null()) ? json_val.get<bool>() : default_val)

std::string file_in;
std::string file_out;

// Module for reading inputs into ILA model
SC_MODULE(Source)
{
  sc_in<bool> clk{"clk"};

  // CSB inputs
  sc_out<sc_biguint<16>> pdp_csb2pdp_addr{"pdp_csb2pdp_addr"};
  sc_out<sc_biguint<32>> pdp_csb2pdp_data{"pdp_csb2pdp_data"};
  sc_out<sc_biguint<1>> pdp_csb2pdp_write{"pdp_csb2pdp_write"};
  sc_out<sc_biguint<1>> pdp_csb2pdp_vld{"pdp_csb2pdp_vld"};

  // PDP control signals
  sc_out<bool> pdp_pdp_last_input_batch{"pdp_pdp_last_input_batch"};
  sc_out<bool> pdp_pdp_input_vld{"pdp_pdp_input_vld"};
  // PDP  inputs

  sc_out<sc_biguint<16>> pdp_pdp_input_0{"pdp_pdp_input_0"};
  sc_out<sc_biguint<16>> pdp_pdp_input_1{"pdp_pdp_input_1"};
  sc_out<sc_biguint<16>> pdp_pdp_input_2{"pdp_pdp_input_2"};
  sc_out<sc_biguint<16>> pdp_pdp_input_3{"pdp_pdp_input_3"};

  sc_out<sc_biguint<16>> pdp_pdp_input_4{"pdp_pdp_input_4"};
  sc_out<sc_biguint<16>> pdp_pdp_input_5{"pdp_pdp_input_5"};
  sc_out<sc_biguint<16>> pdp_pdp_input_6{"pdp_pdp_input_6"};
  sc_out<sc_biguint<16>> pdp_pdp_input_7{"pdp_pdp_input_7"};

  sc_out<sc_biguint<16>> pdp_pdp_input_8{"pdp_pdp_input_8"};
  sc_out<sc_biguint<16>> pdp_pdp_input_9{"pdp_pdp_input_9"};
  sc_out<sc_biguint<16>> pdp_pdp_input_10{"pdp_pdp_input_10"};
  sc_out<sc_biguint<16>> pdp_pdp_input_11{"pdp_pdp_input_11"};

  sc_out<sc_biguint<16>> pdp_pdp_input_12{"pdp_pdp_input_12"};
  sc_out<sc_biguint<16>> pdp_pdp_input_13{"pdp_pdp_input_13"};
  sc_out<sc_biguint<16>> pdp_pdp_input_14{"pdp_pdp_input_14"};
  sc_out<sc_biguint<16>> pdp_pdp_input_15{"pdp_pdp_input_15"};

  sc_out<sc_biguint<16>> pdp_pdp_input_16{"pdp_pdp_input_16"};
  sc_out<sc_biguint<16>> pdp_pdp_input_17{"pdp_pdp_input_17"};
  sc_out<sc_biguint<16>> pdp_pdp_input_18{"pdp_pdp_input_18"};
  sc_out<sc_biguint<16>> pdp_pdp_input_19{"pdp_pdp_input_19"};

  sc_out<sc_biguint<16>> pdp_pdp_input_20{"pdp_pdp_input_20"};
  sc_out<sc_biguint<16>> pdp_pdp_input_21{"pdp_pdp_input_21"};
  sc_out<sc_biguint<16>> pdp_pdp_input_22{"pdp_pdp_input_22"};
  sc_out<sc_biguint<16>> pdp_pdp_input_23{"pdp_pdp_input_23"};

  sc_out<sc_biguint<16>> pdp_pdp_input_24{"pdp_pdp_input_24"};
  sc_out<sc_biguint<16>> pdp_pdp_input_25{"pdp_pdp_input_25"};
  sc_out<sc_biguint<16>> pdp_pdp_input_26{"pdp_pdp_input_26"};
  sc_out<sc_biguint<16>> pdp_pdp_input_27{"pdp_pdp_input_27"};

  sc_out<sc_biguint<16>> pdp_pdp_input_28{"pdp_pdp_input_28"};
  sc_out<sc_biguint<16>> pdp_pdp_input_29{"pdp_pdp_input_29"};
  sc_out<sc_biguint<16>> pdp_pdp_input_30{"pdp_pdp_input_30"};
  sc_out<sc_biguint<16>> pdp_pdp_input_31{"pdp_pdp_input_31"};

  sc_out<sc_biguint<16>> pdp_pdp_input_32{"pdp_pdp_input_32"};
  sc_out<sc_biguint<16>> pdp_pdp_input_33{"pdp_pdp_input_33"};
  sc_out<sc_biguint<16>> pdp_pdp_input_34{"pdp_pdp_input_34"};
  sc_out<sc_biguint<16>> pdp_pdp_input_35{"pdp_pdp_input_35"};

  sc_out<sc_biguint<16>> pdp_pdp_input_36{"pdp_pdp_input_36"};
  sc_out<sc_biguint<16>> pdp_pdp_input_37{"pdp_pdp_input_37"};
  sc_out<sc_biguint<16>> pdp_pdp_input_38{"pdp_pdp_input_38"};
  sc_out<sc_biguint<16>> pdp_pdp_input_39{"pdp_pdp_input_39"};

  sc_out<sc_biguint<16>> pdp_pdp_input_40{"pdp_pdp_input_40"};
  sc_out<sc_biguint<16>> pdp_pdp_input_41{"pdp_pdp_input_41"};
  sc_out<sc_biguint<16>> pdp_pdp_input_42{"pdp_pdp_input_42"};
  sc_out<sc_biguint<16>> pdp_pdp_input_43{"pdp_pdp_input_43"};

  sc_out<sc_biguint<16>> pdp_pdp_input_44{"pdp_pdp_input_44"};
  sc_out<sc_biguint<16>> pdp_pdp_input_45{"pdp_pdp_input_45"};
  sc_out<sc_biguint<16>> pdp_pdp_input_46{"pdp_pdp_input_46"};
  sc_out<sc_biguint<16>> pdp_pdp_input_47{"pdp_pdp_input_47"};

  sc_out<sc_biguint<16>> pdp_pdp_input_48{"pdp_pdp_input_48"};
  sc_out<sc_biguint<16>> pdp_pdp_input_49{"pdp_pdp_input_49"};
  sc_out<sc_biguint<16>> pdp_pdp_input_50{"pdp_pdp_input_50"};
  sc_out<sc_biguint<16>> pdp_pdp_input_51{"pdp_pdp_input_51"};

  sc_out<sc_biguint<16>> pdp_pdp_input_52{"pdp_pdp_input_52"};
  sc_out<sc_biguint<16>> pdp_pdp_input_53{"pdp_pdp_input_53"};
  sc_out<sc_biguint<16>> pdp_pdp_input_54{"pdp_pdp_input_54"};
  sc_out<sc_biguint<16>> pdp_pdp_input_55{"pdp_pdp_input_55"};

  sc_out<sc_biguint<16>> pdp_pdp_input_56{"pdp_pdp_input_56"};
  sc_out<sc_biguint<16>> pdp_pdp_input_57{"pdp_pdp_input_57"};
  sc_out<sc_biguint<16>> pdp_pdp_input_58{"pdp_pdp_input_58"};
  sc_out<sc_biguint<16>> pdp_pdp_input_59{"pdp_pdp_input_59"};

  sc_out<sc_biguint<16>> pdp_pdp_input_60{"pdp_pdp_input_60"};
  sc_out<sc_biguint<16>> pdp_pdp_input_61{"pdp_pdp_input_61"};
  sc_out<sc_biguint<16>> pdp_pdp_input_62{"pdp_pdp_input_62"};
  sc_out<sc_biguint<16>> pdp_pdp_input_63{"pdp_pdp_input_63"};

  sc_out<sc_biguint<1>> input_done{"input_done"};
  ;

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
    pdp_pdp_input_vld = false;

    pdp_pdp_input_0 = 0;
    pdp_pdp_input_1 = 0;
    pdp_pdp_input_2 = 0;
    pdp_pdp_input_3 = 0;

    pdp_pdp_input_4 = 0;
    pdp_pdp_input_5 = 0;
    pdp_pdp_input_6 = 0;
    pdp_pdp_input_7 = 0;

    pdp_pdp_input_8 = 0;
    pdp_pdp_input_9 = 0;
    pdp_pdp_input_10 = 0;
    pdp_pdp_input_11 = 0;

    pdp_pdp_input_12 = 0;
    pdp_pdp_input_13 = 0;
    pdp_pdp_input_14 = 0;
    pdp_pdp_input_15 = 0;

    pdp_pdp_input_16 = 0;
    pdp_pdp_input_17 = 0;
    pdp_pdp_input_18 = 0;
    pdp_pdp_input_19 = 0;

    pdp_pdp_input_20 = 0;
    pdp_pdp_input_21 = 0;
    pdp_pdp_input_22 = 0;
    pdp_pdp_input_23 = 0;

    pdp_pdp_input_24 = 0;
    pdp_pdp_input_25 = 0;
    pdp_pdp_input_26 = 0;
    pdp_pdp_input_27 = 0;

    pdp_pdp_input_28 = 0;
    pdp_pdp_input_29 = 0;
    pdp_pdp_input_30 = 0;
    pdp_pdp_input_31 = 0;

    pdp_pdp_input_32 = 0;
    pdp_pdp_input_33 = 0;
    pdp_pdp_input_34 = 0;
    pdp_pdp_input_35 = 0;

    pdp_pdp_input_36 = 0;
    pdp_pdp_input_37 = 0;
    pdp_pdp_input_38 = 0;
    pdp_pdp_input_39 = 0;

    pdp_pdp_input_40 = 0;
    pdp_pdp_input_41 = 0;
    pdp_pdp_input_42 = 0;
    pdp_pdp_input_43 = 0;

    pdp_pdp_input_44 = 0;
    pdp_pdp_input_45 = 0;
    pdp_pdp_input_46 = 0;
    pdp_pdp_input_47 = 0;

    pdp_pdp_input_48 = 0;
    pdp_pdp_input_49 = 0;
    pdp_pdp_input_50 = 0;
    pdp_pdp_input_51 = 0;

    pdp_pdp_input_52 = 0;
    pdp_pdp_input_53 = 0;
    pdp_pdp_input_54 = 0;
    pdp_pdp_input_55 = 0;

    pdp_pdp_input_56 = 0;
    pdp_pdp_input_57 = 0;
    pdp_pdp_input_58 = 0;
    pdp_pdp_input_59 = 0;

    pdp_pdp_input_60 = 0;
    pdp_pdp_input_61 = 0;
    pdp_pdp_input_62 = 0;
    pdp_pdp_input_63 = 0;

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
      pdp_pdp_input_vld = GET_JSON_BOOL(cmd_seq["program fragment"][i]["pdp_pdp_input_vld"], false);

      // read in input

      pdp_pdp_input_0 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_0"], 0);
      pdp_pdp_input_1 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_1"], 0);
      pdp_pdp_input_2 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_2"], 0);
      pdp_pdp_input_3 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_3"], 0);

      pdp_pdp_input_4 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_4"], 0);
      pdp_pdp_input_5 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_5"], 0);
      pdp_pdp_input_6 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_6"], 0);
      pdp_pdp_input_7 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_7"], 0);

      pdp_pdp_input_8 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_8"], 0);
      pdp_pdp_input_9 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_9"], 0);
      pdp_pdp_input_10 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_10"], 0);
      pdp_pdp_input_11 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_11"], 0);

      pdp_pdp_input_12 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_12"], 0);
      pdp_pdp_input_13 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_13"], 0);
      pdp_pdp_input_14 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_14"], 0);
      pdp_pdp_input_15 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_15"], 0);

      pdp_pdp_input_16 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_16"], 0);
      pdp_pdp_input_17 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_17"], 0);
      pdp_pdp_input_18 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_18"], 0);
      pdp_pdp_input_19 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_19"], 0);

      pdp_pdp_input_20 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_20"], 0);
      pdp_pdp_input_21 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_21"], 0);
      pdp_pdp_input_22 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_22"], 0);
      pdp_pdp_input_23 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_23"], 0);

      pdp_pdp_input_24 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_24"], 0);
      pdp_pdp_input_25 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_25"], 0);
      pdp_pdp_input_26 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_26"], 0);
      pdp_pdp_input_27 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_27"], 0);

      pdp_pdp_input_28 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_28"], 0);
      pdp_pdp_input_29 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_29"], 0);
      pdp_pdp_input_30 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_30"], 0);
      pdp_pdp_input_31 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_31"], 0);

      pdp_pdp_input_32 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_32"], 0);
      pdp_pdp_input_33 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_33"], 0);
      pdp_pdp_input_34 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_34"], 0);
      pdp_pdp_input_35 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_35"], 0);

      pdp_pdp_input_36 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_36"], 0);
      pdp_pdp_input_37 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_37"], 0);
      pdp_pdp_input_38 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_38"], 0);
      pdp_pdp_input_39 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_39"], 0);

      pdp_pdp_input_40 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_40"], 0);
      pdp_pdp_input_41 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_41"], 0);
      pdp_pdp_input_42 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_42"], 0);
      pdp_pdp_input_43 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_43"], 0);

      pdp_pdp_input_44 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_44"], 0);
      pdp_pdp_input_45 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_45"], 0);
      pdp_pdp_input_46 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_46"], 0);
      pdp_pdp_input_47 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_47"], 0);

      pdp_pdp_input_48 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_48"], 0);
      pdp_pdp_input_49 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_49"], 0);
      pdp_pdp_input_50 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_50"], 0);
      pdp_pdp_input_51 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_51"], 0);

      pdp_pdp_input_52 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_52"], 0);
      pdp_pdp_input_53 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_53"], 0);
      pdp_pdp_input_54 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_54"], 0);
      pdp_pdp_input_55 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_55"], 0);

      pdp_pdp_input_56 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_56"], 0);
      pdp_pdp_input_57 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_57"], 0);
      pdp_pdp_input_58 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_58"], 0);
      pdp_pdp_input_59 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_59"], 0);

      pdp_pdp_input_60 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_60"], 0);
      pdp_pdp_input_61 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_61"], 0);
      pdp_pdp_input_62 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_62"], 0);
      pdp_pdp_input_63 = GET_JSON_INT(cmd_seq["program fragment"][i]["pdp_pdp_input_63"], 0);

      wait(10, SC_NS);
    }

    input_done = 1;
  }
};

// Link input data to SystemC model
SC_MODULE(testbench)
{
  pdp pdp_inst;
  Source src;

  sc_clock clk;

  sc_signal<sc_biguint<16>> pdp_csb2pdp_addr_signal{"pdp_csb2pdp_addr_signal"};
  sc_signal<sc_biguint<32>> pdp_csb2pdp_data_signal{"pdp_csb2pdp_data_signal"};
  sc_signal<sc_biguint<1>> pdp_csb2pdp_write_signal{"pdp_csb2pdp_write_signal"};
  sc_signal<sc_biguint<1>> pdp_csb2pdp_vld_signal{"pdp_csb2pdp_vld_signal"};

  sc_signal<bool> pdp_pdp_last_input_batch_signal{"pdp_pdp_last_input_batch_signal"};
  sc_signal<bool> pdp_pdp_input_vld_signal{"pdp_pdp_input_vld_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_0_signal{"pdp_pdp_input_0_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_1_signal{"pdp_pdp_input_1_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_2_signal{"pdp_pdp_input_2_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_3_signal{"pdp_pdp_input_3_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_4_signal{"pdp_pdp_input_4_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_5_signal{"pdp_pdp_input_5_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_6_signal{"pdp_pdp_input_6_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_7_signal{"pdp_pdp_input_7_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_8_signal{"pdp_pdp_input_8_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_9_signal{"pdp_pdp_input_9_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_10_signal{"pdp_pdp_input_10_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_11_signal{"pdp_pdp_input_11_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_12_signal{"pdp_pdp_input_12_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_13_signal{"pdp_pdp_input_13_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_14_signal{"pdp_pdp_input_14_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_15_signal{"pdp_pdp_input_15_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_16_signal{"pdp_pdp_input_16_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_17_signal{"pdp_pdp_input_17_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_18_signal{"pdp_pdp_input_18_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_19_signal{"pdp_pdp_input_19_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_20_signal{"pdp_pdp_input_20_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_21_signal{"pdp_pdp_input_21_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_22_signal{"pdp_pdp_input_22_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_23_signal{"pdp_pdp_input_23_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_24_signal{"pdp_pdp_input_24_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_25_signal{"pdp_pdp_input_25_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_26_signal{"pdp_pdp_input_26_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_27_signal{"pdp_pdp_input_27_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_28_signal{"pdp_pdp_input_28_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_29_signal{"pdp_pdp_input_29_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_30_signal{"pdp_pdp_input_30_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_31_signal{"pdp_pdp_input_31_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_32_signal{"pdp_pdp_input_32_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_33_signal{"pdp_pdp_input_33_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_34_signal{"pdp_pdp_input_34_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_35_signal{"pdp_pdp_input_35_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_36_signal{"pdp_pdp_input_36_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_37_signal{"pdp_pdp_input_37_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_38_signal{"pdp_pdp_input_38_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_39_signal{"pdp_pdp_input_39_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_40_signal{"pdp_pdp_input_40_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_41_signal{"pdp_pdp_input_41_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_42_signal{"pdp_pdp_input_42_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_43_signal{"pdp_pdp_input_43_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_44_signal{"pdp_pdp_input_44_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_45_signal{"pdp_pdp_input_45_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_46_signal{"pdp_pdp_input_46_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_47_signal{"pdp_pdp_input_47_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_48_signal{"pdp_pdp_input_48_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_49_signal{"pdp_pdp_input_49_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_50_signal{"pdp_pdp_input_50_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_51_signal{"pdp_pdp_input_51_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_52_signal{"pdp_pdp_input_52_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_53_signal{"pdp_pdp_input_53_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_54_signal{"pdp_pdp_input_54_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_55_signal{"pdp_pdp_input_55_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_56_signal{"pdp_pdp_input_56_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_57_signal{"pdp_pdp_input_57_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_58_signal{"pdp_pdp_input_58_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_59_signal{"pdp_pdp_input_59_signal"};

  sc_signal<sc_biguint<16>> pdp_pdp_input_60_signal{"pdp_pdp_input_60_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_61_signal{"pdp_pdp_input_61_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_62_signal{"pdp_pdp_input_62_signal"};
  sc_signal<sc_biguint<16>> pdp_pdp_input_63_signal{"pdp_pdp_input_63_signal"};

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
    src.pdp_pdp_input_vld(pdp_pdp_input_vld_signal);

    src.pdp_pdp_input_0(pdp_pdp_input_0_signal);
    src.pdp_pdp_input_1(pdp_pdp_input_1_signal);
    src.pdp_pdp_input_2(pdp_pdp_input_2_signal);
    src.pdp_pdp_input_3(pdp_pdp_input_3_signal);
    src.pdp_pdp_input_4(pdp_pdp_input_4_signal);
    src.pdp_pdp_input_5(pdp_pdp_input_5_signal);
    src.pdp_pdp_input_6(pdp_pdp_input_6_signal);
    src.pdp_pdp_input_7(pdp_pdp_input_7_signal);
    src.pdp_pdp_input_8(pdp_pdp_input_8_signal);
    src.pdp_pdp_input_9(pdp_pdp_input_9_signal);
    src.pdp_pdp_input_10(pdp_pdp_input_10_signal);
    src.pdp_pdp_input_11(pdp_pdp_input_11_signal);
    src.pdp_pdp_input_12(pdp_pdp_input_12_signal);
    src.pdp_pdp_input_13(pdp_pdp_input_13_signal);
    src.pdp_pdp_input_14(pdp_pdp_input_14_signal);
    src.pdp_pdp_input_15(pdp_pdp_input_15_signal);
    src.pdp_pdp_input_16(pdp_pdp_input_16_signal);
    src.pdp_pdp_input_17(pdp_pdp_input_17_signal);
    src.pdp_pdp_input_18(pdp_pdp_input_18_signal);
    src.pdp_pdp_input_19(pdp_pdp_input_19_signal);
    src.pdp_pdp_input_20(pdp_pdp_input_20_signal);
    src.pdp_pdp_input_21(pdp_pdp_input_21_signal);
    src.pdp_pdp_input_22(pdp_pdp_input_22_signal);
    src.pdp_pdp_input_23(pdp_pdp_input_23_signal);
    src.pdp_pdp_input_24(pdp_pdp_input_24_signal);
    src.pdp_pdp_input_25(pdp_pdp_input_25_signal);
    src.pdp_pdp_input_26(pdp_pdp_input_26_signal);
    src.pdp_pdp_input_27(pdp_pdp_input_27_signal);
    src.pdp_pdp_input_28(pdp_pdp_input_28_signal);
    src.pdp_pdp_input_29(pdp_pdp_input_29_signal);
    src.pdp_pdp_input_30(pdp_pdp_input_30_signal);
    src.pdp_pdp_input_31(pdp_pdp_input_31_signal);
    src.pdp_pdp_input_32(pdp_pdp_input_32_signal);
    src.pdp_pdp_input_33(pdp_pdp_input_33_signal);
    src.pdp_pdp_input_34(pdp_pdp_input_34_signal);
    src.pdp_pdp_input_35(pdp_pdp_input_35_signal);
    src.pdp_pdp_input_36(pdp_pdp_input_36_signal);
    src.pdp_pdp_input_37(pdp_pdp_input_37_signal);
    src.pdp_pdp_input_38(pdp_pdp_input_38_signal);
    src.pdp_pdp_input_39(pdp_pdp_input_39_signal);
    src.pdp_pdp_input_40(pdp_pdp_input_40_signal);
    src.pdp_pdp_input_41(pdp_pdp_input_41_signal);
    src.pdp_pdp_input_42(pdp_pdp_input_42_signal);
    src.pdp_pdp_input_43(pdp_pdp_input_43_signal);
    src.pdp_pdp_input_44(pdp_pdp_input_44_signal);
    src.pdp_pdp_input_45(pdp_pdp_input_45_signal);
    src.pdp_pdp_input_46(pdp_pdp_input_46_signal);
    src.pdp_pdp_input_47(pdp_pdp_input_47_signal);
    src.pdp_pdp_input_48(pdp_pdp_input_48_signal);
    src.pdp_pdp_input_49(pdp_pdp_input_49_signal);
    src.pdp_pdp_input_50(pdp_pdp_input_50_signal);
    src.pdp_pdp_input_51(pdp_pdp_input_51_signal);
    src.pdp_pdp_input_52(pdp_pdp_input_52_signal);
    src.pdp_pdp_input_53(pdp_pdp_input_53_signal);
    src.pdp_pdp_input_54(pdp_pdp_input_54_signal);
    src.pdp_pdp_input_55(pdp_pdp_input_55_signal);
    src.pdp_pdp_input_56(pdp_pdp_input_56_signal);
    src.pdp_pdp_input_57(pdp_pdp_input_57_signal);
    src.pdp_pdp_input_58(pdp_pdp_input_58_signal);
    src.pdp_pdp_input_59(pdp_pdp_input_59_signal);
    src.pdp_pdp_input_60(pdp_pdp_input_60_signal);
    src.pdp_pdp_input_61(pdp_pdp_input_61_signal);
    src.pdp_pdp_input_62(pdp_pdp_input_62_signal);
    src.pdp_pdp_input_63(pdp_pdp_input_63_signal);

    src.input_done(input_done);

    // Link with the pdp.h SystemC model

    pdp_inst.pdp_csb2pdp_addr_in(pdp_csb2pdp_addr_signal);
    pdp_inst.pdp_csb2pdp_data_in(pdp_csb2pdp_data_signal);
    pdp_inst.pdp_csb2pdp_write_in(pdp_csb2pdp_write_signal);
    pdp_inst.pdp_csb2pdp_vld_in(pdp_csb2pdp_vld_signal);

    pdp_inst.pdp_pdp_last_input_batch_in(pdp_pdp_last_input_batch_signal);
    pdp_inst.pdp_pdp_input_vld_in(pdp_pdp_input_vld_signal);

    pdp_inst.pdp_pdp_input_0_in(pdp_pdp_input_0_signal);
    pdp_inst.pdp_pdp_input_1_in(pdp_pdp_input_1_signal);
    pdp_inst.pdp_pdp_input_2_in(pdp_pdp_input_2_signal);
    pdp_inst.pdp_pdp_input_3_in(pdp_pdp_input_3_signal);
    pdp_inst.pdp_pdp_input_4_in(pdp_pdp_input_4_signal);
    pdp_inst.pdp_pdp_input_5_in(pdp_pdp_input_5_signal);
    pdp_inst.pdp_pdp_input_6_in(pdp_pdp_input_6_signal);
    pdp_inst.pdp_pdp_input_7_in(pdp_pdp_input_7_signal);
    pdp_inst.pdp_pdp_input_8_in(pdp_pdp_input_8_signal);
    pdp_inst.pdp_pdp_input_9_in(pdp_pdp_input_9_signal);
    pdp_inst.pdp_pdp_input_10_in(pdp_pdp_input_10_signal);
    pdp_inst.pdp_pdp_input_11_in(pdp_pdp_input_11_signal);
    pdp_inst.pdp_pdp_input_12_in(pdp_pdp_input_12_signal);
    pdp_inst.pdp_pdp_input_13_in(pdp_pdp_input_13_signal);
    pdp_inst.pdp_pdp_input_14_in(pdp_pdp_input_14_signal);
    pdp_inst.pdp_pdp_input_15_in(pdp_pdp_input_15_signal);
    pdp_inst.pdp_pdp_input_16_in(pdp_pdp_input_16_signal);
    pdp_inst.pdp_pdp_input_17_in(pdp_pdp_input_17_signal);
    pdp_inst.pdp_pdp_input_18_in(pdp_pdp_input_18_signal);
    pdp_inst.pdp_pdp_input_19_in(pdp_pdp_input_19_signal);
    pdp_inst.pdp_pdp_input_20_in(pdp_pdp_input_20_signal);
    pdp_inst.pdp_pdp_input_21_in(pdp_pdp_input_21_signal);
    pdp_inst.pdp_pdp_input_22_in(pdp_pdp_input_22_signal);
    pdp_inst.pdp_pdp_input_23_in(pdp_pdp_input_23_signal);
    pdp_inst.pdp_pdp_input_24_in(pdp_pdp_input_24_signal);
    pdp_inst.pdp_pdp_input_25_in(pdp_pdp_input_25_signal);
    pdp_inst.pdp_pdp_input_26_in(pdp_pdp_input_26_signal);
    pdp_inst.pdp_pdp_input_27_in(pdp_pdp_input_27_signal);
    pdp_inst.pdp_pdp_input_28_in(pdp_pdp_input_28_signal);
    pdp_inst.pdp_pdp_input_29_in(pdp_pdp_input_29_signal);
    pdp_inst.pdp_pdp_input_30_in(pdp_pdp_input_30_signal);
    pdp_inst.pdp_pdp_input_31_in(pdp_pdp_input_31_signal);
    pdp_inst.pdp_pdp_input_32_in(pdp_pdp_input_32_signal);
    pdp_inst.pdp_pdp_input_33_in(pdp_pdp_input_33_signal);
    pdp_inst.pdp_pdp_input_34_in(pdp_pdp_input_34_signal);
    pdp_inst.pdp_pdp_input_35_in(pdp_pdp_input_35_signal);
    pdp_inst.pdp_pdp_input_36_in(pdp_pdp_input_36_signal);
    pdp_inst.pdp_pdp_input_37_in(pdp_pdp_input_37_signal);
    pdp_inst.pdp_pdp_input_38_in(pdp_pdp_input_38_signal);
    pdp_inst.pdp_pdp_input_39_in(pdp_pdp_input_39_signal);
    pdp_inst.pdp_pdp_input_40_in(pdp_pdp_input_40_signal);
    pdp_inst.pdp_pdp_input_41_in(pdp_pdp_input_41_signal);
    pdp_inst.pdp_pdp_input_42_in(pdp_pdp_input_42_signal);
    pdp_inst.pdp_pdp_input_43_in(pdp_pdp_input_43_signal);
    pdp_inst.pdp_pdp_input_44_in(pdp_pdp_input_44_signal);
    pdp_inst.pdp_pdp_input_45_in(pdp_pdp_input_45_signal);
    pdp_inst.pdp_pdp_input_46_in(pdp_pdp_input_46_signal);
    pdp_inst.pdp_pdp_input_47_in(pdp_pdp_input_47_signal);
    pdp_inst.pdp_pdp_input_48_in(pdp_pdp_input_48_signal);
    pdp_inst.pdp_pdp_input_49_in(pdp_pdp_input_49_signal);
    pdp_inst.pdp_pdp_input_50_in(pdp_pdp_input_50_signal);
    pdp_inst.pdp_pdp_input_51_in(pdp_pdp_input_51_signal);
    pdp_inst.pdp_pdp_input_52_in(pdp_pdp_input_52_signal);
    pdp_inst.pdp_pdp_input_53_in(pdp_pdp_input_53_signal);
    pdp_inst.pdp_pdp_input_54_in(pdp_pdp_input_54_signal);
    pdp_inst.pdp_pdp_input_55_in(pdp_pdp_input_55_signal);
    pdp_inst.pdp_pdp_input_56_in(pdp_pdp_input_56_signal);
    pdp_inst.pdp_pdp_input_57_in(pdp_pdp_input_57_signal);
    pdp_inst.pdp_pdp_input_58_in(pdp_pdp_input_58_signal);
    pdp_inst.pdp_pdp_input_59_in(pdp_pdp_input_59_signal);
    pdp_inst.pdp_pdp_input_60_in(pdp_pdp_input_60_signal);
    pdp_inst.pdp_pdp_input_61_in(pdp_pdp_input_61_signal);
    pdp_inst.pdp_pdp_input_62_in(pdp_pdp_input_62_signal);
    pdp_inst.pdp_pdp_input_63_in(pdp_pdp_input_63_signal);

    SC_THREAD(run);
  }

  // Run the SystemC simuation and log outputs
  void run()
  {
    pdp_inst.instr_log.open("instr_log_conv.txt", ofstream::out | ofstream::trunc);
    pdp_inst.instr_update_log.open("instr_update_log_conv.txt", ios::out | ios::trunc);

    std::cout << "*********** simulation start ***********" << std::endl;
    wait(10, SC_NS);

    // Log final outputs
    std::ofstream fout;
    fout.open(file_out, ios::out | ios::trunc);

    int instr_no = 0;

    while (input_done == 0)
    {

      fout << "instr " << std::dec << instr_no++ << ": ";
      fout << std::dec << (sc_dt::sc_bigint<16>)pdp_inst.pdp_pdp_output << std::endl;
      fout  << (sc_dt::sc_biguint<16>)pdp_inst.pdp_pdp_output << std::endl;

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
