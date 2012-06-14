/*
 *  ofFont.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 3/10/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofFont.h"
#include "ofMain.h"
#include "../parseFunctions/ofParsing.h"

vector<ofTrueTypeFont> fonts;
map<int,int> points;
map<string,map<int,ofTrueTypeFont> > Fonts;

//typedef map<string, map<int,ofTrueTypeFont> > fontMap;

string ssprintf(const char * format, ...)
{
	string temp=format;
	va_list vl;
	va_start(vl,format);
	stringstream sstr;
	int num=0;
	for(unsigned int i=0; i<temp.length(); i++){
		if(temp[i]=='%'){
			string t=getWord(temp,++i,"idsecx%");
			t+=temp[i];
			bool padWithZero=false;
			for(unsigned int j=0; j<t.size(); j++){
				if(t[j]=='0') sstr<<setfill('0');
				else if(t[j]>'1'&&t[j]<'9'){
					if(j>=1&&t[j-1]!='.') sstr << setw(t[j]-'0');
					if(j>=1&&t[j-1]=='.') sstr << setprecision(t[j]-'0');
				}
				if(t[j]=='i'){
					int arg = va_arg(vl,int);
					sstr << arg;
				}
        if(t[j]=='x'){
					int arg = va_arg(vl,int);
					sstr << std::hex << arg;
				}
				if(t[j]=='s'){
					char * arg = va_arg(vl,char *);
					sstr << arg;
				}
				if(t[j]=='f'){
					double arg = va_arg(vl,double);
					sstr << arg;
				}
				if(t[j]=='%'){
					sstr << '%';
				}
			}
		}
		else sstr << temp[i];
	}
	va_end(vl);
	return sstr.str();
}

void ofFontContainer::setSize(int pt){
	map<int,ofTrueTypeFont>::iterator it=Fonts[file].find(pt);
	if (it==Fonts[file].end()) {
		Fonts[file][pt].loadFont(file,pt);
		size=Fonts[file].find(pt);
	}
	else {
		size=it;
	}
}

void ofFontContainer::loadFont(string filename, int pt){
	file=filename;
	map<string,map<int,ofTrueTypeFont> >::iterator it=Fonts.find(filename);
	if (it==Fonts.end()) {
		Fonts[filename][12]=ofTrueTypeFont();
		Fonts[filename][12].loadFont(filename,12);
		font=Fonts.find(filename);
	}
	else {
		font=it;
	}
	if (pt) {
		setSize(pt);
	}
}

void ofFontContainer::operator=(const ofFontContainer & t)
{
	font=t.font;
	size=t.size;
	file=t.file;
}

ofTrueTypeFont & ofFontContainer::operator[](int i)
{
	return size->second;
}

void ofFontContainer::drawString(string s, int x, int y)
{
	size->second.drawString(s,x,y);
}

ofRectangle ofFontContainer::getBoundingBox(string s, int x, int y)
{
	return size->second.getStringBoundingBox(s,x,y);
}

float ofFontContainer::stringWidth(string s)
{
	return size->second.stringWidth(s);
}

float ofFontContainer::stringHeight(string s)
{
	return size->second.stringHeight(s);
}

//map<string,ofFontContainer> font;


ofFont::ofFont()
{
	fonts.reserve(100);
	FONT_MODE=OF_FONT_LEFT;
	V_FONT_MODE=OF_FONT_BOT;
}

void ofFont::setMode(ofFontMode mode){
	if(mode<3) FONT_MODE=mode;
	else V_FONT_MODE=mode;
}

ofFontMode	ofFont::getVertMode()
{
	return V_FONT_MODE;
}

ofFontMode	ofFont::getHorMode()
{
	return FONT_MODE;
}

void ofFont::loadFont(string filename)
{
	file=filename;
	setNum=checkSizes(12);
}

void ofFont::setSize(int pt)
{
	setNum=checkSizes(pt);
}

int ofFont::checkSizes(int pt)
{
	point=pt;
	int ret=0;
	if(pt>=0){
		map<int,int>::iterator it=points.find(pt);
		if (it==points.end()) {
			int current=fonts.size();
			fonts.push_back(ofTrueTypeFont());
			fonts[current].loadFont(file,pt);
			ret=points[pt]=current;
		}
		else {
			ret=it->second;
		}
	}
	else {
		ret=setNum;
	}
	
	return ret;
}

void ofFont::drawString(string s, int x, int y)
{
	if(FONT_MODE==OF_FONT_CENTER) x=(x-stringWidth(s)/2);
	else if(FONT_MODE==OF_FONT_RIGHT) x=(x-stringWidth(s));
	if(V_FONT_MODE==OF_FONT_MID) y=(y+stringHeight("m")/2);
	else if(V_FONT_MODE==OF_FONT_TOP) y=(y+stringHeight("m"));
	fonts[setNum].drawString(s,x,y);
}

ofRectangle ofFont::getBoundingBox(string s, int x, int y)
{
	if(FONT_MODE==OF_FONT_CENTER) x=(x-stringWidth(s)/2);
	else if(FONT_MODE==OF_FONT_RIGHT) x=(x-stringWidth(s));
  if(V_FONT_MODE==OF_FONT_MID) y=(y+stringHeight("m")/2);
	else if(V_FONT_MODE==OF_FONT_TOP) y=(y+stringHeight("m"));
	return fonts[setNum].getStringBoundingBox(s,x,y);
}

float 		ofFont::stringWidth(string s)
{
	return fonts[setNum].stringWidth(s);
}

float 		ofFont::stringHeight(string s)
{
	return fonts[setNum].stringHeight(s);
}