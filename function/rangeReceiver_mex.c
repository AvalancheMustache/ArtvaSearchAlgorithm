#include "mex.h"
#include <math.h>

#ifndef M_PI
	#define M_PI    3.141592653589793
#endif

#if __DEBUG == 2
	#define __DEBUG_2
#elif __DEBUG == 1
	#define __DEBUG_1
#elif __DEBUG == 3
	#define __DEBUG_1
	#define __DEBUG_2
#endif

void minimum(double *out, const double *in, const size_t dim) {
	int i;
	out[0] = in[0];
	#ifdef __DEBUG_2
		mexPrintf("%4f = %4f\n",in[0],out[0]);
	#endif
	for (i=1; i<dim; i++) {
		#ifdef __DEBUG_2
			mexPrintf("%4f > %4f",in[i],out[0]);
		#endif
		if ( out[0] >= in[i] ) { 
			out[0] = in[i]; 
			#ifdef __DEBUG_2
				mexPrintf(" NO ");
			#endif
		}
		#ifdef __DEBUG_2
			mexPrintf("\n");
		#endif
	}
	#ifdef __DEBUG_2
		mexPrintf("MIN = %4f\n",out[0]);
	#endif
}

/* Returns out = R * in */
void project(double *out, const double *in, const double *R) {
    int i = 0;
    for (i=0; i<3; i++) {
        out[i] = R[0+i*3]*in[0] + R[1+i*3]*in[1] +R[2+i*3]*in[2];   
    }
    #ifdef __DEBUG_2
        mexPrintf("[ %4f %4f %4f ] \n[ %4f %4f %4f ]  [ %4f %4f %4f ] -> [ %4f %4f %4f ]\n[ %4f %4f %4f ] \n", R[0],R[1],R[2],R[3],R[4],R[5],in[0],in[1],in[2],out[0],out[1],out[2],R[6],R[7],R[8]);
    #endif
}

/* Returns out = ux * in_1 + uy * in_2 + 0*in_3 */
void dotProductXY(double *out, const double *in, const double *ux, const double *uy) {
    out[0] = in[0]*ux[0] + in[1]*uy[0];
    #ifdef __DEBUG_1
    	mexPrintf(" < [ %4f %4f %4f] , [ %4f %4f 0 ] > = %4f\n", in[0], in[1], in[2], ux[0], uy[0], out[0]);
    #endif
}

/* Returns out = <in,in^T> */
void absolute2(double *out, const double*in) {
	out[0] = in[0]*in[0] + in[1]*in[1] + in[2]*in[2]; 
    #ifdef __DEBUG_2
        mexPrintf("|[ %4f %4f %4f ]|^2 = %4f\n", in[0], in[1], in[2], out[0]);
    #endif
}

/* Returns out = v - w */
void difference(double *out, const double *v, const double *w) {
	int i;
	for (i=0; i<3; i++) out[i] = v[i] - w[i];
	#ifdef __DEBUG_2
    	mexPrintf("[ %4f %4f %4f ] - [ %4f %4f %4f ] = [ %4f %4f %4f ]\n", v[0], v[1], v[2], w[0], w[1], w[2], out[0], out[1], out[2]);
    #endif
}

/* Select every DELTA elements in a vector of SIZE*DELTA elements, with INIT as bias */
void select(double *out, const double *in, const size_t SIZE, const size_t DELTA, const size_t INIT) {
	int i;
	#ifdef __DEBUG_2
    	mexPrintf("Select\n");
    #endif
	if (INIT < DELTA) {
		for (i=0;i<SIZE;i++){
			out[i] = in[DELTA*i+INIT];
			#ifdef __DEBUG_2
    			mexPrintf("%4f\n",out[i]);
    		#endif
		}
	}	
}

/*  = Obbiettivi dell'algoritmo:
 *
 *	Per ogni punto (3 coordinate) dell'ostacolo
 *		calcola la distanza tra punto e sensore
 * 		ruota il vettore nella terna del drone
 *		Per ogni sensore
 *			esegui il prodotto scalare tra vettore distanza e versore
 *			calcola il modulo quadro del vettore distanza
 *			se tale prodotto é maggiore di zero e minore di h
 *				se il modulo quadro del vettore distanza meno la proiezione lungo l'asse é minore del raggio locale
 *					distanza rilevata dal sensore = distanza proiettata sulll'asse
 *				altrimenti
 *					distanza rilevata dal sensore = infinito
 *			altrimenti
 *				distanza rilevata dal sensore
 *	
 *	per ogni sensore
 *		per ogni punto
 *			calcola la distanza minima rilevata
 *
 * Ipotesi di sviluppo: scrivo codice non molto ottimizzato: ci penserá poi il 
 * compilatore a sistemarlo con le routine di ottimizzazione
 */

void rangeFinder(double *out, const double *points, const double *origin, const double *R, const double *parameters, const size_t NPOINTS) {

	#define H parameters[0]
	#define RHO parameters[1]
	#define MIN parameters[2]

	/*
	 * ux : componente x versore sensore
	 * uy : componente y versone sensore
	 * u  : distanza lungo l'asse del punto
	 */
	double ux[6], uy[6], *dist, inf;
	int i;
	inf = mxGetInf();
	dist = (double*)calloc(6*NPOINTS,sizeof(double));

	/* definizione dei versori */
	for (i=0; i<6; i++) { 
		ux[i] = cos(i*M_PI/3); 
		uy[i] = -sin(i*M_PI/3); 
	}

	for (i=0; i<NPOINTS; i++) {

		/* 
		 * p_world : distanza tra punto ostacolo e ricevitore nel sistema di riferimento globale
		 * p : distanza tra punto di riferimento e ricevitore nel sistema di riferimento body
		 * pu : proiezione lungo l'asse
		 * pv2 : proiezione perpendicolare all'asse al quadrato
		 */
		double p_world[3], p[3], pu[6], pv2[6], pabs;
		int j;

		difference(p_world,&points[3*i],origin);
		project(p,p_world,R);
		absolute2(&pabs, p);

		#ifdef __DEBUG_1
    		mexPrintf("\nPOINT %d -- P = [ %4f %4f %4f ]\n",i,p[0],p[1],p[2]);
    	#endif
	
		for (j=0; j<6; j++) {
			dotProductXY(&pu[j], p, &ux[j], &uy[j]);
			pv2[j] = pabs - (pu[j]*pu[j]);

			if (pu[j] > MIN && pu[j] <= H) {
				if ( pv2[j] <= pow((RHO * ((H - pu[j])/H)),2)) {
					dist[6*i+j] = pu[j];
				} else {
					dist[6*i+j] = inf;
				}
			} else {
				dist[6*i+j] = inf;
			}
			#ifdef __DEBUG_1
    			mexPrintf("  SENSOR %d -- PU = [ %4f ], PV^2 = [ %4f ]\n",j,pu[0],pv2[1]);
    		#endif
		}
	}

	for (i=0; i<6; i++) {
		double *dd;
		dd = (double*)calloc(1*NPOINTS,sizeof(double));
		#ifdef __DEBUG_1
			mexPrintf("\nSENSOR %d\n",i);
		#endif
		select(dd, dist, NPOINTS, 6, i);
		minimum(&out[i],dd,NPOINTS);
		#ifdef __DEBUG_1
			mexPrintf(" dist = %4f\n",out[i]);
		#endif
		free(dd);
	}
	free(dist);

}

/* mexFunction - Entry point for Matlab */
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] ) {
    
  double *x_obst, *x_drone, *R_G2B, *parameter, *dist_out;
  size_t N;
  /* Check for proper number of arguments. */
  if(nrhs!=4) {
    mexErrMsgIdAndTxt( "MATLAB:rotation_matrix:invalidNumInputs",
            "4 input required! (x_obst, x_drone, R_G2B, parameter)");
  } else if(nlhs>1) {
    mexErrMsgIdAndTxt( "MATLAB:rotation_matrix:invalidNumOutputs",
            "Too many output arguments.");
  }
  
  /* Assign memory for result */
  plhs[0] = mxCreateDoubleMatrix((mwSize)6, (mwSize)1, mxREAL);
  
  /* Assign pointers to each input and output. */
  x_obst = mxGetPr(prhs[0]);
  x_drone = mxGetPr(prhs[1]);
  R_G2B = mxGetPr(prhs[2]);
  parameter = mxGetPr(prhs[3]);
  dist_out = mxGetPr(plhs[0]);
  N = mxGetN(prhs[0]);
  
  #ifdef __DEBUG_2
    mexPrintf("Size of x_obst: %d\n",N);
  #endif
  /* Call the subroutine. */
  rangeFinder(dist_out, x_obst, x_drone, R_G2B, parameter, N);
}
