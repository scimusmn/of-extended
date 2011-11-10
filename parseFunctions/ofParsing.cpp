/*
 *  ofParsing.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 5/17/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofParsing.h"

bool isDelim(char comp, string delims)
{
	bool ret=false;
	for (unsigned int i=0; i<delims.length(); i++) {
		if(delims[i]==comp) ret=true;
	}
	return ret;
}

double operaterByChar(double a, char op, double b){
  int ret=0;
  switch (op) {
    case '-':
      ret=a-b;
      break;
    case '+':
      ret=a+b;
      break;
    case '/':
      ret=a/b;
      break;
    case '*':
      ret=a*b;
      break;
    default:
      break;
  }
  return ret;
}

string getWord(string buffer,unsigned int & first, string delims)
{
	string ret;
	bool found=0;
	for (unsigned int i=first; i<buffer.length(); i++) {
		if(isDelim(buffer[i], delims)){
			found=true;
			ret=string(buffer,first,i-first);
			first=i;
			break;
		}
	}
  if(!found){
    ret="";//string(buffer,first,(buffer.length()-1)-first);
    first=buffer.length();
  }
	return ret;
}

string peekWord(string buffer,unsigned int first, string delims)
{
	string ret;
	bool found;
	for (unsigned int i=first; i<buffer.length(); i++) {
		if(isDelim(buffer[i], delims)){
			found=true;
			ret=string(buffer,first,i-first);
			first=i;
			break;
		}
	}
	return ret;
}