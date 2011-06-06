/*
 *  ofRadioButtons.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 4/13/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofRadioButtons.h"

void radioButton::draw(double _x, double _y)
{
	x=_x, y=_y;
	ofCircleShadow(x+r, y+r, r+7, .5);
	if(!bPressed&&bAvailable) ofSetColor(255, 255, 255);
	else if(!bPressed&&!bAvailable) ofSetColor(255, 255, 255,96);
	else ofSetColor(128, 128, 128);
	ofRaisedCircle(x+r, y+r, r, .2);
	if(bSelected){
		ofSetColor(32, 96, 192);
		ofRaisedCircle(x+r, y+r, r*.75, .2);
	}
}

void ofRadioButtons::setup(int num, double rad, ofDirection v, double spn)
{
	vert=(v==OF_VERT);
	if(vert) h=spn;
	else w=spn;
	span=spn/num+1;
	for (int i=0; i<num; i++) {
		buttons.push_back(rad);
	}
	if(buttons.size()) select(0);
}

bool ofRadioButtons::clickDown(int _x, int _y)
{
	bool ret=0;
	for (unsigned int i=0; i<buttons.size(); i++) {
		if(buttons[i].clickDown(_x, _y)){
			buttons[i].bSelected=true;
			iSelected=i;
			for (unsigned int j=0; j<buttons.size(); j++) {
				if(j!=i) buttons[j].bSelected=false;
			}
		}
	}
}

bool ofRadioButtons::clickUp()
{
	for (unsigned int i=0; i<buttons.size(); i++) {
		buttons[i].clickUp();
	}
}

void ofRadioButtons::draw(double _x, double _y, double spn)
{
	x=_x, y=_y;
	if(spn){
		span=spn;
	}
	for (unsigned int i=0; i<buttons.size(); i++) {
		if(vert) buttons[i].draw(x,y+(i)*span-buttons[i].h/2);
		else buttons[i].draw(x+(i)*span-buttons[i].w/2,y);
	}
}

void ofRadioButtons::select(int num)
{
	if (num>=0&&num<buttons.size()) {
		for (unsigned int j=0; j<buttons.size(); j++) {
			buttons[j].bSelected=false;
		}
		buttons[num].bSelected=true;
		iSelected=num;
	}
}

void ofRadioButtons::drawButton(int num, double _x, double _y)
{
	if(vert) buttons[num].draw(_x,_y);
	else buttons[num].draw(_x,_y);
}
