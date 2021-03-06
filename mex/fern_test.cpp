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
#include "tld.h"
#ifdef _CHAR16T
#define CHAR16_T
#endif
#include "mex.h" 
using namespace std;
//extern void _main();
/*
double* id;
double thrN;
int nBBOX;
int mBBOX;
int nTREES;
int nFEAT;
int nSCALE;
int iHEIGHT;
int iWIDTH;
int *BBOX = NULL;
int *OFF  = NULL;
double *IIMG = 0;
double *IIMG2 = 0;
vector<vector <double> > WEIGHT;
vector<vector <int> > nP;
vector<vector <int> > nN;
int BBOX_STEP = 7;
int nBIT = 1; // number of bits per feature
*/
double* id_;
static int id = 0;
vector<vector<double> > initw;
vector<vector<int> > initn;
struct fieldstruct {
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
/*
} fields[] = {{ 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, initw, initn, initn, 7, 1 },
              { 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, initw, initn, initn, 7, 1 },
              { 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, initw, initn, initn, 7, 1 },
              { 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, initw, initn, initn, 7, 1 }
*/
};




//static int size = 4;              // jorgeb - ToDo - Remove hard-wired value
//fieldstruct * fields = new fieldstruct[size];  // jorgeb

#define sub2idx(row,col,height) ((int) (floor((row)+0.5) + floor((col)+0.5)*(height)))


//Fernstruct fern2;
//Fernstruct* tmp;
/*
struct list_element {
	Fernstruct* fern;
	list_element* next;
} *list_head;

Fernstruct* fern;
*/

//vector<vector <double>> curWEIGHT;
/*
// append a fern to the end of the list
void list_append(Fernstruct* newfern) {
	//if(newfern == NULL)
	//	throw mwException("ERROR: Tried to append empty element to linked list");
	list_element* new_element = (list_element*)malloc(sizeof(list_element)); // allocate memory

	new_element->fern = newfern; // put the fern in the list element
	mexPrintf("the fern being added to the list has an id of %f\n", new_element->fern->id);
	new_element->next = NULL;
	list_element* iter = list_head; // iterator 
	if(iter == NULL)
		list_head = new_element;
	else {
		while(iter->next != NULL) {
			//mexPrintf("found non-null item!!!\n");
			iter = iter->next;
		}
		iter->next = new_element;
	}
}

// find an element, returns null if not found
Fernstruct* list_find(double id) {
	list_element* iter = list_head; // iterator
	while(iter != NULL) { 
		//		mexPrintf("found something!!!! it has id of %f, looking for id of %f\n", iter->fern->id, id);
		if(iter->fern->id == id) { 
		//	mexPrintf("found the list element!\n");
			return iter->fern;
		}
		iter = iter->next;
	}
	mexPrintf("didn't find the list element1!!!!\n");
	return NULL;
}
*/

fieldstruct * initialize_fields(fieldstruct* fields, int size) {   // jorgeb
    for (int i=0; i<size; i++) {
    	fields[i].thrN = 0.0;
    	fields[i].nBBOX = 0;
    	fields[i].mBBOX = 0;
    	fields[i].nTREES = 0;
    	fields[i].nFEAT = 0;
    	fields[i].nSCALE = 0;
    	fields[i].iHEIGHT = 0;
    	fields[i].iWIDTH = 0;
    	fields[i].BBOX = NULL;
    	fields[i].OFF = NULL;
    	fields[i].IIMG = 0;
    	fields[i].IIMG2 = 0;
    	fields[i].WEIGHT = initw;
    	fields[i].nP = initn;
    	fields[i].nN = initn;
    	fields[i].BBOX_STEP = 7;
    	fields[i].nBIT = 1;
    }
    
    for (int i=0; i<4; i++) {  // jorgeb - hardwired value
        mexPrintf("fields[%d].thrN = %f\n", i, fields[i].thrN);
        mexPrintf("fields[%d].nBBOX = %d\n", i, fields[i].nBBOX);
        mexPrintf("fields[%d].mBBOX = %d\n", i, fields[i].mBBOX);
        mexPrintf("fields[%d].nTREES = %d\n", i, fields[i].nTREES);
        mexPrintf("fields[%d].nFEAT = %d\n", i, fields[i].nFEAT);
        mexPrintf("fields[%d].nSCALE = %d\n", i, fields[i].nSCALE);
        mexPrintf("fields[%d].iHEIGHT = %d\n", i, fields[i].iHEIGHT);
        mexPrintf("fields[%d].iWIDTH = %d\n", i, fields[i].iWIDTH);
        mexPrintf("fields[%d].BBOX = %d\n", i, fields[i].BBOX);
        mexPrintf("fields[%d].OFF = %d\n", i, fields[i].OFF);
        mexPrintf("fields[%d].IIMG = %f\n", i, fields[i].IIMG);
        mexPrintf("fields[%d].IIMG2 = %f\n", i, fields[i].IIMG2);
        mexPrintf("&fields[%d].WEIGHT[0] = %f\n", i, &fields[i].WEIGHT[0]);
        mexPrintf("&fields[%d].nP[0] = %d\n", i, &fields[i].nP[0]);
        mexPrintf("&fields[%d].nN[0] = %d\n", i, &fields[i].nN[0]);
        mexPrintf("fields[%d].BBOX_STEP = %d\n", i, fields[i].BBOX_STEP);
        mexPrintf("fields[%d].nBIT = %d\n", i, fields[i].nBIT);
    }

return fields;
}
static int size = 4;
fieldstruct * fields = new fieldstruct[size];  // jorgeb
//fields = initialize_fields(fields, size); // jorgeb - ToDo - Remove hardwired value


void update(double *x, int C, int N) {
//	mexPrintf("here1\n");
	for (int i = 0; i < fields[id].nTREES; i++) {
		int idx = (int) x[i];

		(C==1) ? (fields[id].nP[i][idx] += N) : (fields[id].nN[i][idx] += N);

		if (fields[id].nP[i][idx]==0) {
			fields[id].WEIGHT[i][idx] = 0;
		} else {
			fields[id].WEIGHT[i][idx] = ((double) (fields[id].nP[i][idx])) / (fields[id].nP[i][idx] + fields[id].nN[i][idx]);
		}
	}
	////mexPrintf("here2\n");
}


double measure_forest(double *idx) {
	double votes = 0;
	for (int i = 0; i < fields[id].nTREES; i++) { 
		votes += fields[id].WEIGHT[i][idx[i]];
	}
	return votes;
}


int measure_tree_offset(unsigned char *img, int idx_bbox, int idx_tree) {
	
	int index = 0;
	int *bbox = fields[id].BBOX + idx_bbox*(fields[id].BBOX_STEP);
	int *off = (fields[id].OFF) + bbox[5] + idx_tree*2*(fields[id].nFEAT);
	for (int i=0; i<(fields[id].nFEAT); i++) {
		index<<=1; 
		int fp0 = img[off[0]+bbox[0]];
		int fp1 = img[off[1]+bbox[0]];
		if (fp0>fp1) { index |= 1;}
		off += 2;
	}
	return index;	
}


double measure_bbox_offset(unsigned char *blur, int idx_bbox, double minVar, double *tPatt) {
	double conf = 0.0;
	double bboxvar = bbox_var_offset(fields[id].IIMG,fields[id].IIMG2,(fields[id].BBOX)+idx_bbox*(fields[id].BBOX_STEP));
	if (bboxvar < minVar) {	return conf; }
	for (int i = 0; i < (fields[id].nTREES); i++) { 
		int idx = measure_tree_offset(blur,idx_bbox,i);
		tPatt[i] = idx;
		conf += fields[id].WEIGHT[i][idx];
	}
	return conf;
}

int* create_offsets(double *scale0, double *x0) {

	int *offsets = (int*) malloc(fields[id].nSCALE*fields[id].nTREES*fields[id].nFEAT*2*sizeof(int));
	int *off = offsets;

	for (int k = 0; k < fields[id].nSCALE; k++){
		double *scale = scale0+2*k;
		for (int i = 0; i < fields[id].nTREES; i++) {
			for (int j = 0; j < fields[id].nFEAT; j++) {
				double *x  = x0 +4*j + (4*fields[id].nFEAT)*i;
				*off++ = sub2idx((scale[0]-1)*x[1],(scale[1]-1)*x[0],fields[id].iHEIGHT);
				*off++ = sub2idx((scale[0]-1)*x[3],(scale[1]-1)*x[2],fields[id].iHEIGHT);
			}
		}
	}
	return offsets;
}

int* create_offsets_bbox(double *bb0) {

	int *offsets = (int*) malloc(fields[id].BBOX_STEP*fields[id].nBBOX*sizeof(int));
	int *off = offsets;

	for (int i = 0; i < fields[id].nBBOX; i++) {
		double *bb = bb0+fields[id].mBBOX*i;
		*off++ = sub2idx(bb[1]-1,bb[0]-1,fields[id].iHEIGHT);
		*off++ = sub2idx(bb[3]-1,bb[0]-1,fields[id].iHEIGHT);
		*off++ = sub2idx(bb[1]-1,bb[2]-1,fields[id].iHEIGHT);
		*off++ = sub2idx(bb[3]-1,bb[2]-1,fields[id].iHEIGHT);
		*off++ = (int) ((bb[2]-bb[0])*(bb[3]-bb[1]));
		*off++ = (int) (bb[4]-1)*2*fields[id].nFEAT*fields[id].nTREES; // pointer to features for this scale
		*off++ = bb[5]; // number of left-right bboxes, will be used for searching neighbors
	}
	return offsets;
}


double randdouble() 
{ 
	return rand()/(double(RAND_MAX)+1); 
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
    
    //fieldstruct * fields = new fieldstruct[4];     // jorgeb - hardwired
    fields = initialize_fields(fields, 4);         // jorgeb - hardwired
    
 	switch ((int) *mxGetPr(prhs[0])) {

		// CLEANUP: function(0);
		// =============================================================================
	case 0:  {
		//mexPrintf("in the cleanup!!!\n");
		id_ = mxGetPr(prhs[1]);
		id = (int)(*id_);

		srand(0); // fix state of random generator
		fields[id].thrN = 0; fields[id].nBBOX = 0; fields[id].mBBOX = 0; fields[id].nTREES = 0; fields[id].nFEAT = 0; fields[id].nSCALE = 0; fields[id].iHEIGHT = 0; fields[id].iWIDTH = 0;
		//mexPrintf("--------in mex cleanup function!!!!!\n");
		free(fields[id].BBOX); fields[id].BBOX = 0;
		free(fields[id].OFF); fields[id].OFF = 0;
		free(fields[id].IIMG); fields[id].IIMG = 0;
		free(fields[id].IIMG2); fields[id].IIMG2 = 0;
		fields[id].WEIGHT.clear();
		fields[id].nP.clear();
		fields[id].nN.clear();
		//mexPrintf("heeeeeeeere23232\n");
	/*	if(id == 0)
			fern1 = *tmp;
		else
			fern2 = *tmp;*/
		//mexPrintf("donnnnee cleanup\n");
		return;
	}

			 // INIT: function(1, img, bb, features, scales, id)
			 //                0  1    2   3         4
			 // =============================================================================
	case 1:  {
 
		if (nrhs!=6) { mexPrintf("fern: wrong input.\n"); return; }
		mexPrintf("-----in mex init function1 donver !!!1\n");
	
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
		if (fields[id].BBOX!=NULL) { mexPrintf("fern: already initialized.\n"); return; }	
		//mexPrintf("2\n");
		//mexPrintf("id: %d\n", id);
		fields[id].iHEIGHT    = mxGetM(prhs[1]);
		//mexPrintf("here1\n");
		fields[id].iWIDTH     = mxGetN(prhs[1]);
		fields[id].nTREES     = mxGetN(mxGetField(prhs[3],0,"x"));
		fields[id].nFEAT      = mxGetM(mxGetField(prhs[3],0,"x")) / 4; // feature has 2 points: x1,y1,x2,y2
		//mexPrintf("here2\n");
		fields[id].thrN       = 0.5 * fields[id].nTREES;
		fields[id].nSCALE     = mxGetN(prhs[4]);
		
		fields[id].IIMG       = (double*) malloc(fields[id].iHEIGHT*fields[id].iWIDTH*sizeof(double));
		fields[id].IIMG2      = (double*) malloc(fields[id].iHEIGHT*fields[id].iWIDTH*sizeof(double));
		//mexPrintf("here2\n");
		// BBOX
		fields[id].mBBOX      = mxGetM(prhs[2]); 
		fields[id].nBBOX      = mxGetN(prhs[2]);
		//mexPrintf("nBBox = %d..........", fields[id].nBBOX);
		fields[id].BBOX	   = create_offsets_bbox(mxGetPr(prhs[2]));
		double *x  = mxGetPr(mxGetField(prhs[3],0,"x"));
		double *s  = mxGetPr(prhs[4]);
		fields[id].OFF		   = create_offsets(s,x);

		for (int i = 0; i<fields[id].nTREES; i++) {
			fields[id].WEIGHT.push_back(vector<double>(pow(2.0,fields[id].nBIT*fields[id].nFEAT), 0));
			fields[id].nP.push_back(vector<int>(pow(2.0,fields[id].nBIT*fields[id].nFEAT), 0));
			fields[id].nN.push_back(vector<int>(pow(2.0,fields[id].nBIT*fields[id].nFEAT), 0));
		}

		for (int i = 0; i<fields[id].nTREES; i++) {
			for (int j = 0; j < fields[id].WEIGHT[i].size(); j++) {
				fields[id].WEIGHT[i].at(j) = 0;
				fields[id].nP[i].at(j) = 0;
				fields[id].nN[i].at(j) = 0;
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
		//mexPrintf("in mex update function!!!!!!!!!!!\n");
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
		double thrP   = *mxGetPr(prhs[3]) * fields[id].nTREES;
		int bootstrap = (int) *mxGetPr(prhs[4]);


		int step = numX / 10;

		if (nrhs == 6) {
			for (int j = 0; j < bootstrap; j++) {
				for (int i = 0; i < step; i++) {
					for (int k = 0; k < 10; k++) {
					
						int I = k*step + i;
						double *x = X+(fields[id].nTREES)*I;
						//mexPrintf("about to call measure_forest.....\n");
						if (Y[I] == 1) {
							if (measure_forest(x) <= thrP) {
								//mexPrintf("about to call update function....\n");
								update(x,1,1);
								//mexPrintf("just finished calling the update function\n");
							}
						} else {
							if (measure_forest(x) >= fields[id].thrN) {
								//mexPrintf("about to call update function\n");
								update(x,0,1);
								//mexPrintf("finished calling the update function\n");
							}
						}
						static int count = 0;
						//mexPrintf("update %d\n", count++);
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
//						if (measure_forest(x, &fern) <= thrP)
//							update(x,1,1,&fern);
//					} else {
//						if (measure_forest(x, &fern) >= thrN)
//							update(x,0,1,&fern);
//					}
//				}
//			}
//		}



		if (nlhs==1) {
			plhs[0] = mxCreateDoubleMatrix(1, numX, mxREAL); 
			double *resp0 = mxGetPr(plhs[0]);

			for (int i = 0; i < numX; i++) {
				*resp0++ = measure_forest((X+(fields[id].nTREES)*i));
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
		//mexPrintf("---------in mex evaluate patterns function1!!!\n");
		
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
			*resp0++ = measure_forest((X+(fields[id].nTREES)*i));
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
		//mexPrintf("-------------in mex detect function!!!!!!!\n");
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
		double *conf = mxGetPr(prhs[4]); if ( mxGetN(prhs[4]) != fields[id].nBBOX) { mexPrintf("1Wrong input.\n"); return; }
		double *patt = mxGetPr(prhs[5]); if ( mxGetN(prhs[5]) != fields[id].nBBOX) { mexPrintf("2Wrong input.\n"); return; }
		for (int i = 0; i < fields[id].nBBOX; i++) { conf[i] = -1; }

		// Setup sampling of the BBox
		double probability = *mxGetPr(prhs[2]);

		double nTest  = fields[id].nBBOX * probability; if (nTest <= 0) return;
		if (nTest > fields[id].nBBOX) nTest = fields[id].nBBOX;
		double pStep  = (double) (fields[id].nBBOX) / nTest;
		double pState = randdouble() * pStep;

		// Input images
		unsigned char *input = (unsigned char*) mxGetPr(mxGetField(prhs[1],0,"input"));
		unsigned char *blur  = (unsigned char*) mxGetPr(mxGetField(prhs[1],0,"blur"));

		// Integral images
		iimg(input,fields[id].IIMG,fields[id].iHEIGHT,fields[id].iWIDTH);
		iimg2(input,fields[id].IIMG2,fields[id].iHEIGHT,fields[id].iWIDTH);

		// log: 0 - not visited, 1 - visited
		int *log = (int*) calloc(fields[id].nBBOX,sizeof(int));

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
			if (pState >= fields[id].nBBOX) { break; }

			// measure bbox
			log[I] = 1;
			double *tPatt = patt + fields[id].nTREES*I;
			conf[I] = measure_bbox_offset(blur,I,minVar,tPatt);

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

		free(log);
	/*	if(id == 0)
			fern1 = *tmp;
		else
			fern2 = *tmp;*/
		//mexPrintf("done with mex detect!!!!\n");
		return;
			}

			// GET PATTERNS
	case 5: {
	//	mexPrintf("--------------------in mex get patterns function!!!!!!!11\n");
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
			iimg(input,fields[id].IIMG,fields[id].iHEIGHT,fields[id].iWIDTH);
			iimg2(input,fields[id].IIMG2,fields[id].iHEIGHT,fields[id].iWIDTH);
		}
		//mexPrintf("successfully grabbed field\n");
		// output patterns
		plhs[0] = mxCreateDoubleMatrix(fields[id].nTREES,numIdx,mxREAL);
		double *patt = mxGetPr(plhs[0]);

		plhs[1] = mxCreateDoubleMatrix(1,numIdx,mxREAL);
		double *status = mxGetPr(plhs[1]);

		for (int j = 0; j < numIdx; j++) {

			if (minVar > 0) {
				double bboxvar = bbox_var_offset(fields[id].IIMG,fields[id].IIMG2,(fields[id].BBOX)+j*(fields[id].BBOX_STEP));
				if (bboxvar < minVar) {	continue; }
			}
			status[j] = 1;
			double *tPatt = patt + j*(fields[id].nTREES);
			for (int i = 0; i < (fields[id].nTREES); i++) {
				tPatt[i] = (double) measure_tree_offset(blur, idx[j]-1, i);
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
