/*
 *  ofTabs.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 3/2/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#ifndef _OF_TABS
#define _OF_TABS

#include "ofButton.h"

class ofTab : public ofButton {
	ofRectangle box;
public:
	ofTab():ofButton(){};
	ofTab(string ttl):ofButton(){
		title=ttl;
		setAvailable(true);
		arial.loadFont("Arial.ttf");
	}
	void draw(int _x, int _y);
	void draw();
	void setup();
	friend class ofTabs;
};

class ofTabs : public ofInterGroup {
	vector<ofTab> tabs;
	int tabOpen;
public:
	void addTab(string ttl);
	void draw(int _x, int _y);
	bool clickDown(int _x, int _y);
	void setDefaultTab(int);
	int getTab(){ return tabOpen;}
	void setup(int _w, int _h);
};

#endif