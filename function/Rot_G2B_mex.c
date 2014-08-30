#include "mex.h"
#include "math.h"

/*
 *  rotation_matrix.c - returns a 3d rotation matrix given 3 angles
 *  Inputs: 
 *  - angles : orientation
 *  Outputs:
 *  - rot : ground 2 body rotation matrix
 */

void rotation_matrix( double *rot, double* angles){
    rot[0] = cos(angles[2]) * cos(angles[1]);
    rot[1] = -sin(angles[2]) * cos(angles[0]) + cos(angles[2]) * sin(angles[1]) * sin(angles[0]);
    rot[2] = sin(angles[2]) * sin(angles[0]) + cos(angles[2]) * sin(angles[1]) * cos(angles[0]);
    rot[3] = sin(angles[2]) * cos(angles[1]);
    rot[4] = cos(angles[2]) * cos(angles[0]) + sin(angles[2]) * sin(angles[1]) * sin(angles[0]);
    rot[5] = -cos(angles[2]) * sin(angles[0]) + sin(angles[2]) * sin(angles[1]) * cos(angles[0]);
    rot[6] = -sin(angles[1]);
    rot[7] = cos(angles[1]) * sin(angles[0]);
    rot[8] = cos(angles[1]) * cos(angles[0]);
}

/* mexFunction - Entry point for Matlab */
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
    
  double *rot, *angles; 
  /* Check for proper number of arguments. */
  if(nrhs!=1) {
    mexErrMsgIdAndTxt( "MATLAB:rotation_matrix:invalidNumInputs",
            "1 input required! (angles)");
  } else if(nlhs>1) {
    mexErrMsgIdAndTxt( "MATLAB:rotation_matrix:invalidNumOutputs",
            "Too many output arguments.");
  }
  
  /* Assign memory for result */
  plhs[0] = mxCreateDoubleMatrix((mwSize)3, (mwSize)3, mxREAL);
  
  /* Assign pointers to each input and output. */
  angles = mxGetPr(prhs[0]);
  rot    = mxGetPr(plhs[0]);
  
  /* Call the timestwo subroutine. */
  rotation_matrix(rot, angles);
}
