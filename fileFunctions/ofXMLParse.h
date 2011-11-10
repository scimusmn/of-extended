/*
 *  ofXMLParse.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 5/5/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include <stack>

struct xmlAttribute {
	string name;
	string value;
	xmlAttribute(string n, string v){
		name=n;
		value=v;
	}
};

class ofTag {
protected:
	vector<ofTag> subnodes;
	vector<xmlAttribute> attributes;
	string label;
	string value;
	int pos;
public:
	ofTag(){
		subnodes.reserve(100);
		pos=0;
	}
	ofTag(string lbl);
  void operator=(const ofTag & t);
	void writeOut(ofstream &k, int t);
	int getNumAttributes();
	xmlAttribute getAttribute(int num){return attributes[num];}
	int size(){return subnodes.size();}
	ofTag & operator [](int i){return subnodes[i];}
	int getNumTags(){return subnodes.size();}
	ofTag & getTag(int i){return subnodes[i];}
	vector<int> findTag(ofTag * find);
	string getAttributeName(int i);
	string getAttribute(string attributeName);
	double getAttributeDouble(string attributeName);
	string getLabel();
	void addAttribute(string name,string val);
	int addNode(string lbl);
  int addNode(ofTag t);
	ofTag & getNode(string lbl, int which=0);
	ofTag & getNode(int which);
	void setValue(string val);
	string getValue(){return value;}
	double getValuef(string lbl, int which=0);
	friend class ofXML;
	int getNumTags(string label);
  int removeNode(string label, int which=0);
  void removeAttribute(string name);
};

class ofXML {
	vector<ofTag> nodes;
	stack<ofTag *> prevLevel;
	ofTag * currentLevel;
public:
  string filename;
	ofXML(){
		nodes.reserve(100);
		currentLevel=0;
	}
	int size(){return nodes.size();}
	ofTag & operator[](int i){ return nodes[i];}
	void loadFile(string file);
	void writeFile(string file);
	int addTag(string label);
	int addSubnode(string label);
	void addAttribute(string name,string value);
	string getAttribute(string name);
	void removeAttribute(string label);
	void removeTag(string label, int which=0);
	ofTag & getTag(string lbl, int which=0);
	ofTag & getTag(int i=0);
	ofTag & getCurrentTag();
	void pushToParent(string fullPath);
	void pushToTag(ofTag * tag);
	bool setCurrentTag(string fullPath, ...);
	bool pushTag(string lbl,int which=0);
	bool pushTag(int pos);
	void popTag();
	void saveFile();
	string parentTag();
	string currentTag();
	void newCurrentTag(string label);
	int getNumTags(string fullPath, ...);
	int getNumTag(string label);
	void addValue(string label, string value);
};