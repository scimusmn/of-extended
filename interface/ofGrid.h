/*
 *  ofGrid.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 1/24/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#ifndef _ofGrid
#define _ofGrid

#include "ofShapes.h"
#include "ofTypes.h"

class grid {
	ofColor color;
public:
	double mainWIDTH,mainHEIGHT,numdivs,x,y,w;
	grid(){
		color.set(.3*255,.6*255,1*255);
	}
	grid(int num,int mW, int mH,int sx=0,int sy=0){
		w=mainWIDTH=mW;
		mainHEIGHT=mH;
		numdivs=num;
		x=sx,y=sy;
	}
	~grid(){}
	void setColor(long hex){
		color.set(hex);
	}
	void update(int num,int mW, int mH,int sx=0,int sy=0){
		mainWIDTH=mW;
		mainHEIGHT=mH;
		numdivs=num;
		x=sx,y=sy;
	}
	void draw(){
		for(int i=0; i<numdivs; i++){
			glLineWidth(1.0);
			glBegin(GL_LINES);
			ofSetColor(color);
			glVertex2f(x+i*(mainWIDTH/numdivs),y); // origin
			glVertex2f(x+i*(mainWIDTH/numdivs),y+mainHEIGHT); // ending
			glEnd();}
		for(int i=0; i<=((float)mainHEIGHT/(mainWIDTH/numdivs)); i++){
			glLineWidth(1.0);
			glBegin(GL_LINES);
			glVertex2f(x+0,y+i*(mainWIDTH/numdivs)); // origin
			glVertex2f(x+mainWIDTH,y+i*(mainWIDTH/numdivs)); // ending
			glEnd();}
	}
	ofPoint vertex(double x_num, double y_num)
	{
		return ofPoint(x+x_num*(mainWIDTH/numdivs),y+(numdivs-y_num)*(mainWIDTH/numdivs));
	}
};

#endif