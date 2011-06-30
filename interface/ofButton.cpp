/*
 *  ofButton.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 1/6/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofButton.h"

void ofButton::setup(int _x, int _y, int _w, int _h, string imageName, string prsImage)
{
	arial.loadFont("Arial.ttf");
	arial.setSize(10);
	cSetup(_x, _y, _w, _h);
	bPressed=false;
	bAvailable=true;
	img=imageName;
	background.loadImage(imageName);
}

void ofButton::setup(int _w, int _h, string imageName, string prsImage)
{
	arial.loadFont("Arial.ttf");
	arial.setSize(10);
	cSetup(0,0, _w, _h);
	bPressed=false;
	bAvailable=true;
	img=imageName;
	img2=prsImage;
	background.loadImage(imageName);
	if(img2.length()) pressImage.loadImage(prsImage);
}

void ofButton::setup(string title, string font,int size)
{
	arial.loadFont(font);
	arial.setSize(size);
	setTitle(title);
	bAvailable=true;
	bPressed=false;
}

void ofButton::setAvailable(bool avlb)
{
	bAvailable=avlb;
}

void ofButton::setTitle(string ttl)
{
	title=ttl;
}

void ofButton::setTextSize(int pt)
{
	arial.setSize(pt);
}

void ofButton::setPressed(bool t)
{
	bPressed=t;
}

void ofButton::draw(int _x, int _y, int _w, int _h)
{
	x=_x,y=_y,w=_w,h=_h;
	if(!bPressed&&bAvailable) ofSetColor(255, 255, 255);
	else if(!bPressed&&!bAvailable) ofSetColor(255, 255, 255,128);
	else ofSetColor(128, 128, 128);
	ofEnableSmoothing();
	if(img.length()){
		if((!img2.length())||!bPressed) background.draw(x, y,_w,_h);
		if(img2.length()&&bPressed) pressImage.draw(x, y,w,h);
	}
	else {
		int curW=arial.stringWidth(title);
		ofRectangle box=arial.getBoundingBox(title, x, y);
		w=box.width+30;
		h=box.height+10;
		ofRoundBox(x, y, _w, _h, _h/2, .3);
		ofSetColor(0,0,0);
		arial.drawString(title, box.x+15, y+arial.stringHeight(title));
	}

	ofDisableSmoothing();
}

void ofButton::drawTextButton(int _x, int _y){
	x=_x,y=_y;
	if(!bPressed&&bAvailable) ofSetColor(255, 255, 255);
	else if(!bPressed&&!bAvailable) ofSetColor(255, 255, 255,96);
	else ofSetColor(128, 128, 128);
	ofEnableSmoothing();
	{
		int curW=arial.stringWidth(title);
		ofRectangle box=arial.getBoundingBox(title, x, y);
		w=box.width+30;
		h=box.height+10;
		ofRoundBox(x, y, w, h, h/2, .3);
		ofSetColor(0,0,0);
		arial.drawString(title, box.x+15, y+arial.stringHeight(title));
	}
	
	ofDisableSmoothing();
}

void ofButton::draw(int _x, int _y)
{
	draw(_x,_y,w,h);
}

bool ofButton::clickDown(double _x, double _y)
{
	bool ret=false;
	if (bAvailable) {
		if(ret=over(_x, _y)) bPressed=true;
	}
	return ret;
}

bool ofButton::toggle(double _x, double _y)
{
	bool ret=false;
	if (bAvailable) {
		if(ret=over(_x, _y)) bPressed=!bPressed;
	}
	return ret;
}

bool ofButton::clickUp()
{
	bool ret=bPressed;
	bPressed=false;
	return ret;
}