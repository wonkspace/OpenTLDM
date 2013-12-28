// Copyright 2011 Zdenek Kalal
//
// This file is part of TLD.
// 
// TLD is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// TLD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with TLD.  If not, see <http://www.gnu.org/licenses/>.

#include "stdio.h"
#include "math.h"
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include "tld.h"
#include "mex.h" 

#ifdef _CHAR16T
	#define CHAR16_T
#endif
#define sub2idx(row,col,height) ((int) (floor((row)+0.5) + floor((col)+0.5)*(height)))
using namespace std;
vector<vector<double> > initw;
vector<vector<int> > initn;

double randdouble(); 


class ImageObject {
public:
  // Data
  int handle;
  double thrN;
  int nBBOX;
  int mBBOX;
  int nTREES;
  int nFEAT;
  int nSCALE;
  int iHEIGHT;
  int iWIDTH;
  int *BBOX;
  int *OFF;
  double *IIMG;
  double *IIMG2;
  vector<vector <double> > WEIGHT;
  vector<vector <int> > nP;
  vector<vector <int> > nN;
  int BBOX_STEP;
  int nBIT; // number of bits per feature
		
  // Methods	
  ImageObject(int handle);
  ~ImageObject();	
  void display();
  void update(double *x, int C, int N);
  double measure_forest(double *idx);
  int measure_tree_offset(unsigned char *img, int idx_bbox, int idx_tree);
  double measure_bbox_offset(unsigned char *blur, int idx_bbox, double minVar, double *tPatt);
  int* create_offsets(double *scale0, double *x0);
  int* create_offsets_bbox(double *bb0);

};

ImageObject::ImageObject(int h) { // Constructor 
	handle = h;
	thrN = 0.0;
	nBBOX = 0;
	mBBOX = 0;
	nTREES = 0;
	nFEAT = 0;
	nSCALE = 0;
	iHEIGHT = 0;
	iWIDTH = 0;
	BBOX = NULL;
	OFF = NULL;
	IIMG = NULL;
	IIMG2 = NULL;
	WEIGHT = initw;
	nP = initn;
	nN = initn;
	BBOX_STEP = 7;
	nBIT = 1;
}

ImageObject::~ImageObject(){}; // Destructor


void ImageObject::display()
{
	#ifdef _WIN32
		/* TODO */
	#else
		cout << "handle = " << handle << endl; 
		cout << "thrN = " << thrN << endl;
		cout << "nBBOX = " << nBBOX << endl;
		cout << "mBBOX = " << mBBOX << endl;
		cout << "nTREES = " << nTREES << endl;
		cout << "nFEAT = " << nFEAT << endl;
		cout << "nSCALE = " << nSCALE << endl;
		cout << "iHEIGHT = " << iHEIGHT << endl;
		cout << "iWIDTH = " << iWIDTH << endl;
		cout << "BBOX_STEP = " << BBOX_STEP << endl;
		cout << "nBIT = " << nBIT << endl << endl;

	#endif
}


void ImageObject::update(double *x, int C, int N) {
	for (int i = 0; i < nTREES; i++) {

		int idx = (int) x[i];

		(C==1) ? nP[i][idx] += N : nN[i][idx] += N;

		if (nP[i][idx]==0) {
			WEIGHT[i][idx] = 0;
		} else {
			WEIGHT[i][idx] = ((double) (nP[i][idx])) / (nP[i][idx] + nN[i][idx]);
		}
	}
}


double ImageObject::measure_forest(double *idx) {
	double votes = 0;
	for (int i = 0; i < nTREES; i++) { 
		votes += WEIGHT[i][idx[i]];
	}
	return votes;
}


int ImageObject::measure_tree_offset(unsigned char *img, int idx_bbox, int idx_tree) {

	int index = 0;
	int *bbox = BBOX + idx_bbox*BBOX_STEP;
	int *off = OFF + bbox[5] + idx_tree*2*nFEAT;
	for (int i=0; i<nFEAT; i++) {
		index<<=1; 
		int fp0 = img[off[0]+bbox[0]];
		int fp1 = img[off[1]+bbox[0]];
		if (fp0>fp1) { index |= 1;}
		off += 2;
	}
	return index;	
}


double ImageObject::measure_bbox_offset(unsigned char *blur, int idx_bbox, double minVar, double *tPatt) {

	double conf = 0.0;
	double bboxvar = bbox_var_offset(IIMG,IIMG2,BBOX+idx_bbox*BBOX_STEP);
	if (bboxvar < minVar) {	return conf; }

	for (int i = 0; i < nTREES; i++) { 
		int idx = measure_tree_offset(blur,idx_bbox,i);
		tPatt[i] = idx;
		conf += WEIGHT[i][idx];
	}
	return conf;
}

int* ImageObject::create_offsets(double *scale0, double *x0) {

	int *offsets = (int*) mxMalloc(nSCALE*nTREES*nFEAT*2*sizeof(int));
	int *off = offsets;

	for (int k = 0; k < nSCALE; k++){
		double *scale = scale0+2*k;
		for (int i = 0; i < nTREES; i++) {
			for (int j = 0; j < nFEAT; j++) {
				double *x  = x0 +4*j + (4*nFEAT)*i;
				*off++ = sub2idx((scale[0]-1)*x[1],(scale[1]-1)*x[0],iHEIGHT);
				*off++ = sub2idx((scale[0]-1)*x[3],(scale[1]-1)*x[2],iHEIGHT);
			}
		}
	}
	return offsets;
}

int* ImageObject::create_offsets_bbox(double *bb0) {

	int *offsets = (int*) mxMalloc(BBOX_STEP*nBBOX*sizeof(int));
	int *off = offsets;

	for (int i = 0; i < nBBOX; i++) {
		double *bb = bb0+mBBOX*i;
		*off++ = sub2idx(bb[1]-1,bb[0]-1,iHEIGHT);
		*off++ = sub2idx(bb[3]-1,bb[0]-1,iHEIGHT);
		*off++ = sub2idx(bb[1]-1,bb[2]-1,iHEIGHT);
		*off++ = sub2idx(bb[3]-1,bb[2]-1,iHEIGHT);
		*off++ = (int) ((bb[2]-bb[0])*(bb[3]-bb[1]));
		*off++ = (int) (bb[4]-1)*2*nFEAT*nTREES; // pointer to features for this scale
		*off++ = bb[5]; // number of left-right bboxes, will be used for searching neighbours
	}
	return offsets;
}


double randdouble() 
{ 
	return rand()/(double(RAND_MAX)+1); 
} 

ImageObject **pImageObject= NULL;
int nObjectTracked = 0;
double* id_;
int id = 0;

void clearArrayOfObjects(){
	if(pImageObject != NULL) {
		for(int i=0;i<nObjectTracked;i++){
			if(pImageObject[i] != NULL){
				if(pImageObject[i]->BBOX != NULL){
					mxFree(pImageObject[i]->BBOX);
				}
				else{
	  				cout << "\rBBOX pointer in object " << i << " is null!" << flush;
				};
				if(pImageObject[i]->OFF != NULL){
					mxFree(pImageObject[i]->OFF);
				}
				else{
	  				cout << "\rOFF pointer in object " << i << " is null!" << flush;
				};
				if(pImageObject[i]->IIMG != NULL){
					mxFree(pImageObject[i]->IIMG);
				}
				else{
	  				cout << "\rIIMG pointer in object " << i << " is null!" << flush;
				};
				if(pImageObject[i]->IIMG2 != NULL){
					mxFree(pImageObject[i]->IIMG2);
				}
				else{
	  				cout << "\rIIMG2 pointer in object " << i << " is null!" << flush;
				};
				mxFree(pImageObject[i]);
	  			cout << "\rCleared object " << i << " in array" << flush;
				usleep(5000);
			}
			else{
	  				cout << "\rImageObject pointer in object " << i << " is null!" << flush;
			};
		}
		mxFree(pImageObject);
	  	cout << endl << "Cleared array" << endl;
	}
	else{
		cout << "\rImageObject array pointer is null!" << flush;
	};
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	//mexPrintf("meeexxxxxxx\n");
	if (nrhs == 0) {
		//mexPrintf("CLEANUP: function(0);\n");
		//mexPrintf("INIT: function(1, img, bb, features, scales, id)\n");
		//mexPrintf("UPDATE: Conf = function(2,X,Y,Margin,Bootstrap,Idx,id)\n");
		//mexPrintf("EVALUATE: Conf = function(3,X)\n");
		//mexPrintf("DETECT: function(4,img,maxBBox,minVar,Conf,X)\n");
		//mexPrintf("GET PATTERNS: patterns = fern(5,img,idx,minVar)\n");
		return;
	}
    
    //int size = 4;
    //fieldstruct * fields = new fieldstruct[size];       // jorgeb - hardwired
    //fields = initialize_fields(fields, size);           // jorgeb - hardwired
    //initialize_fields(4);                                 // jorgeb - hardwired
    
 	switch ((int) *mxGetPr(prhs[0])) {

		// CLEANUP: function(0);
		// =============================================================================
	case 0:  {
		mexPrintf("in the CLEANUP!!!\n");
		id_ = mxGetPr(prhs[1]);
		id = (int)(*id_);

		// Get the number of image objects to be created and create an data structure to hold their attributes 
		nObjectTracked = mxGetScalar(prhs[2]);
		pImageObject = (ImageObject **)mxMalloc(sizeof(ImageObject *) * nObjectTracked);
		mexMakeMemoryPersistent(pImageObject);
		for(int i=0;i<nObjectTracked;i++){
			pImageObject[i] = NULL;
		}

		for (int i=0;i<nObjectTracked;i++){
			ImageObject * ptemp = (ImageObject *)mxMalloc(sizeof(ImageObject));
			mexMakeMemoryPersistent(ptemp);
			pImageObject[i] = new (ptemp) ImageObject(i);
		}
		mexAtExit(clearArrayOfObjects);

		srand(0); // fix state of random generator
		pImageObject[id]->thrN = 0; pImageObject[id]->nBBOX = 0; pImageObject[id]->mBBOX = 0; pImageObject[id]->nTREES = 0; pImageObject[id]->nFEAT = 0; pImageObject[id]->nSCALE = 0; pImageObject[id]->iHEIGHT = 0; pImageObject[id]->iWIDTH = 0;
		//mexPrintf("--------in mex cleanup function!!!!!\n");
		mxFree(pImageObject[id]->BBOX); pImageObject[id]->BBOX = NULL;
		mxFree(pImageObject[id]->OFF); pImageObject[id]->OFF = NULL;
		mxFree(pImageObject[id]->IIMG); pImageObject[id]->IIMG = NULL;
		mxFree(pImageObject[id]->IIMG2); pImageObject[id]->IIMG2 = NULL;
		pImageObject[id]->WEIGHT.clear();
		pImageObject[id]->nP.clear();
		pImageObject[id]->nN.clear();

		//free(fields);
		//mexPrintf("heeeeeeeere23232\n");
	/*	if(id == 0)
			fern1 = *tmp;
		else
			fern2 = *tmp;*/

		return;
	}

			 // INIT: function(1, img, bb, features, scales, id, nObjectTracked)
			 //                0  1    2   3         4
			 // =============================================================================
	case 1:  {
		mexPrintf("in the INIT!!!\n");
 
		if (nrhs!=6) { mexPrintf("fern: wrong input.\n"); return; }
		mexPrintf("-----in mex init function1 donver2 !!!1\n");
	
		id_ = mxGetPr(prhs[5]);
		id = (int)(*id_);


		/*if(id == 0) {
			mexPrintf("heeererererere\n");
			tmp = &fern1;
			mexPrintf("dderererere\n");
		}
		else
			tmp = &fern2;*/
		//mexPrintf("1\n");	
		if (pImageObject[id]->BBOX!=NULL) { mexPrintf("fern: already initialized.\n"); return; }	
		//mexPrintf("2\n");
		//mexPrintf("id: %d\n", id);
		pImageObject[id]->iHEIGHT    = mxGetM(prhs[1]);
		//mexPrintf("here1\n");
		pImageObject[id]->iWIDTH     = mxGetN(prhs[1]);
		pImageObject[id]->nTREES     = mxGetN(mxGetField(prhs[3],0,"x"));
		pImageObject[id]->nFEAT      = mxGetM(mxGetField(prhs[3],0,"x")) / 4; // feature has 2 points: x1,y1,x2,y2
		//mexPrintf("here2\n");
		pImageObject[id]->thrN       = 0.5 * pImageObject[id]->nTREES;
		pImageObject[id]->nSCALE     = mxGetN(prhs[4]);
		
		pImageObject[id]->IIMG       = (double*) mxMalloc(pImageObject[id]->iHEIGHT*pImageObject[id]->iWIDTH*sizeof(double));
		pImageObject[id]->IIMG2      = (double*) mxMalloc(pImageObject[id]->iHEIGHT*pImageObject[id]->iWIDTH*sizeof(double));
		//mexPrintf("here2\n");
		// BBOX
		mexPrintf("Im here ***********************");
		pImageObject[id]->mBBOX      = mxGetM(prhs[2]); 
		pImageObject[id]->nBBOX      = mxGetN(prhs[2]);
		pImageObject[id]->display();	
		//mexPrintf("nBBox = %d..........", pImageObject[id]->nBBOX);
		pImageObject[id]->BBOX	   = pImageObject[id]->create_offsets_bbox(mxGetPr(prhs[2]));
		double *x  = mxGetPr(mxGetField(prhs[3],0,"x"));
		double *s  = mxGetPr(prhs[4]);
		pImageObject[id]->OFF		   = pImageObject[id]->create_offsets(s,x);

		for (int i = 0; i<pImageObject[id]->nTREES; i++) {
			pImageObject[id]->WEIGHT.push_back(vector<double>(pow(2.0,pImageObject[id]->nBIT*pImageObject[id]->nFEAT), 0));
			pImageObject[id]->nP.push_back(vector<int>(pow(2.0,pImageObject[id]->nBIT*pImageObject[id]->nFEAT), 0));
			pImageObject[id]->nN.push_back(vector<int>(pow(2.0,pImageObject[id]->nBIT*pImageObject[id]->nFEAT), 0));
		}

		for (int i = 0; i<pImageObject[id]->nTREES; i++) {
			for (int j = 0; j < pImageObject[id]->WEIGHT[i].size(); j++) {
				pImageObject[id]->WEIGHT[i].at(j) = 0;
				pImageObject[id]->nP[i].at(j) = 0;
				pImageObject[id]->nN[i].at(j) = 0;
			}
		}
	/*	if(id == 0)
			fern1 = *tmp;
		else
			fern2 = *tmp;*/
		//mexPrintf("done with init!!!!!!!!!!!!!!!!\n");
		return;
	}

	// UPDATE
	// =============================================================================
	case 2: {
		mexPrintf("in mex UPDATE function!!!!!!!!!!!\n");
		if (nrhs!=6 && nrhs!=7) { mexPrintf("Conf = function(2,X,Y,Margin,Bootstrap,Id)\n"); return; }
		//                                                   0 1 2 3      4         5

		id_ = mxGetPr(prhs[5]);
		id = (int)(*id_);
		/*if(id == 0)
			tmp = &fern1;
		else
			tmp = &fern2;
		*/
		double *X     = mxGetPr(prhs[1]);
		int numX      = mxGetN(prhs[1]);
		double *Y     = mxGetPr(prhs[2]);
		double thrP   = *mxGetPr(prhs[3]) * pImageObject[id]->nTREES;
		int bootstrap = (int) *mxGetPr(prhs[4]);


		int step = numX / 10;

		if (nrhs == 6) {
			for (int j = 0; j < bootstrap; j++) {
				for (int i = 0; i < step; i++) {
					for (int k = 0; k < 10; k++) {
					
						int I = k*step + i;
						double *x = X+(pImageObject[id]->nTREES)*I;
						//mexPrintf("about to call measure_forest.....\n");
						if (Y[I] == 1) {
							if (pImageObject[id]->measure_forest(x) <= thrP) {
								//mexPrintf("about to call update function....\n");
								pImageObject[id]->update(x,1,1);
								//mexPrintf("just finished calling the update function\n");
							}
						} else {
							if (pImageObject[id]->measure_forest(x) >= pImageObject[id]->thrN) {
								//mexPrintf("about to call update function\n");
								pImageObject[id]->update(x,0,1);
								//mexPrintf("finished calling the update function\n");
							}
						}
						static int count = 0;
						//mexPrintf("pImageObject[id]->measure %d\n", count++);
					}
				}
			}
		}
	//	mexPrintf("finished the for loop!!!!!!232#@3233\n");
		
//		if (nrhs == 7) {
//			double *idx   = mxGetPr(prhs[5]);
//			int nIdx      = mxGetN(prhs[5])*mxGetM(prhs[5]);


//			for (int j = 0; j < bootstrap; j++) {
//				for (int i = 0; i < nIdx; i++) {
//					int I = idx[i]-1;
//					double *x = X+(fern.nTREES)*I;
//					if (Y[I] == 1) {
//						if (pImageObject[id]->measure_forest(x, &fern) <= thrP)
//							pImageObject[id]->measure(x,1,1,&fern);
//					} else {
//						if (pImageObject[id]->measure_forest(x, &fern) >= thrN)
//							pImageObject[id]->measure(x,0,1,&fern);
//					}
//				}
//			}
//		}



		if (nlhs==1) {
			plhs[0] = mxCreateDoubleMatrix(1, numX, mxREAL); 
			double *resp0 = mxGetPr(plhs[0]);

			for (int i = 0; i < numX; i++) {
				*resp0++ = pImageObject[id]->measure_forest((X+(pImageObject[id]->nTREES)*i));
			}
		}
	/*	
		if(id == 0)
			fern1 = *tmp;
		else
			fern2 = *tmp;
		*/
		//mexPrintf("done with mex update case!!!!!!!!!!!!\n");
//mexPrintf("made it to the end of the mex function's update case!!!!!\n");
		return;
	}

	// EVALUATE PATTERNS
	// =============================================================================
	case 3: {
		mexPrintf("---------in mex EVALUATE PATTERNS function1!!!\n");
		
		id_ = mxGetPr(prhs[2]);
		id = (int)(*id_);
		/*if(id == 0)
			tmp = &fern1;
		else
			tmp = &fern2;
*/
		if (nrhs!=3) { mexPrintf("Conf = function(3,X,id)\n"); return; }
		//                                        0 1  

		double *X     = mxGetPr(prhs[1]);
		int numX      = mxGetN(prhs[1]);
		
		plhs[0] = mxCreateDoubleMatrix(1, numX, mxREAL); 
		double *resp0 = mxGetPr(plhs[0]);

		for (int i = 0; i < numX; i++) {
			*resp0++ = pImageObject[id]->measure_forest((X+(pImageObject[id]->nTREES)*i));
		}
/*		
		if(id == 0)
			fern1 = *tmp;
		else
			fern2 = *tmp;*/
		//mexPrintf("done with evaluate patterns!!!!\n");
		return;
	}

			// DETECT: TOTAL RECALL
			// =============================================================================
	case 4: {
		mexPrintf("-------------in mex DETECT function!!!!!!!\n");
		id_ = mxGetPr(prhs[6]);
		id = (int)(*id_);
/*		if(id == 0)
			tmp = &fern1;
		else
			tmp = &fern2;
*/
		if (nrhs != 7) { 
			mexPrintf("function(4,img,maxBBox,minVar,conf,patt,id)\n"); 
			//                  0 1   2       3      4    5    6
			return; 
		}
//		mexPrintf("Detect!!!\n");
		// Pointer to preallocated output matrixes
		double *conf = mxGetPr(prhs[4]); if ( mxGetN(prhs[4]) != pImageObject[id]->nBBOX) { mexPrintf("1Wrong input mxGetN(prhs[4]: %d nBBOX: %d\n",mxGetN(prhs[4]), pImageObject[id]->nBBOX); return; }
		double *patt = mxGetPr(prhs[5]); if ( mxGetN(prhs[5]) != pImageObject[id]->nBBOX) { mexPrintf("2Wrong input.\n"); return; }
		for (int i = 0; i < pImageObject[id]->nBBOX; i++) { conf[i] = -1; }

		// Setup sampling of the BBox
		double probability = *mxGetPr(prhs[2]);

		double nTest  = pImageObject[id]->nBBOX * probability; if (nTest <= 0) return;
		if (nTest > pImageObject[id]->nBBOX) nTest = pImageObject[id]->nBBOX;
		double pStep  = (double) (pImageObject[id]->nBBOX) / nTest;
		double pState = randdouble() * pStep;

		// Input images
		unsigned char *input = (unsigned char*) mxGetPr(mxGetField(prhs[1],0,"input"));
		unsigned char *blur  = (unsigned char*) mxGetPr(mxGetField(prhs[1],0,"blur"));

		// Integral images
		iimg(input,pImageObject[id]->IIMG,pImageObject[id]->iHEIGHT,pImageObject[id]->iWIDTH);
		iimg2(input,pImageObject[id]->IIMG2,pImageObject[id]->iHEIGHT,pImageObject[id]->iWIDTH);

		// log: 0 - not visited, 1 - visited
		int *log = (int*) mxCalloc(pImageObject[id]->nBBOX,sizeof(int));

		// variance
		double minVar = *mxGetPr(prhs[3]);

		// totalrecall
		//double totalrecall = *mxGetPr(prhs[6]);
		int I = 0;
		int K = 2;

		while (1) 
		{
			// Get index of bbox
			I = (int) floor(pState);
			pState += pStep;
			if (pState >= pImageObject[id]->nBBOX) { break; }

			// measure bbox
			log[I] = 1;
			double *tPatt = patt + pImageObject[id]->nTREES*I;
			conf[I] = pImageObject[id]->measure_bbox_offset(blur,I,minVar,tPatt);

			// total recall
			
//			if (totalrecall == 1 && conf[i] > thrN) 
//			{
//				int I;
//				int W = *(BBOX + i*BBOX_STEP + 6);

//				for (int gH = -K; gH <= K; gH++ ) 
//				{
//					for (int gW = -K; gW <= K; gW++)
//					{
//						I = i+gW+(gH)*W;
//						if (I >= 0 && I < nBBOX && log[I]==0)
//						{
///							log[I] = 1;
	//						tPatt = patt + nTREES*I;
//							conf[I] = measure_bbox_offset(blur,I,minVar,tPatt);
//						}
//					}
//				}
//			}
			
		}

		mxFree(log);
	/*	if(id == 0)
			fern1 = *tmp;
		else
			fern2 = *tmp;*/
		//mexPrintf("done with mex detect!!!!\n");
		return;
			}

			// GET PATTERNS
	case 5: {
		mexPrintf("--------------------in mex GET PATTERNS function!!!!!!!11\n");
		if (nrhs !=5) { mexPrintf("patterns = fern(5,img,idx,var,id)\n"); return; }
		//                                         0 1   2   3   4  
		id_ = mxGetPr(prhs[4]);
		id = (int)(*id_);
/*		if(id == 0)
			tmp = &fern1;
		else
			tmp = &fern2;*/
		// image
		unsigned char *input = (unsigned char*) mxGetPr(mxGetField(prhs[1],0,"input"));
		unsigned char *blur  = (unsigned char*) mxGetPr(mxGetField(prhs[1],0,"blur"));

		//if (mxGetM(prhs[1])!=iHEIGHT) { mexPrintf("fern: wrong input image.\n"); return; }

		// bbox indexes
		double *idx = mxGetPr(prhs[2]);
		int numIdx = mxGetM(prhs[2]) * mxGetN(prhs[2]);

		// minimal variance
		double minVar = *mxGetPr(prhs[3]);
		//mexPrintf("about to grab a field from the static array of structs\n");
		if (minVar > 0) {
			iimg(input,pImageObject[id]->IIMG,pImageObject[id]->iHEIGHT,pImageObject[id]->iWIDTH);
			iimg2(input,pImageObject[id]->IIMG2,pImageObject[id]->iHEIGHT,pImageObject[id]->iWIDTH);
		}
		//mexPrintf("successfully grabbed field\n");
		// output patterns
		plhs[0] = mxCreateDoubleMatrix(pImageObject[id]->nTREES,numIdx,mxREAL);
		double *patt = mxGetPr(plhs[0]);

		plhs[1] = mxCreateDoubleMatrix(1,numIdx,mxREAL);
		double *status = mxGetPr(plhs[1]);

		for (int j = 0; j < numIdx; j++) {

			if (minVar > 0) {
				double bboxvar = bbox_var_offset(pImageObject[id]->IIMG,pImageObject[id]->IIMG2,(pImageObject[id]->BBOX)+j*(pImageObject[id]->BBOX_STEP));
				if (bboxvar < minVar) {	continue; }
			}
			status[j] = 1;
			double *tPatt = patt + j*(pImageObject[id]->nTREES);
			for (int i = 0; i < (pImageObject[id]->nTREES); i++) {
				tPatt[i] = (double) pImageObject[id]->measure_tree_offset(blur, idx[j]-1, i);
			}
		}
/*		
		if(id == 0)
			fern1 = *tmp;
		else
			fern2 = *tmp;*/
		//mexPrintf("done with get patterns!!!!\n");
		return;
			}
	}

}
