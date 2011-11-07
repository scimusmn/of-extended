/*
 *  ofDropDown._h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 1/31/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#ifndef _dropdown_
#define _dropdown_

#include "ofGraphics.h"
#include "ofInterObj.h"
//#include "xml_smm.h"
#include "../fileFunctions/ofXMLParse.h"
#include "ofImage.h"

#include <vector>
#include <algorithm>

const char *asString(double i);


class ofDropDown: public ofInterObj {
	vector<string> values;
public:
	bool deci;
	int curPos;
	string svar;
	ofFont arial;
  ofImage unopened;
  string nOpen;
	int steps,nDisp;
	bool open,selected,bOver,bAutoAdj;
	double var;
	int xdis;
	int cursorPos;
	ofDropDown();
	
	ofDropDown(int _x, int _y,int _w,int _h,int low, int hi, int stps=10);
	
	//ofDropDown(xmlParse * xml);
	
	ofDropDown(ofTag xml);
	
	~ofDropDown();
	
	int size();
	
	void setup(int _x, int _y,int _w,int _h);
  
  void setUnopenImage(string fileName);
	
	void setTextSize(int num);
	
	void setRange(double low, double high, int stps=11);
	
	void setValue(string k);
	
	void adjustSizeToStrings();
		
	bool passingClick(int _x,int _y);
	
	void draw();
	
	void draw(double _x, double _y);
	
	void drawShape();
	
	bool clickDown(int _x,int _y);
	
	void motion(int _x, int _y);
	
	double getValue();
	
	string getString();
  
  int getIndex();
	
	int getChoiceNumber();
	
	void setSelected(string comp);
	
	bool isSelected(){ return selected;}
	
	bool justSelected();
	
	void setMode(bool autoAdjustPos){bAutoAdj=autoAdjustPos;}
	
	void operator=(const ofDropDown & t);
};

#endif
