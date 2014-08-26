#ifndef __c6_hexacopter_h__
#define __c6_hexacopter_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc6_hexacopterInstanceStruct
#define typedef_SFc6_hexacopterInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c6_sfEvent;
  boolean_T c6_isStable;
  boolean_T c6_doneDoubleBufferReInit;
  uint8_T c6_is_active_c6_hexacopter;
  real_T c6_counter;
  boolean_T c6_counter_not_empty;
  real_T c6_Hfield_memory[12];
  boolean_T c6_Hfield_memory_not_empty;
  real_T c6_Rposition_memory[12];
  boolean_T c6_Rposition_memory_not_empty;
  real_T c6_RT[3];
  boolean_T c6_RT_not_empty;
  real_T c6_M[3];
  boolean_T c6_M_not_empty;
} SFc6_hexacopterInstanceStruct;

#endif                                 /*typedef_SFc6_hexacopterInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c6_hexacopter_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c6_hexacopter_get_check_sum(mxArray *plhs[]);
extern void c6_hexacopter_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
