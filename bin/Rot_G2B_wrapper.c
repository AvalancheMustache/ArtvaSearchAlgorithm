

/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 3
#define y_width 3
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void Rot_G2B_Outputs_wrapper(const real_T *angles,
			real_T *rot)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
rot[0] = cos(angles[2]) * cos(angles[1]);
rot[1] = -sin(angles[2]) * cos(angles[0]) + cos(angles[2]) * sin(angles[1]) * sin(angles[0]);
rot[2] = sin(angles[2]) * sin(angles[0]) + cos(angles[2]) * sin(angles[1]) * cos(angles[0]);
rot[3] = sin(angles[2]) * cos(angles[1]);
rot[4] = cos(angles[2]) * cos(angles[0]) + sin(angles[2]) * sin(angles[1]) * sin(angles[0]);
rot[5] = -cos(angles[2]) * sin(angles[0]) + sin(angles[2]) * sin(angles[1]) * cos(angles[0]);
rot[6] = -sin(angles[1]);
rot[7] = cos(angles[1]) * sin(angles[0]);
rot[8] = cos(angles[1]) * cos(angles[0]);
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}
