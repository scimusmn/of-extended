/*
 *  ofSpinner.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 3/21/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#ifndef OF_PROG_SPIN
#define OF_PROG_SPIN

#include "ofExtended.h"

class ofProgressSpinner {
	ofTimer clock;
	float	clockSpeed;
	int		curPos;
public:
	ofProgressSpinner(){
		clockSpeed=.1;
		clock.set(clockSpeed);
		curPos=0;
	}
	int count(){ return curPos; }
	void draw(int x, int y, int rad){
		ofColor cur=ofGetStyle().color;
		for (unsigned int i=0; i<12; i++) {
			float phase=M_PI/6*i;
			float angle=30*i;
			ofPushMatrix();
			ofTranslate(x, y, 0);
			ofTranslate(cos(phase)*rad/2, sin(phase)*rad/2, 0);
			ofRotate(angle);
			ofSetColor(cur.r,cur.g,cur.b,255.-((i+curPos)%12)*21.25);
			ofRoundShape(-rad/4, -rad/12, rad/2, rad/6, rad/12, 1);
			ofPopMatrix();
		}
	}
	void spin(){
		if (clock.expired()) {
			clock.set(clockSpeed);
			if(++curPos>=12) curPos=0;
		}
	}
};

#endif