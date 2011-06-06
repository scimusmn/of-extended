/*
 *  ofShapes.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 1/6/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofShapes.h"

void drawBox(double x, double y, double width, double height, float r, float g, float b, float a)
{
	glColor4f(r,g,b,a);
  	glBegin(GL_POLYGON);
	glVertex2f(x, y);  // upper left
	glVertex2f(x, y + height);  // lower left
	glVertex2f(x + width, y + height);  // lower right
	glVertex2f(x + width, y);  // upper right
  	glEnd();
}

void shadeBox(double x, double y, double width, double height, float r,float g, float b, float perc)
{
	glColor3f(r,g,b);
  	glBegin(GL_POLYGON);
	glVertex2f(x, y);  // upper left
	glColor3f(r-perc*r,g-perc*g,b-perc*b);
	glVertex2f(x + width, y);  // upper right
	glVertex2f(x + width, y + height);  // lower right
	glVertex2f(x, y + height);  // lower left
  	glEnd();
}

void setShade(bool on,float perc){
	ofColor cur=ofGetStyle().color;
	if(!on) ofSetColor(cur);
	else glColor3f(cur.r/255.-perc, cur.g/255.-perc, cur.b/255.-perc);
}

void ofShadeBox(double x, double y, double width, double height, ofDirection d, float perc)
{
  	glBegin(GL_POLYGON);
	setShade(d==OF_UP||d==OF_LEFT, perc);
	glVertex2f(x, y);  // upper left
	setShade(d==OF_UP||d==OF_RIGHT,perc);
	glVertex2f(x + width, y);  // upper right
	setShade(d==OF_DOWN||d==OF_RIGHT,perc);
	glVertex2f(x + width, y + height);  // lower right
	setShade(d==OF_DOWN||d==OF_LEFT,perc);
	glVertex2f(x, y + height);  // lower left
  	glEnd();
}

void ofShade(double x, double y, double span, double length, ofDirection d, float start,bool black)
{
	float col=0;
	if(!black) col=1;
	if (d==OF_UP) shadeVer(x, y, length, -span, start, col,col,col,col,col,col);
	if (d==OF_DOWN) shadeVer(x, y, length, span, start, col,col,col,col,col,col);
	if (d==OF_LEFT) shadeHor(x, y, -span, length, start, col,col,col,col,col,col);
	if (d==OF_RIGHT) shadeHor(x, y, span, length, start, col,col,col,col,col,col);
}

void shadeHor(double x, double y, double width, double height,float strt, float r,float g, float b,float r1,float g1, float b1)
{
	glColor4f(r,g,b,strt);
  	glBegin(GL_POLYGON);
	glVertex2f(x, y + height);  // lower left
	glVertex2f(x, y);  // upper left
	glColor4f(r1,g1,b1,0);
	glVertex2f(x + width, y);  // upper right
	glVertex2f(x + width, y + height);  // lower right
  	glEnd();
}

void shadeVer(double x, double y, double width, double height,float start, float r,float g, float b,float rd,float gn, float bl)
{
	if (rd||gn||bl) {
		glColor4f(rd,gn,bl,0);
	}
	else{
		glColor4f(r,g,b,0);
	}
  	glBegin(GL_POLYGON);
	glVertex2f(x + width, y + height);  // lower right
	glVertex2f(x, y + height);  // lower left
	glColor4f(r,g,b,start);
	glVertex2f(x, y);  // upper left
	glVertex2f(x + width, y);  // upper right
  	glEnd();
}

void shadeBoxBottom(double x, double y, double width, double height, float r,float g, float b, float perc)
{
	glColor3f(r,g,b);
  	glBegin(GL_POLYGON);
	glVertex2f(x, y);  // upper left
	glVertex2f(x + width, y);  // upper right
	glColor3f(r-perc*r,g-perc*g,b-perc*b);
	glVertex2f(x + width, y + height);  // lower right
	glVertex2f(x, y + height);  // lower left
  	glEnd();
}

void shadeBoxTop(double x, double y, double width, double height, float r,float g, float b, float perc)
{
	glColor3f(r-perc*r,g-perc*g,b-perc*b);
  	glBegin(GL_POLYGON);
	glVertex2f(x, y);  // upper left
	glVertex2f(x + width, y);  // upper right
	glColor3f(r,g,b);
	glVertex2f(x + width, y + height);  // lower right
	glVertex2f(x, y + height);  // lower left
  	glEnd();
}

void shadeBoxSide(double x, double y, double width, double height, float r,float g, float b, float perc)
{
	glColor3f(r-perc*r,g-perc*g,b-perc*b);
  	glBegin(GL_POLYGON);
	glVertex2f(x, y + height);  // lower left
	glVertex2f(x, y);  // upper left
	glColor3f(r,g,b);
	glVertex2f(x + width, y);  // upper right
	glVertex2f(x + width, y + height);  // lower right
  	glEnd();
}

void shadeCircle(int x, int y, int rad, float r, float g, float b, float perc,bool overshade,int dir)
{
	const int NUM_DIVS = 60;
	glColor3f(r,g,b);
  	glBegin(GL_TRIANGLE_FAN);
  	glVertex2d(x,y);
  	glColor3f(r-perc*r,g-perc*g,b-perc*b);
	for ( int i = 0; i < NUM_DIVS; ++i )
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),
				   y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	glEnd();
	if (overshade) {
		glColor4f(r,g,b,1);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2d(x,y);
		//glColor3f(r-2*perc*r,g-2*perc*g,b-2*perc*b);
		for ( int i = 0; i < NUM_DIVS/2+1; ++i ){
			float perc2 =sin(i*2*M_PI/(NUM_DIVS-1))*perc;
			glColor4f(r-perc2*r,g-perc2*g,b-perc2*b,1);
			glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
		}
		glEnd();
		glColor4f(r,g,b,1);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2d(x,y);
		//glColor3f(r-2*perc*r,g-2*perc*g,b-2*perc*b);
		for ( int i = NUM_DIVS/2; i < NUM_DIVS; ++i ){
			float perc2 = -sin(i*2*M_PI/(NUM_DIVS-1))*perc;
			glColor4f(r+perc2*r,g+perc2*g,b+perc2*b,1);
			glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
		}
		glEnd();
	}
}

void ofRaisedCircle(int x, int y, int rad, float perc)
{
	ofColor k=ofGetStyle().color;
	float r=k.r/255.,g=k.g/255.,b=k.b/255.;
	const int NUM_DIVS = 60;
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x,y);
	for ( int i = 0; i < NUM_DIVS+1; ++i ){
		float perc2 =sin(i*2*M_PI/(NUM_DIVS-1))*perc;
		glColor3f(r-perc2*r,g-perc2*g,b-perc2*b);
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	}
	glEnd();
}
	
void shadeCircleSide(int x, int y, int rad, float r, float g, float b, float perc){
	int NUM_DIVS=30;
	
	glColor4f(r,g,b,1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x,y);
	//glColor3f(r-2*perc*r,g-2*perc*g,b-2*perc*b);
	for ( int i = 0; i < NUM_DIVS; ++i ){
		float perc2 = 0;
		if (cos(i*2*M_PI/(NUM_DIVS-1))<0) {
			perc2= cos(i*2*M_PI/(NUM_DIVS-1))*perc;
		}
		glColor4f(r+perc2*r,g+perc2*g,b+perc2*b,1);
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	}
	glEnd();
}

void shinyCircle(int x, int y, int rad, float r, float g, float b, float perc){
	const int NUM_DIVS = 60;
	glColor4f(r,g,b,1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x,y);
	//glColor3f(r-2*perc*r,g-2*perc*g,b-2*perc*b);
	for ( int i = 0; i < NUM_DIVS/2+1; ++i ){
		float perc2 =sin(i*2*M_PI/(NUM_DIVS-1))*perc;
		glColor4f(r-perc2*r,g-perc2*g,b-perc2*b,1);
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	}
	glEnd();
	glColor4f(r,g,b,1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x,y);
	//glColor3f(r-2*perc*r,g-2*perc*g,b-2*perc*b);
	for ( int i = NUM_DIVS/2; i < NUM_DIVS; ++i ){
		float perc2 = -sin(i*2*M_PI/(NUM_DIVS-1))*perc;
		glColor4f(r+perc2*r,g+perc2*g,b+perc2*b,1);
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	}
	glEnd();
	glColor4f(r,g,b,0);
  	glBegin(GL_TRIANGLE_FAN);
  	glVertex2d(x,y);
	for ( int i = NUM_DIVS/2; i < NUM_DIVS; ++i ){
		float perc2 =-sin(i*2*M_PI/(NUM_DIVS-1))/3;
		glColor4f(1,1,1,perc2);
		glVertex2d(x + (rad-.0*rad)*cos(i*2*M_PI/(NUM_DIVS-1)),y + (rad-.0*rad)*sin(i*2*M_PI/(NUM_DIVS-1)));
	}
	glEnd();
}

void shinyCircleInvert(int x, int y, int rad, float r, float g, float b, float perc){
	const int NUM_DIVS = 60;
	glColor4f(r,g,b,1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x,y);
	//glColor3f(r-2*perc*r,g-2*perc*g,b-2*perc*b);
	for ( int i = 0; i < NUM_DIVS/2+1; ++i ){
		float perc2 =-sin(i*2*M_PI/(NUM_DIVS-1))*perc;
		glColor4f(r-perc2*r,g-perc2*g,b-perc2*b,1);
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	}
	glEnd();
	glColor4f(r,g,b,1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x,y);
	//glColor3f(r-2*perc*r,g-2*perc*g,b-2*perc*b);
	for ( int i = NUM_DIVS/2; i < NUM_DIVS; ++i ){
		float perc2 = sin(i*2*M_PI/(NUM_DIVS-1))*perc;
		glColor4f(r+perc2*r,g+perc2*g,b+perc2*b,1);
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	}
	glEnd();
	glColor4f(r,g,b,0);
  	glBegin(GL_TRIANGLE_FAN);
  	glVertex2d(x,y);
	for ( int i = NUM_DIVS/2; i < NUM_DIVS; ++i ){
		float perc2 =-sin(i*2*M_PI/(NUM_DIVS-1))/3;
		glColor4f(0,0,0,perc2);
		glVertex2d(x + (rad-.0*rad)*cos(i*2*M_PI/(NUM_DIVS-1)),y + (rad-.0*rad)*sin(i*2*M_PI/(NUM_DIVS-1)));
	}
	glEnd();
}

static bool bShade=true;

void roundedBox(double x, double y, double width, double height,double rad, float r,float g, float b, float perc)
{
	shadeCircle(x+width-rad,y+height-rad,rad,r,g,b,perc,true);
	shadeCircle(x+rad,y+height-rad,rad,r,g,b,perc,true);
	shinyCircle(x+width-rad,y+rad,rad,r,g,b,perc);
	shinyCircle(x+rad,y+rad,rad,r,g,b,perc);
	drawBox(x+rad,y+rad,width-rad*2,height-rad*2,r,g,b);
	drawBox(x,y+rad,rad,height-rad*2,r,g,b);
	drawBox(x+width,y+rad,-rad,height-rad*2,r,g,b);
	shadeBoxTop(x+rad,y,width-rad*2,rad,r,g,b,-perc);
	shadeVer(x+rad,y+rad*.0,width-rad*2,rad*1,.33,1,1,1,r,g,b);
	shadeBoxBottom(x+rad,y+height-rad,width-rad*2,rad,r,g,b,perc);
	//shadeVer(x+rad,y+height,width-rad*2,-rad,.5);
}

void ofShadeVertically(double x, double y, double width, double height,float start, bool origColor=false, float perc=.2)
{
	ofColor col=ofGetStyle().color;
	if (origColor) {
		glColor4f(col.r,col.g,col.b,0);
	}
	else{
		glColor4f(0,0,0,0);
	}
  	glBegin(GL_POLYGON);
	glVertex2f(x + width, y + height);  // lower right
	glVertex2f(x, y + height);  // lower left
	(origColor)? glColor4f(col.r-perc,col.g-perc,col.b-perc,start):glColor4f(0, 0, 0, start);
	glVertex2f(x, y);  // upper left
	glVertex2f(x + width, y);  // upper right
  	glEnd();
}

void ofShadeCircle(int x, int y, int rad, float perc)
{
	const int NUM_DIVS = 60;
	glColor4f(0,0,0,0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2d(x,y);
	for ( int i = 0; i < NUM_DIVS/2+1; ++i ){
		float perc2 =sin(i*2*M_PI/(NUM_DIVS-1))*perc;
		glColor4f(0,0,0,perc2);
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	}
	glEnd();
}

void ofRoundBox(double x, double y, double w, double h,double rad,double shade)
{
	bool fill=true;
	glBegin((fill)?GL_QUAD_STRIP:GL_LINE_LOOP);
	ofColor cur=ofGetStyle().color;
	for ( int i = 0; i <= 90; ++i ){
		if(fill){
			ofSetColor(cur);
			glVertex2d(x+w-rad,y+h-rad);
			ofSetColor(cur-shade*255);
		}
		glVertex2d(x+w-rad+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
	}
	if(fill){
		ofSetColor(cur);
		glVertex2d(x+rad,y+h-rad);
		ofSetColor(cur-shade*255);
		glVertex2d(x+rad,y+h);
	}
	for ( int i = 90; i <= 180; ++i ){
		if(fill){
			ofSetColor(cur);
			glVertex2d(x+rad,y+h-rad);
			ofSetColor(cur-shade*cos(((i-90)*2)*M_PI/(180))*255);
		}
		glVertex2d(x+rad+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
	}
	if(fill){
		ofSetColor(cur);
		glVertex2d(x+rad,y+rad);
		ofSetColor(cur+shade*255);
		glVertex2d(x,y+rad);
	}
	for ( int i = 180; i <= 270; ++i ){
		if(fill){
			ofSetColor(cur);
			glVertex2d(x+rad,y+rad);
			ofSetColor(cur+shade*255);
		}
		glVertex2d(x+rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
	}
	if(fill){
		ofSetColor(cur);
		glVertex2d(x+w-rad,y+rad);
		ofSetColor(cur+shade*255);
		glVertex2d(x+w-rad,y);
	}
	for ( int i = 270; i <= 361; ++i ){
		if(fill){
			ofSetColor(cur);
			glVertex2d(x+w-rad,y+rad);
			ofSetColor(cur-shade*cos((i*2)*M_PI/(180))*255);
		}
		glVertex2d(x+w-rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
	}
	if (fill) {
		ofSetColor(cur);
		glVertex2d(x+w-rad,y+h-rad);
		ofSetColor(cur-shade*255);
		glVertex2d(x+w,y+h-rad);
		glEnd();
		ofSetColor(cur);
		glBegin(GL_QUADS);
		glVertex2d(x+w-rad,y+rad);
		glVertex2d(x+w-rad,y+h-rad);
		glVertex2d(x+rad,y+h-rad);
		glVertex2d(x+rad,y+rad);
		glEnd();
	}
	glEnd();
}

void roundedBoxSide(double x, double y, double width, double height,double rad, float r,float g, float b, float perc)
{
	shadeCircle(x+width-rad,y+height-rad,rad,r,g,b,perc,true);
	shadeCircleSide(x+rad,y+height-rad,rad,r,g,b,perc);
	shadeCircleSide(x+width-rad,y+rad,rad,r,g,b,perc);
	shadeCircleSide(x+rad,y+rad,rad,r,g,b,perc);
	drawBox(x+rad,y+rad,width-rad*2,height-rad*2,r,g,b);
	drawBox(x,y+rad,rad,height-rad*2,r,g,b);
	drawBox(x+width,y+rad,-rad,height-rad*2,r,g,b);
	shadeBoxTop(x+rad,y,width-rad*2,rad,r,g,b,-perc);
	shadeHor(x,y+rad,rad*1,height-rad*2,.33,0,0,0,r,g,b);
	shadeBoxBottom(x+rad,y+height-rad,width-rad*2,rad,r,g,b,perc);
	//shadeVer(x+rad,y+height,width-rad*2,-rad,.5);
}

void roundedBoxInvert(double x, double y, double width, double height,double rad, float r,float g, float b, float perc){
	shadeCircle(x+width-rad,y+height-rad,rad,r,g,b,perc,true);
	shadeCircle(x+rad,y+height-rad,rad,r,g,b,perc,true);
	shinyCircleInvert(x+width-rad,y+rad,rad,r,g,b,perc);
	shinyCircleInvert(x+rad,y+rad,rad,r,g,b,perc);
	drawBox(x+rad,y+rad,width-rad*2,height-rad*2,r,g,b);
	drawBox(x,y+rad,rad,height-rad*2,r,g,b);
	drawBox(x+width,y+rad,-rad,height-rad*2,r,g,b);
	shadeBoxBottom(x+rad,y+height-rad,width-rad*2,rad,r,g,b,-perc);
	//shadeVer(x+rad,y+rad*.0,width-rad*2,rad*1,.33,0,0,0,r,g,b);
	shadeBoxTop(x+rad,y,width-rad*2,rad,r,g,b,perc);
}

void darkCircleSection(int x, int y, int rad,float strt, float end,float a){
	const int NUM_DIVS = 60;
	glColor4f(0,0,0,a);
  	glBegin(GL_TRIANGLE_FAN);
  	glVertex2d(x,y);
	glColor4f(0,0,0,0);
	for ( int i = NUM_DIVS*strt; i < NUM_DIVS*end; ++i )
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),
				   y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	glEnd();}

void roundedShade(double x, double y, double width, double height,double rad,int wid){
	shadeVer(x+rad,y+rad,width-rad*2,-wid-rad);
	shadeVer(x+rad,y-rad+height,width-rad*2,wid+rad);
	shadeHor(x+rad,y+rad,-(wid+rad),height-rad*2);
	shadeHor(x-rad+width,y+rad,wid+rad,height-rad*2);
	darkCircleSection(x+rad,y+rad,rad+wid,.5,.75);
	darkCircleSection(x-rad+width,y+rad,rad+wid,.75,1);
	darkCircleSection(x+rad,y+height-rad,rad+wid,.25,.5);
	darkCircleSection(x+width-rad,y+height-rad,rad+wid,0,.25);
}

void roundedShadow(double x, double y, double w, double h,double rad,double strt){
	
	glBegin(GL_QUAD_STRIP);
	for ( int i = 270; i <= 361; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,0);
		glVertex2d(x+w-rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+w-rad,y+rad);
	}
	for ( int i = 0; i <= 90; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,0);
		glVertex2d(x+w-rad+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+w-rad,y+h-rad);
	}
	for ( int i = 90; i <= 180; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,0);
		glVertex2d(x+rad+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+rad,y+h-rad);
	}
	for ( int i = 180; i <= 270; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,0);
		glVertex2d(x+rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+rad,y+rad);
	}
	glColor4f(0,0,0,0);
	glVertex2d(x+w-rad,y);
	glColor4f(0,0,0,strt);
	glVertex2d(x+w-rad,y+rad);	
	glEnd();
	glBegin(GL_QUADS);
	glColor4f(0,0,0,strt);
	glVertex2d(x+w-rad,y+rad);
	glVertex2d(x+w-rad,y+h-rad);
	glVertex2d(x+rad,y+h-rad);
	glVertex2d(x+rad,y+rad);
	glEnd();
}

void ofRoundShadow(double x, double y, double w, double h,double rad,double strt){
	
	glBegin(GL_QUAD_STRIP);
	for ( int i = 270; i <= 361; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,0);
		glVertex2d(x+w-rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+w-rad,y+rad);
	}
	for ( int i = 0; i <= 90; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,0);
		glVertex2d(x+w-rad+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+w-rad,y+h-rad);
	}
	for ( int i = 90; i <= 180; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,0);
		glVertex2d(x+rad+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+rad,y+h-rad);
	}
	for ( int i = 180; i <= 270; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,0);
		glVertex2d(x+rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+rad,y+rad);
	}
	glColor4f(0,0,0,0);
	glVertex2d(x+w-rad,y);
	glColor4f(0,0,0,strt);
	glVertex2d(x+w-rad,y+rad);	
	glEnd();
	glBegin(GL_QUADS);
	glColor4f(0,0,0,strt);
	glVertex2d(x+w-rad,y+rad);
	glVertex2d(x+w-rad,y+h-rad);
	glVertex2d(x+rad,y+h-rad);
	glVertex2d(x+rad,y+rad);
	glEnd();
}

bool fill=true;

void ofRoundShade(double x, double y, double w, double h,double rad,float start,bool fadeOut){
	float strt,end;
	if (fadeOut) {
		strt=start;
		end=0;
	}
	else {
		end=start;
		strt=0;
	}

	glBegin(GL_QUAD_STRIP);
	for ( int i = 270; i <= 361; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,end);
		glVertex2d(x+w-rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+w-rad,y+rad);
	}
	for ( int i = 0; i <= 90; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,end);
		glVertex2d(x+w-rad+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+w-rad,y+h-rad);
	}
	for ( int i = 90; i <= 180; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,end);
		glVertex2d(x+rad+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+rad,y+h-rad);
	}
	for ( int i = 180; i <= 270; ++i ){
		//float perc2 = shBot*cos(i*M_PI/(180))-shTop*sin(i*M_PI/(180));
		glColor4f(0,0,0,end);
		glVertex2d(x+rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
		glColor4f(0,0,0,strt);
		glVertex2f(x+rad,y+rad);
	}
	glColor4f(0,0,0,end);
	glVertex2d(x+w-rad,y);
	glColor4f(0,0,0,strt);
	glVertex2d(x+w-rad,y+rad);	
	glEnd();
	glBegin(GL_QUADS);
	glColor4f(0,0,0,strt);
	glVertex2d(x+w-rad,y+rad);
	glVertex2d(x+w-rad,y+h-rad);
	glVertex2d(x+rad,y+h-rad);
	glVertex2d(x+rad,y+rad);
	glEnd();
}

void ofRoundShape(double x, double y, double w, double h,double rad,bool fill){
	glBegin((fill)?GL_TRIANGLE_FAN:GL_LINE_LOOP);
	ofColor cur=ofGetStyle().color;
	float shade=.2;
	for ( int i = 0; i <= 90; ++i ){
		
		glVertex2d(x+w-rad+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
	}
	for ( int i = 90; i <= 180; ++i ){
		
		glVertex2d(x+rad+rad*cos(i*M_PI/(180)),y+h-rad+rad*sin(i*M_PI/(180)));
	}
	for ( int i = 180; i <= 270; ++i ){
		
		glVertex2d(x+rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
	}
	for ( int i = 270; i <= 361; ++i ){
		
		glVertex2d(x+w-rad+rad*cos(i*M_PI/(180)),y+rad+rad*sin(i*M_PI/(180)));
	}
	glEnd();
	
}

void drawCircle(int x, int y, int rad, float r, float g, float b,float a)
{
	const int NUM_DIVS = 40;
	glColor4f(r,g,b,a);
  	glBegin(GL_TRIANGLE_FAN);
  	glVertex2d(x,y);
	for ( int i = 0; i < NUM_DIVS; ++i )
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),
				   y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	glEnd();}

void drawLine(int sx,int sy, int fx, int fy,float r, float g, float b,float wid)
{
	glLineWidth(wid);
	glColor3f(r,g,b);
	glBegin(GL_LINES);
	glVertex2d(sx,sy);
	glVertex2d(fx,fy);
	glEnd();
}

void drawCircleSlice(int x, int y, int rad,int rad1, float r, float g, float b,float r1, float g1, float b1,float a,float a1,float strt,float end)
{
	const int NUM_DIVS = 40;
	glLineWidth(6.0);
  	glBegin(GL_LINES);
  	//glVertex2d(x,y);
	for ( int i = NUM_DIVS*strt; i < NUM_DIVS*end; ++i ){
		glColor4f(r1,g1,b1,a1);
		glVertex2d(x + rad1*cos(i*2*M_PI/(NUM_DIVS-1)),
				   y + rad1*sin(i*2*M_PI/(NUM_DIVS-1)));
		glColor4f(r,g,b,a);
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),
				   y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	}
	glEnd();}

void constrainCircleSlice(int x, int y, int rad,int rad1, float r, float g, float b,float a,float a1,int xint, int yint, int w, int h)
{
	const int NUM_DIVS = 160;
	glLineWidth((float)6.0);
  	glBegin(GL_LINES);
  	//glVertex2d(x,y);
	for ( int i = 0; i < NUM_DIVS; ++i ){
		glColor4f(r,g,b,a1);
		if (x + rad*cos(i*2*M_PI/(NUM_DIVS-1))>xint+1&&x + rad*cos(i*2*M_PI/(NUM_DIVS-1))<xint+w-1&&\
			y + rad*sin(i*2*M_PI/(NUM_DIVS-1))>yint+1&&y + rad*sin(i*2*M_PI/(NUM_DIVS-1))<yint+h-1&&\
			x + rad1*cos(i*2*M_PI/(NUM_DIVS-1))>xint+1&&x + rad1*cos(i*2*M_PI/(NUM_DIVS-1))<xint+w-1&&\
			y + rad1*sin(i*2*M_PI/(NUM_DIVS-1))>yint+1&&y + rad1*sin(i*2*M_PI/(NUM_DIVS-1))<yint+h-1) {
			glVertex2d(x + rad1*cos(i*2*M_PI/(NUM_DIVS-1)),
					   y + rad1*sin(i*2*M_PI/(NUM_DIVS-1)));
			glColor4f(r,g,b,a);
			glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),
					   y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
		}
	}
	glEnd();
}

void drawSideCircle(int x, int y, int rad, float r, float g, float b,float a, int side)
{
	const int NUM_DIVS = 40;
	glColor4f(r,g,b,a);
  	glBegin(GL_TRIANGLE_FAN);
  	glVertex2d(x,y);
	for ( int i = NUM_DIVS/4+NUM_DIVS/2*side-2; i < 3*NUM_DIVS/4+NUM_DIVS/2*side; ++i )
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)),
				   y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
	glEnd();}

void shadeSideCircle(int x, int y, int rad,float a,int side, float r, float g, float b)
{
	const int NUM_DIVS = 40;
	glColor4f(r,g,b,0);
  	glBegin(GL_TRIANGLE_FAN);
  	glVertex2d(x,y);
	for ( int i = NUM_DIVS/4+NUM_DIVS/2*side-2; i < 3*NUM_DIVS/4+NUM_DIVS/2*side; ++i ){
		float perc2;
		if(side) perc2 =cos(i*2*M_PI/(NUM_DIVS-1))/3;
		else perc2 =-cos(i*2*M_PI/(NUM_DIVS-1))/3;
		glColor4f(r,g,b,a*perc2);
		glVertex2d(x + (rad-.0*rad)*cos(i*2*M_PI/(NUM_DIVS-1)),y + (rad-.0*rad)*sin(i*2*M_PI/(NUM_DIVS-1)));
	}
	glEnd();
}

void shine(double x, double y, double width, double height,double rad,float a,float c)
{
	drawSideCircle(x+rad,y+rad,rad,c,c,c,a,1);
	drawSideCircle(x-rad+width,y+rad,rad,c,c,c,a);
	drawBox(x+rad,y,width-2*rad,height,c,c,c,a);
}

void shinyBox(double x, double y, double width, double height,double rad, float r,float g, float b, float perc,float shn)
{
	roundedBox(x,y,width,height,rad,r,g,b,perc);
	shadeSideCircle(x+rad,y+rad,rad,1);
	shadeSideCircle(x-rad+width,y+rad,rad,1,1);
	shine(x+.015*width,y+.1*height,width-.03*width,.3*height,.15*height,shn);
}



void shadeBoxCenter(double x, double y, double width, double height, float r,float g, float b, float perc)
{
  	glBegin(GL_POLYGON);
	glColor3f(r-perc*r,g-perc*g,b-perc*b);
	glVertex2f(x, y);  // upper left
	glVertex2f(x + width, y);  // upper right
	glColor3f(r,g,b);
	glVertex2f(x + width, y + height/2);  // middle right
	glVertex2f(x, y + height/2);  // middle right
	glEnd();
  	glBegin(GL_POLYGON);
	glColor3f(r-perc*r,g-perc*g,b-perc*b);
	glVertex2f(x + width, y + height);  // lower right
	glVertex2f(x, y + height);  // lower left
	glColor3f(r,g,b);
	glVertex2f(x, y + height/2);  // middle left
	glVertex2f(x+width, y + height/2);  // middle left
  	glEnd();
}

void ofCircleShadow(double x, double y, double rad,double shade){
	const int NUM_DIVS = 40;
	glColor4f(0,0,0,shade);
  	glBegin(GL_QUAD_STRIP);
  	glVertex2d(x,y);
	for ( int i = 0; i < NUM_DIVS; ++i ){
		glColor4f(0,0,0,0);
		glVertex2d(x + rad*cos(i*2*M_PI/(NUM_DIVS-1)), y + rad*sin(i*2*M_PI/(NUM_DIVS-1)));
		glColor4f(0,0,0,shade);
		glVertex2d(x,y);
	}
	glEnd();
}

void ofRing(double x, double y, double ir, double oR){
	glBegin(GL_QUAD_STRIP);
	for ( int i = 0; i < 361; i++ ){
		glVertex2d(x+ir*cos(i*M_PI/(180)),y+ir*sin(i*M_PI/(180)));
		glVertex2d(x+oR*cos(i*M_PI/(180)),y+oR*sin(i*M_PI/(180)));
	}
	glEnd();
}

void ofRingSegment(double x, double y, double ir, double oR, double startDeg, double finishDeg){
	glBegin(GL_QUAD_STRIP);
	for ( int i = startDeg; i < finishDeg; i++ ){
		glVertex2d(x+ir*cos(i*M_PI/(180)),y+ir*sin(i*M_PI/(180)));
		glVertex2d(x+oR*cos(i*M_PI/(180)),y+oR*sin(i*M_PI/(180)));
	}
	glEnd();
}

numberBar::numberBar(double size){
	w=size,h=4.*size;
}
void numberBar::draw(double x_, double y_, bool vert){
	x=x_, y=y_;
	if(vert) ofRoundBox(x, y, w, h, w/2, .1);
	else ofRoundBox(x,y, h, w, w/2, .1);
}

numberTemplate::numberTemplate(double size){
	w=6*size;
	h=11*size;
	
	for (int i=0; i<7; i++) {
		temp.push_back(numberBar(size));
	}
	
}

numberTemplate::~numberTemplate(){
	temp.clear();
}

static int TEMPLATE_NUMS[10][7]= {{1,1,1,0,1,1,1},\
	{0,0,1,0,0,1,0},\
	{1,0,1,1,1,0,1},\
	{1,0,1,1,0,1,1},\
	{0,1,1,1,0,1,0},\
	{1,1,0,1,0,1,1},\
	{1,1,0,1,1,1,1},\
	{1,0,1,0,0,1,0},\
	{1,1,1,1,1,1,1},\
	{1,1,1,1,0,1,1}};

void numberTemplate::draw(double _x, double _y, int num){
	x=_x, y=_y;
	ofColor	cur=ofGetStyle().color;
	for (int i=0; i<7; i++) {
		if(!TEMPLATE_NUMS[num][i]) ofSetColor(32, 32, 32);
		else ofSetColor(cur);
		drawBar(i);
	}
	ofSetColor(cur);
}

void numberTemplate::drawBar(int barNum)
{
	double wid=temp[0].w;
	double hgt=temp[0].h;
	temp[barNum].draw((barNum==1||barNum==4)?x:(barNum==2||barNum==5)?x+wid+hgt:x+wid,\
					  (barNum==0)?y:(barNum==1||barNum==2)?y+wid:(barNum==6)?y+2*wid+2*hgt:(barNum==3)?y+wid+hgt:y+2*wid+hgt, \
				   !(barNum==0||barNum==3||barNum==6));
}

digitDisplay::digitDisplay(double width, int numDigits){
	size=width/(10*numDigits);
	for (int i=0; i<numDigits; i++) {
		numTemp.push_back(numberTemplate(size));
	}
	w=width;
	h=numTemp[numDigits-1].h;
}

void digitDisplay::setup(double width, int numDigits){
	size=width/(10*numDigits);
	for (int i=0; i<numDigits; i++) {
		numTemp.push_back(numberTemplate(size));
	}
	w=width;
	h=numTemp[numDigits-1].h;
}


void digitDisplay::draw(string k, double _x, double _y)
{
	x=_x,y=_y;
	double dx=0;
	int offset=0;
	for (unsigned int i=0; i<k.length(); i++) {
		if(k[i]>='0'&&k[i]<='9'){
			numTemp[i-offset].draw(x+dx,y,k[i]-'0');
			dx+=size*8;
		}
		else if(k[i]==':'){
			offset++;
			dx+=size*2;
			ofCircle(x+dx-size*2, y+7*h/8, size);
			ofCircle(x+dx-size*2, y+3*h/8, size);
		}
		else if(k[i]=='.'){
			offset++;
			dx+=size*2;
			ofCircle(x+dx-size*2, y+7*h/8, size);
		}
	}
	w=dx;
}
