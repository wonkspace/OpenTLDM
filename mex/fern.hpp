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

#ifndef FERN_HPP
#define FERN_HPP

#include "stdio.h"
#include "math.h"
#include <vector>
#include <map>
#include <set>
#include "tld.h"
#include "mex.h" 

# ifdef _CHAR16T
	#define CHAR16_T
# endif
#define sub2idx(row,col,height) ((int) (floor((row)+0.5) + floor((col)+0.5)*(height)))

class ImageObject {
private:
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
		
public:
  // Methods	
  ImageObject(int handle);
  ~ImageObject();	
  void display();
  void update(double *x, int C, int N);
  double measure_forest(double *idx);
  int measure_tree_offset(unsigned char *img, int idx_bbox, int idx_tree);
  double measure_bbox_offset(unsigned char *blur, int idx_bbox, double minVar, double *tPatt);
  int* create_offsets(double *scale0, double *x0);
  double randdouble(); 
}


#endif
