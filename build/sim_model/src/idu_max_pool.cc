#include <pdp.h>
bool pdp::decode_pdp_max_pool() {
sc_biguint<3> local_var_1 = 2;
bool local_var_2 = (pdp_pdp_state == local_var_1);
auto& univ_var_41 = local_var_2;
return univ_var_41;
}
void pdp::update_pdp_max_pool() {
bool local_var_1 = true;
bool local_var_2 = (pdp_pdp_last_input_batch == local_var_1);
sc_biguint<1> local_var_3 = 0;
sc_biguint<1> local_var_4 = 1;
auto local_var_5 = (local_var_2) ? local_var_3 : local_var_4;
auto local_var_5_nxt_holder = local_var_5;
sc_biguint<1> local_var_6 = 1;
auto local_var_6_nxt_holder = local_var_6;
std::unordered_map<int, sc_biguint<16>, MemAddrHashFunc> local_var_7;
store_42(local_var_7);
bool local_var_8 = true;
bool local_var_9 = (pdp_pdp_last_input_batch == local_var_8);
sc_biguint<3> local_var_10 = 0;
sc_biguint<3> local_var_11 = 2;
auto local_var_12 = (local_var_9) ? local_var_10 : local_var_11;
auto local_var_12_nxt_holder = local_var_12;
pdp_group0_pdp_d_op_en_trigger = local_var_5_nxt_holder;
pdp_pdp2csb_data_vld = local_var_6_nxt_holder;
for (auto& it : local_var_7) {
  pdp_pdp_output[it.first] = it.second;
}
pdp_pdp_state = local_var_12_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "max_pool state updates:" << std::endl;
instr_update_log << "    pdp_group0_pdp_d_op_en_trigger => " << std::hex << "0x" << pdp_group0_pdp_d_op_en_trigger << std::endl; 
instr_update_log << "    pdp_pdp2csb_data_vld => " << std::hex << "0x" << pdp_pdp2csb_data_vld << std::endl; 
instr_update_log << "    pdp_pdp_output get updated" << std::endl;
instr_update_log << "    pdp_pdp_state => " << std::hex << "0x" << pdp_pdp_state << std::endl; 
instr_update_log << std::endl;
#endif
}
