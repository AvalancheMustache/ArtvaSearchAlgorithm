

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
#define u_width 6
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
void hexacopter_s_Outputs_wrapper(real_T *y,
			const real_T *xC)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
      y0[0] = u0[0]; 
 For complex signals use: y0[0].re = u0[0].re; 
      y0[0].im = u0[0].im;
      y1[0].re = u1[0].re;
      y1[0].im = u1[0].im;
*/

y[0]  = xC[0];
y[1]  = xC[1];
y[2]  = xC[2];
y[3]  = xC[3];
y[4]  = xC[4];
y[5]  = xC[5];
y[6]  = xC[6];
y[7]  = xC[7];
y[8]  = xC[8];
y[9]  = xC[9];
y[10] = xC[10];
y[11] = xC[11];
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
  *  Derivatives function
  *
  */
void hexacopter_s_Derivatives_wrapper(const real_T *u,
			const real_T *p,
			const real_T *y,
			real_T *dx,
			real_T *xC)
{
/* %%%-SFUNWIZ_wrapper_Derivatives_Changes_BEGIN --- EDIT HERE TO _END */
/*
 * States: xC[0..11]
 * [ x  y  z  u  v  w  phi  theta  psi  p  q  r  ]
 *   0  1  2  3  4  5  6    7      8    9  10 11 
 * Input: u[0..5]
 * [ L1 L2 L3 L4 L5 L6 ]
 *   0  1  2  3  4  5
 */

double m, Ix, Iy, Iz, B, L, g;

m  = p[0];
Ix = p[1];
Iy = p[2];
Iz = p[3];
B  = p[4];
L  = p[5];
g  = p[6];

dx[0] = cos(xC[8]) * cos(xC[7]) * xC[3] + sin(xC[8]) * cos(xC[7]) * xC[4] - sin(xC[7]) * xC[5];
dx[1] = cos(xC[8]) * xC[3] * sin(xC[7]) * sin(xC[6]) + sin(xC[8]) * xC[4] * sin(xC[7]) * sin(xC[6]) + cos(xC[8]) * xC[4] * cos(xC[6]) + cos(xC[7]) * sin(xC[6]) * xC[5] - xC[3] * sin(xC[8]) * cos(xC[6]);
dx[2] = cos(xC[8]) * xC[3] * sin(xC[7]) * cos(xC[6]) + sin(xC[8]) * xC[4] * sin(xC[7]) * cos(xC[6]) - cos(xC[8]) * xC[4] * sin(xC[6]) + cos(xC[7]) * cos(xC[6]) * xC[5] + xC[3] * sin(xC[8]) * sin(xC[6]);
dx[3] = xC[11] * xC[4] + sin(xC[7]) * g - xC[10] * xC[5];
dx[4] = -cos(xC[7]) * sin(xC[6]) * g - xC[11] * xC[3] + xC[9] * xC[5];
dx[5] = -cos(xC[7]) * cos(xC[6]) * g + xC[10] * xC[3] - xC[9] * xC[4] + (-u[0] - u[1] - u[2] - u[3] - u[4] - u[5]) / m;
dx[6] = 0.1e1 / cos(xC[7]) * (cos(xC[6]) * sin(xC[7]) * xC[11] + sin(xC[6]) * sin(xC[7]) * xC[10] + xC[9] * cos(xC[7]));
dx[7] = cos(xC[6]) * xC[10] - sin(xC[6]) * xC[11];
dx[8] = 0.1e1 / cos(xC[7]) * (cos(xC[6]) * xC[11] + sin(xC[6]) * xC[10]);
dx[9] = (-sqrt(0.3e1) * u[1] - sqrt(0.3e1) * u[2] + sqrt(0.3e1) * u[4] + sqrt(0.3e1) * u[5]) / Ix * L / 0.2e1 + (double) (2 * Iy - 2 * Iz) / Ix * xC[11] * xC[10] / 0.2e1;
dx[10] = -0.1e1 / (double) Iy * (-0.2e1 * u[0] - u[1] + u[2] + 0.2e1 * u[3] + u[4] - u[5]) * L / 0.2e1 - 0.1e1 / (double) Iy * (0.2e1 * Ix - (double) (2 * Iz)) * xC[11] * xC[9] / 0.2e1;
dx[11] = (u[0] - u[1] + u[2] - u[3] + u[4] - u[5]) / (double) Iz * B + (Ix - (double) Iy) / (double) Iz * xC[10] * xC[9];
/* %%%-SFUNWIZ_wrapper_Derivatives_Changes_END --- EDIT HERE TO _BEGIN */
}
