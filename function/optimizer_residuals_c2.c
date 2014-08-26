#include "mex.h"
#include "math.h"
#include <stdlib.h>

#define PERTURBAZIONE 0.1e-20

#ifdef __DEBUG
    #define DEB(m)   mexPrintf("[debug] line :: %d \n",m);  
#else
    #define DEB(m)   ;
#endif

void eval_H(double HField[], double rT[], double m[], double rR[]) {

    double x, y, z, r;
    
    x = rR[0] - rT[0]; 
    y = rR[1] - rT[1]; 
    z = rR[2] - rT[2]; 
    r = sqrt(x * x + y * y + z * z + PERTURBAZIONE); ;
    HField[0] = 0.250e0 * M_1_PI * pow(r, -0.5e1) * (-0.1e1 * r * r + 0.3e1 * x * x) * m[0] + 0.750e0 * M_1_PI * pow(r, -0.5e1) * x * y * m[1] + 0.750e0 * M_1_PI * pow(r, -0.5e1) * x * z * m[2]; 
    HField[1] = 0.750e0 * M_1_PI * pow(r, -0.5e1) * x * y * m[0] + 0.250e0 * M_1_PI * pow(r, -0.5e1) * (-0.1e1 * r * r + 0.3e1 * y * y) * m[1] + 0.750e0 * M_1_PI * pow(r, -0.5e1) * y * z * m[2]; 
    HField[2] = 0.750e0 * M_1_PI * pow(r, -0.5e1) * x * z * m[0] + 0.750e0 * M_1_PI * pow(r, -0.5e1) * y * z * m[1] + 0.250e0 * M_1_PI * pow(r, -0.5e1) * (-0.1e1 * r * r + 0.3e1 * z * z) * m[2];
    
    
}

void optimize_residuals(double residuals[], double rt[], double m[], double rr[], double H_meas[], int MEMORY) {
    
    
    /* Allocation of memory */
    double *Hfield;
    Hfield = (double*)malloc(3*MEMORY*sizeof(double));

    int i = 0;
    for (i = 0; i < MEMORY; i++) {
      eval_H(&Hfield[3*i], rt, m, &rr[3*i]);  
    }
    
    i = 0;
    for (i = 0; i < 3*MEMORY; i++) {
      residuals[i] = pow((Hfield[i] - H_meas[i]),0.2e1);
    }
    
    /* Residuals evaluation */
    /*residuals[0] = pow((Hfield[0] - H_meas[0]), 0.2e1);
    residuals[1] = pow((Hfield[1] - H_meas[1]), 0.2e1);
    residuals[2] = pow((Hfield[2] - H_meas[2]), 0.2e1);*/
    
    free(Hfield);
    
}

#ifdef __DEBUG
void print_dimensions(const mxArray* input, const char* name) {
    size_t inp_rows, inp_cols;
    inp_rows = mxGetM(input);
    inp_cols = mxGetN(input);
    
    mexPrintf("Input: %s, dimensions %d x %d\n", name, inp_rows, inp_cols);
}
#endif


void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
    
  double *x, *rr, *m, *rt, *H_meas, *residuals;
  size_t MEMORY;
  
    /* Check for proper number of arguments. */
  if(nrhs!=3) {
    mexErrMsgIdAndTxt( "MATLAB:optimizer_residuals_c2:invalidNumInputs",
            "3 inputs required: (X, rr, H_meas)");
  } else if(nlhs>1) {
    mexErrMsgIdAndTxt( "MATLAB:optimizer_residuals_c2:invalidNumOutputs",
            "Too many output arguments.");
  }
  
  /* Assign pointers to each input and output. */
  x      = mxGetPr(prhs[0]);
  rr     = mxGetPr(prhs[1]);
  H_meas = mxGetPr(prhs[2]);
  MEMORY = mxGetN(prhs[1]);
  
  #ifdef __DEBUG
    mexPrintf("DEBUG INFORMATION :: optimizer_residuals_c2\n");
    print_dimensions(prhs[0],"x");
    print_dimensions(prhs[1],"rr");
    print_dimensions(prhs[2],"H_meas");
    mexPrintf("MEMORY :: %d\n",MEMORY);
  #endif
  
  /* Create matrix for the return argument Hfield */
  plhs[0] = mxCreateDoubleMatrix((mwSize)(3*MEMORY), (mwSize)1, mxREAL);
    
  residuals = mxGetPr(plhs[0]);
    
  rt = (double*)malloc(3*MEMORY*sizeof(double));
  m = (double*)malloc(3*MEMORY*sizeof(double));
  
  int i = 0;
  for(i = 0; i < 3; i++) {
    rt[i] = x[i];
    m[i] = x[3+i];
  }

    
  /* Call the optimizer subroutine. */
  
  optimize_residuals(residuals, rt, m, rr, H_meas, MEMORY);
  
  free(rt);
  free(m);
}
