/*==========================================================
 * mexdyn.cpp - example in MATLAB External Interfaces
 *              and using dynamic objects
 *
 * Illustrates how to use some C++ language features in a MEX-file.
 * It makes use of member functions, constructors, destructors, and the
 * iostream.
 *
 * The calling syntax is:
 *
 *		mexdyn( call_type, <no_of_objects> )
 *
 * Run the program with "matlab -nojvm -r testmex
 *
 *========================================================*/
// Created by Don Johnson <kodosaru@gmail.com> on Dec 22, 2013
// Modified and augmented original example supplied by Mathworks

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "mex.h"
#include "mexdyn.hpp"

using namespace std;

extern void _main();

MyData::MyData(int h, int v1, int v2)
{
	handle = h;
  	val1 = v1;
  	val2 = v2;
}

void MyData::display()
{
	#ifdef _WIN32
		mexPrintf("Handle = %g\n", handle);
		mexPrintf("Value1 = %g\n", val1);
		mexPrintf("Value2 = %g\n\n", val2);
	#else
	  cout << "Handle = " << handle << endl;
	  cout << "Value1 = " << val1 << endl;
	  cout << "Value2 = " << val2 << endl << endl;
	#endif
}

MyData **pMyData;
int nobject_count=0;

void clearArrayOfObjects(){
	if(pMyData != NULL) {
		for(int i=0;i<nobject_count;i++){
			if(pMyData[i] != NULL){
				mxFree(pMyData[i]);
	  			cout << "\rCleared object " << i << " in array" << flush;
				usleep(5000);
			}
		}
		mxFree(pMyData);
	  	cout << endl << "Cleared array" << endl;
	}
}

void mexFunction(
		 int          nlhs,
		 mxArray      *[],
		 int          nrhs,
		 const mxArray *prhs[]
		 )
{
 	if (nlhs >= 1) {
		mexErrMsgIdAndTxt("MATLAB:mexdyn:nargout", "mexdyn requires no output argument.");
	}

	int call_type = mxGetScalar(prhs[0]);
	switch (call_type) {
		// Create the objects
		case 0: {
			if (nrhs != 2) {
				mexErrMsgIdAndTxt("MATLAB:mexdyn:nargin", "mexdyn requires the call \
					type and number objects to be created as an input arguments.");
			}
			int ndesired_count = mxGetScalar(prhs[1]);
			pMyData = (MyData **)mxMalloc(sizeof(MyData *) * ndesired_count);
			mexMakeMemoryPersistent(pMyData);
			for(int i=0;i<ndesired_count;i++){
				pMyData[i] = NULL;
			}
			for(int i=0;i<ndesired_count;i++){
				MyData *ptemp = (MyData *)mxMalloc(sizeof(MyData));
				mexMakeMemoryPersistent(ptemp);
				pMyData[i] = new (ptemp) MyData(i,rand(),rand()); // Create a  MyData object
				pMyData[i]->display();
				nobject_count++;
			}
			mexAtExit(clearArrayOfObjects);
			return;
		}

		// Destroy the objects
		case 1: {
			if (nrhs != 1) {
				mexErrMsgIdAndTxt("MATLAB:mexdyn:nargin", "mexdyn requires the call type as an input argument.");
			}
			cout << "First object" << endl;
			pMyData[0]->display();
			cout << endl;
			cout << "Last object" << endl;
			pMyData[nobject_count-1]->display();
			return;
		}
	}

	return;
}
