#include <pdp.h>
bool pdp::decode_pdp_load_prepooling_variables() {
sc_biguint<3> local_var_1 = 1;
bool local_var_2 = (pdp_pdp_state == local_var_1);
auto& univ_var_40 = local_var_2;
return univ_var_40;
}
void pdp::update_pdp_load_prepooling_variables() {
auto local_var_1 = pdp_group0_pdp_d_cube_in_channel.range(12, 0);
auto local_var_1_nxt_holder = local_var_1;
auto local_var_3 = pdp_group0_pdp_d_pad_value_1x.range(15, 0);
auto local_var_3_nxt_holder = local_var_3;
sc_biguint<2> local_var_4 = 0;
auto local_var_4_nxt_holder = local_var_4;
sc_biguint<2> local_var_6 = 1;
bool local_var_7 = (pdp_group0_pdp_d_pooling_method == local_var_6);
sc_biguint<3> local_var_8 = 2;
sc_biguint<2> local_var_9 = 2;
bool local_var_10 = (pdp_group0_pdp_d_pooling_method == local_var_9);
sc_biguint<3> local_var_11 = 3;
sc_biguint<3> local_var_12 = 4;
auto local_var_13 = (local_var_10) ? local_var_11 : local_var_12;
auto local_var_14 = (local_var_7) ? local_var_8 : local_var_13;
auto local_var_14_nxt_holder = local_var_14;
pdp_group0_pdp_d_cube_out_channel = local_var_1_nxt_holder;
pdp_pdp_padding_value = local_var_3_nxt_holder;
pdp_pdp_pooling_stage_split_width = local_var_4_nxt_holder;
pdp_pdp_state = local_var_14_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "load_prepooling_variables state updates:" << std::endl;
instr_update_log << "    pdp_group0_pdp_d_cube_out_channel => " << std::hex << "0x" << pdp_group0_pdp_d_cube_out_channel << std::endl; 
instr_update_log << "    pdp_pdp_padding_value => " << std::hex << "0x" << pdp_pdp_padding_value << std::endl; 
instr_update_log << "    pdp_pdp_pooling_stage_split_width => " << std::hex << "0x" << pdp_pdp_pooling_stage_split_width << std::endl; 
instr_update_log << "    pdp_pdp_state => " << std::hex << "0x" << pdp_pdp_state << std::endl; 
instr_update_log << std::endl;
#endif
}
