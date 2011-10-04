/*
 *  ofGraphicEx.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 3/6/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofGraphicEx.h"

bool ofInTriangle(ofPoint A,ofPoint B, ofPoint C, ofPoint P)
{
	ofVector v0(C-A);
	ofVector v1(B-A);
	ofVector v2(P-A);
	
	double d00=(v0*v0);
	double d01=(v0*v1);
	double d02=(v0*v2);
	double d11=(v1*v1);
	double d12=(v1*v2);
	
	double invDen=1/(d00*d11-d01*d01);
	double u=(d11*d02-d01*d12)*invDen;
	double v=(d00*d12-d01*d02)*invDen;
	
	return (u>0&&v>0&&u+v<1);
}

bool ofInShape(vector<ofPoint> k, int x, int y)
{
	bool ret=false;
	int num=k.size();
	if (num>=3) {
		for (unsigned int i=0; i<num+1; i++) {
			if(ret=ofInTriangle(k[i%(num)], k[(i+1)%(num)], k[(i+2)%(num)], ofPoint(x,y))) break;
		}
	}
	else {
		ret=false;
	}
	return ret;
}
