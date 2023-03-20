#include <pdp.h>
bool pdp::decode_pdp_set_kernel_width_height() {
 std::cout << "decode kernel_width_height 1" << std::endl;
auto local_var_1 = pdp_csb2pdp_addr.range(11, 0);
 std::cout << "decode kernel_width_height 2" << std::endl;
sc_biguint<12> local_var_2 = 52;
 std::cout << "decode kernel_width_height 3" << std::endl;
bool local_var_3 = (local_var_1 == local_var_2);
 std::cout << "decode kernel_width_height 4" << std::endl;
sc_biguint<1> local_var_5 = 1;
 std::cout << "decode kernel_width_height 5" << std::endl;
bool local_var_6 = (pdp_pdp2csb_rdy == local_var_5);
 std::cout << "decode kernel_width_height 6" << std::endl;
sc_biguint<1> local_var_8 = 1;
 std::cout << "decode kernel_width_height 7" << std::endl;
bool local_var_9 = (pdp_csb2pdp_vld == local_var_8);
 std::cout << "decode kernel_width_height 8" << std::endl;
bool local_var_10 = (local_var_6 & local_var_9);
 std::cout << "decode kernel_width_height 9" << std::endl;
bool local_var_11 = (local_var_3 & local_var_10);
 std::cout << "decode kernel_width_height 10" << std::endl;
sc_biguint<1> local_var_13 = 1;
 std::cout << "decode kernel_width_height 11" << std::endl;
bool local_var_14 = (pdp_csb2pdp_write == local_var_13);
 std::cout << "decode kernel_width_height 12" << std::endl;
bool local_var_15 = (local_var_11 & local_var_14);
 std::cout << "decode kernel_width_height 13" << std::endl;
auto& univ_var_13 = local_var_15;
std::cout << local_var_15 << std::endl;

return univ_var_13;
}
 //std::cout << "decode kernel_width_height 15" << std::endl;
void pdp::update_pdp_set_kernel_width_height() {
auto local_var_1 = pdp_csb2pdp_data.range(11, 8);
auto local_var_1_nxt_holder = local_var_1;
auto local_var_2 = pdp_csb2pdp_data.range(23, 20);
auto local_var_2_nxt_holder = local_var_2;
auto local_var_3 = pdp_csb2pdp_data.range(3, 0);
auto local_var_3_nxt_holder = local_var_3;
auto local_var_4 = pdp_csb2pdp_data.range(19, 16);
auto local_var_4_nxt_holder = local_var_4;
pdp_group0_pdp_d_kernel_height = local_var_1_nxt_holder;
pdp_group0_pdp_d_kernel_stride_width = local_var_2_nxt_holder;
pdp_group0_pdp_d_kernel_width = local_var_3_nxt_holder;
pdp_group0_pdp_kernel_stride_height = local_var_4_nxt_holder;
#ifdef ILATOR_VERBOSE
instr_update_log << "No." << std::dec << GetInstrCntr() << '\t' << "set_kernel_width_height state updates:" << std::endl;
instr_update_log << "    pdp_group0_pdp_d_kernel_height => " << std::hex << "0x" << pdp_group0_pdp_d_kernel_height << std::endl; 
instr_update_log << "    pdp_group0_pdp_d_kernel_stride_width => " << std::hex << "0x" << pdp_group0_pdp_d_kernel_stride_width << std::endl; 
instr_update_log << "    pdp_group0_pdp_d_kernel_width => " << std::hex << "0x" << pdp_group0_pdp_d_kernel_width << std::endl; 
instr_update_log << "    pdp_group0_pdp_kernel_stride_height => " << std::hex << "0x" << pdp_group0_pdp_kernel_stride_height << std::endl; 
instr_update_log << std::endl;
#endif
}
