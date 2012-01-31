/*
 *  ofVMouse.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 5/26/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofVMouse.h"

ofVMouseEvent::ofVMouseEvent(vMouseType eventType, int _x, int _y, unsigned long time)
{
	duration=time;
	xPos=_x;
	yPos=_y;
	type=eventType;
	executed=false;
	objPtr=0;
}

ofVMouseEvent::ofVMouseEvent(vMouseType eventType, ofInterObj & obj, unsigned long time)
{
	duration=time;
	xPos=0;
	yPos=0;
	type=eventType;
	executed=false;
	objPtr=&obj;
}

ofVMouseEvent::ofVMouseEvent(vMouseType eventType, ofInterObj & obj, int _x, int _y, unsigned long time)
{
	duration=time;
	xPos=_x;
	yPos=_y;
	type=eventType;
	executed=false;
	objPtr=&obj;
}

int ofVMouseEvent::x(){
	int ret=xPos;
	if(objPtr&&xPos==0&&yPos==0) ret+=objPtr->x+objPtr->w/4;
	else if(objPtr) ret+=objPtr->x;
	return ret;
}

int ofVMouseEvent::y(){
	int ret=yPos;
	if(objPtr&&xPos==0&&yPos==0) ret+=objPtr->y+objPtr->h/4;
	else if(objPtr) ret+=objPtr->y;
	return ret;
}

ofVMouse::ofVMouse()
{
	
}

ofVMouse::~ofVMouse()
{
	events.clear();
}

void ofVMouse::setup(ofAnimation * anim)
{
  animHolder=anim;
	x=y=0;
	mouseState=0;
	startTime=0;
	running=false;
	elapsedAtPause=0;
	appPtr=ofGetAppPtr();
}

void ofVMouse::addEvent(vMouseType eventType, int _x, int _y, double timeInSeconds)
{
	events.push_back(ofVMouseEvent(eventType,_x,_y,timeInSeconds*1000));
}

void ofVMouse::addEvent(vMouseType eventType, ofInterObj & obj, double timeInSeconds)
{
	events.push_back(ofVMouseEvent(eventType,obj,timeInSeconds*1000));
}

void ofVMouse::addEvent(vMouseType eventType, ofInterObj & obj, int _x, int _y, double timeInSeconds)
{
	events.push_back(ofVMouseEvent(eventType,obj, _x, _y,timeInSeconds*1000));
}

void ofVMouse::play()
{
	startTime=ofGetElapsedTimeMillis();
	running=true;
	x0=x;
	y0=y;
}

void ofVMouse::pause()
{
	running=false;
	elapsedAtPause=ofGetElapsedTimeMillis()-startTime;
}

void ofVMouse::reset()
{
	elapsedAtPause=0;
	for (unsigned int i=0; i<events.size(); i++) {
		events[i].executed=false;
	}
}

void ofVMouse::stop()
{
  elapsedAtPause=0;
  events.clear();
  running=false;
  curEvent.type=OF_VMOUSE_BLANK;
}

void ofVMouse::update()
{
	unsigned long sumTime=elapsedAtPause;
	bool ran=false;
	unsigned long timeNow=ofGetElapsedTimeMillis();
	if(running){
		for (unsigned int i=0; i<events.size(); i++) {
			if (!ran&&!events[i].executed&&startTime+sumTime+events[i].duration>timeNow) {
				double percentDone=double(timeNow-(startTime+sumTime))/events[i].duration;
				x=x0+percentDone*double(events[i].x()-x0);
				y=y0+percentDone*double(events[i].y()-y0);
				if(mouseState) appPtr->mouseDragged(x, y, 0);
				else appPtr->mouseMoved(x, y);
				ran=true;
			}
			else if (!events[i].executed&&startTime+sumTime+events[i].duration<timeNow) {
				events[i].executed=true;
				x=x0=events[i].x();
				y=y0=events[i].y();
				if(events[i].type==OF_VMOUSE_CLICK_DOWN){
					mouseState=true;
					appPtr->mousePressed(x, y, 0);
				}
				else if(events[i].type==OF_VMOUSE_CLICK_UP){
					mouseState=false;
					appPtr->mouseReleased(x, y, 0);
				}
			}
			sumTime+=events[i].duration;
		}
		if(timeNow>startTime+sumTime) running=false;
	}
}

void ofVMouse::updateNextEvent()
{
	unsigned long sumTime=elapsedAtPause;
	bool ran=false;
	unsigned long timeNow=ofGetElapsedTimeMillis();
	if(running){
    if(curEvent.type==OF_VMOUSE_END) running=false,curEvent.type=OF_VMOUSE_BLANK;
    else if(curEvent.type==OF_VMOUSE_BLANK){
      if(!animHolder)
        appPtr->keyPressed('n');
      else if(animHolder)
        animHolder->animationStepRequested();
      startTime=ofGetElapsedTimeMillis();
    }
    else if (!ran&&!curEvent.executed&&startTime+sumTime+curEvent.duration>timeNow) {
      double percentDone=double(timeNow-(startTime+sumTime))/curEvent.duration;
      x=x0+percentDone*double(curEvent.x()-x0);
      y=y0+percentDone*double(curEvent.y()-y0);
      if(mouseState) appPtr->mouseDragged(x, y, VMOUSE_BUTTON);
      else appPtr->mouseMoved(x, y);
      ran=true;
    }
    else if (!curEvent.executed&&startTime+sumTime+curEvent.duration<timeNow) {
      curEvent.executed=true;
      x=x0=curEvent.x();
      y=y0=curEvent.y();
      if(curEvent.type==OF_VMOUSE_CLICK_DOWN){
        mouseState=true;
        appPtr->mousePressed(x, y, VMOUSE_BUTTON);
      }
      else if(curEvent.type==OF_VMOUSE_CLICK_UP){
        mouseState=false;
        appPtr->mouseReleased(x, y, VMOUSE_BUTTON);
      }
      
      //******* signal the app to grab next event
      if(!animHolder)
        appPtr->keyPressed('n');
      else if(animHolder)
        animHolder->animationStepRequested();
      
      startTime=ofGetElapsedTimeMillis();
    }
		//if(timeNow>startTime+sumTime) running=false;
	}
}

ofTag ofVMouse::getRequestEvent()
{
  return ofTag();
}

void ofVMouse::nextEvent(vMouseType eventType, ofInterObj & obj, int _x, int _y, double timeInSeconds)
{
  curEvent=ofVMouseEvent(eventType,obj, _x, _y,timeInSeconds*1000);
}

void ofVMouse::nextEvent(vMouseType eventType, int _x, int _y, double timeInSeconds)
{
  curEvent=ofVMouseEvent(eventType, _x, _y,timeInSeconds*1000);
}