#include "mex.h"
#include "SimpleMedian.h"
#include <omp.h>

void applyParallelMedianFilter(double* output, int rows, int cols, double* input, int scope, int lenBuffer){	
	#pragma omp parallel
	{
		int inBuffer = 0, focusK = 0, focusM = 0, i = 0, j = 0;
		double* buffer = malloc(sizeof(double)*lenBuffer);//WARNING: mxMalloc is NOT THREAD-SAFE
		// Never call any of the mex api functions inside the portion of your code that you are trying to parallelise using openmp.  
		// Don’t try to interact with MATLAB at all during the parallel portion of your code. See: https://walkingrandomly.com/?p=1795
		#pragma omp for
		for(int index = 0; index<(cols*rows); index++){	
			i = index % cols; // COLS
			j = index / cols; // ROWS
			inBuffer = 0;
			for(int k = i-scope; k<=(i+scope); k++){//Applying the 2D-window
				focusK = k;
				if(k<0){
					focusK = 0;
				}else if (k>=cols){
					focusK = (cols-1);
				}
				for(int m = j-scope; m<=(j+scope); m++){
					focusM = m;
					if(m<0){
						focusM = 0;
					}else if(m>=rows){
						focusM = (rows-1);
					}
					buffer[inBuffer] = input[focusK*rows + focusM];//Matlab uses column-major order
					inBuffer++;
				}
			}
			output[i*rows + j] = median(buffer, lenBuffer);
		}
		free(buffer);
	}
}

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
	if(nlhs!=1 || nrhs!=2) {/*Ouput: 1; Input: 2*/
    		mexErrMsgTxt("Usage: out_Matrix = PPolishMatrix(real_matrix, integer_scope)"); 
  	}/*EXITING by mexErrMsgTxt*/
	
	/*Get the size of the input matrix:*/
	int rows = mxGetM(prhs[0]);
	int cols = mxGetN(prhs[0]);
	
	int scope = (int) mxGetScalar(prhs[1]);/*The offset in pixels from the center, i.e., a scope=1 means a 3x3 window (2+1)^2*/
	int lenBuffer = (2*scope + 1)*(2*scope + 1);

	double *input = 0, *output = 0;/*Pointers to the data in the input, buffer and output matrices*/

	if(rows>0 && cols>0 && scope>0 && lenBuffer<(rows*cols)){
		plhs[0] = mxCreateDoubleMatrix(rows, cols, mxREAL);/*Getting room for the output*/
		output = mxGetPr(plhs[0]);
		input = mxGetPr(prhs[0]);		
		if (input && output){
			applyParallelMedianFilter(output, rows, cols, input, scope, lenBuffer);
		}else{
			mexErrMsgTxt("Memory allocation failed");/*EXITING by mexErrMsgTxt. If your application called mxCreate* routines to allocate memory, mexErrMsgIdAndTxt automatically frees the allocated memory.*/
		}	
	}else{
		mexErrMsgTxt("The input matrix must be of size MxN with M>0 and N>0. The scope S must be S>0 with (2*S+1)^2 <MxN");
	}/*EXITING by mexErrMsgTxt*/
}

