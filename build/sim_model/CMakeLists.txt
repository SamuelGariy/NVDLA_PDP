# CMakeLists.txt for pdp
cmake_minimum_required(VERSION 3.14.0)
project(pdp LANGUAGES CXX)

option(ILATOR_PROFILING "Enable instruction sequence logging and profiling" OFF)
option(ILATOR_VERBOSE "Enable instruction state updates logging" OFF)
option(JSON_SUPPORT "Build JSON parser support" OFF)

find_package(SystemCLanguage CONFIG REQUIRED)
set(CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

aux_source_directory(extern extern_src)
add_executable(pdp
  ${CMAKE_CURRENT_SOURCE_DIR}/app/main.cc
  ${extern_src}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/all_valid_funcs_in_hier.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/compute.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/constant_memory_def.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_load_prepooling_variables.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_max_pool.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_min_pool.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_pdp_start_to_load.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_cube_in_channel.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_cube_in_height.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_cube_in_width.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_cube_out_channel.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_cube_out_height.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_cube_out_width.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_destination_address_high.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_destination_address_low.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_destination_line_stride.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_destination_surface_stride.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_infinity_input_number.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_input_data_format.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_kernel_height_reciprocal.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_kernel_width_height.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_kernel_width_reciprocal.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_nan_flush_to_zero.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_nan_input_number.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_nan_output_number.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_padding_size.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_padding_value_1x.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_padding_value_2x.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_padding_value_3x.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_padding_value_4x.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_padding_value_5x.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_padding_value_6x.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_padding_value_7x.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_partial_width_in.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_partial_width_out.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_perf_count_enable.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_perf_write_stall.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_producer.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_ram_type.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_source_address_high.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_source_address_low.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_source_line_stride.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_source_surface_stride.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_split_number.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idu_set_start_group0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/memory_update_functions_0.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/setup_initial_condition.cc
)

target_include_directories(pdp PRIVATE include)
target_link_libraries(pdp SystemC::systemc)
if(${ILATOR_PROFILING})
  target_compile_definitions(pdp PRIVATE ILATOR_PROFILING)
endif()
if(${ILATOR_VERBOSE})
  target_compile_definitions(pdp PRIVATE ILATOR_PROFILING ILATOR_VERBOSE)
endif()
if(${JSON_SUPPORT})
  include(FetchContent)
  FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.8.0
  )
  FetchContent_MakeAvailable(json)
  target_link_libraries(pdp nlohmann_json::nlohmann_json)
endif()
