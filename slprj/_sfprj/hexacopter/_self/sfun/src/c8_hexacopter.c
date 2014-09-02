/* Include files */

#include <stddef.h>
#include "blas.h"
#include "hexacopter_sfun.h"
#include "c8_hexacopter.h"
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
static const char * c8_debug_family_names[8] = { "feval_ret", "nargin",
  "nargout", "x_obst", "x_drone", "R_G2B", "parameter", "dist_out" };

/* Function Declarations */
static void initialize_c8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance);
static void initialize_params_c8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance);
static void enable_c8_hexacopter(SFc8_hexacopterInstanceStruct *chartInstance);
static void disable_c8_hexacopter(SFc8_hexacopterInstanceStruct *chartInstance);
static void c8_update_debugger_state_c8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c8_hexacopter(SFc8_hexacopterInstanceStruct *
  chartInstance);
static void set_sim_state_c8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance, const mxArray *c8_st);
static void finalize_c8_hexacopter(SFc8_hexacopterInstanceStruct *chartInstance);
static void sf_gateway_c8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance);
static void initSimStructsc8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber, uint32_T c8_instanceNumber);
static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData);
static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_e_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static real_T c8_emlrt_marshallIn(SFc8_hexacopterInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static void c8_b_emlrt_marshallIn(SFc8_hexacopterInstanceStruct *chartInstance,
  const mxArray *c8_feval, const char_T *c8_identifier, real_T c8_y[6]);
static void c8_c_emlrt_marshallIn(SFc8_hexacopterInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId, real_T c8_y[6]);
static const mxArray *c8_f_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int32_T c8_d_emlrt_marshallIn(SFc8_hexacopterInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static uint8_T c8_e_emlrt_marshallIn(SFc8_hexacopterInstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_hexacopter, const char_T
  *c8_identifier);
static uint8_T c8_f_emlrt_marshallIn(SFc8_hexacopterInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void init_dsm_address_info(SFc8_hexacopterInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance)
{
  chartInstance->c8_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c8_is_active_c8_hexacopter = 0U;
}

static void initialize_params_c8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c8_hexacopter(SFc8_hexacopterInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c8_hexacopter(SFc8_hexacopterInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c8_update_debugger_state_c8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c8_hexacopter(SFc8_hexacopterInstanceStruct *
  chartInstance)
{
  const mxArray *c8_st;
  const mxArray *c8_y = NULL;
  int32_T c8_i0;
  real_T c8_u[6];
  const mxArray *c8_b_y = NULL;
  uint8_T c8_hoistedGlobal;
  uint8_T c8_b_u;
  const mxArray *c8_c_y = NULL;
  real_T (*c8_dist_out)[6];
  c8_dist_out = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_st = NULL;
  c8_st = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createcellmatrix(2, 1), false);
  for (c8_i0 = 0; c8_i0 < 6; c8_i0++) {
    c8_u[c8_i0] = (*c8_dist_out)[c8_i0];
  }

  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_setcell(c8_y, 0, c8_b_y);
  c8_hoistedGlobal = chartInstance->c8_is_active_c8_hexacopter;
  c8_b_u = c8_hoistedGlobal;
  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c8_y, 1, c8_c_y);
  sf_mex_assign(&c8_st, c8_y, false);
  return c8_st;
}

static void set_sim_state_c8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance, const mxArray *c8_st)
{
  const mxArray *c8_u;
  real_T c8_dv0[6];
  int32_T c8_i1;
  real_T (*c8_dist_out)[6];
  c8_dist_out = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c8_doneDoubleBufferReInit = true;
  c8_u = sf_mex_dup(c8_st);
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 0)),
                        "dist_out", c8_dv0);
  for (c8_i1 = 0; c8_i1 < 6; c8_i1++) {
    (*c8_dist_out)[c8_i1] = c8_dv0[c8_i1];
  }

  chartInstance->c8_is_active_c8_hexacopter = c8_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 1)),
     "is_active_c8_hexacopter");
  sf_mex_destroy(&c8_u);
  c8_update_debugger_state_c8_hexacopter(chartInstance);
  sf_mex_destroy(&c8_st);
}

static void finalize_c8_hexacopter(SFc8_hexacopterInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance)
{
  int32_T c8_i2;
  int32_T c8_i3;
  real_T c8_x_obst[3993];
  int32_T c8_i4;
  real_T c8_x_drone[3];
  int32_T c8_i5;
  real_T c8_R_G2B[9];
  int32_T c8_i6;
  real_T c8_parameter[3];
  uint32_T c8_debug_family_var_map[8];
  real_T c8_feval_ret[6];
  real_T c8_nargin = 4.0;
  real_T c8_nargout = 1.0;
  real_T c8_dist_out[6];
  int32_T c8_i7;
  int32_T c8_i8;
  int32_T c8_i9;
  static char_T c8_cv0[17] = { 'r', 'a', 'n', 'g', 'e', 'R', 'e', 'c', 'e', 'i',
    'v', 'e', 'r', '_', 'm', 'e', 'x' };

  char_T c8_u[17];
  const mxArray *c8_y = NULL;
  int32_T c8_i10;
  real_T c8_b_u[3993];
  const mxArray *c8_b_y = NULL;
  int32_T c8_i11;
  real_T c8_c_u[3];
  const mxArray *c8_c_y = NULL;
  int32_T c8_i12;
  real_T c8_d_u[9];
  const mxArray *c8_d_y = NULL;
  int32_T c8_i13;
  real_T c8_e_u[3];
  const mxArray *c8_e_y = NULL;
  real_T c8_dv1[6];
  int32_T c8_i14;
  int32_T c8_i15;
  int32_T c8_i16;
  int32_T c8_i17;
  int32_T c8_i18;
  int32_T c8_i19;
  int32_T c8_i20;
  real_T (*c8_b_dist_out)[6];
  real_T (*c8_b_parameter)[3];
  real_T (*c8_b_R_G2B)[9];
  real_T (*c8_b_x_drone)[3];
  real_T (*c8_b_x_obst)[3993];
  c8_b_parameter = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
  c8_b_R_G2B = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 2);
  c8_b_x_drone = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c8_b_dist_out = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c8_b_x_obst = (real_T (*)[3993])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 6U, chartInstance->c8_sfEvent);
  for (c8_i2 = 0; c8_i2 < 3993; c8_i2++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_x_obst)[c8_i2], 0U);
  }

  chartInstance->c8_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 6U, chartInstance->c8_sfEvent);
  for (c8_i3 = 0; c8_i3 < 3993; c8_i3++) {
    c8_x_obst[c8_i3] = (*c8_b_x_obst)[c8_i3];
  }

  for (c8_i4 = 0; c8_i4 < 3; c8_i4++) {
    c8_x_drone[c8_i4] = (*c8_b_x_drone)[c8_i4];
  }

  for (c8_i5 = 0; c8_i5 < 9; c8_i5++) {
    c8_R_G2B[c8_i5] = (*c8_b_R_G2B)[c8_i5];
  }

  for (c8_i6 = 0; c8_i6 < 3; c8_i6++) {
    c8_parameter[c8_i6] = (*c8_b_parameter)[c8_i6];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c8_debug_family_names,
    c8_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_feval_ret, 0U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargin, 1U, c8_e_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargout, 2U, c8_e_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_x_obst, 3U, c8_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_x_drone, 4U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_R_G2B, 5U, c8_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c8_parameter, 6U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c8_dist_out, 7U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 2);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 3);
  for (c8_i7 = 0; c8_i7 < 6; c8_i7++) {
    c8_feval_ret[c8_i7] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 4);
  for (c8_i8 = 0; c8_i8 < 6; c8_i8++) {
    c8_dist_out[c8_i8] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 5);
  for (c8_i9 = 0; c8_i9 < 17; c8_i9++) {
    c8_u[c8_i9] = c8_cv0[c8_i9];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 10, 0U, 1U, 0U, 2, 1, 17), false);
  for (c8_i10 = 0; c8_i10 < 3993; c8_i10++) {
    c8_b_u[c8_i10] = c8_x_obst[c8_i10];
  }

  c8_b_y = NULL;
  sf_mex_assign(&c8_b_y, sf_mex_create("y", c8_b_u, 0, 0U, 1U, 0U, 2, 3, 1331),
                false);
  for (c8_i11 = 0; c8_i11 < 3; c8_i11++) {
    c8_c_u[c8_i11] = c8_x_drone[c8_i11];
  }

  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", c8_c_u, 0, 0U, 1U, 0U, 1, 3), false);
  for (c8_i12 = 0; c8_i12 < 9; c8_i12++) {
    c8_d_u[c8_i12] = c8_R_G2B[c8_i12];
  }

  c8_d_y = NULL;
  sf_mex_assign(&c8_d_y, sf_mex_create("y", c8_d_u, 0, 0U, 1U, 0U, 2, 3, 3),
                false);
  for (c8_i13 = 0; c8_i13 < 3; c8_i13++) {
    c8_e_u[c8_i13] = c8_parameter[c8_i13];
  }

  c8_e_y = NULL;
  sf_mex_assign(&c8_e_y, sf_mex_create("y", c8_e_u, 0, 0U, 1U, 0U, 1, 3), false);
  c8_b_emlrt_marshallIn(chartInstance, sf_mex_call_debug
                        (sfGlobalDebugInstanceStruct, "feval", 1U, 5U, 14, c8_y,
    14, c8_b_y, 14, c8_c_y, 14, c8_d_y, 14, c8_e_y), "feval", c8_dv1);
  for (c8_i14 = 0; c8_i14 < 6; c8_i14++) {
    c8_feval_ret[c8_i14] = c8_dv1[c8_i14];
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 6);
  for (c8_i15 = 0; c8_i15 < 6; c8_i15++) {
    c8_dist_out[c8_i15] = c8_feval_ret[c8_i15];
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, -6);
  _SFD_SYMBOL_SCOPE_POP();
  for (c8_i16 = 0; c8_i16 < 6; c8_i16++) {
    (*c8_b_dist_out)[c8_i16] = c8_dist_out[c8_i16];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c8_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_hexacopterMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c8_i17 = 0; c8_i17 < 6; c8_i17++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_dist_out)[c8_i17], 1U);
  }

  for (c8_i18 = 0; c8_i18 < 3; c8_i18++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_x_drone)[c8_i18], 2U);
  }

  for (c8_i19 = 0; c8_i19 < 9; c8_i19++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_R_G2B)[c8_i19], 3U);
  }

  for (c8_i20 = 0; c8_i20 < 3; c8_i20++) {
    _SFD_DATA_RANGE_CHECK((*c8_b_parameter)[c8_i20], 4U);
  }
}

static void initSimStructsc8_hexacopter(SFc8_hexacopterInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber, uint32_T c8_instanceNumber)
{
  (void)c8_machineNumber;
  (void)c8_chartNumber;
  (void)c8_instanceNumber;
}

static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i21;
  real_T c8_b_inData[6];
  int32_T c8_i22;
  real_T c8_u[6];
  const mxArray *c8_y = NULL;
  SFc8_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc8_hexacopterInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i21 = 0; c8_i21 < 6; c8_i21++) {
    c8_b_inData[c8_i21] = (*(real_T (*)[6])c8_inData)[c8_i21];
  }

  for (c8_i22 = 0; c8_i22 < 6; c8_i22++) {
    c8_u[c8_i22] = c8_b_inData[c8_i22];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_feval;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y[6];
  int32_T c8_i23;
  SFc8_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc8_hexacopterInstanceStruct *)chartInstanceVoid;
  c8_feval = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_feval), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_feval);
  for (c8_i23 = 0; c8_i23 < 6; c8_i23++) {
    (*(real_T (*)[6])c8_outData)[c8_i23] = c8_y[c8_i23];
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i24;
  real_T c8_b_inData[3];
  int32_T c8_i25;
  real_T c8_u[3];
  const mxArray *c8_y = NULL;
  SFc8_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc8_hexacopterInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  for (c8_i24 = 0; c8_i24 < 3; c8_i24++) {
    c8_b_inData[c8_i24] = (*(real_T (*)[3])c8_inData)[c8_i24];
  }

  for (c8_i25 = 0; c8_i25 < 3; c8_i25++) {
    c8_u[c8_i25] = c8_b_inData[c8_i25];
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i26;
  int32_T c8_i27;
  int32_T c8_i28;
  real_T c8_b_inData[9];
  int32_T c8_i29;
  int32_T c8_i30;
  int32_T c8_i31;
  real_T c8_u[9];
  const mxArray *c8_y = NULL;
  SFc8_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc8_hexacopterInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_i26 = 0;
  for (c8_i27 = 0; c8_i27 < 3; c8_i27++) {
    for (c8_i28 = 0; c8_i28 < 3; c8_i28++) {
      c8_b_inData[c8_i28 + c8_i26] = (*(real_T (*)[9])c8_inData)[c8_i28 + c8_i26];
    }

    c8_i26 += 3;
  }

  c8_i29 = 0;
  for (c8_i30 = 0; c8_i30 < 3; c8_i30++) {
    for (c8_i31 = 0; c8_i31 < 3; c8_i31++) {
      c8_u[c8_i31 + c8_i29] = c8_b_inData[c8_i31 + c8_i29];
    }

    c8_i29 += 3;
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_i32;
  int32_T c8_i33;
  int32_T c8_i34;
  real_T c8_b_inData[3993];
  int32_T c8_i35;
  int32_T c8_i36;
  int32_T c8_i37;
  real_T c8_u[3993];
  const mxArray *c8_y = NULL;
  SFc8_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc8_hexacopterInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_i32 = 0;
  for (c8_i33 = 0; c8_i33 < 1331; c8_i33++) {
    for (c8_i34 = 0; c8_i34 < 3; c8_i34++) {
      c8_b_inData[c8_i34 + c8_i32] = (*(real_T (*)[3993])c8_inData)[c8_i34 +
        c8_i32];
    }

    c8_i32 += 3;
  }

  c8_i35 = 0;
  for (c8_i36 = 0; c8_i36 < 1331; c8_i36++) {
    for (c8_i37 = 0; c8_i37 < 3; c8_i37++) {
      c8_u[c8_i37 + c8_i35] = c8_b_inData[c8_i37 + c8_i35];
    }

    c8_i35 += 3;
  }

  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 0, 0U, 1U, 0U, 2, 3, 1331),
                false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static const mxArray *c8_e_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  real_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc8_hexacopterInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(real_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static real_T c8_emlrt_marshallIn(SFc8_hexacopterInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  real_T c8_y;
  real_T c8_d0;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_d0, 1, 0, 0U, 0, 0U, 0);
  c8_y = c8_d0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_nargout;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y;
  SFc8_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc8_hexacopterInstanceStruct *)chartInstanceVoid;
  c8_nargout = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_nargout), &c8_thisId);
  sf_mex_destroy(&c8_nargout);
  *(real_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

const mxArray *sf_c8_hexacopter_get_eml_resolved_functions_info(void)
{
  const mxArray *c8_nameCaptureInfo = NULL;
  c8_nameCaptureInfo = NULL;
  sf_mex_assign(&c8_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c8_nameCaptureInfo;
}

static void c8_b_emlrt_marshallIn(SFc8_hexacopterInstanceStruct *chartInstance,
  const mxArray *c8_feval, const char_T *c8_identifier, real_T c8_y[6])
{
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_feval), &c8_thisId, c8_y);
  sf_mex_destroy(&c8_feval);
}

static void c8_c_emlrt_marshallIn(SFc8_hexacopterInstanceStruct *chartInstance,
  const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId, real_T c8_y[6])
{
  real_T c8_dv2[6];
  int32_T c8_i38;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), c8_dv2, 1, 0, 0U, 1, 0U, 1, 6);
  for (c8_i38 = 0; c8_i38 < 6; c8_i38++) {
    c8_y[c8_i38] = c8_dv2[c8_i38];
  }

  sf_mex_destroy(&c8_u);
}

static const mxArray *c8_f_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc8_hexacopterInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(int32_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static int32_T c8_d_emlrt_marshallIn(SFc8_hexacopterInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int32_T c8_y;
  int32_T c8_i39;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_i39, 1, 6, 0U, 0, 0U, 0);
  c8_y = c8_i39;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_sfEvent;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  int32_T c8_y;
  SFc8_hexacopterInstanceStruct *chartInstance;
  chartInstance = (SFc8_hexacopterInstanceStruct *)chartInstanceVoid;
  c8_b_sfEvent = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_sfEvent),
    &c8_thisId);
  sf_mex_destroy(&c8_b_sfEvent);
  *(int32_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static uint8_T c8_e_emlrt_marshallIn(SFc8_hexacopterInstanceStruct
  *chartInstance, const mxArray *c8_b_is_active_c8_hexacopter, const char_T
  *c8_identifier)
{
  uint8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c8_b_is_active_c8_hexacopter), &c8_thisId);
  sf_mex_destroy(&c8_b_is_active_c8_hexacopter);
  return c8_y;
}

static uint8_T c8_f_emlrt_marshallIn(SFc8_hexacopterInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  uint8_T c8_u0;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_u0, 1, 3, 0U, 0, 0U, 0);
  c8_y = c8_u0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void init_dsm_address_info(SFc8_hexacopterInstanceStruct *chartInstance)
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

void sf_c8_hexacopter_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2961155726U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(810193549U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2010010183U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3994175631U);
}

mxArray *sf_c8_hexacopter_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("2yrathVMbLDVwWv6821qVE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1331);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c8_hexacopter_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c8_hexacopter_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c8_hexacopter(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"dist_out\",},{M[8],M[0],T\"is_active_c8_hexacopter\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c8_hexacopter_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_hexacopterInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc8_hexacopterInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _hexacopterMachineNumber_,
           8,
           1,
           1,
           0,
           5,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"x_obst");
          _SFD_SET_DATA_PROPS(1,2,0,1,"dist_out");
          _SFD_SET_DATA_PROPS(2,1,1,0,"x_drone");
          _SFD_SET_DATA_PROPS(3,1,1,0,"R_G2B");
          _SFD_SET_DATA_PROPS(4,1,1,0,"parameter");
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
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,977);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 1331;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_sf_marshallOut,(MexInFcnForType)
            c8_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c8_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c8_x_obst)[3993];
          real_T (*c8_dist_out)[6];
          real_T (*c8_x_drone)[3];
          real_T (*c8_R_G2B)[9];
          real_T (*c8_parameter)[3];
          c8_parameter = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 3);
          c8_R_G2B = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 2);
          c8_x_drone = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c8_dist_out = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
          c8_x_obst = (real_T (*)[3993])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c8_x_obst);
          _SFD_SET_DATA_VALUE_PTR(1U, *c8_dist_out);
          _SFD_SET_DATA_VALUE_PTR(2U, *c8_x_drone);
          _SFD_SET_DATA_VALUE_PTR(3U, *c8_R_G2B);
          _SFD_SET_DATA_VALUE_PTR(4U, *c8_parameter);
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
  return "m8cGyVNx2n7tAaCkAmBMPF";
}

static void sf_opaque_initialize_c8_hexacopter(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc8_hexacopterInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c8_hexacopter((SFc8_hexacopterInstanceStruct*)
    chartInstanceVar);
  initialize_c8_hexacopter((SFc8_hexacopterInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c8_hexacopter(void *chartInstanceVar)
{
  enable_c8_hexacopter((SFc8_hexacopterInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c8_hexacopter(void *chartInstanceVar)
{
  disable_c8_hexacopter((SFc8_hexacopterInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c8_hexacopter(void *chartInstanceVar)
{
  sf_gateway_c8_hexacopter((SFc8_hexacopterInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c8_hexacopter(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c8_hexacopter
    ((SFc8_hexacopterInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_hexacopter();/* state var info */
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

extern void sf_internal_set_sim_state_c8_hexacopter(SimStruct* S, const mxArray *
  st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c8_hexacopter();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c8_hexacopter((SFc8_hexacopterInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c8_hexacopter(SimStruct* S)
{
  return sf_internal_get_sim_state_c8_hexacopter(S);
}

static void sf_opaque_set_sim_state_c8_hexacopter(SimStruct* S, const mxArray
  *st)
{
  sf_internal_set_sim_state_c8_hexacopter(S, st);
}

static void sf_opaque_terminate_c8_hexacopter(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc8_hexacopterInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_hexacopter_optimization_info();
    }

    finalize_c8_hexacopter((SFc8_hexacopterInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc8_hexacopter((SFc8_hexacopterInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c8_hexacopter(SimStruct *S)
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
    initialize_params_c8_hexacopter((SFc8_hexacopterInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c8_hexacopter(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_hexacopter_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,8);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,8,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,8,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,8);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,8,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,8,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,8);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2572777476U));
  ssSetChecksum1(S,(2821887363U));
  ssSetChecksum2(S,(2861542502U));
  ssSetChecksum3(S,(2990155535U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c8_hexacopter(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c8_hexacopter(SimStruct *S)
{
  SFc8_hexacopterInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc8_hexacopterInstanceStruct *)utMalloc(sizeof
    (SFc8_hexacopterInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc8_hexacopterInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c8_hexacopter;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c8_hexacopter;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c8_hexacopter;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c8_hexacopter;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c8_hexacopter;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c8_hexacopter;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c8_hexacopter;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c8_hexacopter;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c8_hexacopter;
  chartInstance->chartInfo.mdlStart = mdlStart_c8_hexacopter;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c8_hexacopter;
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

void c8_hexacopter_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c8_hexacopter(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c8_hexacopter(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c8_hexacopter(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c8_hexacopter_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
