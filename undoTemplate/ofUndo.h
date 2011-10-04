/*
 *  ofUndo.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 7/1/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"
#include <deque>

template <class T>
class stateSave {
  deque<T> storedState;
	unsigned int stateCount;
public:
  stateSave(){
    stateCount=0;
  }
  
  void recordState(T t);
	
	T * undoState();
	
	T * redoState();
	
	bool undoAvailable();
	
	bool redoAvailable();
};

template <class T>
void stateSave<T>::recordState(T t)
{
	while (stateCount>0) {
		storedState.pop_front();
		stateCount--;
	}
	storedState.push_front(t);
	if (storedState.size()>10) {
		storedState.pop_back();
	}
}

template <class T>
T * stateSave<T>::undoState()
{
  T * ret=0;
	if (storedState.size()&&++stateCount>storedState.size()-1) {
		stateCount=storedState.size()-1;
	}
	if(storedState.size()){
		ret=&storedState[stateCount];
  }
  return ret;
}

template <class T>
T * stateSave<T>::redoState()
{
  T * ret=0;
	if (--stateCount<0) {
		stateCount=0;
	}
	ret=&storedState[stateCount];
  return ret;
}

template <class T>
bool stateSave<T>::undoAvailable()
{
	return (stateCount<storedState.size()-1);
}

template <class T>
bool stateSave<T>::redoAvailable()
{
	return stateCount>0;
}
