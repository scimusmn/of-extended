/*
 *  ofTabs.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 3/2/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofTabs.h"

void ofTab::draw(int _x, int _y)
{
	x=_x, y=_y;
	draw();
}

void ofTab::draw()
{	
	ofColor cur=ofGetStyle().color;
	ofBeginShape();
	int rad=h/2;
	 for ( int i = 90; i >= 0; --i ){
		 ofVertex(x+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
	 }
	for ( int i = 180; i <= 270; ++i ){
		ofVertex(x+2*rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
	}
	for ( int i = 270; i <= 360; ++i ){
		ofVertex(x+w-2*rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
	}
	for ( int i = 180; i >= 90; --i ){
		ofVertex(x+w+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
	}
	ofEndShape();
	
	
	ofSetColor(0, 0, 0);
	ofNoFill();
	ofEnableSmoothing();
	ofBeginShape();
	for ( int i = 90; i >= 0; --i ){
		ofVertex(x+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
	}
	for ( int i = 180; i <= 270; ++i ){
		ofVertex(x+2*rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
	}
	for ( int i = 270; i <= 360; ++i ){
		ofVertex(x+w-2*rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
	}
	for ( int i = 180; i >= 90; --i ){
		ofVertex(x+w+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
	}
	ofEndShape();
	ofDisableSmoothing();
	ofFill();
	
	arial.drawString(title, x+h, y+15);
	
	ofSetColor(cur);
}

void ofTab::setup()
{
	box=arial.getBoundingBox(title, x, y);
	w=box.width+48;
	h=box.height+5;
}


void ofTabs::addTab(string ttl)
{
	int cur=tabs.size();
	tabs.push_back(ofTab(ttl));
	tabs[cur].setup();
	tabOpen=cur;
}

void ofTabs::draw(int _x, int _y)
{
	x=_x, y=_y;
	ofColor cur=ofGetStyle().color;
	
	if(tabs.size()) tabs[0].draw(x+20,y);
	for (unsigned int i=1; i<tabs.size(); i++) {
		tabs[i].draw(tabs[i-1].x+tabs[i-1].w-tabs[i-1].h*3/4,y);
	}
	ofFlat();
	ofRoundedRect(x,y+=tabs[tabOpen].h-1,w,h,20);
	ofSetColor(0, 0, 0);
  ofNoFill();
	ofRoundedRect(x,y,w,h,20);
  ofFill();
	ofSetColor(cur);
	tabs[tabOpen].draw();
}

void ofTabs::setup(int _w, int _h)
{
	w=_w, h=_h;
}

void ofTabs::setDefaultTab(int num)
{	
	tabOpen=num;
}

bool ofTabs::clickDown(int _x, int _y)
{
	bool ret=0;
	for (unsigned int i=0; i<tabs.size(); i++) {
		if (tabs[i].clickDown(_x,_y)) {
			ret=true;
			tabOpen=i;
		}
	}
	return ret;
}