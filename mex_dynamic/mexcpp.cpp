/*==========================================================
 * mexcpp.cpp - example in MATLAB External Interfaces
 *
 * Illustrates how to use some C++ language features in a MEX-file.
 * It makes use of member functions, constructors, destructors, and the
 * iostream.
 *
 * The routine simply defines a class, constructs a simple object,
 * and displays the initial values of the internal variables.  It
 * then sets the data members of the object based on the input given
 * to the MEX-file and displays the changed values.
 *
 * This file uses the extension .cpp.  Other common C++ extensions such
 * as .C, .cc, and .cxx are also supported.
 *
 * The calling syntax is:
 *
 *		mexcpp( num1, num2 )
 *
 * Limitations:
 * On Windows, this example uses mexPrintf instead cout.  Iostreams 
 * (such as cout) are not supported with MATLAB with all C++ compilers.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2009 The MathWorks, Inc.
 *
 *========================================================*/
/* $Revision: 1.5.4.4 $ */

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "mex.h"

using namespace std;

extern void _main();

class MyData {

	public:
	  void display();
	  MyData(int handle=-1, int v1 = 0, int v2 = 0);
	  ~MyData() {}
	private:
	  int handle, val1, val2;
};

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
	  cout << "Handle = " << handle << "\n";
	  cout << "Value1 = " << val1 << "\n";
	  cout << "Value2 = " << val2 << "\n\n";
	#endif
}

MyData **pMyData;
int nobject_count=0;

void mexFunction(
		 int          nlhs,
		 mxArray      *[],
		 int          nrhs,
		 const mxArray *prhs[]
		 )
{
 	if (nlhs >= 1) {
		mexErrMsgIdAndTxt("MATLAB:mexcpp:nargout", "MEXCPP requires no output argument.");
	}

	int call_type = mxGetScalar(prhs[0]);
	switch (call_type) {
		// Create the objects
		case 0: {
			if (nrhs != 2) {
				mexErrMsgIdAndTxt("MATLAB:mexcpp:nargin", "MEXCPP requires the call \
					type and number objects to be created as an input arguments.");
			}
			int ndesired_count = mxGetScalar(prhs[1]);
			pMyData = (MyData **)mxMalloc(sizeof(MyData *) * ndesired_count);
			for(int i=0;i<ndesired_count;i++){
				MyData *ptemp = (MyData *)mxMalloc(sizeof(MyData));
				pMyData[i] = new (ptemp) MyData(i,rand(),rand()); // Create a  MyData object
				pMyData[i]->display();
				nobject_count++;
			}
			return;
		}

		// Destroy the objects
		case 1: {
			if (nrhs != 1) {
				mexErrMsgIdAndTxt("MATLAB:mexcpp:nargin", "MEXCPP requires the call type as an input argument.");
			}
			cout << "First object" << endl;
			pMyData[0]->display();
			cout << endl;
			cout << "Last object" << endl;
			pMyData[nobject_count-1]->display();
			mxFree(pMyData[0]);
			for(int i=0;i<nobject_count;i++){
				mxFree(pMyData[i]);
			}
			mxFree(pMyData);
			return;
		}
	}

	return;
}
