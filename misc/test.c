#include "mex.h"

void transport( double *out, double *in){
    int i = 0;
    for (i=0; i<9; i++){
      out[i] = in[i];
    }
}

/* mexFunction - Entry point for Matlab */
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
    
  double *out, *in; 
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
  in = mxGetPr(prhs[0]);
  out    = mxGetPr(plhs[0]);
  
  /* Call the timestwo subroutine. */
  transport(out, in);
}