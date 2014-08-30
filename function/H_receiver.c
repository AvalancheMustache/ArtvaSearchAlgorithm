#include "mex.h"
#include <math.h>

/*
 *  H_RECEIVER.c - receive a position and returns the value of the vector field in such position.
 *  Inputs: 
 *  - tP     : position of transmitter
 *  - m      : magnetic transmission vector
 *  - rP     : receiver position
 *  - angles : receiver orientation
 *  Outputs:
 *  - Hfield : strength of magnetic field in receiver position
 */
#ifndef M_1_PI 
    #define M_1_PI 3.183098861837907e-01
#endif

#define PERTURBATION 0.1e-9

void H_receiver(double Hfield[], double tP[], double m[], double rP[], double angles[]) {
    Hfield[0] = pow(sqrt(pow(rP[0] - tP[0], 0.2e1) + pow(rP[1] - tP[1], 0.2e1) + pow(rP[2] - tP[2], 0.2e1)) + PERTURBATION, -0.5e1) * M_1_PI * cos(angles[2]) * cos(angles[1]) * ((0.2e1 * pow(rP[0] - tP[0], 0.2e1) - pow(rP[1] - tP[1], 0.2e1) - pow(rP[2] - tP[2], 0.2e1)) * m[0] + 0.3e1 * (rP[0] - tP[0]) * (rP[1] - tP[1]) * m[1] + 0.3e1 * (rP[0] - tP[0]) * (rP[2] - tP[2]) * m[2]) / 0.4e1 + pow(sqrt(pow(rP[0] - tP[0], 0.2e1) + pow(rP[1] - tP[1], 0.2e1) + pow(rP[2] - tP[2], 0.2e1)) + PERTURBATION, -0.5e1) * M_1_PI * sin(angles[2]) * cos(angles[1]) * (0.3e1 * (rP[0] - tP[0]) * (rP[1] - tP[1]) * m[0] + (-pow(rP[0] - tP[0], 0.2e1) + 0.2e1 * pow(rP[1] - tP[1], 0.2e1) - pow(rP[2] - tP[2], 0.2e1)) * m[1] + 0.3e1 * (rP[1] - tP[1]) * (rP[2] - tP[2]) * m[2]) / 0.4e1 - pow(sqrt(pow(rP[0] - tP[0], 0.2e1) + pow(rP[1] - tP[1], 0.2e1) + pow(rP[2] - tP[2], 0.2e1)) + PERTURBATION, -0.5e1) * M_1_PI * sin(angles[1]) * (0.3e1 * (rP[0] - tP[0]) * (rP[2] - tP[2]) * m[0] + 0.3e1 * (rP[1] - tP[1]) * (rP[2] - tP[2]) * m[1] + (-pow(rP[0] - tP[0], 0.2e1) - pow(rP[1] - tP[1], 0.2e1) + 0.2e1 * pow(rP[2] - tP[2], 0.2e1)) * m[2]) / 0.4e1;
    Hfield[1] = pow(sqrt(pow(rP[0] - tP[0], 0.2e1) + pow(rP[1] - tP[1], 0.2e1) + pow(rP[2] - tP[2], 0.2e1)) + PERTURBATION, -0.5e1) * M_1_PI * (-sin(angles[2]) * cos(angles[0]) + cos(angles[2]) * sin(angles[1]) * sin(angles[0])) * ((0.2e1 * pow(rP[0] - tP[0], 0.2e1) - pow(rP[1] - tP[1], 0.2e1) - pow(rP[2] - tP[2], 0.2e1)) * m[0] + 0.3e1 * (rP[0] - tP[0]) * (rP[1] - tP[1]) * m[1] + 0.3e1 * (rP[0] - tP[0]) * (rP[2] - tP[2]) * m[2]) / 0.4e1 + pow(sqrt(pow(rP[0] - tP[0], 0.2e1) + pow(rP[1] - tP[1], 0.2e1) + pow(rP[2] - tP[2], 0.2e1)) + PERTURBATION, -0.5e1) * M_1_PI * (cos(angles[2]) * cos(angles[0]) + sin(angles[2]) * sin(angles[1]) * sin(angles[0])) * (0.3e1 * (rP[0] - tP[0]) * (rP[1] - tP[1]) * m[0] + (-pow(rP[0] - tP[0], 0.2e1) + 0.2e1 * pow(rP[1] - tP[1], 0.2e1) - pow(rP[2] - tP[2], 0.2e1)) * m[1] + 0.3e1 * (rP[1] - tP[1]) * (rP[2] - tP[2]) * m[2]) / 0.4e1 + pow(sqrt(pow(rP[0] - tP[0], 0.2e1) + pow(rP[1] - tP[1], 0.2e1) + pow(rP[2] - tP[2], 0.2e1)) + PERTURBATION, -0.5e1) * M_1_PI * cos(angles[1]) * sin(angles[0]) * (0.3e1 * (rP[0] - tP[0]) * (rP[2] - tP[2]) * m[0] + 0.3e1 * (rP[1] - tP[1]) * (rP[2] - tP[2]) * m[1] + (-pow(rP[0] - tP[0], 0.2e1) - pow(rP[1] - tP[1], 0.2e1) + 0.2e1 * pow(rP[2] - tP[2], 0.2e1)) * m[2]) / 0.4e1;
    Hfield[2] = pow(sqrt(pow(rP[0] - tP[0], 0.2e1) + pow(rP[1] - tP[1], 0.2e1) + pow(rP[2] - tP[2], 0.2e1)) + PERTURBATION, -0.5e1) * M_1_PI * (sin(angles[2]) * sin(angles[0]) + cos(angles[2]) * sin(angles[1]) * cos(angles[0])) * ((0.2e1 * pow(rP[0] - tP[0], 0.2e1) - pow(rP[1] - tP[1], 0.2e1) - pow(rP[2] - tP[2], 0.2e1)) * m[0] + 0.3e1 * (rP[0] - tP[0]) * (rP[1] - tP[1]) * m[1] + 0.3e1 * (rP[0] - tP[0]) * (rP[2] - tP[2]) * m[2]) / 0.4e1 + pow(sqrt(pow(rP[0] - tP[0], 0.2e1) + pow(rP[1] - tP[1], 0.2e1) + pow(rP[2] - tP[2], 0.2e1)) + PERTURBATION, -0.5e1) * M_1_PI * (-cos(angles[2]) * sin(angles[0]) + sin(angles[2]) * sin(angles[1]) * cos(angles[0])) * (0.3e1 * (rP[0] - tP[0]) * (rP[1] - tP[1]) * m[0] + (-pow(rP[0] - tP[0], 0.2e1) + 0.2e1 * pow(rP[1] - tP[1], 0.2e1) - pow(rP[2] - tP[2], 0.2e1)) * m[1] + 0.3e1 * (rP[1] - tP[1]) * (rP[2] - tP[2]) * m[2]) / 0.4e1 + pow(sqrt(pow(rP[0] - tP[0], 0.2e1) + pow(rP[1] - tP[1], 0.2e1) + pow(rP[2] - tP[2], 0.2e1)) + PERTURBATION, -0.5e1) * M_1_PI * cos(angles[1]) * cos(angles[0]) * (0.3e1 * (rP[0] - tP[0]) * (rP[2] - tP[2]) * m[0] + 0.3e1 * (rP[1] - tP[1]) * (rP[2] - tP[2]) * m[1] + (-pow(rP[0] - tP[0], 0.2e1) - pow(rP[1] - tP[1], 0.2e1) + 0.2e1 * pow(rP[2] - tP[2], 0.2e1)) * m[2]) / 0.4e1;
    
}

/* mexFunction - Entry point for Matlab */
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
  
  /* 
   * nhls - number of elements as output mxArrays
   * plhs - pointer to output elements mxArrays
   * nrhs - number of input elements mxArrays
   * prhs - pointer to output elements mxArrays
   */
    
   
    
    
  double *tP,*m,*rP, *angles, *Hfield;
  
  
  /* Check for proper number of arguments. */
  if(nrhs!=4) {
    mexErrMsgIdAndTxt( "MATLAB:H_receiver:invalidNumInputs",
            "4 inputs required: (tPos, mV, rPos, rAngle)");
  } else if(nlhs>1) {
    mexErrMsgIdAndTxt( "MATLAB:H_receiver:invalidNumOutputs",
            "Too many output arguments.");
  }
  
  /* Create matrix for the return argument Hfield */
  plhs[0] = mxCreateDoubleMatrix((mwSize)3, (mwSize)1, mxREAL);
  
  /* Assign pointers to each input and output. */
  tP     = mxGetPr(prhs[0]);
  m      = mxGetPr(prhs[1]);
  rP     = mxGetPr(prhs[2]);
  angles = mxGetPr(prhs[3]);
  Hfield = mxGetPr(plhs[0]);
  
  /* Call the timestwo subroutine. */
  H_receiver(Hfield, tP, m, rP, angles);
}
