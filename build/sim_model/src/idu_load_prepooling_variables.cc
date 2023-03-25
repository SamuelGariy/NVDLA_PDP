#include <pdp.h>
bool pdp::decode_pdp_load_prepooling_variables() {
sc_biguint<3> local_var_1 = 1;
bool local_var_2 = (pdp_pdp_state == local_var_1);
auto& univ_var_40 = local_var_2;
return univ_var_40;
}
void pdp::update_pdp_load_prepooling_variables() {
sc_biguint<2> local_var_1 = 1;
bool local_var_2 = (pdp_group0_pdp_d_pooling_method == local_var_1);
sc_biguint<3> local_var_3 = 2;
sc_biguint<2> local_var_4 = 2;
bool local_var_5 = (pdp_group0_pdp_d_pooling_method == local_var_4);
sc_biguint<3> local_var_6 = 3;
sc_biguint<3> local_var_7 = 4;
auto local_var_8 = (local_var_5) ? local_var_6 : local_var_7;
auto local_var_9 = (local_var_2) ? local_var_3 : local_var_8;
auto local_var_9_nxt_holder = local_var_9;
pdp_pdp_state = local_var_9_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "load_prepooling_variables state updates:" << std::endl;
instr_update_log << "    pdp_pdp_state => " << std::hex << "0x" << pdp_pdp_state << std::endl; 
instr_update_log << std::endl;
#endif
}
