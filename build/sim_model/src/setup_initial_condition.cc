#include <pdp.h>
void pdp::setup_initial_condition() {
pdp_pdp2csb_rdy = 1;
pdp_pdp2csb_data_vld = 0;
pdp_pdp_s_status0 = 0;
pdp_pdp_s_status1 = 0;
pdp_pdp_s_producer = 0;
pdp_pdp_s_consumer = 0;
pdp_group0_pdp_d_op_en_trigger = 0;
pdp_pdp_state = 0;
}
