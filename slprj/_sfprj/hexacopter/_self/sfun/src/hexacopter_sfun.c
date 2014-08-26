/* Include files */

#include "hexacopter_sfun.h"
#include "hexacopter_sfun_debug_macros.h"
#include "c2_hexacopter.h"
#include "c4_hexacopter.h"
#include "c5_hexacopter.h"
#include "c6_hexacopter.h"
#include "c7_hexacopter.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _hexacopterMachineNumber_;

/* Function Declarations */

/* Function Definitions */
void hexacopter_initializer(void)
{
}

void hexacopter_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_hexacopter_method_dispatcher(SimStruct *simstructPtr, unsigned
  int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==2) {
    c2_hexacopter_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==4) {
    c4_hexacopter_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_hexacopter_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_hexacopter_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==7) {
    c7_hexacopter_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_hexacopter_process_check_sum_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(973671587U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4230242475U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2155721743U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4169002366U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(705404295U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2095585383U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(26680082U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2092693423U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 2:
        {
          extern void sf_c2_hexacopter_get_check_sum(mxArray *plhs[]);
          sf_c2_hexacopter_get_check_sum(plhs);
          break;
        }

       case 4:
        {
          extern void sf_c4_hexacopter_get_check_sum(mxArray *plhs[]);
          sf_c4_hexacopter_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_hexacopter_get_check_sum(mxArray *plhs[]);
          sf_c5_hexacopter_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_hexacopter_get_check_sum(mxArray *plhs[]);
          sf_c6_hexacopter_get_check_sum(plhs);
          break;
        }

       case 7:
        {
          extern void sf_c7_hexacopter_get_check_sum(mxArray *plhs[]);
          sf_c7_hexacopter_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2083502392U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1110276785U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3258378658U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3926592909U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2301022654U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(926384027U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2066203469U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2546976957U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_hexacopter_autoinheritance_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(aiChksum, "IQzNPkVThnimm3bwWqVzwE") == 0) {
          extern mxArray *sf_c2_hexacopter_get_autoinheritance_info(void);
          plhs[0] = sf_c2_hexacopter_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 4:
      {
        if (strcmp(aiChksum, "3SzNvpxH6yB9SoDgMxILvC") == 0) {
          extern mxArray *sf_c4_hexacopter_get_autoinheritance_info(void);
          plhs[0] = sf_c4_hexacopter_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "OnJZXFio7OsNmudanMVT7") == 0) {
          extern mxArray *sf_c5_hexacopter_get_autoinheritance_info(void);
          plhs[0] = sf_c5_hexacopter_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 6:
      {
        if (strcmp(aiChksum, "VPpirRPaJobkGazvXCFnEB") == 0) {
          extern mxArray *sf_c6_hexacopter_get_autoinheritance_info(void);
          plhs[0] = sf_c6_hexacopter_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 7:
      {
        if (strcmp(aiChksum, "SDOwiPgmZCjGK45TVfIrRB") == 0) {
          extern mxArray *sf_c7_hexacopter_get_autoinheritance_info(void);
          plhs[0] = sf_c7_hexacopter_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_hexacopter_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        extern const mxArray *sf_c2_hexacopter_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_hexacopter_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 4:
      {
        extern const mxArray *sf_c4_hexacopter_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c4_hexacopter_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray *sf_c5_hexacopter_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_hexacopter_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray *sf_c6_hexacopter_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_hexacopter_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 7:
      {
        extern const mxArray *sf_c7_hexacopter_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c7_hexacopter_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_hexacopter_third_party_uses_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the third_party_uses_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_third_party_uses_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(tpChksum, "L4eKtY4R8goqwLCtFl1YIB") == 0) {
          extern mxArray *sf_c2_hexacopter_third_party_uses_info(void);
          plhs[0] = sf_c2_hexacopter_third_party_uses_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "iIMOg8yeTcCo3E7hfe7R3") == 0) {
          extern mxArray *sf_c4_hexacopter_third_party_uses_info(void);
          plhs[0] = sf_c4_hexacopter_third_party_uses_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "ssbDcwceJR28RzZ08fGQRG") == 0) {
          extern mxArray *sf_c5_hexacopter_third_party_uses_info(void);
          plhs[0] = sf_c5_hexacopter_third_party_uses_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "pktUXJT0dUq0bB0DN3b3zC") == 0) {
          extern mxArray *sf_c6_hexacopter_third_party_uses_info(void);
          plhs[0] = sf_c6_hexacopter_third_party_uses_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "nyYUqSqzfUC61H7ygiZynE") == 0) {
          extern mxArray *sf_c7_hexacopter_third_party_uses_info(void);
          plhs[0] = sf_c7_hexacopter_third_party_uses_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

unsigned int sf_hexacopter_updateBuildInfo_args_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{
  char commandName[64];
  char tpChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the updateBuildInfo_args_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  mxGetString(prhs[2], tpChksum,sizeof(tpChksum)/sizeof(char));
  tpChksum[(sizeof(tpChksum)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_updateBuildInfo_args_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 2:
      {
        if (strcmp(tpChksum, "L4eKtY4R8goqwLCtFl1YIB") == 0) {
          extern mxArray *sf_c2_hexacopter_updateBuildInfo_args_info(void);
          plhs[0] = sf_c2_hexacopter_updateBuildInfo_args_info();
          break;
        }
      }

     case 4:
      {
        if (strcmp(tpChksum, "iIMOg8yeTcCo3E7hfe7R3") == 0) {
          extern mxArray *sf_c4_hexacopter_updateBuildInfo_args_info(void);
          plhs[0] = sf_c4_hexacopter_updateBuildInfo_args_info();
          break;
        }
      }

     case 5:
      {
        if (strcmp(tpChksum, "ssbDcwceJR28RzZ08fGQRG") == 0) {
          extern mxArray *sf_c5_hexacopter_updateBuildInfo_args_info(void);
          plhs[0] = sf_c5_hexacopter_updateBuildInfo_args_info();
          break;
        }
      }

     case 6:
      {
        if (strcmp(tpChksum, "pktUXJT0dUq0bB0DN3b3zC") == 0) {
          extern mxArray *sf_c6_hexacopter_updateBuildInfo_args_info(void);
          plhs[0] = sf_c6_hexacopter_updateBuildInfo_args_info();
          break;
        }
      }

     case 7:
      {
        if (strcmp(tpChksum, "nyYUqSqzfUC61H7ygiZynE") == 0) {
          extern mxArray *sf_c7_hexacopter_updateBuildInfo_args_info(void);
          plhs[0] = sf_c7_hexacopter_updateBuildInfo_args_info();
          break;
        }
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;
}

void hexacopter_debug_initialize(struct SfDebugInstanceStruct* debugInstance)
{
  _hexacopterMachineNumber_ = sf_debug_initialize_machine(debugInstance,
    "hexacopter","sfun",0,5,0,0,0);
  sf_debug_set_machine_event_thresholds(debugInstance,_hexacopterMachineNumber_,
    0,0);
  sf_debug_set_machine_data_thresholds(debugInstance,_hexacopterMachineNumber_,0);
}

void hexacopter_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_hexacopter_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info("hexacopter",
      "hexacopter");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_hexacopter_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
