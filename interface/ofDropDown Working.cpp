/*
 *  ofDropDown.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 1/31/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofDropDown.h"

const char *asString(double i)
{
  	stringstream oss;
  	oss << i; oss.flush();
	return oss.str().c_str();
}

ofDropDown::ofDropDown():ofInterObj(){
	open=selected=false;
	deci=false;
	var=0;
	svar="";
	cursorPos=-1;
}

ofDropDown::ofDropDown(int _x, int _y,int _w,int _h,int low, int hi, int stps):ofInterObj(_x,_y,_w,_h){
	arial.loadFont("Arial.ttf");
	arial.setSize(10);
	steps=stps;
	var=0;
	open=selected=false;
	deci=false;
	svar="";
}

ofDropDown::~ofDropDown(){
	dds.clear();
	ddd.clear();
}

int ofDropDown::size(){
	return steps;
}

void ofDropDown::setup(int _x, int _y,int _w,int _h){
	arial.loadFont("Arial.ttf");
	arial.setSize(10);
	cSetup(_x, _y, _w, _h);
}

void ofDropDown::setRange(double low, double high, int stps){
	steps=stps;
	float maxWid=0;
	float maxHgt=0;
	if(!ddd.size()&&!dds.size())
		for(int i=0; i<steps; i++){
			ddd.push_back(double(low+(i)*((high-low)/((int)steps-1))));
			maxWid=max(maxWid,arial.stringWidth(asString(ddd[ddd.size()-1])));
			maxHgt=max(maxHgt,arial.stringHeight(asString(ddd[ddd.size()-1])));
		}
	w=maxWid+7;
	h=maxHgt+4;
}

void ofDropDown::setValue(string k)
{
	deci=false;
	if (!ddd.size()) {
		dds.push_back(k);
	}
	arial.setSize(10);
	int maxWid=max(w,double(arial.stringWidth(dds[dds.size()-1])));
	int maxHgt=max(h,double(arial.stringHeight(dds[dds.size()-1])));
	w=maxWid+7;
	h=maxHgt+4;
	steps=dds.size();
}

bool ofDropDown::passingClick(int _x,int _y){
	return ((!over(_x,_y)));
}

void ofDropDown::draw(){
	string vars;
	if(dds.size()&&!deci) vars=svar;
	else if ((var)>=0) vars=asString(var);
	float sHgt= arial.stringHeight(vars)/2;
	ofSetColor(0x8f8f8f);
	ofNoFill();
	ofEnableSmoothing();
	ofRoundBox(x-h/2-1,y-1,w+h+2,h+2,h/2+1);
	ofFill();
	ofDisableSmoothing();
	ofSetColor(0xECECEC);
	ofRoundBox(x-h/2,y,w+h,h,h/2);
	if(!open){
		ofSetColor(0, 0, 0);
		ofEnableSmoothing();
		ofNoFill();
		ofSetLineWidth(1);
		ofTriangle(x+w,y+h/2+2,x+w-4,y+h/2+2,x+w-2,y+3*h/4);
		ofTriangle(x+w,y+h/2-2,x+w-4,y+h/2-2,x+w-2,y+h/4);
		ofFill();
		ofDisableSmoothing();
		ofTriangle(x+w,y+h/2+2,x+w-4,y+h/2+2,x+w-2,y+3*h/4);
		ofTriangle(x+w,y+h/2-2,x+w-4,y+h/2-2,x+w-2,y+h/4);
		glColor3f(0,0,0);
		arial.drawString(vars, x,y+h-5);
	}
	else{
		ofSetColor(0xFCFCFC);
		ofRoundBox(x,y-5,w,h*(steps+1)+10,5);
		glColor3f(0,0,0);
		arial.drawString(svar, x,y+h-5);
		for (int i=0; i<steps; i++) {
			if(cursorPos!=i) ofSetColor(0,0,0);
			else {
				ofSetColor(100, 100, 100);
				ofRect(x, y+h*(cursorPos+1), w, h);
				ofSetColor(255,255,255);
			}
			if(dds.size()) arial.drawString(dds[i],x,y+(i+2)*h-5);
			else if(var>=0) arial.drawString(asString(ddd[i]),x,y+(i+2)*h-5);
		}
	}
}

void ofDropDown::drawShape(){
	if(!open){
		ofSetColor(0x8f8f8f);
		ofNoFill();
		ofEnableSmoothing();
		ofRoundBox(x-h/2-1,y-1,w+h+2,h+2,h/2+1);
		ofFill();
		ofDisableSmoothing();
		ofSetColor(0xECECEC);
		ofRoundBox(x-h/2,y,w+h,h,h/2);
		ofSetColor(0, 0, 0);
		ofEnableSmoothing();
		ofNoFill();
		ofSetLineWidth(1);
		ofTriangle(x+w,y+h/2+2,x+w-4,y+h/2+2,x+w-2,y+3*h/4);
		ofTriangle(x+w,y+h/2-2,x+w-4,y+h/2-2,x+w-2,y+h/4);
		ofFill();
		ofDisableSmoothing();
		ofTriangle(x+w,y+h/2+2,x+w-4,y+h/2+2,x+w-2,y+3*h/4);
		ofTriangle(x+w,y+h/2-2,x+w-4,y+h/2-2,x+w-2,y+h/4);
	}
}

bool ofDropDown::clickDown(int _x,int _y){
	bool ret=false;
	if (over(_x,_y)&&!open) {
		open=ret=true;
		selected=false;
	}
	else if(open&&_x>x&&_x<x+w&&_y>y&&_y<y+h*(steps+1)){
		for (int i=0; i<steps; i++) {
			if(_y>y+h*(i+1)&&_y<y+h*(i+2)&&dds.size()&&!deci){
				svar=dds[i];
				selected=true;
			}
			else if (_y>y+h*(i+1)&&_y<y+h*(i+2)&&var>=0) {
				var=ddd[i];
				selected=true;
			}
			open=ret=false;
		}
	}
	else {
		open=ret=false;
	}
	return ret;
}

void ofDropDown::motion(int _x, int _y)
{
	int newPos=-1;
	if(open&&_x>x&&_x<x+w&&_y>y&&_y<y+h*(steps+1))
		for (int i=0; i<steps; i++) {
			if(_y>y+h*(i+1)&&_y<y+h*(i+2))
				newPos=i;
		}
	else newPos=-1;
	if (newPos!=cursorPos) {
		cursorPos=newPos;
		cout << cursorPos <<endl;
	}
}
	
void ofDropDown::operator=(const ofDropDown & t)
{
	x=t.x;
	y=t.y;
	w=t.w;
	h=t.h;
	arial.loadFont("Arial.ttf");
	arial.setSize(10);
	bool deci;
	ddd.clear();
	for (unsigned int i=0; i<t.ddd.size(); i++) {
		ddd.push_back(t.ddd[i]);
	}
	dds.clear();
	for (unsigned int i=0; i<t.dds.size(); i++) {
		dds.push_back(t.dds[i]);
	}
	selected=t.selected;
	svar=t.svar;
	steps=t.steps;
	open=t.open;
	var=t.var;
	xdis=t.xdis;
	cursorPos=t.cursorPos;
}

