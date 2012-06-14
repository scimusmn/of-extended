/*
 *  ofFont.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 3/10/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#ifndef _OF_FONT
#define _OF_FONT

#include "ofTrueTypeFont.h"
#include <stdarg.h>
//#include "ofImage.h"
#include <map>

string ssprintf(const char * format, ... );

enum ofFontMode {
	OF_FONT_CENTER, OF_FONT_LEFT, OF_FONT_RIGHT, OF_FONT_MID, OF_FONT_TOP, OF_FONT_BOT
};

class ofFont {
	int setNum;
	ofFontMode FONT_MODE;
	ofFontMode V_FONT_MODE;
public:
	int point;
	string file;
	ofFont();
	~ofFont(){}
	int			checkSizes(int pt);
	void		setSize(int pt);
	int			getSize(){ return point; }
	void		loadFont(string filename);
	void		drawString(string s, int x, int y);
	ofRectangle getBoundingBox(string s, int x, int y);
	float 		stringWidth(string s);
	float 		stringHeight(string s);
	void		setMode(ofFontMode MODE);
	ofFontMode	getVertMode();
	ofFontMode	getHorMode();
};

class ofFontContainer {
public:
	string file;
	map<string,map<int,ofTrueTypeFont> >::iterator font;
	map<int,ofTrueTypeFont>::iterator size;
	ofFontContainer(){
	}
	
	void setSize(int pt);
	
	void loadFont(string filename, int pt=0);
	
	ofTrueTypeFont & operator[](int i);
	
	void drawString(string s, int x, int y);
	
	ofRectangle getBoundingBox(string s, int x, int y);
	
	float stringWidth(string s);
	
	float stringHeight(string s);
	
	void operator=(const ofFontContainer & t);
};

#endif