/*
 *  ofxShapes.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 5/19/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofxShapes.h"

void ofRegularPolygon(int x, int y, double s, double numSides)
{
	ofVector k=ofVector(0,1).unit()*s*3/numSides;
	ofPoint pos(x, y);
	double exAng=(360./numSides);
	double intAng=180-(360/numSides);
	ofBeginShape();
	for (int i=0; i<numSides; i++) {
		ofVertex(pos);
		pos=pos+k;
		k.rotate(-exAng);
	}
	ofVertex(pos);
	ofEndShape();
}