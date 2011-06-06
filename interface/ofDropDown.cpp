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
	curPos=0;
	arial.loadFont("Arial.ttf");
	open=selected=bOver=false;
	deci=false;
	var=0;
	svar="";
	cursorPos=-1;
	nDisp=0;
	bAutoAdj=true;
}

ofDropDown::ofDropDown(int _x, int _y,int _w,int _h,int low, int hi, int stps):ofInterObj(_x,_y,_w,_h){
	arial.loadFont("Arial.ttf");
	arial.setSize(10);
	steps=stps;
	var=0;
	open=selected=false;
	deci=false;
	svar="";
	nDisp=0;
}

ofDropDown::ofDropDown(xmlParse * xml):ofInterObj(){
	curPos=0;
	arial.loadFont("Arial.ttf");
	arial.setSize(10);
	open=selected=bOver=false;
	deci=false;
	nDisp=0;
	cursorPos=-1;
	int ddhigh=0;
	int ddlow=0;
	int numSteps=0;
	map<string,int> list;
	list["ddhigh"]=0;
	list["ddlow"]=1;
	list["dds"]=2;
	list["ddsteps"]=3;
	for(int i=0;i<xml->size();i++){
		string * node=xml->getSubnode(i);
		switch (list.find(node[0])->second) {
			case 0:
				ddhigh=atoi(node[1].c_str());
				break;
			case 1:
				ddlow=atoi(node[1].c_str());
				break;
			case 2:
				setValue(node[1]);
				break;
			case 3:
				numSteps=atoi(node[1].c_str());
				break;
			default:
				break;
		}
	}
	if (ddhigh||ddlow) {
		if(!numSteps) numSteps=11;
		setRange(ddlow, ddhigh, numSteps);
	}
}

ofDropDown::ofDropDown(ofTag xml):ofInterObj(){
	curPos=0;
	arial.loadFont("Arial.ttf");
	arial.setSize(10);
	open=selected=bOver=false;
	deci=false;
	nDisp=0;
	cursorPos=-1;
	int ddhigh=0;
	int ddlow=0;
	int numSteps=0;
	string sel;
	map<string,int> list;
	list["ddhigh"]=0;
	list["ddlow"]=1;
	list["dds"]=2;
	list["ddsteps"]=3;
	list["selected"]=4;
	for(int i=0;i<xml.size();i++){
		string node[2]={xml[i].getLabel(),xml[i].getValue()};
		switch (list.find(node[0])->second) {
			case 0:
				ddhigh=atoi(node[1].c_str());
				break;
			case 1:
				ddlow=atoi(node[1].c_str());
				break;
			case 2:
				setValue(node[1]);
				break;
			case 3:
				numSteps=atoi(node[1].c_str());
				break;
			case 4:
				sel=node[1];
				break;
			default:
				break;
		}
	}
	if (ddhigh||ddlow) {
		if(!numSteps) numSteps=11;
		setRange(ddlow, ddhigh, numSteps);
	}
	if(sel.length()) setSelected(sel);
}

ofDropDown::~ofDropDown(){
	dds.clear();
	ddd.clear();
}

int ofDropDown::size(){
	return values.size();
}

void ofDropDown::setup(int _x, int _y,int _w,int _h){
	nDisp=0;
	arial.loadFont("Arial.ttf");
	arial.setSize(10);
	cSetup(_x, _y, _w, _h);
}

void ofDropDown::setTextSize(int size){
	arial.setSize(size);
}

void ofDropDown::setRange(double low, double high, int stps){
	steps=stps;
	float maxWid=0;
	float maxHgt=0;
	if(!values.size())
		for(int i=0; i<steps; i++){
			values.push_back(asString(low+(i)*((high-low)/((int)steps-1))));
		}
	adjustSizeToStrings();
}

void ofDropDown::setValue(string k)
{
	deci=false;
	int cur=values.size();
	values.push_back(k);
	adjustSizeToStrings();
	steps=values.size();
}

void ofDropDown::adjustSizeToStrings()
{
	float tempWid=0, tempHgt=0;
	for (unsigned int i=0; i<values.size(); i++) {
		tempWid=max(tempWid, arial.stringWidth(values[i]));
		tempHgt=max(tempHgt, arial.stringHeight(values[i]));
	}
	h=tempHgt+4;
	w=tempWid+7+h;
}

bool ofDropDown::passingClick(int _x,int _y){
	return (!over(_x,_y)&&!open);
}

void ofDropDown::draw(double _x, double _y)
{
	x=_x;
	y=_y;
	draw();
}

void ofDropDown::draw(){
	string vars;
	if(values.size()) vars=values[curPos];
	float sHgt= arial.stringHeight(vars)/2;
	ofSetColor(0x8f8f8f);
	ofNoFill();
	ofEnableSmoothing();
	ofRoundBox(x-1,y-1,w+2,h+2,h/2+1);
	ofFill();
	ofDisableSmoothing();
	ofSetColor(0xECECEC);
	ofRoundBox(x,y,w,h,h/2);
	int textX=x+h/2;
	if(!open){
		int triX=x+w-h/2;
		ofSetColor(0, 0, 0);
		ofEnableSmoothing();
		ofNoFill();
		ofSetLineWidth(1);
		ofTriangle(triX,y+h/2+2,triX-4,y+h/2+2,triX-2,y+3*h/4);
		ofTriangle(triX,y+h/2-2,triX-4,y+h/2-2,triX-2,y+h/4);
		ofFill();
		ofDisableSmoothing();
		ofTriangle(triX,y+h/2+2,triX-4,y+h/2+2,triX-2,y+3*h/4);
		ofTriangle(triX,y+h/2-2,triX-4,y+h/2-2,triX-2,y+h/4);
		glColor3f(0,0,0);
		arial.drawString(vars, textX,y+h-5);
	}
	else{
		ofSetColor(0xFCFCFC);
		int yDisp=(curPos>=nDisp&&curPos<nDisp+values.size()%10)?curPos%10:0;
		if(y-5<h*curPos||!bAutoAdj) yDisp=0;
		steps=values.size();
		if(bOver=(steps>11)){
			steps=min(steps-nDisp, 10);
		}
		ofRoundBox(x+h/2,y-5-yDisp*h,w-h,h*((bOver)?steps+2:steps)+10,5);
		glColor3f(0,0,0);
		//arial.drawString(vars, x,y+h-5);
		for (int i=0; i<steps; i++) {
			if(cursorPos!=i) ofSetColor(0,0,0);
			else {
				ofSetColor(100, 100, 100);
				ofRect(x, y+h*(cursorPos-yDisp), w, h);
				ofSetColor(255,255,255);
			}
			arial.drawString(values[i+nDisp],textX,y+(i+1-yDisp)*h-5);
		}
		if(bOver){
			ofSetLineWidth(1);
			ofLine(x+2, y+(steps-yDisp)*h, x+w-2, y+(steps-yDisp)*h);
			if(nDisp>0) ofSetColor(0, 0, 0);
			else ofSetColor(128,128,128);
			arial.drawString("previous page",textX,y+(steps+1-yDisp)*h-5);
			if(nDisp<values.size()-10) ofSetColor(0, 0, 0);
			else ofSetColor(128,128,128);
			arial.drawString("next page",textX,y+(steps+2-yDisp)*h-5);
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
		int triX=x+w-h/2;
		ofTriangle(triX,y+h/2+2,triX-4,y+h/2+2,triX-2,y+3*h/4);
		ofTriangle(triX,y+h/2-2,triX-4,y+h/2-2,triX-2,y+h/4);
		ofFill();
		ofDisableSmoothing();
		ofTriangle(triX,y+h/2+2,triX-4,y+h/2+2,triX-2,y+3*h/4);
		ofTriangle(triX,y+h/2-2,triX-4,y+h/2-2,triX-2,y+h/4);
	}
}

bool ofDropDown::clickDown(int _x,int _y){
	bool ret=false;
	//cout << "here" << endl;
	int yDisp=(curPos>=nDisp&&curPos<nDisp+values.size()%10)?curPos%10:0;
	if (over(_x,_y)&&!open) {
		open=ret=true;
		selected=false;
	}
	else if(open&&_x>x&&_x<x+w&&_y>y-h*yDisp&&_y<y+h*(steps+2-yDisp)){
		if(y-5<h*curPos||!bAutoAdj) yDisp=0;
		for (int i=0; i<steps; i++) {
			if(_y>y-h*yDisp&&_y<y+h*(steps-yDisp)){
				if(_y>y+h*(i-yDisp)&&_y<y+h*(i+1-yDisp)){
					cout << "and here" <<endl;
					curPos=i+nDisp;
					selected=true;
				}
				open=ret=false;
				if (selected) {
					break;
				}
			}
		}
		if(values.size()>10&&_y>y+h*(steps-yDisp)&&_y<y+h*(steps+1-yDisp)&&nDisp>=10){
			nDisp-=10;
		}
		else if(values.size()>10&&_y>y+h*(steps+1-yDisp)&&_y<y+h*(steps+2-yDisp)&&nDisp<=values.size()-values.size()%10-10){
			nDisp+=10;
		}
	}
	else {
		open=ret=false;
	}
	ret|=open;
	return ret;
}

bool ofDropDown::justSelected()
{
	bool ret=selected;
	selected=false;
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
	arial.setSize((t.arial.point));
	bool deci;
	values=t.values;
	ddd=t.ddd;
	dds=t.dds;
	selected=t.selected;
	svar=t.svar;
	steps=t.steps;
	open=t.open;
	var=t.var;
	xdis=t.xdis;
	cursorPos=t.cursorPos;
	curPos=t.curPos;
	nDisp=t.nDisp;
}

double ofDropDown::getValue()
{
	return atof(values[curPos].c_str());
}

int ofDropDown::getChoiceNumber()
{
	return curPos;
}

string ofDropDown::getString()
{
	return values[curPos];
}

void ofDropDown::setSelected(string comp)
{
	for (unsigned int i=0; i<values.size(); i++) {
		if (!comp.compare(values[i])) {
			curPos=i;
		}
	}
}