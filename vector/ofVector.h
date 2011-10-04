/*
 *  ofVector.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 1/24/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#ifndef _ofVector
#define _ofVector

#include <math.h>
#include "ofTypes.h"

class ofVector {
public:
	union  {
        struct {
            float x;
            float y;
            float z;
        };
        float v[3];
    };
	
	float& operator[]( int n ){
		return v[n];
	}
	
	ofVector(){
		x=y=z=0;
	}
	
	ofVector(double X, double Y, double Z=0);
	
	ofVector(const ofPoint & P);
	
	ofVector(const ofVector & B);
	
	double mag();
	
	double operator*(ofVector B);
	
	ofVector operator^(ofVector B);
	
	ofVector operator*(double c);
	
	ofVector operator/(double c);
	
	ofVector operator+(ofVector A);
	
	ofVector operator-(ofVector A);
	
	void operator-=(ofVector A);
	
	void operator+=(ofVector A);
	
	void operator*=(double c);
	
	void operator=(ofVector A);
	
	void operator=(double c);
	
	ofVector rotate(double degrees);
  
  double angleDifference(ofVector b);
  
  double absoluteAngle();
	
	ofVector operator-();
	
	double slope();
	
	ofVector unit();
	
	ofVector ortho();
};

ofVector operator*(double c, ofVector B);

ofPoint operator+(ofPoint p, ofVector v);

ofPoint operator-(ofPoint p, ofVector v);

ofVector sqrt(ofVector k);

#endif