#include <pdp.h>
bool pdp::decode_pdp_pdp_start_to_load() {
sc_biguint<3> local_var_1 = 0;
bool local_var_2 = (pdp_pdp_state == local_var_1);
sc_biguint<1> local_var_4 = 0;
bool local_var_5 = (pdp_pdp_s_consumer == local_var_4);
sc_biguint<1> local_var_7 = 1;
bool local_var_8 = (pdp_group0_pdp_d_op_en_trigger == local_var_7);
bool local_var_9 = (local_var_5 & local_var_8);
bool local_var_10 = (local_var_2 & local_var_9);
bool local_var_12 = (local_var_10 & pdp_pdp_input_vld);
auto& univ_var_39 = local_var_12;
return univ_var_39;
}
void pdp::update_pdp_pdp_start_to_load() {
sc_biguint<3> local_var_0 = 1;
auto local_var_0_nxt_holder = local_var_0;
pdp_pdp_state = local_var_0_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "pdp_start_to_load state updates:" << std::endl;
instr_update_log << "    pdp_pdp_state => " << std::hex << "0x" << pdp_pdp_state << std::endl; 
instr_update_log << std::endl;
#endif
}
