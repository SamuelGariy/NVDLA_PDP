#include <iomanip>
#include <pdp.h>
#include <chrono>
static int instr_cntr = 0;
int pdp::GetInstrCntr() {
  std::cout << "GetInstrCntr" << std::endl;
  return instr_cntr;
}
void pdp::IncrementInstrCntr() {
   std::cout << "GetInstrCntr" << std::endl;
  instr_cntr++;
}
void pdp::LogInstrSequence(const std::string& instr_name, const long int& exec_time) {
  std::cout << "LogInstrSequence1" << std::endl;
  instr_log << "Instr No. " << std::setw(8) << GetInstrCntr() << '\t';
  std::cout << "LogInstrSequence2" << std::endl;
  instr_log << instr_name << " is activated\t";
    std::cout << "LogInstrSequence3" << std::endl;
  instr_log << "exec_time: " << exec_time * 1e-3 << " us\n";
    std::cout << "LogInstrSequence4" << std::endl;
  IncrementInstrCntr();
   std::cout << "LogInstrSequence_end" << std::endl;
}
static bool g_initialized = false;
void pdp::compute() {
  std::cout << "compute_start" << std::endl;
if (!g_initialized) {
  setup_initial_condition();
  g_initialized = true;
    std::cout << "initialised" << std::endl;
}
 std::cout << "inputs_read_start" << std::endl;
pdp_csb2pdp_addr = pdp_csb2pdp_addr_in.read();
pdp_csb2pdp_data = pdp_csb2pdp_data_in.read();
pdp_csb2pdp_write = pdp_csb2pdp_write_in.read();
pdp_csb2pdp_vld = pdp_csb2pdp_vld_in.read();
pdp_pdp_input_0 = pdp_pdp_input_0_in.read();
pdp_pdp_input_1 = pdp_pdp_input_1_in.read();
pdp_pdp_input_2 = pdp_pdp_input_2_in.read();
pdp_pdp_input_3 = pdp_pdp_input_3_in.read();
pdp_pdp_input_4 = pdp_pdp_input_4_in.read();
pdp_pdp_input_5 = pdp_pdp_input_5_in.read();
pdp_pdp_input_6 = pdp_pdp_input_6_in.read();
pdp_pdp_input_7 = pdp_pdp_input_7_in.read();
pdp_pdp_input_8 = pdp_pdp_input_8_in.read();
pdp_pdp_input_9 = pdp_pdp_input_9_in.read();
pdp_pdp_input_10 = pdp_pdp_input_10_in.read();
pdp_pdp_input_11 = pdp_pdp_input_11_in.read();
pdp_pdp_input_12 = pdp_pdp_input_12_in.read();
pdp_pdp_input_13 = pdp_pdp_input_13_in.read();
pdp_pdp_input_14 = pdp_pdp_input_14_in.read();
pdp_pdp_input_15 = pdp_pdp_input_15_in.read();
pdp_pdp_input_16 = pdp_pdp_input_16_in.read();
pdp_pdp_input_17 = pdp_pdp_input_17_in.read();
pdp_pdp_input_18 = pdp_pdp_input_18_in.read();
pdp_pdp_input_19 = pdp_pdp_input_19_in.read();
pdp_pdp_input_20 = pdp_pdp_input_20_in.read();
pdp_pdp_input_21 = pdp_pdp_input_21_in.read();
pdp_pdp_input_22 = pdp_pdp_input_22_in.read();
pdp_pdp_input_23 = pdp_pdp_input_23_in.read();
pdp_pdp_input_24 = pdp_pdp_input_24_in.read();
pdp_pdp_input_25 = pdp_pdp_input_25_in.read();
pdp_pdp_input_26 = pdp_pdp_input_26_in.read();
pdp_pdp_input_27 = pdp_pdp_input_27_in.read();
pdp_pdp_input_28 = pdp_pdp_input_28_in.read();
pdp_pdp_input_29 = pdp_pdp_input_29_in.read();
pdp_pdp_input_30 = pdp_pdp_input_30_in.read();
pdp_pdp_input_31 = pdp_pdp_input_31_in.read();
pdp_pdp_input_32 = pdp_pdp_input_32_in.read();
pdp_pdp_input_33 = pdp_pdp_input_33_in.read();
pdp_pdp_input_34 = pdp_pdp_input_34_in.read();
pdp_pdp_input_35 = pdp_pdp_input_35_in.read();
pdp_pdp_input_36 = pdp_pdp_input_36_in.read();
pdp_pdp_input_37 = pdp_pdp_input_37_in.read();
pdp_pdp_input_38 = pdp_pdp_input_38_in.read();
pdp_pdp_input_39 = pdp_pdp_input_39_in.read();
pdp_pdp_input_40 = pdp_pdp_input_40_in.read();
pdp_pdp_input_41 = pdp_pdp_input_41_in.read();
pdp_pdp_input_42 = pdp_pdp_input_42_in.read();
pdp_pdp_input_43 = pdp_pdp_input_43_in.read();
pdp_pdp_input_44 = pdp_pdp_input_44_in.read();
pdp_pdp_input_45 = pdp_pdp_input_45_in.read();
pdp_pdp_input_46 = pdp_pdp_input_46_in.read();
pdp_pdp_input_47 = pdp_pdp_input_47_in.read();
pdp_pdp_input_48 = pdp_pdp_input_48_in.read();
pdp_pdp_input_49 = pdp_pdp_input_49_in.read();
pdp_pdp_input_50 = pdp_pdp_input_50_in.read();
pdp_pdp_input_51 = pdp_pdp_input_51_in.read();
pdp_pdp_input_52 = pdp_pdp_input_52_in.read();
pdp_pdp_input_53 = pdp_pdp_input_53_in.read();
pdp_pdp_input_54 = pdp_pdp_input_54_in.read();
pdp_pdp_input_55 = pdp_pdp_input_55_in.read();
pdp_pdp_input_56 = pdp_pdp_input_56_in.read();
pdp_pdp_input_57 = pdp_pdp_input_57_in.read();
pdp_pdp_input_58 = pdp_pdp_input_58_in.read();
pdp_pdp_input_59 = pdp_pdp_input_59_in.read();
pdp_pdp_input_60 = pdp_pdp_input_60_in.read();
pdp_pdp_input_61 = pdp_pdp_input_61_in.read();
pdp_pdp_input_62 = pdp_pdp_input_62_in.read();
pdp_pdp_input_63 = pdp_pdp_input_63_in.read();
pdp_pdp_last_input_batch = pdp_pdp_last_input_batch_in.read();
 std::cout << "inputs_read" << std::endl;
if (valid_pdp() && decode_pdp_set_producer()) {
  std::cout << "decode_pdp_set_producer" << std::endl;
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_producer();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_producer", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_start_group0()) {
  std::cout << "decode_pdp_set_start_group0" << std::endl;
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_start_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_start_group0", exec_time);
#endif
 std::cout << "after_decode_pdp_set_start_group0" << std::endl;
}
 std::cout << "1" << std::endl;
if (valid_pdp() && decode_pdp_set_cube_in_width()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_cube_in_width();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_cube_in_width", exec_time);
#endif
}
 std::cout << "2" << std::endl;
if (valid_pdp() && decode_pdp_set_cube_in_height()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_cube_in_height();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_cube_in_height", exec_time);
#endif
}
 std::cout << "3" << std::endl;
if (valid_pdp() && decode_pdp_set_cube_in_channel()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_cube_in_channel();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_cube_in_channel", exec_time);
#endif
}
 std::cout << "4" << std::endl;
if (valid_pdp() && decode_pdp_set_cube_out_width()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_cube_out_width();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_cube_out_width", exec_time);
#endif
}
 std::cout << "5" << std::endl;
if (valid_pdp() && decode_pdp_set_cube_out_height()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_cube_out_height();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_cube_out_height", exec_time);
#endif
}
 std::cout << "6" << std::endl;
if (valid_pdp() && decode_pdp_set_cube_out_channel()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_cube_out_channel();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_cube_out_channel", exec_time);
#endif
}
 std::cout << "7" << std::endl;
if (valid_pdp() && decode_pdp_set_split_number()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_split_number();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_split_number", exec_time);
#endif
}
 std::cout << "8" << std::endl;
if (valid_pdp() && decode_pdp_set_nan_flush_to_zero()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_nan_flush_to_zero();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_nan_flush_to_zero", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_partial_width_in()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_partial_width_in();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_partial_width_in", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_partial_width_out()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_partial_width_out();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_partial_width_out", exec_time);
#endif
  std::cout << "before_kernel_width_height" << std::endl;
}
 std::cout << "before kernel" << std::endl;
if (valid_pdp() && decode_pdp_set_kernel_width_height()) {
   std::cout << "decode_pdp_set_kernel_width_height" << std::endl;
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
   std::cout << "decode_pdp_set_kernel_width_height_clock" << std::endl;
#endif
 std::cout << "before update_pdp_set_kernel_width_height" << std::endl;
  update_pdp_set_kernel_width_height();
  std::cout << "after update_pdp_set_kernel_width_height" << std::endl;
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_kernel_width_height", exec_time);
#endif
std::cout << "end kernel height wdth" << std::endl;
}
std::cout << "11" << std::endl;
if (valid_pdp() && decode_pdp_set_kernel_width_reciprocal()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_kernel_width_reciprocal();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_kernel_width_reciprocal", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_kernel_height_reciprocal()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_kernel_height_reciprocal();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_kernel_height_reciprocal", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_padding_size()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_padding_size();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_padding_size", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_padding_value_1x()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_padding_value_1x();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_padding_value_1x", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_padding_value_2x()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_padding_value_2x();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_padding_value_2x", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_padding_value_3x()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_padding_value_3x();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_padding_value_3x", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_padding_value_4x()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_padding_value_4x();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_padding_value_4x", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_padding_value_5x()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_padding_value_5x();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_padding_value_5x", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_padding_value_6x()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_padding_value_6x();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_padding_value_6x", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_padding_value_7x()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_padding_value_7x();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_padding_value_7x", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_source_address_low()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_source_address_low();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_source_address_low", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_source_address_high()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_source_address_high();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_source_address_high", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_source_line_stride()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_source_line_stride();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_source_line_stride", exec_time);
#endif
}
std::cout << "12" << std::endl;
if (valid_pdp() && decode_pdp_set_source_surface_stride()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_source_surface_stride();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_source_surface_stride", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_destination_address_low()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_destination_address_low();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_destination_address_low", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_destination_address_high()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_destination_address_high();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_destination_address_high", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_destination_line_stride()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_destination_line_stride();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_destination_line_stride", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_destination_surface_stride()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_destination_surface_stride();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_destination_surface_stride", exec_time);
#endif
}
std::cout << "13" << std::endl;
if (valid_pdp() && decode_pdp_set_ram_type()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_ram_type();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_ram_type", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_input_data_format()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_input_data_format();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_input_data_format", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_infinity_input_number()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_infinity_input_number();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_infinity_input_number", exec_time);
#endif
}
std::cout << "14" << std::endl;
if (valid_pdp() && decode_pdp_set_nan_input_number()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_nan_input_number();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_nan_input_number", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_nan_output_number()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_nan_output_number();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_nan_output_number", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_perf_count_enable()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_perf_count_enable();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_perf_count_enable", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_set_perf_write_stall()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_perf_write_stall();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_perf_write_stall", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_pdp_start_to_load()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_pdp_start_to_load();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("pdp_start_to_load", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_load_prepooling_variables()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_load_prepooling_variables();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("load_prepooling_variables", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_max_pool()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_max_pool();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("max_pool", exec_time);
#endif
}
if (valid_pdp() && decode_pdp_min_pool()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_min_pool();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("min_pool", exec_time);
#endif
}
std::cout << "end of ins sequence" << std::endl;
while (1) {
  int schedule_counter = 0;
  if (schedule_counter == 0) {
    break;
  }
}
std::cout << "instruction_up" << std::endl;
}
