/* Include files */

#include <stddef.h>
#include "blas.h"
#include "hexacopter_sfun.h"
#include "c6_hexacopter.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hexacopter_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c6_debug_family_names[17] = { "MEMORY", "alpha",
  "optimized_vector", "optimized", "nargin", "nargout", "pos", "H", "pos_trasm",
  "m_trasm", "pos_opt", "m_opt", "counter", "Hfield_memory", "Rposition_memory",
  "RT", "M" };

/* Function Declarations */
static void initialize_c6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance);
static void initialize_params_c6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance);
static void enable_c6_hexacopter(SFc6_hexacopterInstanceStruct *chartInstance);
static void disable_c6_hexacopter(SFc6_hexacopterInstanceStruct *chartInstance);
static void c6_update_debugger_state_c6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c6_hexacopter(SFc6_hexacopterInstanceStruct *
  chartInstance);
static void set_sim_state_c6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance, const mxArray *c6_st);
static void finalize_c6_hexacopter(SFc6_hexacopterInstanceStruct *chartInstance);
static void sf_gateway_c6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance);
static void initSimStructsc6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber, uint32_T c6_instanceNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static void c6_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_b_M, const char_T *c6_identifier, real_T c6_y[3]);
static void c6_b_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3]);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_c_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_b_RT, const char_T *c6_identifier, real_T c6_y[3]);
static void c6_d_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3]);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_e_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_b_Rposition_memory, const char_T *c6_identifier, real_T
  c6_y[12]);
static void c6_f_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[12]);
static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_g_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_b_Hfield_memory, const char_T *c6_identifier, real_T c6_y[12]);
static void c6_h_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[12]);
static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static real_T c6_i_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_b_counter, const char_T *c6_identifier);
static real_T c6_j_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_f_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_k_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_m_opt, const char_T *c6_identifier, real_T c6_y[3]);
static void c6_l_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3]);
static void c6_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_g_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_m_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_m_trasm, const char_T *c6_identifier, real_T c6_y[3]);
static void c6_n_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3]);
static void c6_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_h_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static real_T c6_o_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_i_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_j_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static void c6_info_helper(const mxArray **c6_info);
static const mxArray *c6_emlrt_marshallOut(const char * c6_u);
static const mxArray *c6_b_emlrt_marshallOut(const uint32_T c6_u);
static void c6_p_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_optimized, const char_T *c6_identifier, real_T c6_y[6]);
static void c6_q_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[6]);
static const mxArray *c6_k_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static int32_T c6_r_emlrt_marshallIn(SFc6_hexacopterInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static uint8_T c6_s_emlrt_marshallIn(SFc6_hexacopterInstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_hexacopter, const char_T
  *c6_identifier);
static uint8_T c6_t_emlrt_marshallIn(SFc6_hexacopterInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void init_dsm_address_info(SFc6_hexacopterInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance)
{
  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c6_counter_not_empty = false;
  chartInstance->c6_Hfield_memory_not_empty = false;
  chartInstance->c6_Rposition_memory_not_empty = false;
  chartInstance->c6_RT_not_empty = false;
  chartInstance->c6_M_not_empty = false;
  chartInstance->c6_is_active_c6_hexacopter = 0U;
}

static void initialize_params_c6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c6_hexacopter(SFc6_hexacopterInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c6_hexacopter(SFc6_hexacopterInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c6_update_debugger_state_c6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c6_hexacopter(SFc6_hexacopterInstanceStruct *
  chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  int32_T c6_i0;
  real_T c6_u[3];
  const mxArray *c6_b_y = NULL;
  int32_T c6_i1;
  real_T c6_b_u[3];
  const mxArray *c6_c_y = NULL;
  int32_T c6_i2;
  real_T c6_c_u[3];
  const mxArray *c6_d_y = NULL;
  int32_T c6_i3;
  real_T c6_d_u[3];
  const mxArray *c6_e_y = NULL;
  int32_T c6_i4;
  real_T c6_e_u[12];
  const mxArray *c6_f_y = NULL;
  int32_T c6_i5;
  real_T c6_f_u[3];
  const mxArray *c6_g_y = NULL;
  int32_T c6_i6;
  real_T c6_g_u[3];
  const mxArray *c6_h_y = NULL;
  int32_T c6_i7;
  real_T c6_h_u[12];
  const mxArray *c6_i_y = NULL;
  real_T c6_hoistedGlobal;
  real_T c6_i_u;
  const mxArray *c6_j_y = NULL;
  uint8_T c6_b_hoistedGlobal;
  uint8_T c6_j_u;
  const mxArray *c6_k_y = NULL;
  real_T (*c6_pos_trasm)[3];
  real_T (*c6_pos_opt)[3];
  real_T (*c6_m_trasm)[3];
  real_T (*c6_m_opt)[3];
  c6_m_opt = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c6_pos_opt = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c6_m_trasm = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c6_pos_trasm = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellmatrix(10, 1), false);
  for (c6_i0 = 0; c6_i0 < 3; c6_i0++) {
    c6_u[c6_i0] = (*c6_m_opt)[c6_i0];
  }

  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  for (c6_i1 = 0; c6_i1 < 3; c6_i1++) {
    c6_b_u[c6_i1] = (*c6_m_trasm)[c6_i1];
  }

  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", c6_b_u, 0, 0U, 1U, 0U, 2, 1, 3),
                false);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  for (c6_i2 = 0; c6_i2 < 3; c6_i2++) {
    c6_c_u[c6_i2] = (*c6_pos_opt)[c6_i2];
  }

  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", c6_c_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c6_y, 2, c6_d_y);
  for (c6_i3 = 0; c6_i3 < 3; c6_i3++) {
    c6_d_u[c6_i3] = (*c6_pos_trasm)[c6_i3];
  }

  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", c6_d_u, 0, 0U, 1U, 0U, 2, 1, 3),
                false);
  sf_mex_setcell(c6_y, 3, c6_e_y);
  for (c6_i4 = 0; c6_i4 < 12; c6_i4++) {
    c6_e_u[c6_i4] = chartInstance->c6_Hfield_memory[c6_i4];
  }

  c6_f_y = NULL;
  if (!chartInstance->c6_Hfield_memory_not_empty) {
    sf_mex_assign(&c6_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c6_f_y, sf_mex_create("y", c6_e_u, 0, 0U, 1U, 0U, 2, 4, 3),
                  false);
  }

  sf_mex_setcell(c6_y, 4, c6_f_y);
  for (c6_i5 = 0; c6_i5 < 3; c6_i5++) {
    c6_f_u[c6_i5] = chartInstance->c6_M[c6_i5];
  }

  c6_g_y = NULL;
  if (!chartInstance->c6_M_not_empty) {
    sf_mex_assign(&c6_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c6_g_y, sf_mex_create("y", c6_f_u, 0, 0U, 1U, 0U, 2, 1, 3),
                  false);
  }

  sf_mex_setcell(c6_y, 5, c6_g_y);
  for (c6_i6 = 0; c6_i6 < 3; c6_i6++) {
    c6_g_u[c6_i6] = chartInstance->c6_RT[c6_i6];
  }

  c6_h_y = NULL;
  if (!chartInstance->c6_RT_not_empty) {
    sf_mex_assign(&c6_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c6_h_y, sf_mex_create("y", c6_g_u, 0, 0U, 1U, 0U, 2, 1, 3),
                  false);
  }

  sf_mex_setcell(c6_y, 6, c6_h_y);
  for (c6_i7 = 0; c6_i7 < 12; c6_i7++) {
    c6_h_u[c6_i7] = chartInstance->c6_Rposition_memory[c6_i7];
  }

  c6_i_y = NULL;
  if (!chartInstance->c6_Rposition_memory_not_empty) {
    sf_mex_assign(&c6_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c6_i_y, sf_mex_create("y", c6_h_u, 0, 0U, 1U, 0U, 2, 4, 3),
                  false);
  }

  sf_mex_setcell(c6_y, 7, c6_i_y);
  c6_hoistedGlobal = chartInstance->c6_counter;
  c6_i_u = c6_hoistedGlobal;
  c6_j_y = NULL;
  if (!chartInstance->c6_counter_not_empty) {
    sf_mex_assign(&c6_j_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c6_j_y, sf_mex_create("y", &c6_i_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c6_y, 8, c6_j_y);
  c6_b_hoistedGlobal = chartInstance->c6_is_active_c6_hexacopter;
  c6_j_u = c6_b_hoistedGlobal;
  c6_k_y = NULL;
  sf_mex_assign(&c6_k_y, sf_mex_create("y", &c6_j_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 9, c6_k_y);
  sf_mex_assign(&c6_st, c6_y, false);
  return c6_st;
}

static void set_sim_state_c6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance, const mxArray *c6_st)
{
  const mxArray *c6_u;
  real_T c6_dv0[3];
  int32_T c6_i8;
  real_T c6_dv1[3];
  int32_T c6_i9;
  real_T c6_dv2[3];
  int32_T c6_i10;
  real_T c6_dv3[3];
  int32_T c6_i11;
  real_T c6_dv4[12];
  int32_T c6_i12;
  real_T c6_dv5[3];
  int32_T c6_i13;
  real_T c6_dv6[3];
  int32_T c6_i14;
  real_T c6_dv7[12];
  int32_T c6_i15;
  real_T (*c6_m_opt)[3];
  real_T (*c6_pos_opt)[3];
  real_T (*c6_pos_trasm)[3];
  real_T (*c6_m_trasm)[3];
  c6_m_opt = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c6_pos_opt = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c6_m_trasm = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c6_pos_trasm = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c6_doneDoubleBufferReInit = true;
  c6_u = sf_mex_dup(c6_st);
  c6_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 0)),
                        "m_opt", c6_dv0);
  for (c6_i8 = 0; c6_i8 < 3; c6_i8++) {
    (*c6_m_opt)[c6_i8] = c6_dv0[c6_i8];
  }

  c6_m_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 1)),
                        "m_trasm", c6_dv1);
  for (c6_i9 = 0; c6_i9 < 3; c6_i9++) {
    (*c6_m_trasm)[c6_i9] = c6_dv1[c6_i9];
  }

  c6_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 2)),
                        "pos_opt", c6_dv2);
  for (c6_i10 = 0; c6_i10 < 3; c6_i10++) {
    (*c6_pos_opt)[c6_i10] = c6_dv2[c6_i10];
  }

  c6_m_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 3)),
                        "pos_trasm", c6_dv3);
  for (c6_i11 = 0; c6_i11 < 3; c6_i11++) {
    (*c6_pos_trasm)[c6_i11] = c6_dv3[c6_i11];
  }

  c6_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 4)),
                        "Hfield_memory", c6_dv4);
  for (c6_i12 = 0; c6_i12 < 12; c6_i12++) {
    chartInstance->c6_Hfield_memory[c6_i12] = c6_dv4[c6_i12];
  }

  c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 5)), "M",
                      c6_dv5);
  for (c6_i13 = 0; c6_i13 < 3; c6_i13++) {
    chartInstance->c6_M[c6_i13] = c6_dv5[c6_i13];
  }

  c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 6)), "RT",
                        c6_dv6);
  for (c6_i14 = 0; c6_i14 < 3; c6_i14++) {
    chartInstance->c6_RT[c6_i14] = c6_dv6[c6_i14];
  }

  c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 7)),
                        "Rposition_memory", c6_dv7);
  for (c6_i15 = 0; c6_i15 < 12; c6_i15++) {
    chartInstance->c6_Rposition_memory[c6_i15] = c6_dv7[c6_i15];
  }

  chartInstance->c6_counter = c6_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 8)), "counter");
  chartInstance->c6_is_active_c6_hexacopter = c6_s_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 9)),
     "is_active_c6_hexacopter");
  sf_mex_destroy(&c6_u);
  c6_update_debugger_state_c6_hexacopter(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void finalize_c6_hexacopter(SFc6_hexacopterInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance)
{
  int32_T c6_i16;
  int32_T c6_i17;
  real_T c6_pos[3];
  int32_T c6_i18;
  real_T c6_H[3];
  uint32_T c6_debug_family_var_map[17];
  real_T c6_MEMORY;
  real_T c6_alpha;
  real_T c6_optimized_vector[6];
  const mxArray *c6_optimized = NULL;
  real_T c6_nargin = 2.0;
  real_T c6_nargout = 4.0;
  real_T c6_pos_trasm[3];
  real_T c6_m_trasm[3];
  real_T c6_pos_opt[3];
  real_T c6_m_opt[3];
  int32_T c6_i19;
  int32_T c6_i20;
  int32_T c6_i21;
  int32_T c6_i22;
  int32_T c6_i23;
  int32_T c6_i24;
  int32_T c6_i25;
  int32_T c6_i26;
  int32_T c6_i27;
  int32_T c6_i28;
  static char_T c6_cv0[10] = { 'o', 'p', 't', 'i', 'm', 'i', 'z', 'e', 'r', '2'
  };

  char_T c6_u[10];
  const mxArray *c6_y = NULL;
  int32_T c6_i29;
  real_T c6_hoistedGlobal[12];
  int32_T c6_i30;
  int32_T c6_i31;
  int32_T c6_i32;
  int32_T c6_i33;
  real_T c6_b_u[12];
  const mxArray *c6_b_y = NULL;
  int32_T c6_i34;
  int32_T c6_i35;
  int32_T c6_i36;
  int32_T c6_i37;
  int32_T c6_i38;
  real_T c6_c_u[12];
  const mxArray *c6_c_y = NULL;
  int32_T c6_i39;
  real_T c6_b_hoistedGlobal[3];
  int32_T c6_i40;
  real_T c6_c_hoistedGlobal[3];
  int32_T c6_i41;
  real_T c6_d_hoistedGlobal[6];
  int32_T c6_i42;
  int32_T c6_i43;
  real_T c6_d_u[6];
  const mxArray *c6_d_y = NULL;
  real_T c6_dv8[6];
  int32_T c6_i44;
  int32_T c6_i45;
  int32_T c6_i46;
  int32_T c6_i47;
  int32_T c6_i48;
  int32_T c6_i49;
  int32_T c6_i50;
  int32_T c6_i51;
  int32_T c6_i52;
  int32_T c6_i53;
  int32_T c6_i54;
  int32_T c6_i55;
  int32_T c6_i56;
  int32_T c6_i57;
  int32_T c6_i58;
  int32_T c6_i59;
  int32_T c6_i60;
  int32_T c6_i61;
  int32_T c6_i62;
  int32_T c6_i63;
  int32_T c6_i64;
  int32_T c6_i65;
  int32_T c6_i66;
  int32_T c6_i67;
  real_T (*c6_b_pos_opt)[3];
  real_T (*c6_b_m_opt)[3];
  real_T (*c6_b_m_trasm)[3];
  real_T (*c6_b_pos_trasm)[3];
  real_T (*c6_b_H)[3];
  real_T (*c6_b_pos)[3];
  c6_b_m_opt = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c6_b_pos_opt = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c6_b_m_trasm = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c6_b_H = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c6_b_pos_trasm = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c6_b_pos = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c6_sfEvent);
  for (c6_i16 = 0; c6_i16 < 3; c6_i16++) {
    _SFD_DATA_RANGE_CHECK((*c6_b_pos)[c6_i16], 0U);
  }

  chartInstance->c6_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c6_sfEvent);
  for (c6_i17 = 0; c6_i17 < 3; c6_i17++) {
    c6_pos[c6_i17] = (*c6_b_pos)[c6_i17];
  }

  for (c6_i18 = 0; c6_i18 < 3; c6_i18++) {
    c6_H[c6_i18] = (*c6_b_H)[c6_i18];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 17U, 17U, c6_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_MEMORY, 0U, c6_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_alpha, 1U, c6_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_optimized_vector, 2U,
    c6_j_sf_marshallOut, c6_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c6_optimized, 3U, c6_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 4U, c6_h_sf_marshallOut,
    c6_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 5U, c6_h_sf_marshallOut,
    c6_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_pos, 6U, c6_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c6_H, 7U, c6_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_pos_trasm, 8U, c6_g_sf_marshallOut,
    c6_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_m_trasm, 9U, c6_g_sf_marshallOut,
    c6_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_pos_opt, 10U, c6_f_sf_marshallOut,
    c6_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c6_m_opt, 11U, c6_f_sf_marshallOut,
    c6_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c6_counter, 12U,
    c6_e_sf_marshallOut, c6_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c6_Hfield_memory, 13U,
    c6_d_sf_marshallOut, c6_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c6_Rposition_memory, 14U,
    c6_c_sf_marshallOut, c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c6_RT, 15U,
    c6_b_sf_marshallOut, c6_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c6_M, 16U,
    c6_sf_marshallOut, c6_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 4);
  c6_MEMORY = 4.0;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 7);
  c6_alpha = 0.3;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 9);
  for (c6_i19 = 0; c6_i19 < 6; c6_i19++) {
    c6_optimized_vector[c6_i19] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 10);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 11);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 12);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 13);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 14);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 16);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c6_counter_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 17);
    chartInstance->c6_counter = 0.0;
    chartInstance->c6_counter_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 20);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c6_Hfield_memory_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 21);
    for (c6_i20 = 0; c6_i20 < 12; c6_i20++) {
      chartInstance->c6_Hfield_memory[c6_i20] = 0.0;
    }

    chartInstance->c6_Hfield_memory_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 23);
  if (CV_EML_IF(0, 1, 2, !chartInstance->c6_Rposition_memory_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 24);
    for (c6_i21 = 0; c6_i21 < 12; c6_i21++) {
      chartInstance->c6_Rposition_memory[c6_i21] = 0.0;
    }

    chartInstance->c6_Rposition_memory_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 28);
  if (CV_EML_IF(0, 1, 3, !chartInstance->c6_RT_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 29);
    for (c6_i22 = 0; c6_i22 < 3; c6_i22++) {
      chartInstance->c6_RT[c6_i22] = 0.0;
    }

    chartInstance->c6_RT_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 31);
  if (CV_EML_IF(0, 1, 4, !chartInstance->c6_M_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 32);
    for (c6_i23 = 0; c6_i23 < 3; c6_i23++) {
      chartInstance->c6_M[c6_i23] = 0.0;
    }

    chartInstance->c6_M_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 35);
  chartInstance->c6_counter++;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 36);
  c6_i24 = _SFD_EML_ARRAY_BOUNDS_CHECK("Hfield_memory", (int32_T)
    _SFD_INTEGER_CHECK("counter", chartInstance->c6_counter), 1, 4, 1, 0) - 1;
  for (c6_i25 = 0; c6_i25 < 3; c6_i25++) {
    chartInstance->c6_Hfield_memory[c6_i24 + (c6_i25 << 2)] = c6_H[c6_i25];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 37);
  c6_i26 = _SFD_EML_ARRAY_BOUNDS_CHECK("Rposition_memory", (int32_T)
    _SFD_INTEGER_CHECK("counter", chartInstance->c6_counter), 1, 4, 1, 0) - 1;
  for (c6_i27 = 0; c6_i27 < 3; c6_i27++) {
    chartInstance->c6_Rposition_memory[c6_i26 + (c6_i27 << 2)] = c6_pos[c6_i27];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 38);
  if (CV_EML_IF(0, 1, 5, chartInstance->c6_counter == c6_MEMORY)) {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 39);
    chartInstance->c6_counter = 0.0;
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 40);
    for (c6_i28 = 0; c6_i28 < 10; c6_i28++) {
      c6_u[c6_i28] = c6_cv0[c6_i28];
    }

    c6_y = NULL;
    sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 10, 0U, 1U, 0U, 2, 1, 10),
                  false);
    for (c6_i29 = 0; c6_i29 < 12; c6_i29++) {
      c6_hoistedGlobal[c6_i29] = chartInstance->c6_Rposition_memory[c6_i29];
    }

    c6_i30 = 0;
    for (c6_i31 = 0; c6_i31 < 4; c6_i31++) {
      c6_i32 = 0;
      for (c6_i33 = 0; c6_i33 < 3; c6_i33++) {
        c6_b_u[c6_i33 + c6_i30] = c6_hoistedGlobal[c6_i32 + c6_i31];
        c6_i32 += 4;
      }

      c6_i30 += 3;
    }

    c6_b_y = NULL;
    sf_mex_assign(&c6_b_y, sf_mex_create("y", c6_b_u, 0, 0U, 1U, 0U, 2, 3, 4),
                  false);
    for (c6_i34 = 0; c6_i34 < 12; c6_i34++) {
      c6_hoistedGlobal[c6_i34] = chartInstance->c6_Hfield_memory[c6_i34];
    }

    c6_i35 = 0;
    for (c6_i36 = 0; c6_i36 < 4; c6_i36++) {
      c6_i37 = 0;
      for (c6_i38 = 0; c6_i38 < 3; c6_i38++) {
        c6_c_u[c6_i38 + c6_i35] = c6_hoistedGlobal[c6_i37 + c6_i36];
        c6_i37 += 4;
      }

      c6_i35 += 3;
    }

    c6_c_y = NULL;
    sf_mex_assign(&c6_c_y, sf_mex_create("y", c6_c_u, 0, 0U, 1U, 0U, 2, 3, 4),
                  false);
    for (c6_i39 = 0; c6_i39 < 3; c6_i39++) {
      c6_b_hoistedGlobal[c6_i39] = chartInstance->c6_RT[c6_i39];
    }

    for (c6_i40 = 0; c6_i40 < 3; c6_i40++) {
      c6_c_hoistedGlobal[c6_i40] = chartInstance->c6_M[c6_i40];
    }

    for (c6_i41 = 0; c6_i41 < 3; c6_i41++) {
      c6_d_hoistedGlobal[c6_i41] = c6_b_hoistedGlobal[c6_i41];
    }

    for (c6_i42 = 0; c6_i42 < 3; c6_i42++) {
      c6_d_hoistedGlobal[c6_i42 + 3] = c6_c_hoistedGlobal[c6_i42];
    }

    for (c6_i43 = 0; c6_i43 < 6; c6_i43++) {
      c6_d_u[c6_i43] = c6_d_hoistedGlobal[c6_i43];
    }

    c6_d_y = NULL;
    sf_mex_assign(&c6_d_y, sf_mex_create("y", c6_d_u, 0, 0U, 1U, 0U, 1, 6),
                  false);
    sf_mex_assign(&c6_optimized, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
      "feval", 1U, 4U, 14, c6_y, 14, c6_b_y, 14, c6_c_y, 14, c6_d_y), false);
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 41);
    c6_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_optimized), "optimized",
                          c6_dv8);
    for (c6_i44 = 0; c6_i44 < 6; c6_i44++) {
      c6_optimized_vector[c6_i44] = c6_dv8[c6_i44];
    }

    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 42);
    for (c6_i45 = 0; c6_i45 < 3; c6_i45++) {
      c6_b_hoistedGlobal[c6_i45] = chartInstance->c6_RT[c6_i45];
    }

    for (c6_i46 = 0; c6_i46 < 3; c6_i46++) {
      c6_b_hoistedGlobal[c6_i46] *= 0.7;
    }

    for (c6_i47 = 0; c6_i47 < 3; c6_i47++) {
      c6_c_hoistedGlobal[c6_i47] = c6_optimized_vector[c6_i47];
    }

    for (c6_i48 = 0; c6_i48 < 3; c6_i48++) {
      c6_c_hoistedGlobal[c6_i48] *= 0.3;
    }

    for (c6_i49 = 0; c6_i49 < 3; c6_i49++) {
      chartInstance->c6_RT[c6_i49] = c6_b_hoistedGlobal[c6_i49] +
        c6_c_hoistedGlobal[c6_i49];
    }

    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 43);
    for (c6_i50 = 0; c6_i50 < 3; c6_i50++) {
      c6_b_hoistedGlobal[c6_i50] = chartInstance->c6_M[c6_i50];
    }

    for (c6_i51 = 0; c6_i51 < 3; c6_i51++) {
      c6_b_hoistedGlobal[c6_i51] *= 0.7;
    }

    for (c6_i52 = 0; c6_i52 < 3; c6_i52++) {
      c6_c_hoistedGlobal[c6_i52] = c6_optimized_vector[c6_i52];
    }

    for (c6_i53 = 0; c6_i53 < 3; c6_i53++) {
      c6_c_hoistedGlobal[c6_i53] *= 0.3;
    }

    for (c6_i54 = 0; c6_i54 < 3; c6_i54++) {
      chartInstance->c6_M[c6_i54] = c6_b_hoistedGlobal[c6_i54] +
        c6_c_hoistedGlobal[c6_i54];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 46);
  for (c6_i55 = 0; c6_i55 < 3; c6_i55++) {
    c6_pos_trasm[c6_i55] = chartInstance->c6_RT[c6_i55];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 47);
  for (c6_i56 = 0; c6_i56 < 3; c6_i56++) {
    c6_m_trasm[c6_i56] = chartInstance->c6_M[c6_i56];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 48);
  for (c6_i57 = 0; c6_i57 < 3; c6_i57++) {
    c6_pos_opt[c6_i57] = c6_optimized_vector[c6_i57];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 49);
  for (c6_i58 = 0; c6_i58 < 3; c6_i58++) {
    c6_m_opt[c6_i58] = c6_optimized_vector[c6_i58 + 3];
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, -49);
  _SFD_SYMBOL_SCOPE_POP();
  sf_mex_destroy(&c6_optimized);
  for (c6_i59 = 0; c6_i59 < 3; c6_i59++) {
    (*c6_b_pos_trasm)[c6_i59] = c6_pos_trasm[c6_i59];
  }

  for (c6_i60 = 0; c6_i60 < 3; c6_i60++) {
    (*c6_b_m_trasm)[c6_i60] = c6_m_trasm[c6_i60];
  }

  for (c6_i61 = 0; c6_i61 < 3; c6_i61++) {
    (*c6_b_pos_opt)[c6_i61] = c6_pos_opt[c6_i61];
  }

  for (c6_i62 = 0; c6_i62 < 3; c6_i62++) {
    (*c6_b_m_opt)[c6_i62] = c6_m_opt[c6_i62];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c6_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_hexacopterMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c6_i63 = 0; c6_i63 < 3; c6_i63++) {
    _SFD_DATA_RANGE_CHECK((*c6_b_pos_trasm)[c6_i63], 1U);
  }

  for (c6_i64 = 0; c6_i64 < 3; c6_i64++) {
    _SFD_DATA_RANGE_CHECK((*c6_b_H)[c6_i64], 2U);
  }

  for (c6_i65 = 0; c6_i65 < 3; c6_i65++) {
    _SFD_DATA_RANGE_CHECK((*c6_b_m_trasm)[c6_i65], 3U);
  }

  for (c6_i66 = 0; c6_i66 < 3; c6_i66++) {
    _SFD_DATA_RANGE_CHECK((*c6_b_pos_opt)[c6_i66], 4U);
  }

  for (c6_i67 = 0; c6_i67 < 3; c6_i67++) {
    _SFD_DATA_RANGE_CHECK((*c6_b_m_opt)[c6_i67], 5U);
  }
}

static void initSimStructsc6_hexacopter(SFc6_hexacopterInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber, uint32_T c6_instanceNumber)
{
  (void)c6_machineNumber;
  (void)c6_chartNumber;
  (void)c6_instanceNumber;
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i68;
  real_T c6_b_inData[3];
  int32_T c6_i69;
  real_T c6_u[3];
  const mxArray *c6_y = NULL;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i68 = 0; c6_i68 < 3; c6_i68++) {
    c6_b_inData[c6_i68] = (*(real_T (*)[3])c6_inData)[c6_i68];
  }

  for (c6_i69 = 0; c6_i69 < 3; c6_i69++) {
    c6_u[c6_i69] = c6_b_inData[c6_i69];
  }

  c6_y = NULL;
  if (!chartInstance->c6_M_not_empty) {
    sf_mex_assign(&c6_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 1, 3), false);
  }

  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_b_M, const char_T *c6_identifier, real_T c6_y[3])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_M), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_M);
}

static void c6_b_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3])
{
  real_T c6_dv9[3];
  int32_T c6_i70;
  if (mxIsEmpty(c6_u)) {
    chartInstance->c6_M_not_empty = false;
  } else {
    chartInstance->c6_M_not_empty = true;
    sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv9, 1, 0, 0U, 1, 0U, 2, 1,
                  3);
    for (c6_i70 = 0; c6_i70 < 3; c6_i70++) {
      c6_y[c6_i70] = c6_dv9[c6_i70];
    }
  }

  sf_mex_destroy(&c6_u);
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_M;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[3];
  int32_T c6_i71;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_b_M = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_M), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_M);
  for (c6_i71 = 0; c6_i71 < 3; c6_i71++) {
    (*(real_T (*)[3])c6_outData)[c6_i71] = c6_y[c6_i71];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i72;
  real_T c6_b_inData[3];
  int32_T c6_i73;
  real_T c6_u[3];
  const mxArray *c6_y = NULL;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i72 = 0; c6_i72 < 3; c6_i72++) {
    c6_b_inData[c6_i72] = (*(real_T (*)[3])c6_inData)[c6_i72];
  }

  for (c6_i73 = 0; c6_i73 < 3; c6_i73++) {
    c6_u[c6_i73] = c6_b_inData[c6_i73];
  }

  c6_y = NULL;
  if (!chartInstance->c6_RT_not_empty) {
    sf_mex_assign(&c6_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 1, 3), false);
  }

  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_c_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_b_RT, const char_T *c6_identifier, real_T c6_y[3])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_RT), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_RT);
}

static void c6_d_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3])
{
  real_T c6_dv10[3];
  int32_T c6_i74;
  if (mxIsEmpty(c6_u)) {
    chartInstance->c6_RT_not_empty = false;
  } else {
    chartInstance->c6_RT_not_empty = true;
    sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv10, 1, 0, 0U, 1, 0U, 2, 1,
                  3);
    for (c6_i74 = 0; c6_i74 < 3; c6_i74++) {
      c6_y[c6_i74] = c6_dv10[c6_i74];
    }
  }

  sf_mex_destroy(&c6_u);
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_RT;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[3];
  int32_T c6_i75;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_b_RT = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_RT), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_RT);
  for (c6_i75 = 0; c6_i75 < 3; c6_i75++) {
    (*(real_T (*)[3])c6_outData)[c6_i75] = c6_y[c6_i75];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i76;
  int32_T c6_i77;
  int32_T c6_i78;
  real_T c6_b_inData[12];
  int32_T c6_i79;
  int32_T c6_i80;
  int32_T c6_i81;
  real_T c6_u[12];
  const mxArray *c6_y = NULL;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_i76 = 0;
  for (c6_i77 = 0; c6_i77 < 3; c6_i77++) {
    for (c6_i78 = 0; c6_i78 < 4; c6_i78++) {
      c6_b_inData[c6_i78 + c6_i76] = (*(real_T (*)[12])c6_inData)[c6_i78 +
        c6_i76];
    }

    c6_i76 += 4;
  }

  c6_i79 = 0;
  for (c6_i80 = 0; c6_i80 < 3; c6_i80++) {
    for (c6_i81 = 0; c6_i81 < 4; c6_i81++) {
      c6_u[c6_i81 + c6_i79] = c6_b_inData[c6_i81 + c6_i79];
    }

    c6_i79 += 4;
  }

  c6_y = NULL;
  if (!chartInstance->c6_Rposition_memory_not_empty) {
    sf_mex_assign(&c6_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 4, 3), false);
  }

  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_e_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_b_Rposition_memory, const char_T *c6_identifier, real_T
  c6_y[12])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_Rposition_memory),
                        &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_Rposition_memory);
}

static void c6_f_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[12])
{
  real_T c6_dv11[12];
  int32_T c6_i82;
  if (mxIsEmpty(c6_u)) {
    chartInstance->c6_Rposition_memory_not_empty = false;
  } else {
    chartInstance->c6_Rposition_memory_not_empty = true;
    sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv11, 1, 0, 0U, 1, 0U, 2, 4,
                  3);
    for (c6_i82 = 0; c6_i82 < 12; c6_i82++) {
      c6_y[c6_i82] = c6_dv11[c6_i82];
    }
  }

  sf_mex_destroy(&c6_u);
}

static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_Rposition_memory;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[12];
  int32_T c6_i83;
  int32_T c6_i84;
  int32_T c6_i85;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_b_Rposition_memory = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_Rposition_memory),
                        &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_Rposition_memory);
  c6_i83 = 0;
  for (c6_i84 = 0; c6_i84 < 3; c6_i84++) {
    for (c6_i85 = 0; c6_i85 < 4; c6_i85++) {
      (*(real_T (*)[12])c6_outData)[c6_i85 + c6_i83] = c6_y[c6_i85 + c6_i83];
    }

    c6_i83 += 4;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i86;
  int32_T c6_i87;
  int32_T c6_i88;
  real_T c6_b_inData[12];
  int32_T c6_i89;
  int32_T c6_i90;
  int32_T c6_i91;
  real_T c6_u[12];
  const mxArray *c6_y = NULL;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_i86 = 0;
  for (c6_i87 = 0; c6_i87 < 3; c6_i87++) {
    for (c6_i88 = 0; c6_i88 < 4; c6_i88++) {
      c6_b_inData[c6_i88 + c6_i86] = (*(real_T (*)[12])c6_inData)[c6_i88 +
        c6_i86];
    }

    c6_i86 += 4;
  }

  c6_i89 = 0;
  for (c6_i90 = 0; c6_i90 < 3; c6_i90++) {
    for (c6_i91 = 0; c6_i91 < 4; c6_i91++) {
      c6_u[c6_i91 + c6_i89] = c6_b_inData[c6_i91 + c6_i89];
    }

    c6_i89 += 4;
  }

  c6_y = NULL;
  if (!chartInstance->c6_Hfield_memory_not_empty) {
    sf_mex_assign(&c6_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 4, 3), false);
  }

  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_g_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_b_Hfield_memory, const char_T *c6_identifier, real_T c6_y[12])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_Hfield_memory),
                        &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_Hfield_memory);
}

static void c6_h_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[12])
{
  real_T c6_dv12[12];
  int32_T c6_i92;
  if (mxIsEmpty(c6_u)) {
    chartInstance->c6_Hfield_memory_not_empty = false;
  } else {
    chartInstance->c6_Hfield_memory_not_empty = true;
    sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv12, 1, 0, 0U, 1, 0U, 2, 4,
                  3);
    for (c6_i92 = 0; c6_i92 < 12; c6_i92++) {
      c6_y[c6_i92] = c6_dv12[c6_i92];
    }
  }

  sf_mex_destroy(&c6_u);
}

static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_Hfield_memory;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[12];
  int32_T c6_i93;
  int32_T c6_i94;
  int32_T c6_i95;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_b_Hfield_memory = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_Hfield_memory),
                        &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_Hfield_memory);
  c6_i93 = 0;
  for (c6_i94 = 0; c6_i94 < 3; c6_i94++) {
    for (c6_i95 = 0; c6_i95 < 4; c6_i95++) {
      (*(real_T (*)[12])c6_outData)[c6_i95 + c6_i93] = c6_y[c6_i95 + c6_i93];
    }

    c6_i93 += 4;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  if (!chartInstance->c6_counter_not_empty) {
    sf_mex_assign(&c6_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static real_T c6_i_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_b_counter, const char_T *c6_identifier)
{
  real_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_counter),
    &c6_thisId);
  sf_mex_destroy(&c6_b_counter);
  return c6_y;
}

static real_T c6_j_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d0;
  if (mxIsEmpty(c6_u)) {
    chartInstance->c6_counter_not_empty = false;
  } else {
    chartInstance->c6_counter_not_empty = true;
    sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d0, 1, 0, 0U, 0, 0U, 0);
    c6_y = c6_d0;
  }

  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_counter;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_b_counter = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_counter),
    &c6_thisId);
  sf_mex_destroy(&c6_b_counter);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_f_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i96;
  real_T c6_b_inData[3];
  int32_T c6_i97;
  real_T c6_u[3];
  const mxArray *c6_y = NULL;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i96 = 0; c6_i96 < 3; c6_i96++) {
    c6_b_inData[c6_i96] = (*(real_T (*)[3])c6_inData)[c6_i96];
  }

  for (c6_i97 = 0; c6_i97 < 3; c6_i97++) {
    c6_u[c6_i97] = c6_b_inData[c6_i97];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_k_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_m_opt, const char_T *c6_identifier, real_T c6_y[3])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_m_opt), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_m_opt);
}

static void c6_l_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3])
{
  real_T c6_dv13[3];
  int32_T c6_i98;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv13, 1, 0, 0U, 1, 0U, 1, 3);
  for (c6_i98 = 0; c6_i98 < 3; c6_i98++) {
    c6_y[c6_i98] = c6_dv13[c6_i98];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_m_opt;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[3];
  int32_T c6_i99;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_m_opt = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_m_opt), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_m_opt);
  for (c6_i99 = 0; c6_i99 < 3; c6_i99++) {
    (*(real_T (*)[3])c6_outData)[c6_i99] = c6_y[c6_i99];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_g_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i100;
  real_T c6_b_inData[3];
  int32_T c6_i101;
  real_T c6_u[3];
  const mxArray *c6_y = NULL;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i100 = 0; c6_i100 < 3; c6_i100++) {
    c6_b_inData[c6_i100] = (*(real_T (*)[3])c6_inData)[c6_i100];
  }

  for (c6_i101 = 0; c6_i101 < 3; c6_i101++) {
    c6_u[c6_i101] = c6_b_inData[c6_i101];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 2, 1, 3), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_m_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_m_trasm, const char_T *c6_identifier, real_T c6_y[3])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_m_trasm), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_m_trasm);
}

static void c6_n_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[3])
{
  real_T c6_dv14[3];
  int32_T c6_i102;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv14, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c6_i102 = 0; c6_i102 < 3; c6_i102++) {
    c6_y[c6_i102] = c6_dv14[c6_i102];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_m_trasm;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[3];
  int32_T c6_i103;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_m_trasm = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_m_trasm), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_m_trasm);
  for (c6_i103 = 0; c6_i103 < 3; c6_i103++) {
    (*(real_T (*)[3])c6_outData)[c6_i103] = c6_y[c6_i103];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_h_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static real_T c6_o_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d1;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d1, 1, 0, 0U, 0, 0U, 0);
  c6_y = c6_d1;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_nargout;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_nargout = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_nargout), &c6_thisId);
  sf_mex_destroy(&c6_nargout);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_i_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  const mxArray *c6_u;
  const mxArray *c6_y = NULL;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = sf_mex_dup(*(const mxArray **)c6_inData);
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_duplicatearraysafe(&c6_u), false);
  sf_mex_destroy(&c6_u);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static const mxArray *c6_j_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i104;
  real_T c6_b_inData[6];
  int32_T c6_i105;
  real_T c6_u[6];
  const mxArray *c6_y = NULL;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i104 = 0; c6_i104 < 6; c6_i104++) {
    c6_b_inData[c6_i104] = (*(real_T (*)[6])c6_inData)[c6_i104];
  }

  for (c6_i105 = 0; c6_i105 < 6; c6_i105++) {
    c6_u[c6_i105] = c6_b_inData[c6_i105];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_optimized;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[6];
  int32_T c6_i106;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_optimized = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_optimized), &c6_thisId,
                        c6_y);
  sf_mex_destroy(&c6_optimized);
  for (c6_i106 = 0; c6_i106 < 6; c6_i106++) {
    (*(real_T (*)[6])c6_outData)[c6_i106] = c6_y[c6_i106];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

const mxArray *sf_c6_hexacopter_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  sf_mex_assign(&c6_nameCaptureInfo, sf_mex_createstruct("structure", 2, 2, 1),
                false);
  c6_info_helper(&c6_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c6_nameCaptureInfo);
  return c6_nameCaptureInfo;
}

static void c6_info_helper(const mxArray **c6_info)
{
  const mxArray *c6_rhs0 = NULL;
  const mxArray *c6_lhs0 = NULL;
  const mxArray *c6_rhs1 = NULL;
  const mxArray *c6_lhs1 = NULL;
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 0);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c6_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c6_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c6_info, c6_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c6_info, c6_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c6_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c6_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c6_info, sf_mex_duplicatearraysafe(&c6_lhs1), "lhs", "lhs", 1);
  sf_mex_destroy(&c6_rhs0);
  sf_mex_destroy(&c6_lhs0);
  sf_mex_destroy(&c6_rhs1);
  sf_mex_destroy(&c6_lhs1);
}

static const mxArray *c6_emlrt_marshallOut(const char * c6_u)
{
  const mxArray *c6_y = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c6_u)), false);
  return c6_y;
}

static const mxArray *c6_b_emlrt_marshallOut(const uint32_T c6_u)
{
  const mxArray *c6_y = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 7, 0U, 0U, 0U, 0), false);
  return c6_y;
}

static void c6_p_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_optimized, const char_T *c6_identifier, real_T c6_y[6])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_optimized), &c6_thisId,
                        c6_y);
  sf_mex_destroy(&c6_optimized);
}

static void c6_q_emlrt_marshallIn(SFc6_hexacopterInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[6])
{
  real_T c6_dv15[6];
  int32_T c6_i107;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv15, 1, 0, 0U, 1, 0U, 1, 6);
  for (c6_i107 = 0; c6_i107 < 6; c6_i107++) {
    c6_y[c6_i107] = c6_dv15[c6_i107];
  }

  sf_mex_destroy(&c6_u);
}

static const mxArray *c6_k_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static int32_T c6_r_emlrt_marshallIn(SFc6_hexacopterInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i108;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i108, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i108;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc6_hexacopterInstanceStruct *)chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent),
    &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static uint8_T c6_s_emlrt_marshallIn(SFc6_hexacopterInstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_hexacopter, const char_T
  *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_t_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_is_active_c6_hexacopter), &c6_thisId);
  sf_mex_destroy(&c6_b_is_active_c6_hexacopter);
  return c6_y;
}

static uint8_T c6_t_emlrt_marshallIn(SFc6_hexacopterInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u0;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u0, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void init_dsm_address_info(SFc6_hexacopterInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c6_hexacopter_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2493327798U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2723219770U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4120505833U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4250784801U);
}

mxArray *sf_c6_hexacopter_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("VPpirRPaJobkGazvXCFnEB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(3);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(3);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c6_hexacopter_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c6_hexacopter_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c6_hexacopter(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[12],T\"m_opt\",},{M[1],M[7],T\"m_trasm\",},{M[1],M[11],T\"pos_opt\",},{M[1],M[5],T\"pos_trasm\",},{M[4],M[0],T\"Hfield_memory\",S'l','i','p'{{M1x2[270 283],M[0],}}},{M[4],M[0],T\"M\",S'l','i','p'{{M1x2[352 353],M[0],}}},{M[4],M[0],T\"RT\",S'l','i','p'{{M1x2[333 335],M[0],}}},{M[4],M[0],T\"Rposition_memory\",S'l','i','p'{{M1x2[300 316],M[0],}}},{M[4],M[0],T\"counter\",S'l','i','p'{{M1x2[247 254],M[0],}}},{M[8],M[0],T\"is_active_c6_hexacopter\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 10, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_hexacopter_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_hexacopterInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc6_hexacopterInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _hexacopterMachineNumber_,
           6,
           1,
           1,
           0,
           6,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_hexacopterMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_hexacopterMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _hexacopterMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"pos");
          _SFD_SET_DATA_PROPS(1,2,0,1,"pos_trasm");
          _SFD_SET_DATA_PROPS(2,1,1,0,"H");
          _SFD_SET_DATA_PROPS(3,2,0,1,"m_trasm");
          _SFD_SET_DATA_PROPS(4,2,0,1,"pos_opt");
          _SFD_SET_DATA_PROPS(5,2,0,1,"m_opt");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,6,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1234);
        _SFD_CV_INIT_EML_IF(0,1,0,367,386,-1,415);
        _SFD_CV_INIT_EML_IF(0,1,1,444,469,-1,518);
        _SFD_CV_INIT_EML_IF(0,1,2,523,551,-1,603);
        _SFD_CV_INIT_EML_IF(0,1,3,634,648,-1,680);
        _SFD_CV_INIT_EML_IF(0,1,4,685,698,-1,727);
        _SFD_CV_INIT_EML_IF(0,1,5,834,854,-1,1120);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_g_sf_marshallOut,(MexInFcnForType)
            c6_g_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_g_sf_marshallOut,(MexInFcnForType)
            c6_g_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_f_sf_marshallOut,(MexInFcnForType)
            c6_f_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_f_sf_marshallOut,(MexInFcnForType)
            c6_f_sf_marshallIn);
        }

        {
          real_T (*c6_pos)[3];
          real_T (*c6_pos_trasm)[3];
          real_T (*c6_H)[3];
          real_T (*c6_m_trasm)[3];
          real_T (*c6_pos_opt)[3];
          real_T (*c6_m_opt)[3];
          c6_m_opt = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
          c6_pos_opt = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
          c6_m_trasm = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
          c6_H = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c6_pos_trasm = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            1);
          c6_pos = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c6_pos);
          _SFD_SET_DATA_VALUE_PTR(1U, *c6_pos_trasm);
          _SFD_SET_DATA_VALUE_PTR(2U, *c6_H);
          _SFD_SET_DATA_VALUE_PTR(3U, *c6_m_trasm);
          _SFD_SET_DATA_VALUE_PTR(4U, *c6_pos_opt);
          _SFD_SET_DATA_VALUE_PTR(5U, *c6_m_opt);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _hexacopterMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "pktUXJT0dUq0bB0DN3b3zC";
}

static void sf_opaque_initialize_c6_hexacopter(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_hexacopterInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c6_hexacopter((SFc6_hexacopterInstanceStruct*)
    chartInstanceVar);
  initialize_c6_hexacopter((SFc6_hexacopterInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c6_hexacopter(void *chartInstanceVar)
{
  enable_c6_hexacopter((SFc6_hexacopterInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c6_hexacopter(void *chartInstanceVar)
{
  disable_c6_hexacopter((SFc6_hexacopterInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c6_hexacopter(void *chartInstanceVar)
{
  sf_gateway_c6_hexacopter((SFc6_hexacopterInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c6_hexacopter(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c6_hexacopter
    ((SFc6_hexacopterInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_hexacopter();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c6_hexacopter(SimStruct* S, const mxArray *
  st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c6_hexacopter();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c6_hexacopter((SFc6_hexacopterInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c6_hexacopter(SimStruct* S)
{
  return sf_internal_get_sim_state_c6_hexacopter(S);
}

static void sf_opaque_set_sim_state_c6_hexacopter(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c6_hexacopter(S, st);
}

static void sf_opaque_terminate_c6_hexacopter(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_hexacopterInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_hexacopter_optimization_info();
    }

    finalize_c6_hexacopter((SFc6_hexacopterInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc6_hexacopter((SFc6_hexacopterInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_hexacopter(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c6_hexacopter((SFc6_hexacopterInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c6_hexacopter(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_hexacopter_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,6);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,6,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,6,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,6);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,6,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,6,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,6);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2225838408U));
  ssSetChecksum1(S,(715413352U));
  ssSetChecksum2(S,(2683306836U));
  ssSetChecksum3(S,(604836356U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c6_hexacopter(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c6_hexacopter(SimStruct *S)
{
  SFc6_hexacopterInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc6_hexacopterInstanceStruct *)utMalloc(sizeof
    (SFc6_hexacopterInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc6_hexacopterInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c6_hexacopter;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c6_hexacopter;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c6_hexacopter;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_hexacopter;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_hexacopter;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c6_hexacopter;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c6_hexacopter;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c6_hexacopter;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_hexacopter;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_hexacopter;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c6_hexacopter;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c6_hexacopter_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_hexacopter(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_hexacopter(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_hexacopter(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_hexacopter_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
