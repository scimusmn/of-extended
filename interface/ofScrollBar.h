/*
 *  ofScrollBar.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 3/30/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once

#include "ofInterObj.h"
#include "ofButton.h"

class ofScrollTab : public ofButton {
protected:
	bool vert;
public:
	void setup(double span, bool vert);
	void draw(int _x, int _y);
	void draw(int dp);
	void draw();
	void mouseMotion(int _x, int _y);
	friend class ofScrollBar;
};

class ofScrollBar : public ofInterObj{
protected:
	ofScrollTab tab;
	double viewSize, fullSize, tabRange,endPad;
	bool vert;
	double xDisp, yDisp;
public:
	ofScrollBar():ofInterObj(){}
	~ofScrollBar();
	void setup(double span, double length, ofDirection DIRECTION);
	void registerArea(double vSize, double fSize);
	double getScrollPercent();
  void setScrollPercent(double perc);
	bool setScrollPosition(double newPos);
	double getScrollPosition();
	bool clickDown(int _x, int _y);
	bool clickUp();
	virtual void draw(int _x, int _y);
	bool mouseMotion(int _x, int _y);
	void update(double percent);
	void update();
	bool available();
	double barSize();
	double getFullSize(){ return fullSize;}
  void setPressed(bool state);
};