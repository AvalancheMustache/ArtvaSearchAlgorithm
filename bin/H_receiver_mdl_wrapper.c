

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
#include "math.h"
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 3
#define y_width 1
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
void H_receiver_mdl_Outputs_wrapper(const real_T *rT,
			const real_T *rR,
			const real_T *m,
			real_T *HField,
			real_T *Hstrenght)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
#define M_1_PI 3.183098861837907e-01
double x, y, z, r;
#define PERTURBAZIONE 1e-15

x = rR[0] - rT[0];
y = rR[1] - rT[1];
z = rR[2] - rT[2];
r = sqrt(x * x + y * y + z * z + PERTURBAZIONE);
HField[0] = 0.250e0 * M_1_PI * pow(r, -0.5e1) * (-0.1e1 * r * r + 0.3e1 * x * x) * m[0] + 0.750e0 * M_1_PI * pow(r, -0.5e1) * x * y * m[1] + 0.750e0 * M_1_PI * pow(r, -0.5e1) * x * z * m[2];
HField[1] = 0.750e0 * M_1_PI * pow(r, -0.5e1) * x * y * m[0] + 0.250e0 * M_1_PI * pow(r, -0.5e1) * (-0.1e1 * r * r + 0.3e1 * y * y) * m[1] + 0.750e0 * M_1_PI * pow(r, -0.5e1) * y * z * m[2];
HField[2] = 0.750e0 * M_1_PI * pow(r, -0.5e1) * x * z * m[0] + 0.750e0 * M_1_PI * pow(r, -0.5e1) * y * z * m[1] + 0.250e0 * M_1_PI * pow(r, -0.5e1) * (-0.1e1 * r * r + 0.3e1 * z * z) * m[2];

Hstrenght[0] = sqrt(HField[0]*HField[0] + HField[1]*HField[1] + HField[2]*HField[2]);
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}
