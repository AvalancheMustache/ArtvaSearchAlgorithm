#include "mex.h"
#include "math.h"

#define M_1_SQRT_2_PI  0.39894228040143270286e0  

#ifdef __DEBUG
    #define DEBf(s_,f_)   mexPrintf("%s = %f\n",s_,f_);
    #define DEBi(s_,i_)   mexPrintf("%s = %d\n",s_,i_);
#else
    #define DEBf(s_,f_)   ;
    #define DEBi(s_,i_)   ;
#endif

double GaussianKernel(double* x, double* mu, double* sigma) {
    DEBf("x",x[0]);
    DEBf("mu",mu[0]);
    DEBf("sigma",sigma[0]);
    return M_1_SQRT_2_PI*(1/sigma[0])*exp((-0.5)*pow((x[0]-mu[0])/sigma[0],0.2e1));
}

void ParzenWindow(double *result,double *x, double *mu, double *sigma, size_t MEMORY) {
    double ret = 0.0;
    int i = 0;
    
    for ( i = 0; i < MEMORY; i++ ) {
       DEBi("i",i);
       ret += GaussianKernel(x,&mu[i],sigma);    
    }
    
    result[0] = (double)1/MEMORY * ret;
}

/* mexFunction - Entry point for Matlab */
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
  
  double *x, *mu, *sigma, *result;
  size_t MEMORY;
  
  /* Check for proper number of arguments. */
  if(nrhs!=3) {
    mexErrMsgIdAndTxt( "MATLAB:ParzenWindowEstimator:invalidNumInputs",
            "3 inputs required: (x,mu,sigma)");
  } else if(nlhs>1) {
    mexErrMsgIdAndTxt( "MATLAB:H_receiver:invalidNumOutputs",
            "Too many output arguments.");
  }
  
  /* Create matrix for the return argument Hfield */
  plhs[0] = mxCreateDoubleMatrix((mwSize)1, (mwSize)1, mxREAL);
  
  /* Assign pointers to each input and output. */
  x = mxGetPr(prhs[0]);
  mu = mxGetPr(prhs[1]);
  sigma = mxGetPr(prhs[2]);
  result = mxGetPr(plhs[0]);
  
  MEMORY = mxGetM(prhs[1]);
  
  /* Call the timestwo subroutine. */
  ParzenWindow(result, x, mu , sigma, MEMORY); 
}
