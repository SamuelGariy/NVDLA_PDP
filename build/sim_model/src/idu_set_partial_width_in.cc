#include <pdp.h>
bool pdp::decode_pdp_set_partial_width_in() {
auto local_var_1 = pdp_csb2pdp_addr.range(11, 0);
sc_biguint<12> local_var_2 = 44;
bool local_var_3 = (local_var_1 == local_var_2);
sc_biguint<1> local_var_5 = 1;
bool local_var_6 = (pdp_pdp2csb_rdy == local_var_5);
sc_biguint<1> local_var_8 = 1;
bool local_var_9 = (pdp_csb2pdp_vld == local_var_8);
bool local_var_10 = (local_var_6 & local_var_9);
bool local_var_11 = (local_var_3 & local_var_10);
sc_biguint<1> local_var_13 = 1;
bool local_var_14 = (pdp_csb2pdp_write == local_var_13);
bool local_var_15 = (local_var_11 & local_var_14);
auto& univ_var_11 = local_var_15;
return univ_var_11;
}
void pdp::update_pdp_set_partial_width_in() {
auto local_var_1 = pdp_csb2pdp_data.range(9, 0);
auto local_var_1_nxt_holder = local_var_1;
auto local_var_2 = pdp_csb2pdp_data.range(29, 20);
auto local_var_2_nxt_holder = local_var_2;
auto local_var_3 = pdp_csb2pdp_data.range(19, 10);
auto local_var_3_nxt_holder = local_var_3;
pdp_group0_pdp_d_partial_width_in_first = local_var_1_nxt_holder;
pdp_group0_pdp_d_partial_width_in_last = local_var_2_nxt_holder;
pdp_group0_pdp_d_partial_width_in_mid = local_var_3_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "set_partial_width_in state updates:" << std::endl;
instr_update_log << "    pdp_group0_pdp_d_partial_width_in_first => " << std::hex << "0x" << pdp_group0_pdp_d_partial_width_in_first << std::endl; 
instr_update_log << "    pdp_group0_pdp_d_partial_width_in_last => " << std::hex << "0x" << pdp_group0_pdp_d_partial_width_in_last << std::endl; 
instr_update_log << "    pdp_group0_pdp_d_partial_width_in_mid => " << std::hex << "0x" << pdp_group0_pdp_d_partial_width_in_mid << std::endl; 
instr_update_log << std::endl;
#endif
}
