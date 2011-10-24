/*
 *  ofNewShapes.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 10/17/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"

enum ofDirection {
	OF_UP,OF_DOWN,OF_LEFT,OF_RIGHT,OF_VERT,OF_HOR
};

void ofLightSource(ofDirection dir);

void ofLightSource(int dir);

int ofCurrentLight();

void ofRaised(double pop);
void ofFlat();

void ofSetShadowDarkness(double depth);

void ofShade(double x, double y, double span, double length, ofDirection d=OF_UP, bool black=true);

void ofRoundedRect(double x, double y, double width, double height,double rad);

void ofRect(ofRectangle t);

void ofCircle_Plus(double x, double y, double rad, double start=0, double fin=360);

void ofShadowCircle(double x, double y, double rad, double depth=5);

void ofShadowRounded(double x, double y, double width, double height,double rad, double depth=5);

void ofRing(double x, double y, double ir, double Or);

void ofRingSegment(double x, double y, double ir, double Or,double start, double finish);

