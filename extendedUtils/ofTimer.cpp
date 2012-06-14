/*
 *  ofTimer.cpp
 *  SonicTracker
 *
 *  Created by SMM Exhibits on 3/8/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofTimer.h"

ofTimer::ofTimer(){
	timeSet=ofGetElapsedTimeMillis();
	alarm=timeSet;
	bSet=false;
	bPaused=false;
}

void ofTimer::set(float delay){
	elapsed=0;
	originalTime=delay*1000;
	timeSet=ofGetElapsedTimeMillis();
	alarm=timeSet+delay*1000.;
	bSet=alarm>timeSet;
}

void ofTimer::setPosition(double elpsd)
{
	elapsed=elpsd*1000;
	remaining=originalTime-elapsed;
}

void ofTimer::setPercent(double perc)
{
	elapsed=originalTime*perc;
	remaining=originalTime-elapsed;
	if(running()){
		timeSet=ofGetElapsedTimeMillis();
		alarm=timeSet+remaining;
		bSet=alarm>timeSet;
	}
}

void ofTimer::reset(){
	alarm=timeSet;
  elapsed=0;
  remaining=originalTime;
  timeSet=ofGetElapsedTimeMillis();
  alarm=timeSet;
	bSet=false;
}

void ofTimer::pause(){
	elapsed=getElapsed();
	remaining=getRemaining();
	bPaused=true;
	//reset();
  alarm=ofGetElapsedTimeMillis();
}

void ofTimer::run(){
	if(bPaused){
		timeSet=ofGetElapsedTimeMillis();
		alarm=timeSet+remaining;
		bSet=alarm>timeSet;
		bPaused=false;
	}
}

bool ofTimer::expired(){
	return (alarm<=ofGetElapsedTimeMillis()&&!bPaused);
}

bool ofTimer::running(){
	return alarm>ofGetElapsedTimeMillis()&&!bPaused;
}

double ofTimer::getElapsedf(){
	return double(getElapsed())/1000.;
}

long ofTimer::getElapsed(){
	return (!expired()&&!bPaused)?(ofGetElapsedTimeMillis()-timeSet)+elapsed:(bPaused)?elapsed:originalTime;
}

long ofTimer::getRemaining(){
	long curTime=ofGetElapsedTimeMillis();
	return (alarm>curTime)?alarm-curTime:(bPaused)?remaining:0;
}

double ofTimer::getPercent()
{
  return getElapsedf()/(double(originalTime)/1000.);
}

bool ofTimer::justExpired(){
	bool ret=false;
	if(expired()&&bSet)
		ret=true, bSet=false;
	return ret;
}
