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
#include <math.h>
#include "mex.h"

using namespace std;

extern void _main();

class MyData {

	public:
	  void display();
	  void set_data(double v1, double v2);
	  MyData(int handle=-1, double v1 = 0, double v2 = 0);
	  ~MyData() {}
	private:
	  int handle;
	  double val1, val2;
};

MyData::MyData(int h, double v1, double v2)
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

void MyData::set_data(double v1, double v2) { val1 = v1; val2 = v2; }


static void create_object( int handle, double num1, double num2)
{
	MyData * pMyData=(MyData *)mxMalloc(sizeof(MyData));
	MyData *d = new (pMyData) MyData(handle); // Create a  MyData object

	d->set_data(num1,num2); // Set data members to incoming  values
	d->display();           // Make sure the set_data() worked

	mxFree(pMyData);
	flush(cout);
	return;
}

void mexFunction(
		 int          nlhs,
		 mxArray      *[],
		 int          nrhs,
		 const mxArray *prhs[]
		 )
{
	int handle;
	double      *vin1, *vin2;

	/* Check for proper number of arguments */
	if (nrhs != 3) {
		mexErrMsgIdAndTxt("MATLAB:mexcpp:nargin", "MEXCPP requires two input arguments.");
	} else if (nlhs >= 1) {
		mexErrMsgIdAndTxt("MATLAB:mexcpp:nargout", "MEXCPP requires no output argument.");
	}

	handle = mxGetScalar(prhs[0]);
	vin1 = (double *) mxGetPr(prhs[1]);
	vin2 = (double *) mxGetPr(prhs[2]);

	create_object(handle, *vin1, *vin2);
	return;
}
