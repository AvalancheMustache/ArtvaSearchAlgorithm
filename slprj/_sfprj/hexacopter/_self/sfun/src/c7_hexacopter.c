/* Include files */

#include <stddef.h>
#include "blas.h"
#include "hexacopter_sfun.h"
#include "c7_hexacopter.h"
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
static const char * c7_debug_family_names[13] = { "n", "h_tmp", "cov_tmp", "j",
  "nargin", "nargout", "H_sample", "i", "H", "Hcov", "HVECTOR", "HMEAN",
  "HCOVARIANCE" };

/* Function Declarations */
static void initialize_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance);
static void initialize_params_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance);
static void enable_c7_hexacopter(SFc7_hexacopterInstanceStruct *chartInstance);
static void disable_c7_hexacopter(SFc7_hexacopterInstanceStruct *chartInstance);
static void c7_update_debugger_state_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c7_hexacopter(SFc7_hexacopterInstanceStruct *
  chartInstance);
static void set_sim_state_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance, const mxArray *c7_st);
static void finalize_c7_hexacopter(SFc7_hexacopterInstanceStruct *chartInstance);
static void sf_gateway_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance);
static void c7_chartstep_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance);
static void initSimStructsc7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber, uint32_T c7_instanceNumber);
static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData);
static void c7_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_b_HCOVARIANCE, const char_T *c7_identifier, real_T c7_y[9]);
static void c7_b_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[9]);
static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static void c7_c_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_b_HMEAN, const char_T *c7_identifier, real_T c7_y[3]);
static void c7_d_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[3]);
static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static void c7_e_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_b_HVECTOR, const char_T *c7_identifier, real_T c7_y[150]);
static void c7_f_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[150]);
static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static void c7_g_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_Hcov, const char_T *c7_identifier, real_T c7_y[9]);
static void c7_h_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[9]);
static void c7_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_e_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static void c7_i_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_H, const char_T *c7_identifier, real_T c7_y[3]);
static void c7_j_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[3]);
static void c7_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_f_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static const mxArray *c7_g_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static const mxArray *c7_h_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static real_T c7_k_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_i_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static void c7_l_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[150]);
static void c7_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static void c7_info_helper(const mxArray **c7_info);
static const mxArray *c7_emlrt_marshallOut(const char * c7_u);
static const mxArray *c7_b_emlrt_marshallOut(const uint32_T c7_u);
static void c7_scalarEg(SFc7_hexacopterInstanceStruct *chartInstance);
static real_T c7_eml_xdotu(SFc7_hexacopterInstanceStruct *chartInstance, real_T
  c7_x[3], real_T c7_y[3]);
static int32_T c7_m_emlrt_marshallIn(SFc7_hexacopterInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static uint8_T c7_n_emlrt_marshallIn(SFc7_hexacopterInstanceStruct
  *chartInstance, const mxArray *c7_b_is_active_c7_hexacopter, const char_T
  *c7_identifier);
static uint8_T c7_o_emlrt_marshallIn(SFc7_hexacopterInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void init_dsm_address_info(SFc7_hexacopterInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance)
{
  chartInstance->c7_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c7_HVECTOR_not_empty = false;
  chartInstance->c7_HMEAN_not_empty = false;
  chartInstance->c7_HCOVARIANCE_not_empty = false;
  chartInstance->c7_is_active_c7_hexacopter = 0U;
}

static void initialize_params_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c7_hexacopter(SFc7_hexacopterInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c7_hexacopter(SFc7_hexacopterInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c7_update_debugger_state_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c7_hexacopter(SFc7_hexacopterInstanceStruct *
  chartInstance)
{
  const mxArray *c7_st;
  const mxArray *c7_y = NULL;
  int32_T c7_i0;
  real_T c7_u[3];
  const mxArray *c7_b_y = NULL;
  int32_T c7_i1;
  real_T c7_b_u[9];
  const mxArray *c7_c_y = NULL;
  int32_T c7_i2;
  real_T c7_c_u[9];
  const mxArray *c7_d_y = NULL;
  int32_T c7_i3;
  real_T c7_d_u[3];
  const mxArray *c7_e_y = NULL;
  int32_T c7_i4;
  real_T c7_e_u[150];
  const mxArray *c7_f_y = NULL;
  uint8_T c7_hoistedGlobal;
  uint8_T c7_f_u;
  const mxArray *c7_g_y = NULL;
  real_T (*c7_Hcov)[9];
  real_T (*c7_H)[3];
  c7_Hcov = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c7_H = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_st = NULL;
  c7_st = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_createcellmatrix(6, 1), false);
  for (c7_i0 = 0; c7_i0 < 3; c7_i0++) {
    c7_u[c7_i0] = (*c7_H)[c7_i0];
  }

  c7_b_y = NULL;
  sf_mex_assign(&c7_b_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c7_y, 0, c7_b_y);
  for (c7_i1 = 0; c7_i1 < 9; c7_i1++) {
    c7_b_u[c7_i1] = (*c7_Hcov)[c7_i1];
  }

  c7_c_y = NULL;
  sf_mex_assign(&c7_c_y, sf_mex_create("y", c7_b_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  sf_mex_setcell(c7_y, 1, c7_c_y);
  for (c7_i2 = 0; c7_i2 < 9; c7_i2++) {
    c7_c_u[c7_i2] = chartInstance->c7_HCOVARIANCE[c7_i2];
  }

  c7_d_y = NULL;
  if (!chartInstance->c7_HCOVARIANCE_not_empty) {
    sf_mex_assign(&c7_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c7_d_y, sf_mex_create("y", c7_c_u, 0, 0U, 1U, 0U, 2, 3, 3),
                  false);
  }

  sf_mex_setcell(c7_y, 2, c7_d_y);
  for (c7_i3 = 0; c7_i3 < 3; c7_i3++) {
    c7_d_u[c7_i3] = chartInstance->c7_HMEAN[c7_i3];
  }

  c7_e_y = NULL;
  if (!chartInstance->c7_HMEAN_not_empty) {
    sf_mex_assign(&c7_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c7_e_y, sf_mex_create("y", c7_d_u, 0, 0U, 1U, 0U, 1, 3),
                  false);
  }

  sf_mex_setcell(c7_y, 3, c7_e_y);
  for (c7_i4 = 0; c7_i4 < 150; c7_i4++) {
    c7_e_u[c7_i4] = chartInstance->c7_HVECTOR[c7_i4];
  }

  c7_f_y = NULL;
  if (!chartInstance->c7_HVECTOR_not_empty) {
    sf_mex_assign(&c7_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c7_f_y, sf_mex_create("y", c7_e_u, 0, 0U, 1U, 0U, 2, 3, 50),
                  false);
  }

  sf_mex_setcell(c7_y, 4, c7_f_y);
  c7_hoistedGlobal = chartInstance->c7_is_active_c7_hexacopter;
  c7_f_u = c7_hoistedGlobal;
  c7_g_y = NULL;
  sf_mex_assign(&c7_g_y, sf_mex_create("y", &c7_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c7_y, 5, c7_g_y);
  sf_mex_assign(&c7_st, c7_y, false);
  return c7_st;
}

static void set_sim_state_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance, const mxArray *c7_st)
{
  const mxArray *c7_u;
  real_T c7_dv0[3];
  int32_T c7_i5;
  real_T c7_dv1[9];
  int32_T c7_i6;
  real_T c7_dv2[9];
  int32_T c7_i7;
  real_T c7_dv3[3];
  int32_T c7_i8;
  real_T c7_dv4[150];
  int32_T c7_i9;
  real_T (*c7_H)[3];
  real_T (*c7_Hcov)[9];
  c7_Hcov = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c7_H = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c7_doneDoubleBufferReInit = true;
  c7_u = sf_mex_dup(c7_st);
  c7_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 0)), "H",
                        c7_dv0);
  for (c7_i5 = 0; c7_i5 < 3; c7_i5++) {
    (*c7_H)[c7_i5] = c7_dv0[c7_i5];
  }

  c7_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 1)),
                        "Hcov", c7_dv1);
  for (c7_i6 = 0; c7_i6 < 9; c7_i6++) {
    (*c7_Hcov)[c7_i6] = c7_dv1[c7_i6];
  }

  c7_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 2)),
                      "HCOVARIANCE", c7_dv2);
  for (c7_i7 = 0; c7_i7 < 9; c7_i7++) {
    chartInstance->c7_HCOVARIANCE[c7_i7] = c7_dv2[c7_i7];
  }

  c7_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 3)),
                        "HMEAN", c7_dv3);
  for (c7_i8 = 0; c7_i8 < 3; c7_i8++) {
    chartInstance->c7_HMEAN[c7_i8] = c7_dv3[c7_i8];
  }

  c7_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 4)),
                        "HVECTOR", c7_dv4);
  for (c7_i9 = 0; c7_i9 < 150; c7_i9++) {
    chartInstance->c7_HVECTOR[c7_i9] = c7_dv4[c7_i9];
  }

  chartInstance->c7_is_active_c7_hexacopter = c7_n_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 5)),
     "is_active_c7_hexacopter");
  sf_mex_destroy(&c7_u);
  c7_update_debugger_state_c7_hexacopter(chartInstance);
  sf_mex_destroy(&c7_st);
}

static void finalize_c7_hexacopter(SFc7_hexacopterInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance)
{
  int32_T c7_i10;
  int32_T c7_i11;
  int32_T c7_i12;
  int32_T *c7_i;
  real_T (*c7_Hcov)[9];
  real_T (*c7_H)[3];
  real_T (*c7_H_sample)[3];
  c7_Hcov = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c7_i = (int32_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c7_H = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_H_sample = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c7_sfEvent);
  for (c7_i10 = 0; c7_i10 < 3; c7_i10++) {
    _SFD_DATA_RANGE_CHECK((*c7_H_sample)[c7_i10], 0U);
  }

  chartInstance->c7_sfEvent = CALL_EVENT;
  c7_chartstep_c7_hexacopter(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_hexacopterMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c7_i11 = 0; c7_i11 < 3; c7_i11++) {
    _SFD_DATA_RANGE_CHECK((*c7_H)[c7_i11], 1U);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*c7_i, 2U);
  for (c7_i12 = 0; c7_i12 < 9; c7_i12++) {
    _SFD_DATA_RANGE_CHECK((*c7_Hcov)[c7_i12], 3U);
  }
}

static void c7_chartstep_c7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance)
{
  int32_T c7_hoistedGlobal;
  int32_T c7_i13;
  real_T c7_H_sample[3];
  int32_T c7_i;
  uint32_T c7_debug_family_var_map[13];
  real_T c7_n;
  real_T c7_h_tmp[3];
  real_T c7_cov_tmp[150];
  real_T c7_j;
  real_T c7_nargin = 2.0;
  real_T c7_nargout = 2.0;
  real_T c7_H[3];
  real_T c7_Hcov[9];
  int32_T c7_i14;
  int32_T c7_i15;
  int32_T c7_i16;
  int32_T c7_i17;
  int32_T c7_i18;
  int32_T c7_i19;
  real_T c7_b_hoistedGlobal[150];
  int32_T c7_iy;
  int32_T c7_ixstart;
  int32_T c7_b_j;
  int32_T c7_a;
  int32_T c7_b_a;
  int32_T c7_ix;
  real_T c7_s;
  int32_T c7_k;
  int32_T c7_c_a;
  int32_T c7_d_a;
  int32_T c7_e_a;
  int32_T c7_f_a;
  real_T c7_y[3];
  int32_T c7_i20;
  int32_T c7_c_j;
  int32_T c7_d_j;
  int32_T c7_e_j;
  int32_T c7_i21;
  int32_T c7_i22;
  real_T c7_c_hoistedGlobal[9];
  int32_T c7_f_j;
  int32_T c7_i23;
  real_T c7_g_a[3];
  int32_T c7_i24;
  int32_T c7_i25;
  real_T c7_h_a[3];
  int32_T c7_i26;
  real_T c7_b_y[3];
  real_T c7_c_y;
  int32_T c7_i27;
  int32_T c7_i28;
  int32_T c7_i29;
  int32_T c7_b_i;
  int32_T c7_i30;
  int32_T c7_i31;
  int32_T c7_i32;
  int32_T c7_i33;
  int32_T c7_i34;
  int32_T *c7_c_i;
  real_T (*c7_b_H)[3];
  real_T (*c7_b_Hcov)[9];
  real_T (*c7_b_H_sample)[3];
  c7_b_Hcov = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
  c7_c_i = (int32_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c7_b_H = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_b_H_sample = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c7_sfEvent);
  c7_hoistedGlobal = *c7_c_i;
  for (c7_i13 = 0; c7_i13 < 3; c7_i13++) {
    c7_H_sample[c7_i13] = (*c7_b_H_sample)[c7_i13];
  }

  c7_i = c7_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c7_debug_family_names,
    c7_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c7_n, 0U, c7_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_h_tmp, 1U, c7_e_sf_marshallOut,
    c7_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_cov_tmp, 2U, c7_i_sf_marshallOut,
    c7_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_j, 3U, c7_h_sf_marshallOut,
    c7_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargin, 4U, c7_h_sf_marshallOut,
    c7_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c7_nargout, 5U, c7_h_sf_marshallOut,
    c7_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c7_H_sample, 6U, c7_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c7_i, 7U, c7_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_H, 8U, c7_e_sf_marshallOut,
    c7_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c7_Hcov, 9U, c7_d_sf_marshallOut,
    c7_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c7_HVECTOR, 10U,
    c7_c_sf_marshallOut, c7_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c7_HMEAN, 11U,
    c7_b_sf_marshallOut, c7_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c7_HCOVARIANCE, 12U,
    c7_sf_marshallOut, c7_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 3);
  c7_n = 50.0;
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 5);
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 6);
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 7);
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 8);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c7_HVECTOR_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 9);
    for (c7_i14 = 0; c7_i14 < 150; c7_i14++) {
      chartInstance->c7_HVECTOR[c7_i14] = 0.0;
    }

    chartInstance->c7_HVECTOR_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 11);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c7_HMEAN_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 12);
    for (c7_i15 = 0; c7_i15 < 3; c7_i15++) {
      chartInstance->c7_HMEAN[c7_i15] = 0.0;
    }

    chartInstance->c7_HMEAN_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 14);
  if (CV_EML_IF(0, 1, 2, !chartInstance->c7_HCOVARIANCE_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 15);
    for (c7_i16 = 0; c7_i16 < 9; c7_i16++) {
      chartInstance->c7_HCOVARIANCE[c7_i16] = 0.0;
    }

    chartInstance->c7_HCOVARIANCE_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 18);
  for (c7_i17 = 0; c7_i17 < 3; c7_i17++) {
    c7_h_tmp[c7_i17] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 19);
  for (c7_i18 = 0; c7_i18 < 150; c7_i18++) {
    c7_cov_tmp[c7_i18] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 21);
  if (CV_EML_IF(0, 1, 3, (real_T)c7_i == c7_n)) {
    _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 23);
    for (c7_i19 = 0; c7_i19 < 150; c7_i19++) {
      c7_b_hoistedGlobal[c7_i19] = chartInstance->c7_HVECTOR[c7_i19];
    }

    c7_iy = 0;
    c7_ixstart = 0;
    for (c7_b_j = 1; c7_b_j < 4; c7_b_j++) {
      c7_a = c7_ixstart;
      c7_b_a = c7_a + 1;
      c7_ixstart = c7_b_a;
      c7_ix = c7_ixstart;
      c7_s = c7_b_hoistedGlobal[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", (real_T)c7_ix), 1, 150, 1, 0) - 1];
      for (c7_k = 2; c7_k < 51; c7_k++) {
        c7_c_a = c7_ix;
        c7_d_a = c7_c_a + 3;
        c7_ix = c7_d_a;
        c7_s += c7_b_hoistedGlobal[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c7_ix), 1, 150, 1, 0) - 1];
      }

      c7_e_a = c7_iy;
      c7_f_a = c7_e_a + 1;
      c7_iy = c7_f_a;
      c7_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c7_iy), 1, 3, 1, 0) - 1] = c7_s;
    }

    for (c7_i20 = 0; c7_i20 < 3; c7_i20++) {
      chartInstance->c7_HMEAN[c7_i20] = 0.02 * c7_y[c7_i20];
    }

    _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 25);
    c7_j = 1.0;
    c7_c_j = 0;
    while (c7_c_j < 50) {
      c7_j = 1.0 + (real_T)c7_c_j;
      CV_EML_FOR(0, 1, 0, 1);
      _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 26);
      c7_d_j = _SFD_EML_ARRAY_BOUNDS_CHECK("cov_tmp", (int32_T)
        _SFD_INTEGER_CHECK("j", c7_j), 1, 50, 2, 0) - 1;
      c7_e_j = _SFD_EML_ARRAY_BOUNDS_CHECK("HVECTOR", (int32_T)
        _SFD_INTEGER_CHECK("j", c7_j), 1, 50, 2, 0) - 1;
      for (c7_i21 = 0; c7_i21 < 3; c7_i21++) {
        c7_cov_tmp[c7_i21 + 3 * c7_d_j] = chartInstance->c7_HVECTOR[c7_i21 + 3 *
          c7_e_j] - chartInstance->c7_HMEAN[c7_i21];
      }

      _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 27);
      for (c7_i22 = 0; c7_i22 < 9; c7_i22++) {
        c7_c_hoistedGlobal[c7_i22] = chartInstance->c7_HCOVARIANCE[c7_i22];
      }

      c7_f_j = _SFD_EML_ARRAY_BOUNDS_CHECK("cov_tmp", (int32_T)
        _SFD_INTEGER_CHECK("j", c7_j), 1, 50, 2, 0) - 1;
      for (c7_i23 = 0; c7_i23 < 3; c7_i23++) {
        c7_g_a[c7_i23] = c7_cov_tmp[c7_i23 + 3 * c7_f_j];
      }

      for (c7_i24 = 0; c7_i24 < 3; c7_i24++) {
        c7_y[c7_i24] = c7_cov_tmp[c7_i24];
      }

      c7_scalarEg(chartInstance);
      for (c7_i25 = 0; c7_i25 < 3; c7_i25++) {
        c7_h_a[c7_i25] = c7_g_a[c7_i25];
      }

      for (c7_i26 = 0; c7_i26 < 3; c7_i26++) {
        c7_b_y[c7_i26] = c7_y[c7_i26];
      }

      c7_c_y = c7_eml_xdotu(chartInstance, c7_h_a, c7_b_y);
      for (c7_i27 = 0; c7_i27 < 9; c7_i27++) {
        chartInstance->c7_HCOVARIANCE[c7_i27] = c7_c_hoistedGlobal[c7_i27] +
          c7_c_y;
      }

      c7_c_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 0, 0);
    _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 29);
    for (c7_i28 = 0; c7_i28 < 9; c7_i28++) {
      c7_c_hoistedGlobal[c7_i28] = chartInstance->c7_HCOVARIANCE[c7_i28];
    }

    for (c7_i29 = 0; c7_i29 < 9; c7_i29++) {
      chartInstance->c7_HCOVARIANCE[c7_i29] = 0.02 * c7_c_hoistedGlobal[c7_i29];
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 31);
    c7_b_i = _SFD_EML_ARRAY_BOUNDS_CHECK("HVECTOR", (int32_T)_SFD_INTEGER_CHECK(
      "i", (real_T)c7_i), 1, 50, 2, 0) - 1;
    for (c7_i30 = 0; c7_i30 < 3; c7_i30++) {
      chartInstance->c7_HVECTOR[c7_i30 + 3 * c7_b_i] = c7_H_sample[c7_i30];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 34);
  for (c7_i31 = 0; c7_i31 < 3; c7_i31++) {
    c7_H[c7_i31] = chartInstance->c7_HMEAN[c7_i31];
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 35);
  for (c7_i32 = 0; c7_i32 < 9; c7_i32++) {
    c7_Hcov[c7_i32] = chartInstance->c7_HCOVARIANCE[c7_i32];
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, -35);
  _SFD_SYMBOL_SCOPE_POP();
  for (c7_i33 = 0; c7_i33 < 3; c7_i33++) {
    (*c7_b_H)[c7_i33] = c7_H[c7_i33];
  }

  for (c7_i34 = 0; c7_i34 < 9; c7_i34++) {
    (*c7_b_Hcov)[c7_i34] = c7_Hcov[c7_i34];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c7_sfEvent);
}

static void initSimStructsc7_hexacopter(SFc7_hexacopterInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber, uint32_T c7_instanceNumber)
{
  (void)c7_machineNumber;
  (void)c7_chartNumber;
  (void)c7_instanceNumber;
}

static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i35;
  int32_T c7_i36;
  int32_T c7_i37;
  real_T c7_b_inData[9];
  int32_T c7_i38;
  int32_T c7_i39;
  int32_T c7_i40;
  real_T c7_u[9];
  const mxArray *c7_y = NULL;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_i35 = 0;
  for (c7_i36 = 0; c7_i36 < 3; c7_i36++) {
    for (c7_i37 = 0; c7_i37 < 3; c7_i37++) {
      c7_b_inData[c7_i37 + c7_i35] = (*(real_T (*)[9])c7_inData)[c7_i37 + c7_i35];
    }

    c7_i35 += 3;
  }

  c7_i38 = 0;
  for (c7_i39 = 0; c7_i39 < 3; c7_i39++) {
    for (c7_i40 = 0; c7_i40 < 3; c7_i40++) {
      c7_u[c7_i40 + c7_i38] = c7_b_inData[c7_i40 + c7_i38];
    }

    c7_i38 += 3;
  }

  c7_y = NULL;
  if (!chartInstance->c7_HCOVARIANCE_not_empty) {
    sf_mex_assign(&c7_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  }

  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static void c7_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_b_HCOVARIANCE, const char_T *c7_identifier, real_T c7_y[9])
{
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_HCOVARIANCE), &c7_thisId,
                        c7_y);
  sf_mex_destroy(&c7_b_HCOVARIANCE);
}

static void c7_b_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[9])
{
  real_T c7_dv5[9];
  int32_T c7_i41;
  if (mxIsEmpty(c7_u)) {
    chartInstance->c7_HCOVARIANCE_not_empty = false;
  } else {
    chartInstance->c7_HCOVARIANCE_not_empty = true;
    sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv5, 1, 0, 0U, 1, 0U, 2, 3,
                  3);
    for (c7_i41 = 0; c7_i41 < 9; c7_i41++) {
      c7_y[c7_i41] = c7_dv5[c7_i41];
    }
  }

  sf_mex_destroy(&c7_u);
}

static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_b_HCOVARIANCE;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[9];
  int32_T c7_i42;
  int32_T c7_i43;
  int32_T c7_i44;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_b_HCOVARIANCE = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_HCOVARIANCE), &c7_thisId,
                        c7_y);
  sf_mex_destroy(&c7_b_HCOVARIANCE);
  c7_i42 = 0;
  for (c7_i43 = 0; c7_i43 < 3; c7_i43++) {
    for (c7_i44 = 0; c7_i44 < 3; c7_i44++) {
      (*(real_T (*)[9])c7_outData)[c7_i44 + c7_i42] = c7_y[c7_i44 + c7_i42];
    }

    c7_i42 += 3;
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i45;
  real_T c7_b_inData[3];
  int32_T c7_i46;
  real_T c7_u[3];
  const mxArray *c7_y = NULL;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  for (c7_i45 = 0; c7_i45 < 3; c7_i45++) {
    c7_b_inData[c7_i45] = (*(real_T (*)[3])c7_inData)[c7_i45];
  }

  for (c7_i46 = 0; c7_i46 < 3; c7_i46++) {
    c7_u[c7_i46] = c7_b_inData[c7_i46];
  }

  c7_y = NULL;
  if (!chartInstance->c7_HMEAN_not_empty) {
    sf_mex_assign(&c7_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 1, 3), false);
  }

  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static void c7_c_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_b_HMEAN, const char_T *c7_identifier, real_T c7_y[3])
{
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_HMEAN), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_b_HMEAN);
}

static void c7_d_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[3])
{
  real_T c7_dv6[3];
  int32_T c7_i47;
  if (mxIsEmpty(c7_u)) {
    chartInstance->c7_HMEAN_not_empty = false;
  } else {
    chartInstance->c7_HMEAN_not_empty = true;
    sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv6, 1, 0, 0U, 1, 0U, 1, 3);
    for (c7_i47 = 0; c7_i47 < 3; c7_i47++) {
      c7_y[c7_i47] = c7_dv6[c7_i47];
    }
  }

  sf_mex_destroy(&c7_u);
}

static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_b_HMEAN;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[3];
  int32_T c7_i48;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_b_HMEAN = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_HMEAN), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_b_HMEAN);
  for (c7_i48 = 0; c7_i48 < 3; c7_i48++) {
    (*(real_T (*)[3])c7_outData)[c7_i48] = c7_y[c7_i48];
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i49;
  int32_T c7_i50;
  int32_T c7_i51;
  real_T c7_b_inData[150];
  int32_T c7_i52;
  int32_T c7_i53;
  int32_T c7_i54;
  real_T c7_u[150];
  const mxArray *c7_y = NULL;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_i49 = 0;
  for (c7_i50 = 0; c7_i50 < 50; c7_i50++) {
    for (c7_i51 = 0; c7_i51 < 3; c7_i51++) {
      c7_b_inData[c7_i51 + c7_i49] = (*(real_T (*)[150])c7_inData)[c7_i51 +
        c7_i49];
    }

    c7_i49 += 3;
  }

  c7_i52 = 0;
  for (c7_i53 = 0; c7_i53 < 50; c7_i53++) {
    for (c7_i54 = 0; c7_i54 < 3; c7_i54++) {
      c7_u[c7_i54 + c7_i52] = c7_b_inData[c7_i54 + c7_i52];
    }

    c7_i52 += 3;
  }

  c7_y = NULL;
  if (!chartInstance->c7_HVECTOR_not_empty) {
    sf_mex_assign(&c7_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 2, 3, 50),
                  false);
  }

  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static void c7_e_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_b_HVECTOR, const char_T *c7_identifier, real_T c7_y[150])
{
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_HVECTOR), &c7_thisId,
                        c7_y);
  sf_mex_destroy(&c7_b_HVECTOR);
}

static void c7_f_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[150])
{
  real_T c7_dv7[150];
  int32_T c7_i55;
  if (mxIsEmpty(c7_u)) {
    chartInstance->c7_HVECTOR_not_empty = false;
  } else {
    chartInstance->c7_HVECTOR_not_empty = true;
    sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv7, 1, 0, 0U, 1, 0U, 2, 3,
                  50);
    for (c7_i55 = 0; c7_i55 < 150; c7_i55++) {
      c7_y[c7_i55] = c7_dv7[c7_i55];
    }
  }

  sf_mex_destroy(&c7_u);
}

static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_b_HVECTOR;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[150];
  int32_T c7_i56;
  int32_T c7_i57;
  int32_T c7_i58;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_b_HVECTOR = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_HVECTOR), &c7_thisId,
                        c7_y);
  sf_mex_destroy(&c7_b_HVECTOR);
  c7_i56 = 0;
  for (c7_i57 = 0; c7_i57 < 50; c7_i57++) {
    for (c7_i58 = 0; c7_i58 < 3; c7_i58++) {
      (*(real_T (*)[150])c7_outData)[c7_i58 + c7_i56] = c7_y[c7_i58 + c7_i56];
    }

    c7_i56 += 3;
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i59;
  int32_T c7_i60;
  int32_T c7_i61;
  real_T c7_b_inData[9];
  int32_T c7_i62;
  int32_T c7_i63;
  int32_T c7_i64;
  real_T c7_u[9];
  const mxArray *c7_y = NULL;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_i59 = 0;
  for (c7_i60 = 0; c7_i60 < 3; c7_i60++) {
    for (c7_i61 = 0; c7_i61 < 3; c7_i61++) {
      c7_b_inData[c7_i61 + c7_i59] = (*(real_T (*)[9])c7_inData)[c7_i61 + c7_i59];
    }

    c7_i59 += 3;
  }

  c7_i62 = 0;
  for (c7_i63 = 0; c7_i63 < 3; c7_i63++) {
    for (c7_i64 = 0; c7_i64 < 3; c7_i64++) {
      c7_u[c7_i64 + c7_i62] = c7_b_inData[c7_i64 + c7_i62];
    }

    c7_i62 += 3;
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static void c7_g_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_Hcov, const char_T *c7_identifier, real_T c7_y[9])
{
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_Hcov), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_Hcov);
}

static void c7_h_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[9])
{
  real_T c7_dv8[9];
  int32_T c7_i65;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv8, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c7_i65 = 0; c7_i65 < 9; c7_i65++) {
    c7_y[c7_i65] = c7_dv8[c7_i65];
  }

  sf_mex_destroy(&c7_u);
}

static void c7_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_Hcov;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[9];
  int32_T c7_i66;
  int32_T c7_i67;
  int32_T c7_i68;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_Hcov = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_Hcov), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_Hcov);
  c7_i66 = 0;
  for (c7_i67 = 0; c7_i67 < 3; c7_i67++) {
    for (c7_i68 = 0; c7_i68 < 3; c7_i68++) {
      (*(real_T (*)[9])c7_outData)[c7_i68 + c7_i66] = c7_y[c7_i68 + c7_i66];
    }

    c7_i66 += 3;
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_e_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i69;
  real_T c7_b_inData[3];
  int32_T c7_i70;
  real_T c7_u[3];
  const mxArray *c7_y = NULL;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  for (c7_i69 = 0; c7_i69 < 3; c7_i69++) {
    c7_b_inData[c7_i69] = (*(real_T (*)[3])c7_inData)[c7_i69];
  }

  for (c7_i70 = 0; c7_i70 < 3; c7_i70++) {
    c7_u[c7_i70] = c7_b_inData[c7_i70];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static void c7_i_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_H, const char_T *c7_identifier, real_T c7_y[3])
{
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_H), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_H);
}

static void c7_j_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[3])
{
  real_T c7_dv9[3];
  int32_T c7_i71;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv9, 1, 0, 0U, 1, 0U, 1, 3);
  for (c7_i71 = 0; c7_i71 < 3; c7_i71++) {
    c7_y[c7_i71] = c7_dv9[c7_i71];
  }

  sf_mex_destroy(&c7_u);
}

static void c7_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_H;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[3];
  int32_T c7_i72;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_H = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_H), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_H);
  for (c7_i72 = 0; c7_i72 < 3; c7_i72++) {
    (*(real_T (*)[3])c7_outData)[c7_i72] = c7_y[c7_i72];
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_f_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(int32_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static const mxArray *c7_g_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i73;
  real_T c7_b_inData[3];
  int32_T c7_i74;
  real_T c7_u[3];
  const mxArray *c7_y = NULL;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  for (c7_i73 = 0; c7_i73 < 3; c7_i73++) {
    c7_b_inData[c7_i73] = (*(real_T (*)[3])c7_inData)[c7_i73];
  }

  for (c7_i74 = 0; c7_i74 < 3; c7_i74++) {
    c7_u[c7_i74] = c7_b_inData[c7_i74];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 2, 3, 1), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static const mxArray *c7_h_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  real_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(real_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static real_T c7_k_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  real_T c7_y;
  real_T c7_d0;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_d0, 1, 0, 0U, 0, 0U, 0);
  c7_y = c7_d0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_nargout;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_nargout = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_nargout), &c7_thisId);
  sf_mex_destroy(&c7_nargout);
  *(real_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_i_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i75;
  int32_T c7_i76;
  int32_T c7_i77;
  real_T c7_b_inData[150];
  int32_T c7_i78;
  int32_T c7_i79;
  int32_T c7_i80;
  real_T c7_u[150];
  const mxArray *c7_y = NULL;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_i75 = 0;
  for (c7_i76 = 0; c7_i76 < 50; c7_i76++) {
    for (c7_i77 = 0; c7_i77 < 3; c7_i77++) {
      c7_b_inData[c7_i77 + c7_i75] = (*(real_T (*)[150])c7_inData)[c7_i77 +
        c7_i75];
    }

    c7_i75 += 3;
  }

  c7_i78 = 0;
  for (c7_i79 = 0; c7_i79 < 50; c7_i79++) {
    for (c7_i80 = 0; c7_i80 < 3; c7_i80++) {
      c7_u[c7_i80 + c7_i78] = c7_b_inData[c7_i80 + c7_i78];
    }

    c7_i78 += 3;
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 2, 3, 50), false);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, false);
  return c7_mxArrayOutData;
}

static void c7_l_emlrt_marshallIn(SFc7_hexacopterInstanceStruct *chartInstance,
  const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId, real_T c7_y[150])
{
  real_T c7_dv10[150];
  int32_T c7_i81;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv10, 1, 0, 0U, 1, 0U, 2, 3,
                50);
  for (c7_i81 = 0; c7_i81 < 150; c7_i81++) {
    c7_y[c7_i81] = c7_dv10[c7_i81];
  }

  sf_mex_destroy(&c7_u);
}

static void c7_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_cov_tmp;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[150];
  int32_T c7_i82;
  int32_T c7_i83;
  int32_T c7_i84;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_cov_tmp = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_cov_tmp), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_cov_tmp);
  c7_i82 = 0;
  for (c7_i83 = 0; c7_i83 < 50; c7_i83++) {
    for (c7_i84 = 0; c7_i84 < 3; c7_i84++) {
      (*(real_T (*)[150])c7_outData)[c7_i84 + c7_i82] = c7_y[c7_i84 + c7_i82];
    }

    c7_i82 += 3;
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

const mxArray *sf_c7_hexacopter_get_eml_resolved_functions_info(void)
{
  const mxArray *c7_nameCaptureInfo = NULL;
  c7_nameCaptureInfo = NULL;
  sf_mex_assign(&c7_nameCaptureInfo, sf_mex_createstruct("structure", 2, 49, 1),
                false);
  c7_info_helper(&c7_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c7_nameCaptureInfo);
  return c7_nameCaptureInfo;
}

static void c7_info_helper(const mxArray **c7_info)
{
  const mxArray *c7_rhs0 = NULL;
  const mxArray *c7_lhs0 = NULL;
  const mxArray *c7_rhs1 = NULL;
  const mxArray *c7_lhs1 = NULL;
  const mxArray *c7_rhs2 = NULL;
  const mxArray *c7_lhs2 = NULL;
  const mxArray *c7_rhs3 = NULL;
  const mxArray *c7_lhs3 = NULL;
  const mxArray *c7_rhs4 = NULL;
  const mxArray *c7_lhs4 = NULL;
  const mxArray *c7_rhs5 = NULL;
  const mxArray *c7_lhs5 = NULL;
  const mxArray *c7_rhs6 = NULL;
  const mxArray *c7_lhs6 = NULL;
  const mxArray *c7_rhs7 = NULL;
  const mxArray *c7_lhs7 = NULL;
  const mxArray *c7_rhs8 = NULL;
  const mxArray *c7_lhs8 = NULL;
  const mxArray *c7_rhs9 = NULL;
  const mxArray *c7_lhs9 = NULL;
  const mxArray *c7_rhs10 = NULL;
  const mxArray *c7_lhs10 = NULL;
  const mxArray *c7_rhs11 = NULL;
  const mxArray *c7_lhs11 = NULL;
  const mxArray *c7_rhs12 = NULL;
  const mxArray *c7_lhs12 = NULL;
  const mxArray *c7_rhs13 = NULL;
  const mxArray *c7_lhs13 = NULL;
  const mxArray *c7_rhs14 = NULL;
  const mxArray *c7_lhs14 = NULL;
  const mxArray *c7_rhs15 = NULL;
  const mxArray *c7_lhs15 = NULL;
  const mxArray *c7_rhs16 = NULL;
  const mxArray *c7_lhs16 = NULL;
  const mxArray *c7_rhs17 = NULL;
  const mxArray *c7_lhs17 = NULL;
  const mxArray *c7_rhs18 = NULL;
  const mxArray *c7_lhs18 = NULL;
  const mxArray *c7_rhs19 = NULL;
  const mxArray *c7_lhs19 = NULL;
  const mxArray *c7_rhs20 = NULL;
  const mxArray *c7_lhs20 = NULL;
  const mxArray *c7_rhs21 = NULL;
  const mxArray *c7_lhs21 = NULL;
  const mxArray *c7_rhs22 = NULL;
  const mxArray *c7_lhs22 = NULL;
  const mxArray *c7_rhs23 = NULL;
  const mxArray *c7_lhs23 = NULL;
  const mxArray *c7_rhs24 = NULL;
  const mxArray *c7_lhs24 = NULL;
  const mxArray *c7_rhs25 = NULL;
  const mxArray *c7_lhs25 = NULL;
  const mxArray *c7_rhs26 = NULL;
  const mxArray *c7_lhs26 = NULL;
  const mxArray *c7_rhs27 = NULL;
  const mxArray *c7_lhs27 = NULL;
  const mxArray *c7_rhs28 = NULL;
  const mxArray *c7_lhs28 = NULL;
  const mxArray *c7_rhs29 = NULL;
  const mxArray *c7_lhs29 = NULL;
  const mxArray *c7_rhs30 = NULL;
  const mxArray *c7_lhs30 = NULL;
  const mxArray *c7_rhs31 = NULL;
  const mxArray *c7_lhs31 = NULL;
  const mxArray *c7_rhs32 = NULL;
  const mxArray *c7_lhs32 = NULL;
  const mxArray *c7_rhs33 = NULL;
  const mxArray *c7_lhs33 = NULL;
  const mxArray *c7_rhs34 = NULL;
  const mxArray *c7_lhs34 = NULL;
  const mxArray *c7_rhs35 = NULL;
  const mxArray *c7_lhs35 = NULL;
  const mxArray *c7_rhs36 = NULL;
  const mxArray *c7_lhs36 = NULL;
  const mxArray *c7_rhs37 = NULL;
  const mxArray *c7_lhs37 = NULL;
  const mxArray *c7_rhs38 = NULL;
  const mxArray *c7_lhs38 = NULL;
  const mxArray *c7_rhs39 = NULL;
  const mxArray *c7_lhs39 = NULL;
  const mxArray *c7_rhs40 = NULL;
  const mxArray *c7_lhs40 = NULL;
  const mxArray *c7_rhs41 = NULL;
  const mxArray *c7_lhs41 = NULL;
  const mxArray *c7_rhs42 = NULL;
  const mxArray *c7_lhs42 = NULL;
  const mxArray *c7_rhs43 = NULL;
  const mxArray *c7_lhs43 = NULL;
  const mxArray *c7_rhs44 = NULL;
  const mxArray *c7_lhs44 = NULL;
  const mxArray *c7_rhs45 = NULL;
  const mxArray *c7_lhs45 = NULL;
  const mxArray *c7_rhs46 = NULL;
  const mxArray *c7_lhs46 = NULL;
  const mxArray *c7_rhs47 = NULL;
  const mxArray *c7_lhs47 = NULL;
  const mxArray *c7_rhs48 = NULL;
  const mxArray *c7_lhs48 = NULL;
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("mrdivide"), "name", "name", 0);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1388460096U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1370009886U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c7_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 1);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 1);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c7_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 2);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("rdivide"), "name", "name", 2);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1363713880U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c7_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 3);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c7_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 4);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1286818796U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c7_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_div"), "name", "name", 5);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c7_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 6);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c7_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "context", "context", 7);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("sum"), "name", "name", 7);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1363713858U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c7_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 8);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c7_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 9);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_assert_valid_dim"), "name",
                  "name", 9);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c7_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m"),
                  "context", "context", 10);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.assertValidDim"),
                  "name", "name", 10);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assertValidDim.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c7_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assertValidDim.m"),
                  "context", "context", 11);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 11);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c7_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assertValidDim.m"),
                  "context", "context", 12);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("floor"), "name", "name", 12);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1363713854U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c7_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 13);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c7_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 14);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1286818726U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c7_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assertValidDim.m"),
                  "context", "context", 15);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("intmax"), "name", "name", 15);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 15);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c7_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 16);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 16);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c7_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 17);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 17);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c7_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 18);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 18);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c7_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 19);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 19);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c7_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_matrix_vstride"), "name",
                  "name", 20);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_vstride.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1360282350U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c7_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_vstride.m"),
                  "context", "context", 21);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.prodsize"),
                  "name", "name", 21);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/prodsize.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1360282588U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c7_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 22);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_matrix_npages"), "name",
                  "name", 22);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_npages.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1360282350U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c7_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_matrix_npages.m"),
                  "context", "context", 23);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.prodsize"),
                  "name", "name", 23);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/prodsize.m"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1360282588U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c7_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 24);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 24);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c7_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 25);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("intmax"), "name", "name", 25);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 25);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1362261882U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c7_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 26);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 26);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c7_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 27);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 27);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c7_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 28);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 28);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 28);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1372582416U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c7_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 29);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 29);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 29);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c7_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "context", "context", 30);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 30);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1383877294U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c7_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 31);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 31);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1363714556U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c7_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 32);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 32);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1323170578U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c7_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 33);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 33);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 33);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c7_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 34);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 34);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c7_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 35);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_xdotu"), "name", "name",
                  35);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m"),
                  "resolved", "resolved", 35);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1375980690U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c7_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m"), "context",
                  "context", 36);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 36);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 36);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c7_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m"), "context",
                  "context", 37);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.blas.xdotu"),
                  "name", "name", 37);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdotu.p"),
                  "resolved", "resolved", 37);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c7_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdotu.p"),
                  "context", "context", 38);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.blas.xdot"),
                  "name", "name", 38);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdot.p"),
                  "resolved", "resolved", 38);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c7_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdot.p"),
                  "context", "context", 39);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 39);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c7_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdot.p!below_threshold"),
                  "context", "context", 40);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 40);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 40);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c7_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 41);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 41);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 41);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1381850300U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c7_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xdot.p"),
                  "context", "context", 42);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.refblas.xdot"),
                  "name", "name", 42);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdot.p"),
                  "resolved", "resolved", 42);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c7_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdot.p"),
                  "context", "context", 43);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.refblas.xdotx"),
                  "name", "name", 43);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "resolved", "resolved", 43);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307922U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c7_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "context", "context", 44);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 44);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 44);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1389307920U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c7_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "context", "context", 45);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.indexMinus"),
                  "name", "name", 45);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexMinus.m"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c7_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "context", "context", 46);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.indexTimes"),
                  "name", "name", 46);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 46);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexTimes.m"),
                  "resolved", "resolved", 46);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c7_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "context", "context", 47);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 47);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 47);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1372583160U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c7_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xdotx.p"),
                  "context", "context", 48);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 48);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 48);
  sf_mex_addfield(*c7_info, c7_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 48);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(1375980688U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c7_info, c7_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c7_rhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c7_lhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c7_info, sf_mex_duplicatearraysafe(&c7_lhs48), "lhs", "lhs",
                  48);
  sf_mex_destroy(&c7_rhs0);
  sf_mex_destroy(&c7_lhs0);
  sf_mex_destroy(&c7_rhs1);
  sf_mex_destroy(&c7_lhs1);
  sf_mex_destroy(&c7_rhs2);
  sf_mex_destroy(&c7_lhs2);
  sf_mex_destroy(&c7_rhs3);
  sf_mex_destroy(&c7_lhs3);
  sf_mex_destroy(&c7_rhs4);
  sf_mex_destroy(&c7_lhs4);
  sf_mex_destroy(&c7_rhs5);
  sf_mex_destroy(&c7_lhs5);
  sf_mex_destroy(&c7_rhs6);
  sf_mex_destroy(&c7_lhs6);
  sf_mex_destroy(&c7_rhs7);
  sf_mex_destroy(&c7_lhs7);
  sf_mex_destroy(&c7_rhs8);
  sf_mex_destroy(&c7_lhs8);
  sf_mex_destroy(&c7_rhs9);
  sf_mex_destroy(&c7_lhs9);
  sf_mex_destroy(&c7_rhs10);
  sf_mex_destroy(&c7_lhs10);
  sf_mex_destroy(&c7_rhs11);
  sf_mex_destroy(&c7_lhs11);
  sf_mex_destroy(&c7_rhs12);
  sf_mex_destroy(&c7_lhs12);
  sf_mex_destroy(&c7_rhs13);
  sf_mex_destroy(&c7_lhs13);
  sf_mex_destroy(&c7_rhs14);
  sf_mex_destroy(&c7_lhs14);
  sf_mex_destroy(&c7_rhs15);
  sf_mex_destroy(&c7_lhs15);
  sf_mex_destroy(&c7_rhs16);
  sf_mex_destroy(&c7_lhs16);
  sf_mex_destroy(&c7_rhs17);
  sf_mex_destroy(&c7_lhs17);
  sf_mex_destroy(&c7_rhs18);
  sf_mex_destroy(&c7_lhs18);
  sf_mex_destroy(&c7_rhs19);
  sf_mex_destroy(&c7_lhs19);
  sf_mex_destroy(&c7_rhs20);
  sf_mex_destroy(&c7_lhs20);
  sf_mex_destroy(&c7_rhs21);
  sf_mex_destroy(&c7_lhs21);
  sf_mex_destroy(&c7_rhs22);
  sf_mex_destroy(&c7_lhs22);
  sf_mex_destroy(&c7_rhs23);
  sf_mex_destroy(&c7_lhs23);
  sf_mex_destroy(&c7_rhs24);
  sf_mex_destroy(&c7_lhs24);
  sf_mex_destroy(&c7_rhs25);
  sf_mex_destroy(&c7_lhs25);
  sf_mex_destroy(&c7_rhs26);
  sf_mex_destroy(&c7_lhs26);
  sf_mex_destroy(&c7_rhs27);
  sf_mex_destroy(&c7_lhs27);
  sf_mex_destroy(&c7_rhs28);
  sf_mex_destroy(&c7_lhs28);
  sf_mex_destroy(&c7_rhs29);
  sf_mex_destroy(&c7_lhs29);
  sf_mex_destroy(&c7_rhs30);
  sf_mex_destroy(&c7_lhs30);
  sf_mex_destroy(&c7_rhs31);
  sf_mex_destroy(&c7_lhs31);
  sf_mex_destroy(&c7_rhs32);
  sf_mex_destroy(&c7_lhs32);
  sf_mex_destroy(&c7_rhs33);
  sf_mex_destroy(&c7_lhs33);
  sf_mex_destroy(&c7_rhs34);
  sf_mex_destroy(&c7_lhs34);
  sf_mex_destroy(&c7_rhs35);
  sf_mex_destroy(&c7_lhs35);
  sf_mex_destroy(&c7_rhs36);
  sf_mex_destroy(&c7_lhs36);
  sf_mex_destroy(&c7_rhs37);
  sf_mex_destroy(&c7_lhs37);
  sf_mex_destroy(&c7_rhs38);
  sf_mex_destroy(&c7_lhs38);
  sf_mex_destroy(&c7_rhs39);
  sf_mex_destroy(&c7_lhs39);
  sf_mex_destroy(&c7_rhs40);
  sf_mex_destroy(&c7_lhs40);
  sf_mex_destroy(&c7_rhs41);
  sf_mex_destroy(&c7_lhs41);
  sf_mex_destroy(&c7_rhs42);
  sf_mex_destroy(&c7_lhs42);
  sf_mex_destroy(&c7_rhs43);
  sf_mex_destroy(&c7_lhs43);
  sf_mex_destroy(&c7_rhs44);
  sf_mex_destroy(&c7_lhs44);
  sf_mex_destroy(&c7_rhs45);
  sf_mex_destroy(&c7_lhs45);
  sf_mex_destroy(&c7_rhs46);
  sf_mex_destroy(&c7_lhs46);
  sf_mex_destroy(&c7_rhs47);
  sf_mex_destroy(&c7_lhs47);
  sf_mex_destroy(&c7_rhs48);
  sf_mex_destroy(&c7_lhs48);
}

static const mxArray *c7_emlrt_marshallOut(const char * c7_u)
{
  const mxArray *c7_y = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c7_u)), false);
  return c7_y;
}

static const mxArray *c7_b_emlrt_marshallOut(const uint32_T c7_u)
{
  const mxArray *c7_y = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 7, 0U, 0U, 0U, 0), false);
  return c7_y;
}

static void c7_scalarEg(SFc7_hexacopterInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static real_T c7_eml_xdotu(SFc7_hexacopterInstanceStruct *chartInstance, real_T
  c7_x[3], real_T c7_y[3])
{
  real_T c7_d;
  int32_T c7_k;
  int32_T c7_b_k;
  c7_scalarEg(chartInstance);
  c7_d = 0.0;
  for (c7_k = 1; c7_k < 4; c7_k++) {
    c7_b_k = c7_k;
    c7_d += c7_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c7_b_k), 1, 3, 1, 0) - 1] * c7_y[_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)_SFD_INTEGER_CHECK("", (real_T)c7_b_k), 1, 3, 1, 0) - 1];
  }

  return c7_d;
}

static int32_T c7_m_emlrt_marshallIn(SFc7_hexacopterInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  int32_T c7_y;
  int32_T c7_i85;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_i85, 1, 6, 0U, 0, 0U, 0);
  c7_y = c7_i85;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_b_sfEvent;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  int32_T c7_y;
  SFc7_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc7_hexacopterInstanceStruct *)chartInstanceVoid;
  c7_b_sfEvent = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_sfEvent),
    &c7_thisId);
  sf_mex_destroy(&c7_b_sfEvent);
  *(int32_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static uint8_T c7_n_emlrt_marshallIn(SFc7_hexacopterInstanceStruct
  *chartInstance, const mxArray *c7_b_is_active_c7_hexacopter, const char_T
  *c7_identifier)
{
  uint8_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_o_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c7_b_is_active_c7_hexacopter), &c7_thisId);
  sf_mex_destroy(&c7_b_is_active_c7_hexacopter);
  return c7_y;
}

static uint8_T c7_o_emlrt_marshallIn(SFc7_hexacopterInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  uint8_T c7_y;
  uint8_T c7_u0;
  (void)chartInstance;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_u0, 1, 3, 0U, 0, 0U, 0);
  c7_y = c7_u0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void init_dsm_address_info(SFc7_hexacopterInstanceStruct *chartInstance)
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

void sf_c7_hexacopter_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1689074615U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(829874842U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3329842432U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1044896153U);
}

mxArray *sf_c7_hexacopter_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("SDOwiPgmZCjGK45TVfIrRB");
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
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(8));
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c7_hexacopter_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c7_hexacopter_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c7_hexacopter(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[5],T\"H\",},{M[1],M[7],T\"Hcov\",},{M[4],M[0],T\"HCOVARIANCE\",S'l','i','p'{{M1x2[124 135],M[0],}}},{M[4],M[0],T\"HMEAN\",S'l','i','p'{{M1x2[102 107],M[0],}}},{M[4],M[0],T\"HVECTOR\",S'l','i','p'{{M1x2[78 85],M[0],}}},{M[8],M[0],T\"is_active_c7_hexacopter\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c7_hexacopter_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc7_hexacopterInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc7_hexacopterInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _hexacopterMachineNumber_,
           7,
           1,
           1,
           0,
           4,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"H_sample");
          _SFD_SET_DATA_PROPS(1,2,0,1,"H");
          _SFD_SET_DATA_PROPS(2,1,1,0,"i");
          _SFD_SET_DATA_PROPS(3,2,0,1,"Hcov");
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
        _SFD_CV_INIT_EML(0,1,1,4,0,0,0,1,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,806);
        _SFD_CV_INIT_EML_IF(0,1,0,141,160,-1,199);
        _SFD_CV_INIT_EML_IF(0,1,1,204,221,-1,257);
        _SFD_CV_INIT_EML_IF(0,1,2,262,285,-1,327);
        _SFD_CV_INIT_EML_IF(0,1,3,392,401,681,726);
        _SFD_CV_INIT_EML_FOR(0,1,0,494,506,637);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_e_sf_marshallOut,(MexInFcnForType)
            c7_e_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_f_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_d_sf_marshallOut,(MexInFcnForType)
            c7_d_sf_marshallIn);
        }

        {
          int32_T *c7_i;
          real_T (*c7_H_sample)[3];
          real_T (*c7_H)[3];
          real_T (*c7_Hcov)[9];
          c7_Hcov = (real_T (*)[9])ssGetOutputPortSignal(chartInstance->S, 2);
          c7_i = (int32_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c7_H = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c7_H_sample = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c7_H_sample);
          _SFD_SET_DATA_VALUE_PTR(1U, *c7_H);
          _SFD_SET_DATA_VALUE_PTR(2U, c7_i);
          _SFD_SET_DATA_VALUE_PTR(3U, *c7_Hcov);
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
  return "nyYUqSqzfUC61H7ygiZynE";
}

static void sf_opaque_initialize_c7_hexacopter(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc7_hexacopterInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c7_hexacopter((SFc7_hexacopterInstanceStruct*)
    chartInstanceVar);
  initialize_c7_hexacopter((SFc7_hexacopterInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c7_hexacopter(void *chartInstanceVar)
{
  enable_c7_hexacopter((SFc7_hexacopterInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c7_hexacopter(void *chartInstanceVar)
{
  disable_c7_hexacopter((SFc7_hexacopterInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c7_hexacopter(void *chartInstanceVar)
{
  sf_gateway_c7_hexacopter((SFc7_hexacopterInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c7_hexacopter(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c7_hexacopter
    ((SFc7_hexacopterInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c7_hexacopter();/* state var info */
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

extern void sf_internal_set_sim_state_c7_hexacopter(SimStruct* S, const mxArray *
  st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c7_hexacopter();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c7_hexacopter((SFc7_hexacopterInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c7_hexacopter(SimStruct* S)
{
  return sf_internal_get_sim_state_c7_hexacopter(S);
}

static void sf_opaque_set_sim_state_c7_hexacopter(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c7_hexacopter(S, st);
}

static void sf_opaque_terminate_c7_hexacopter(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc7_hexacopterInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_hexacopter_optimization_info();
    }

    finalize_c7_hexacopter((SFc7_hexacopterInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc7_hexacopter((SFc7_hexacopterInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c7_hexacopter(SimStruct *S)
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
    initialize_params_c7_hexacopter((SFc7_hexacopterInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c7_hexacopter(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_hexacopter_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,7);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,7,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,7,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,7);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,7,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,7,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,7);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2010083353U));
  ssSetChecksum1(S,(3859637349U));
  ssSetChecksum2(S,(4272081846U));
  ssSetChecksum3(S,(2944813708U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c7_hexacopter(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c7_hexacopter(SimStruct *S)
{
  SFc7_hexacopterInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc7_hexacopterInstanceStruct *)utMalloc(sizeof
    (SFc7_hexacopterInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc7_hexacopterInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c7_hexacopter;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c7_hexacopter;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c7_hexacopter;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c7_hexacopter;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c7_hexacopter;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c7_hexacopter;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c7_hexacopter;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c7_hexacopter;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c7_hexacopter;
  chartInstance->chartInfo.mdlStart = mdlStart_c7_hexacopter;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c7_hexacopter;
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

void c7_hexacopter_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c7_hexacopter(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c7_hexacopter(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c7_hexacopter(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c7_hexacopter_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
