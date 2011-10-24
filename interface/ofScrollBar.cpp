/*
 *  ofScrollBar.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 3/30/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofScrollBar.h"

void ofScrollTab::setup(double span, bool vrt)
{
	vert=vrt;
	if (!vert) h=span;
	else if (vert) w=span;
}

void ofScrollTab::draw(int _x, int _y)
{
	x=_x, y=_y;
	draw();
}

void ofScrollTab::draw(int dp)
{
	if(vert) x=dp;
	else y=dp;
	draw();
}

void ofScrollTab::draw()
{
	double r=(vert)?w/2:h/2;
	ofColor k=ofGetStyle().color;
	ofSetColor((getAvailable())?k:k+.4*255);
  ofRaised(.3);
	ofRoundedRect(x, y, w, h, r);
  ofFlat();
	ofSetColor(0, 0, 0,16*k.a/255.);
	ofSetLineWidth(1);
	if(vert) for(int i=1; i<(h-w)/4; i++){
		ofLine(x+2, y+w/2+i*4, x+w-2, y+w/2+i*4);
	}
	else for(int i=1; i<(w-h)/4; i++){
		ofLine(x+h/2+i*4, y+2, x+h/2+i*4, y+h-2);
	}
}

void ofScrollTab::mouseMotion(int _x, int _y)
{
	
}

ofScrollBar::~ofScrollBar()
{
	
}

void ofScrollBar::setup(double span, double length, ofDirection DIRECTION)
{
	vert=(OF_VERT==DIRECTION);
	if (!vert) h=span, w=length, fullEx=length-4,exDisp=(w-fullEx)/2;
	else w=span, h=length, fullEx=length-4,exDisp=(h-fullEx)/2;
	tab.setup(span-2,vert);
}

void ofScrollBar::registerArea(double vSize, double fSize)
{
	viewSize=vSize;
	fullSize=fSize;
	double perc=((viewSize/fullSize)>=1)?1:(viewSize/fullSize);
	if (!vert) tab.w=perc*(fullEx-2);
	else tab.h=perc*(fullEx-2);
	tab.setAvailable((fullSize/viewSize)>1);
}

bool ofScrollBar::clickDown(int _x, int _y)
{
	bool ret=false;
	if(tab.clickDown(_x, _y)){
		cout << "test made it to here" << endl;
		xDisp=_x-tab.x;
		yDisp=_y-tab.y;
	}
	else if(over(_x, _y))
		tab.setPressed(true);
	return tab.pressed();
}

bool ofScrollBar::clickUp()
{
	bool ret=false;
  bPressed=false;
	if(ret=tab.pressed()) tab.clickUp();
	return ret;
}

void ofScrollBar::draw(int _x, int _y)
{
  ofColor k=ofGetStyle().color;
	x=_x, y=_y;
	double r=(vert)?w/2.:h/2.;
	double off=(vert)?(h-fullEx)/2.:(w-fullEx)/2.;
	ofSetColor(210, 210, 210, k.a);
	ofRect(x, y, (vert)?w+2:w, (vert)?h:h+2);
	ofSetColor(150, 150, 150, k.a);
	ofRoundedRect((vert)?x+1:x+off, (vert)?y+off:y+1, (vert)?w:fullEx, (!vert)?h:fullEx, r);
  ofSetColor(60, 170, 220,k.a);
	tab.draw((vert)?x+2:y+2);
}

bool ofScrollBar::mouseMotion(int _x, int _y)
{
	bool ret=false;
	if(ret=tab.pressed()){
		if (!vert) {
			if(_x-xDisp<x+exDisp+1) tab.x=x+exDisp+1;
			else if(_x+tab.w-xDisp>x+w-exDisp-1) tab.x=x+w-exDisp-tab.w-1;
			else tab.x=_x-xDisp;
		}
		else {
			if(_y-yDisp<y+exDisp+1) tab.y=y+exDisp+1;
			else if(_y+tab.h-yDisp>y+h-exDisp-1) tab.y=y+h-exDisp-tab.h-1;
			else tab.y=_y-yDisp;
		}
	}
	return ret;
}

double ofScrollBar::getScrollPercent()
{
	double ret=0;
	if (vert) ret=(tab.y-y-exDisp)/(fullEx-tab.h);
	else ret=(tab.x-x-exDisp)/(fullEx-tab.w);
	return ret;
}


double ofScrollBar::getScrollPosition()
{
	double ret=0;
	if(available()) ret=getScrollPercent()*(fullSize-viewSize);
	return ret;
}

bool ofScrollBar::setScrollPosition(double newPos)
{
	bool ret=false;
	if(newPos<fullSize&&newPos>=0){
		ret=true;
		if(vert){
			double pos=newPos*(fullEx-tab.h)/(fullSize-viewSize)+exDisp;
			if(pos<exDisp) pos=exDisp;
			else if(pos+tab.h>h-exDisp*2) pos=h-exDisp*2-tab.h;
			tab.y=pos+y;
		}
		else {
			double pos=newPos*(fullEx-tab.w)/(fullSize-viewSize)+exDisp;
			if(pos<exDisp) pos=exDisp;
			else if(pos+tab.w>w-exDisp*2-2) pos=w-exDisp*2-2-tab.w;
			tab.x=pos+x;
		}
	}
	return	ret;
}
	

void ofScrollBar::update(double percent)
{
	if (!vert) tab.w=percent*(fullEx-2);
	else tab.h=percent*(fullEx-2);
}
	
void ofScrollBar::update()
{
	if(!vert){
		if(tab.x<x+exDisp+1) tab.x=x+exDisp+1;
		else if(tab.x+tab.w>x+w-exDisp-1) tab.x=x+w-exDisp-tab.w-1;
	}
	else {
		if(tab.y<y+exDisp+1) tab.y=y+exDisp+1;
		else if(tab.y+tab.h>y+h-exDisp-1) tab.y=y+h-exDisp-tab.h-1;
	}

	tab.setAvailable((fullSize/viewSize)>1);
}

bool ofScrollBar::available()
{
	return tab.getAvailable();
}

double ofScrollBar::barSize()
{
	double ret=0;
	if(vert) ret=tab.h;
	else ret=tab.w;
	return ret;
}

void ofScrollBar::setPressed(bool state)
{
  bPressed=state;
  tab.setPressed(state);
}
