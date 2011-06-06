/*
 *  ofParsing.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 5/17/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"

bool isDelim(char comp, string delims);

string getWord(string buffer,unsigned int & first, string delims);

string peekWord(string buffer,unsigned int first, string delims);