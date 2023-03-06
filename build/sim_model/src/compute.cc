#include <iomanip>
#include <pdp.h>
#include <chrono>
static int instr_cntr = 0;
int pdp::GetInstrCntr() {
  return instr_cntr;
}
void pdp::IncrementInstrCntr() {
  instr_cntr++;
}
void pdp::LogInstrSequence(const std::string& instr_name, const long int& exec_time) {
  instr_log << "Instr No. " << std::setw(8) << GetInstrCntr() << '\t';
  instr_log << instr_name << " is activated\t";
  instr_log << "exec_time: " << exec_time * 1e-3 << " us\n";
  IncrementInstrCntr();
}
static bool g_initialized = false;
void pdp::compute() {
if (!g_initialized) {
  setup_initial_condition();
  g_initialized = true;
}
pdp_csb2pdp_addr = pdp_csb2pdp_addr_in.read();
pdp_csb2pdp_data = pdp_csb2pdp_data_in.read();
pdp_csb2pdp_write = pdp_csb2pdp_write_in.read();
pdp_csb2pdp_vld = pdp_csb2pdp_vld_in.read();
pdp_pdp_input_0_0 = pdp_pdp_input_0_0_in.read();
pdp_pdp_input_0_1 = pdp_pdp_input_0_1_in.read();
pdp_pdp_input_0_2 = pdp_pdp_input_0_2_in.read();
pdp_pdp_input_0_3 = pdp_pdp_input_0_3_in.read();
pdp_pdp_input_0_4 = pdp_pdp_input_0_4_in.read();
pdp_pdp_input_0_5 = pdp_pdp_input_0_5_in.read();
pdp_pdp_input_0_6 = pdp_pdp_input_0_6_in.read();
pdp_pdp_input_0_7 = pdp_pdp_input_0_7_in.read();
pdp_pdp_input_0_8 = pdp_pdp_input_0_8_in.read();
pdp_pdp_input_0_9 = pdp_pdp_input_0_9_in.read();
pdp_pdp_input_0_10 = pdp_pdp_input_0_10_in.read();
pdp_pdp_input_0_11 = pdp_pdp_input_0_11_in.read();
pdp_pdp_input_0_12 = pdp_pdp_input_0_12_in.read();
pdp_pdp_input_0_13 = pdp_pdp_input_0_13_in.read();
pdp_pdp_input_0_14 = pdp_pdp_input_0_14_in.read();
pdp_pdp_input_0_15 = pdp_pdp_input_0_15_in.read();
pdp_pdp_input_1_0 = pdp_pdp_input_1_0_in.read();
pdp_pdp_input_1_1 = pdp_pdp_input_1_1_in.read();
pdp_pdp_input_1_2 = pdp_pdp_input_1_2_in.read();
pdp_pdp_input_1_3 = pdp_pdp_input_1_3_in.read();
pdp_pdp_input_1_4 = pdp_pdp_input_1_4_in.read();
pdp_pdp_input_1_5 = pdp_pdp_input_1_5_in.read();
pdp_pdp_input_1_6 = pdp_pdp_input_1_6_in.read();
pdp_pdp_input_1_7 = pdp_pdp_input_1_7_in.read();
pdp_pdp_input_1_8 = pdp_pdp_input_1_8_in.read();
pdp_pdp_input_1_9 = pdp_pdp_input_1_9_in.read();
pdp_pdp_input_1_10 = pdp_pdp_input_1_10_in.read();
pdp_pdp_input_1_11 = pdp_pdp_input_1_11_in.read();
pdp_pdp_input_1_12 = pdp_pdp_input_1_12_in.read();
pdp_pdp_input_1_13 = pdp_pdp_input_1_13_in.read();
pdp_pdp_input_1_14 = pdp_pdp_input_1_14_in.read();
pdp_pdp_input_1_15 = pdp_pdp_input_1_15_in.read();
pdp_pdp_input_2_0 = pdp_pdp_input_2_0_in.read();
pdp_pdp_input_2_1 = pdp_pdp_input_2_1_in.read();
pdp_pdp_input_2_2 = pdp_pdp_input_2_2_in.read();
pdp_pdp_input_2_3 = pdp_pdp_input_2_3_in.read();
pdp_pdp_input_2_4 = pdp_pdp_input_2_4_in.read();
pdp_pdp_input_2_5 = pdp_pdp_input_2_5_in.read();
pdp_pdp_input_2_6 = pdp_pdp_input_2_6_in.read();
pdp_pdp_input_2_7 = pdp_pdp_input_2_7_in.read();
pdp_pdp_input_2_8 = pdp_pdp_input_2_8_in.read();
pdp_pdp_input_2_9 = pdp_pdp_input_2_9_in.read();
pdp_pdp_input_2_10 = pdp_pdp_input_2_10_in.read();
pdp_pdp_input_2_11 = pdp_pdp_input_2_11_in.read();
pdp_pdp_input_2_12 = pdp_pdp_input_2_12_in.read();
pdp_pdp_input_2_13 = pdp_pdp_input_2_13_in.read();
pdp_pdp_input_2_14 = pdp_pdp_input_2_14_in.read();
pdp_pdp_input_2_15 = pdp_pdp_input_2_15_in.read();
pdp_pdp_input_3_0 = pdp_pdp_input_3_0_in.read();
pdp_pdp_input_3_1 = pdp_pdp_input_3_1_in.read();
pdp_pdp_input_3_2 = pdp_pdp_input_3_2_in.read();
pdp_pdp_input_3_3 = pdp_pdp_input_3_3_in.read();
pdp_pdp_input_3_4 = pdp_pdp_input_3_4_in.read();
pdp_pdp_input_3_5 = pdp_pdp_input_3_5_in.read();
pdp_pdp_input_3_6 = pdp_pdp_input_3_6_in.read();
pdp_pdp_input_3_7 = pdp_pdp_input_3_7_in.read();
pdp_pdp_input_3_8 = pdp_pdp_input_3_8_in.read();
pdp_pdp_input_3_9 = pdp_pdp_input_3_9_in.read();
pdp_pdp_input_3_10 = pdp_pdp_input_3_10_in.read();
pdp_pdp_input_3_11 = pdp_pdp_input_3_11_in.read();
pdp_pdp_input_3_12 = pdp_pdp_input_3_12_in.read();
pdp_pdp_input_3_13 = pdp_pdp_input_3_13_in.read();
pdp_pdp_input_3_14 = pdp_pdp_input_3_14_in.read();
pdp_pdp_input_3_15 = pdp_pdp_input_3_15_in.read();
pdp_pdp_input_4_0 = pdp_pdp_input_4_0_in.read();
pdp_pdp_input_4_1 = pdp_pdp_input_4_1_in.read();
pdp_pdp_input_4_2 = pdp_pdp_input_4_2_in.read();
pdp_pdp_input_4_3 = pdp_pdp_input_4_3_in.read();
pdp_pdp_input_4_4 = pdp_pdp_input_4_4_in.read();
pdp_pdp_input_4_5 = pdp_pdp_input_4_5_in.read();
pdp_pdp_input_4_6 = pdp_pdp_input_4_6_in.read();
pdp_pdp_input_4_7 = pdp_pdp_input_4_7_in.read();
pdp_pdp_input_4_8 = pdp_pdp_input_4_8_in.read();
pdp_pdp_input_4_9 = pdp_pdp_input_4_9_in.read();
pdp_pdp_input_4_10 = pdp_pdp_input_4_10_in.read();
pdp_pdp_input_4_11 = pdp_pdp_input_4_11_in.read();
pdp_pdp_input_4_12 = pdp_pdp_input_4_12_in.read();
pdp_pdp_input_4_13 = pdp_pdp_input_4_13_in.read();
pdp_pdp_input_4_14 = pdp_pdp_input_4_14_in.read();
pdp_pdp_input_4_15 = pdp_pdp_input_4_15_in.read();
pdp_pdp_input_5_0 = pdp_pdp_input_5_0_in.read();
pdp_pdp_input_5_1 = pdp_pdp_input_5_1_in.read();
pdp_pdp_input_5_2 = pdp_pdp_input_5_2_in.read();
pdp_pdp_input_5_3 = pdp_pdp_input_5_3_in.read();
pdp_pdp_input_5_4 = pdp_pdp_input_5_4_in.read();
pdp_pdp_input_5_5 = pdp_pdp_input_5_5_in.read();
pdp_pdp_input_5_6 = pdp_pdp_input_5_6_in.read();
pdp_pdp_input_5_7 = pdp_pdp_input_5_7_in.read();
pdp_pdp_input_5_8 = pdp_pdp_input_5_8_in.read();
pdp_pdp_input_5_9 = pdp_pdp_input_5_9_in.read();
pdp_pdp_input_5_10 = pdp_pdp_input_5_10_in.read();
pdp_pdp_input_5_11 = pdp_pdp_input_5_11_in.read();
pdp_pdp_input_5_12 = pdp_pdp_input_5_12_in.read();
pdp_pdp_input_5_13 = pdp_pdp_input_5_13_in.read();
pdp_pdp_input_5_14 = pdp_pdp_input_5_14_in.read();
pdp_pdp_input_5_15 = pdp_pdp_input_5_15_in.read();
pdp_pdp_input_6_0 = pdp_pdp_input_6_0_in.read();
pdp_pdp_input_6_1 = pdp_pdp_input_6_1_in.read();
pdp_pdp_input_6_2 = pdp_pdp_input_6_2_in.read();
pdp_pdp_input_6_3 = pdp_pdp_input_6_3_in.read();
pdp_pdp_input_6_4 = pdp_pdp_input_6_4_in.read();
pdp_pdp_input_6_5 = pdp_pdp_input_6_5_in.read();
pdp_pdp_input_6_6 = pdp_pdp_input_6_6_in.read();
pdp_pdp_input_6_7 = pdp_pdp_input_6_7_in.read();
pdp_pdp_input_6_8 = pdp_pdp_input_6_8_in.read();
pdp_pdp_input_6_9 = pdp_pdp_input_6_9_in.read();
pdp_pdp_input_6_10 = pdp_pdp_input_6_10_in.read();
pdp_pdp_input_6_11 = pdp_pdp_input_6_11_in.read();
pdp_pdp_input_6_12 = pdp_pdp_input_6_12_in.read();
pdp_pdp_input_6_13 = pdp_pdp_input_6_13_in.read();
pdp_pdp_input_6_14 = pdp_pdp_input_6_14_in.read();
pdp_pdp_input_6_15 = pdp_pdp_input_6_15_in.read();
pdp_pdp_input_7_0 = pdp_pdp_input_7_0_in.read();
pdp_pdp_input_7_1 = pdp_pdp_input_7_1_in.read();
pdp_pdp_input_7_2 = pdp_pdp_input_7_2_in.read();
pdp_pdp_input_7_3 = pdp_pdp_input_7_3_in.read();
pdp_pdp_input_7_4 = pdp_pdp_input_7_4_in.read();
pdp_pdp_input_7_5 = pdp_pdp_input_7_5_in.read();
pdp_pdp_input_7_6 = pdp_pdp_input_7_6_in.read();
pdp_pdp_input_7_7 = pdp_pdp_input_7_7_in.read();
pdp_pdp_input_7_8 = pdp_pdp_input_7_8_in.read();
pdp_pdp_input_7_9 = pdp_pdp_input_7_9_in.read();
pdp_pdp_input_7_10 = pdp_pdp_input_7_10_in.read();
pdp_pdp_input_7_11 = pdp_pdp_input_7_11_in.read();
pdp_pdp_input_7_12 = pdp_pdp_input_7_12_in.read();
pdp_pdp_input_7_13 = pdp_pdp_input_7_13_in.read();
pdp_pdp_input_7_14 = pdp_pdp_input_7_14_in.read();
pdp_pdp_input_7_15 = pdp_pdp_input_7_15_in.read();
pdp_pdp_input_8_0 = pdp_pdp_input_8_0_in.read();
pdp_pdp_input_8_1 = pdp_pdp_input_8_1_in.read();
pdp_pdp_input_8_2 = pdp_pdp_input_8_2_in.read();
pdp_pdp_input_8_3 = pdp_pdp_input_8_3_in.read();
pdp_pdp_input_8_4 = pdp_pdp_input_8_4_in.read();
pdp_pdp_input_8_5 = pdp_pdp_input_8_5_in.read();
pdp_pdp_input_8_6 = pdp_pdp_input_8_6_in.read();
pdp_pdp_input_8_7 = pdp_pdp_input_8_7_in.read();
pdp_pdp_input_8_8 = pdp_pdp_input_8_8_in.read();
pdp_pdp_input_8_9 = pdp_pdp_input_8_9_in.read();
pdp_pdp_input_8_10 = pdp_pdp_input_8_10_in.read();
pdp_pdp_input_8_11 = pdp_pdp_input_8_11_in.read();
pdp_pdp_input_8_12 = pdp_pdp_input_8_12_in.read();
pdp_pdp_input_8_13 = pdp_pdp_input_8_13_in.read();
pdp_pdp_input_8_14 = pdp_pdp_input_8_14_in.read();
pdp_pdp_input_8_15 = pdp_pdp_input_8_15_in.read();
pdp_pdp_input_9_0 = pdp_pdp_input_9_0_in.read();
pdp_pdp_input_9_1 = pdp_pdp_input_9_1_in.read();
pdp_pdp_input_9_2 = pdp_pdp_input_9_2_in.read();
pdp_pdp_input_9_3 = pdp_pdp_input_9_3_in.read();
pdp_pdp_input_9_4 = pdp_pdp_input_9_4_in.read();
pdp_pdp_input_9_5 = pdp_pdp_input_9_5_in.read();
pdp_pdp_input_9_6 = pdp_pdp_input_9_6_in.read();
pdp_pdp_input_9_7 = pdp_pdp_input_9_7_in.read();
pdp_pdp_input_9_8 = pdp_pdp_input_9_8_in.read();
pdp_pdp_input_9_9 = pdp_pdp_input_9_9_in.read();
pdp_pdp_input_9_10 = pdp_pdp_input_9_10_in.read();
pdp_pdp_input_9_11 = pdp_pdp_input_9_11_in.read();
pdp_pdp_input_9_12 = pdp_pdp_input_9_12_in.read();
pdp_pdp_input_9_13 = pdp_pdp_input_9_13_in.read();
pdp_pdp_input_9_14 = pdp_pdp_input_9_14_in.read();
pdp_pdp_input_9_15 = pdp_pdp_input_9_15_in.read();
pdp_pdp_input_10_0 = pdp_pdp_input_10_0_in.read();
pdp_pdp_input_10_1 = pdp_pdp_input_10_1_in.read();
pdp_pdp_input_10_2 = pdp_pdp_input_10_2_in.read();
pdp_pdp_input_10_3 = pdp_pdp_input_10_3_in.read();
pdp_pdp_input_10_4 = pdp_pdp_input_10_4_in.read();
pdp_pdp_input_10_5 = pdp_pdp_input_10_5_in.read();
pdp_pdp_input_10_6 = pdp_pdp_input_10_6_in.read();
pdp_pdp_input_10_7 = pdp_pdp_input_10_7_in.read();
pdp_pdp_input_10_8 = pdp_pdp_input_10_8_in.read();
pdp_pdp_input_10_9 = pdp_pdp_input_10_9_in.read();
pdp_pdp_input_10_10 = pdp_pdp_input_10_10_in.read();
pdp_pdp_input_10_11 = pdp_pdp_input_10_11_in.read();
pdp_pdp_input_10_12 = pdp_pdp_input_10_12_in.read();
pdp_pdp_input_10_13 = pdp_pdp_input_10_13_in.read();
pdp_pdp_input_10_14 = pdp_pdp_input_10_14_in.read();
pdp_pdp_input_10_15 = pdp_pdp_input_10_15_in.read();
pdp_pdp_input_11_0 = pdp_pdp_input_11_0_in.read();
pdp_pdp_input_11_1 = pdp_pdp_input_11_1_in.read();
pdp_pdp_input_11_2 = pdp_pdp_input_11_2_in.read();
pdp_pdp_input_11_3 = pdp_pdp_input_11_3_in.read();
pdp_pdp_input_11_4 = pdp_pdp_input_11_4_in.read();
pdp_pdp_input_11_5 = pdp_pdp_input_11_5_in.read();
pdp_pdp_input_11_6 = pdp_pdp_input_11_6_in.read();
pdp_pdp_input_11_7 = pdp_pdp_input_11_7_in.read();
pdp_pdp_input_11_8 = pdp_pdp_input_11_8_in.read();
pdp_pdp_input_11_9 = pdp_pdp_input_11_9_in.read();
pdp_pdp_input_11_10 = pdp_pdp_input_11_10_in.read();
pdp_pdp_input_11_11 = pdp_pdp_input_11_11_in.read();
pdp_pdp_input_11_12 = pdp_pdp_input_11_12_in.read();
pdp_pdp_input_11_13 = pdp_pdp_input_11_13_in.read();
pdp_pdp_input_11_14 = pdp_pdp_input_11_14_in.read();
pdp_pdp_input_11_15 = pdp_pdp_input_11_15_in.read();
pdp_pdp_input_12_0 = pdp_pdp_input_12_0_in.read();
pdp_pdp_input_12_1 = pdp_pdp_input_12_1_in.read();
pdp_pdp_input_12_2 = pdp_pdp_input_12_2_in.read();
pdp_pdp_input_12_3 = pdp_pdp_input_12_3_in.read();
pdp_pdp_input_12_4 = pdp_pdp_input_12_4_in.read();
pdp_pdp_input_12_5 = pdp_pdp_input_12_5_in.read();
pdp_pdp_input_12_6 = pdp_pdp_input_12_6_in.read();
pdp_pdp_input_12_7 = pdp_pdp_input_12_7_in.read();
pdp_pdp_input_12_8 = pdp_pdp_input_12_8_in.read();
pdp_pdp_input_12_9 = pdp_pdp_input_12_9_in.read();
pdp_pdp_input_12_10 = pdp_pdp_input_12_10_in.read();
pdp_pdp_input_12_11 = pdp_pdp_input_12_11_in.read();
pdp_pdp_input_12_12 = pdp_pdp_input_12_12_in.read();
pdp_pdp_input_12_13 = pdp_pdp_input_12_13_in.read();
pdp_pdp_input_12_14 = pdp_pdp_input_12_14_in.read();
pdp_pdp_input_12_15 = pdp_pdp_input_12_15_in.read();
pdp_pdp_input_13_0 = pdp_pdp_input_13_0_in.read();
pdp_pdp_input_13_1 = pdp_pdp_input_13_1_in.read();
pdp_pdp_input_13_2 = pdp_pdp_input_13_2_in.read();
pdp_pdp_input_13_3 = pdp_pdp_input_13_3_in.read();
pdp_pdp_input_13_4 = pdp_pdp_input_13_4_in.read();
pdp_pdp_input_13_5 = pdp_pdp_input_13_5_in.read();
pdp_pdp_input_13_6 = pdp_pdp_input_13_6_in.read();
pdp_pdp_input_13_7 = pdp_pdp_input_13_7_in.read();
pdp_pdp_input_13_8 = pdp_pdp_input_13_8_in.read();
pdp_pdp_input_13_9 = pdp_pdp_input_13_9_in.read();
pdp_pdp_input_13_10 = pdp_pdp_input_13_10_in.read();
pdp_pdp_input_13_11 = pdp_pdp_input_13_11_in.read();
pdp_pdp_input_13_12 = pdp_pdp_input_13_12_in.read();
pdp_pdp_input_13_13 = pdp_pdp_input_13_13_in.read();
pdp_pdp_input_13_14 = pdp_pdp_input_13_14_in.read();
pdp_pdp_input_13_15 = pdp_pdp_input_13_15_in.read();
pdp_pdp_input_14_0 = pdp_pdp_input_14_0_in.read();
pdp_pdp_input_14_1 = pdp_pdp_input_14_1_in.read();
pdp_pdp_input_14_2 = pdp_pdp_input_14_2_in.read();
pdp_pdp_input_14_3 = pdp_pdp_input_14_3_in.read();
pdp_pdp_input_14_4 = pdp_pdp_input_14_4_in.read();
pdp_pdp_input_14_5 = pdp_pdp_input_14_5_in.read();
pdp_pdp_input_14_6 = pdp_pdp_input_14_6_in.read();
pdp_pdp_input_14_7 = pdp_pdp_input_14_7_in.read();
pdp_pdp_input_14_8 = pdp_pdp_input_14_8_in.read();
pdp_pdp_input_14_9 = pdp_pdp_input_14_9_in.read();
pdp_pdp_input_14_10 = pdp_pdp_input_14_10_in.read();
pdp_pdp_input_14_11 = pdp_pdp_input_14_11_in.read();
pdp_pdp_input_14_12 = pdp_pdp_input_14_12_in.read();
pdp_pdp_input_14_13 = pdp_pdp_input_14_13_in.read();
pdp_pdp_input_14_14 = pdp_pdp_input_14_14_in.read();
pdp_pdp_input_14_15 = pdp_pdp_input_14_15_in.read();
pdp_pdp_input_15_0 = pdp_pdp_input_15_0_in.read();
pdp_pdp_input_15_1 = pdp_pdp_input_15_1_in.read();
pdp_pdp_input_15_2 = pdp_pdp_input_15_2_in.read();
pdp_pdp_input_15_3 = pdp_pdp_input_15_3_in.read();
pdp_pdp_input_15_4 = pdp_pdp_input_15_4_in.read();
pdp_pdp_input_15_5 = pdp_pdp_input_15_5_in.read();
pdp_pdp_input_15_6 = pdp_pdp_input_15_6_in.read();
pdp_pdp_input_15_7 = pdp_pdp_input_15_7_in.read();
pdp_pdp_input_15_8 = pdp_pdp_input_15_8_in.read();
pdp_pdp_input_15_9 = pdp_pdp_input_15_9_in.read();
pdp_pdp_input_15_10 = pdp_pdp_input_15_10_in.read();
pdp_pdp_input_15_11 = pdp_pdp_input_15_11_in.read();
pdp_pdp_input_15_12 = pdp_pdp_input_15_12_in.read();
pdp_pdp_input_15_13 = pdp_pdp_input_15_13_in.read();
pdp_pdp_input_15_14 = pdp_pdp_input_15_14_in.read();
pdp_pdp_input_15_15 = pdp_pdp_input_15_15_in.read();
pdp_pdp_last_input_batch = pdp_pdp_last_input_batch_in.read();
if (valid_pdp() && decode_pdp_set_producer()) {
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
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_start_group0();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_start_group0", exec_time);
#endif
}
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
}
if (valid_pdp() && decode_pdp_set_kernel_width_height()) {
#ifdef ILATOR_PROFILING
  auto start = std::chrono::high_resolution_clock::now();
#endif
  update_pdp_set_kernel_width_height();
  
#ifdef ILATOR_PROFILING
  auto stop = std::chrono::high_resolution_clock::now();
  auto exec_time = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
  LogInstrSequence("set_kernel_width_height", exec_time);
#endif
}
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
while (1) {
  int schedule_counter = 0;
  if (schedule_counter == 0) {
    break;
  }
}
}
