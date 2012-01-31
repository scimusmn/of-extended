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
  
  relPos.x=relPos.y=0;
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
	ofRoundedRect(x+relPos.x, y+relPos.y, w, h, r);
  ofFlat();
	ofSetColor(0, 0, 0,16*k.a/255.);
	ofSetLineWidth(1);
	if(vert) for(int i=1; i<(h-w)/4; i++){
		ofLine(x+relPos.x+2, y+relPos.x+w/2+i*4, x+w-2, y+w/2+i*4);
	}
	else for(int i=1; i<(w-h)/4; i++){
		ofLine(x+relPos.x+h/2+i*4, y+relPos.x+2, x+h/2+i*4, y+h-2);
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
	if (!vert) h=span, w=length, tabRange=length-4,endPad=(w-tabRange)/2;
	else w=span, h=length, tabRange=length-4,endPad=(h-tabRange)/2;
	tab.setup(span-2,vert);
}

void ofScrollBar::registerArea(double vSize, double fSize)
{
	viewSize=vSize;
	fullSize=fSize;
	double perc=((viewSize/fullSize)>=1)?1:(viewSize/fullSize);
	if (!vert) tab.w=perc*(tabRange-2);
	else tab.h=perc*(tabRange-2);
	tab.setAvailable((fullSize/viewSize)>1);
  
  if(vert) tab.relPos.y=endPad+1;
  else tab.relPos.x=endPad+1;
}

bool ofScrollBar::clickDown(int _x, int _y)
{
	bool ret=false;
	if(tab.clickDown(_x-tab.relPos.x, _y-tab.relPos.y)){
    relMouse.x=_x-(tab.x+tab.relPos.x);
		relMouse.y=_y-(tab.y+tab.relPos.y);
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
	double off=(vert)?(h-tabRange)/2.:(w-tabRange)/2.;
	ofSetColor(210, 210, 210, k.a);
	ofRect(x, y, (vert)?w+2:w, (vert)?h:h+2);
	ofSetColor(150, 150, 150, k.a);
	ofRoundedRect((vert)?x+1:x+off, (vert)?y+off:y+1, (vert)?w:tabRange, (!vert)?h:tabRange, r);
  ofSetColor(60, 170, 220,k.a);
	tab.draw(x,y);
}

bool ofScrollBar::mouseMotion(int _x, int _y)
{
	bool ret=false;
	if(ret=tab.pressed()){
		if (!vert) {
			if(_x-relMouse.x<tab.x+endPad+1) tab.relPos.x=endPad+1;
			else if(_x+tab.w-relMouse.x>tab.x+w-endPad-1) tab.relPos.x=w-endPad-tab.w-1;
			else tab.relPos.x=(_x-tab.x)-relMouse.x;
		}
		else {
			if(_y-relMouse.y<tab.y+endPad+1) tab.relPos.y=endPad+1;
			else if(_y+tab.h-relMouse.y>tab.y+h-endPad-1) tab.relPos.y=h-endPad-tab.h-1;
			else tab.relPos.y=(_y-tab.y)-relMouse.y;
		}
	}
	return ret;
}

double ofScrollBar::getScrollPercent()
{
	double ret=0;
	if (vert) ret=(tab.relPos.y-endPad)/(tabRange-tab.h);
	else ret=(tab.relPos.x-endPad)/(tabRange-tab.w);
  if((fullSize/viewSize)<=1) ret=1;
	return ret;
}


double ofScrollBar::getScrollPosition()
{
	double ret=0;
	if(available()) ret=getScrollPercent()*(fullSize-viewSize);
	return ret;
}

void ofScrollBar::setScrollPercent(double perc)
{
  perc=ofClamp(perc, 0, 1);
  if (vert) tab.relPos.y=perc*(tabRange-tab.h)+endPad;
	else tab.relPos.x=perc*(tabRange-tab.w)+endPad;
}

bool ofScrollBar::setScrollPosition(double newPos)
{
	bool ret=false;
	if(1){
		ret=true;
		if(vert){
			double pos=newPos*(tabRange-tab.h)/(fullSize-viewSize)+endPad;
			if(pos<endPad) pos=endPad+1;
			else if(pos+tab.h>h-(endPad+1)*2) pos=h-(endPad+1)*2-tab.h;
			tab.relPos.y=pos;
		}
		else {
			double pos=newPos*(tabRange-tab.w)/(fullSize-viewSize)+endPad;
			if(pos<endPad+1) pos=endPad+1;
			else if(pos+tab.w>w-endPad*2-2) pos=w-endPad*2-2-tab.w;
			tab.relPos.x=pos;
		}
	}
	return	ret;
}
	

void ofScrollBar::update(double percent)
{
	if (!vert) tab.w=percent*(tabRange-2);
	else tab.h=percent*(tabRange-2);
}
	
void ofScrollBar::update()
{
	if(!vert){
		if(tab.relPos.x<endPad+1) tab.relPos.x=endPad+1;
		else if(tab.relPos.x+tab.w>w-endPad-1) tab.relPos.x=w-endPad*2-tab.w-1;
	}
	else {
		if(tab.y<y+endPad+1) tab.relPos.y=endPad+1;
		else if(tab.y+tab.h>y+h-endPad-1) tab.relPos.y=h-endPad*2-tab.h-1;
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
