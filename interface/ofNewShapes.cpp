/*
 *  ofNewShapes.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 10/17/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofNewShapes.h"


extern float	drawMode;
double depthVal=0;
int lghtAng=225;

double shDk=.5;

void ofRaised(double pop)
{
  depthVal=pop;
}

void ofFlat()
{
  depthVal=0;
}

void ofLightSource(int deg){
  lghtAng=deg;
}

int ofCurrentLight(){
  return lghtAng;
}

void ofSetShadowDarkness(double depth)
{
  shDk=depth;
}

void shadeHor(double x, double y, double width, double height,float strt)
{
  ofColor k = ofGetStyle().color;
	ofSetColor(k.opacity(strt));
  glBegin(GL_POLYGON);
	glVertex2f(x, y + height);  // lower left
	glVertex2f(x, y);  // upper left
	ofSetColor(k.opacity(0));
	glVertex2f(x + width, y);  // upper right
	glVertex2f(x + width, y + height);  // lower right
  glEnd();
}

void shadeVer(double x, double y, double width, double height,float start)
{
  ofColor k = ofGetStyle().color;
  ofSetColor(k.opacity(0));
  glBegin(GL_POLYGON);
	glVertex2f(x + width, y + height);  // lower right
	glVertex2f(x, y + height);  // lower left
	ofSetColor(k.opacity(start));
	glVertex2f(x, y);  // upper left
	glVertex2f(x + width, y);  // upper right
  glEnd();
}

void ofShade(double x, double y, double span, double length, ofDirection d,bool black)
{
  ofColor k=ofGetStyle().color;
	ofSetColor(0,0,0,shDk*255);
	if(!black) ofSetColor(255,255,255,shDk*255);
  
  switch (d) {
    case OF_UP:
      shadeVer(x, y, length, -span, shDk);
      break;
    case OF_DOWN:
      shadeVer(x, y, length, span, shDk);
      break;
    case OF_LEFT:
      shadeHor(x, y, -span, length, shDk);
      break;
    case OF_RIGHT:
      shadeHor(x, y, span, length, shDk);
      break;
    default:
      break;
  }
  
  ofSetColor(k);
}

void angleColor(int curAng, ofColor cur=ofColor(0,0,0))
{
  if(drawMode==OF_FILLED) ofSetColor(cur+depthVal*cos((lghtAng-curAng)/180.*M_PI)*255);
}

void curveVertex(double x,double y,double rad, double deg){
  glVertex2d(x+rad*cos(deg*M_PI/(180)),y+rad*sin(deg*M_PI/(180)));
}

void cornerDraw(double x, double y, double rad, ofColor cur, int start){
  for ( double i = start; i <= start+90; i+=9 ){
		if(drawMode==OF_FILLED){
			ofSetColor(cur);
			glVertex2d(x,y);
      angleColor(i, cur);
		}
    curveVertex(x, y, rad, i);
	}
}

void ofRoundedRect(double x, double y, double w, double h,double rad){
  bool fill=(drawMode==OF_FILLED);
  float shade=depthVal;
  
  glBegin((fill)?GL_QUAD_STRIP:GL_LINE_LOOP);
	ofColor cur=ofGetStyle().color;
  
  //------- lower right corner
  cornerDraw(x+w-rad, y+h-rad, rad, cur, 0);
  
  //------- lower left corner
  cornerDraw(x+rad, y+h-rad, rad, cur, 90);
	
  //------- upper left corner
	cornerDraw(x+rad, y+rad, rad, cur, 180);
  
  //------- upper right draw
	cornerDraw(x+w-rad, y+rad, rad, cur, 270);
  
  if(fill){
    ofSetColor(cur);
    glVertex2d(x+w-rad,y+h-rad);
  }
  angleColor(0, cur);
  glVertex2d(x+w,y+h-rad);
	glEnd();
  if(fill){
    ofSetColor(cur);
    //ofRect(x+rad, y+rad, w-rad*2, h-rad*2);
    glBegin(GL_QUADS);
    {
      glVertex2d(x+rad, y+rad);
      glVertex2d(x+w-rad,y+rad);
      glVertex2d(x+w-rad,y+h-rad);
      glVertex2d(x+rad,y+h-rad);
      glEnd();
    }
  }
}

void ofRect(ofRectangle t)
{
  ofRect(t.x,t.y,t.width,t.height);
}

void ofCircle_Plus(double x, double y, double rad, double startInDegrees, double finishInDegrees)
{
  bool fill=(drawMode==OF_FILLED);
  float shade=depthVal;
  ofColor cur=ofGetStyle().color;
  
  glBegin((fill)?GL_TRIANGLE_FAN:GL_LINE_LOOP);
  if(fill) glVertex2d(x,y);
  const double NUM_DIVS = 40;
	for ( double i = startInDegrees; i <= finishInDegrees; i+=(finishInDegrees-startInDegrees)/NUM_DIVS ){
		angleColor(i, cur);
		glVertex2d(x + rad*cos(i*M_PI/(180)),y + rad*sin(i*M_PI/(180)));
	}
	glEnd();
}

void ofShadowCircle(double x, double y, double rad, double depth)
{
  /*glBegin(GL_TRIANGLE_FAN);
  glColor4f(0,0,0,shDk);
  glVertex2d(x,y);
  const double NUM_DIVS = 40;
  glColor4f(0,0,0,0);
	for ( double i = 0; i <= 360; i+=(360)/NUM_DIVS ){
		glVertex2d(x + (rad+depth)*cos(i*M_PI/(180)),y + (rad+depth)*sin(i*M_PI/(180)));
	}
	glEnd();*/
  
  glBegin(GL_QUAD_STRIP);
  const double NUM_DIVS = 40;
	for ( double i = 0; i <= 360; i+=(360)/NUM_DIVS ){
    float cA=cos(i*M_PI/(180));
    float sA=sin(i*M_PI/(180));
    glColor4f(0,0,0,shDk);
    glVertex2d(x + rad*cA,y + rad*sA);
    glColor4f(0,0,0,0);
		glVertex2d(x + (rad+depth)*cA,y + (rad+depth)*sA);
	}
  glEnd();

  glColor4f(0,0,0,shDk);
  ofPushStyle();
  ofSetCircleResolution(NUM_DIVS);
  ofCircle(x,y,rad);
  ofPopStyle();
  
}

void shadowCornerDraw(int x, int y, int rad, int start){
  for ( int i = start; i <= start+90; i+=9 ){
    glColor4f(0,0,0,shDk);
    //curveVertex(x, y, rad, i);
    glVertex2d(x, y);
    glColor4f(0,0,0,0);
    curveVertex(x, y, rad, i);
	}
}

void ofShadowRounded(double x, double y, double w, double h,double rad, double depth)
{
  glBegin(GL_QUAD_STRIP);
  
  double rad2=rad+depth;
  rad/=2;
  
  //------- lower right corner
  shadowCornerDraw(x+w-rad, y+h-rad, rad2, 0);
  
  //------- lower left corner
  shadowCornerDraw(x+rad, y+h-rad, rad2, 90);
	
  //------- upper left corner
	shadowCornerDraw(x+rad, y+rad, rad2, 180);
  
  //------- upper right draw
	shadowCornerDraw(x+w-rad, y+rad, rad2, 270);
  
  glColor4f(0,0,0,shDk);
  glVertex2d(x+w-rad,y+h-rad);
  glColor4f(0,0,0,0);
  glVertex2d(x+w-rad+rad2,y+h-rad);
	glEnd();
  glColor4f(0,0,0,shDk);
  ofRect(x+rad, y+rad, w-rad*2, h-rad*2);
  
  /*//------- lower right corner
  shadowCornerDraw(x+w-rad, y+h-rad, rad, rad+depth, 0);
  
  //------- lower left corner
  shadowCornerDraw(x+rad, y+h-rad, rad, rad+depth, 90);
	
  //------- upper left corner
	shadowCornerDraw(x+rad, y+rad, rad, rad+depth, 180);
  
  //------- upper right draw
	shadowCornerDraw(x+w-rad, y+rad, rad, rad+depth, 270);
  
  glColor4f(0,0,0,shDk);
  glVertex2d(x+w,y+h-rad);
  glColor4f(0,0,0,0);
  glVertex2d(x+w-rad+depth,y+h-rad);
  glEnd();
  
  ofSetColor(0,0,0,shDk*255);
  ofRoundedRect(x, y, w, h,rad);*/
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