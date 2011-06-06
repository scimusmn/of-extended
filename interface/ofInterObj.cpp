/*
 *  ofInterObj.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 2/2/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofInterObj.h"

static vector<ofInterObj *>	interfaceObjects;

void ofInterObj::registerEvents(){
	interfaceObjects.push_back(this);
}

vector<ofInterObj *> & interObjects(){
	return interfaceObjects;
}