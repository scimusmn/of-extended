/*
 *  ofRadioButtons.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 4/13/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once

#include "ofButton.h"

class radioButton : public ofButton{
protected:
	double r;
	bool bSelected;
public:
	radioButton(double rad=10):ofButton(0, 0, rad*2,rad*2){
		r=rad;
		bSelected=false;
	}
	void draw(double _x, double _y);
	friend class ofRadioButtons;
};

class ofRadioButtons : public ofInterGroup{
protected:
	int iSelected;
	bool vert;
	double span;
public:
	vector<radioButton> buttons;
	ofRadioButtons():ofInterGroup(){
		iSelected=0;
	}
	void setup(int num, double rad, ofDirection v=OF_VERT, double spn=200);
	bool clickDown(int _x, int _y);
	bool clickUp();
	void draw(double _x, double _y,double spn=0);
	void drawButton(int num, double _x, double y);
	void select(int num);
	int getChoice(){ return iSelected;}
	int size(){return buttons.size();}
	radioButton & operator[](int num){ return buttons[num];}
};