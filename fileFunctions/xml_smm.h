/*
 *  XML.h
 *  
 *
 *  Created by Exhibits on 9/27/10.
 *  Copyright 2010 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofMain.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#ifndef _xml_smm_
#define _xml_smm_

class xmlParse{
public:
	vector<xmlParse> child;
	xmlParse * parent;
	string label;
	string name;
	string value;
	string prop;
	string attrib;
	string attribName;
	bool read;
	int nodePtr;
	xmlParse(const char * l ="",xmlParse * p=0,const char * n="",const char * v="");
	
	~xmlParse();
	
	void addChild(const char * l ="",const char * n="",const char * v="");
	
	void addName(const char * n);
	
	void addAttribute( string aName, string aValue); 
	
	void addValue(const char* v);
	
	void addProperty(const char* p);
	
	xmlParse * stepDown(unsigned int next);
	
	bool isChild();
	
	xmlParse * stepUp();
	
	int numChildren();
	
	bool lastGeneration();
	
	void write();
	
	int size();
	
	string getSubNode(string k);
	
	string * getNextSubnode();
	
	string * getSubnode(int i=0);
};

xmlParse * parseFile(const char * filename);
	
#endif