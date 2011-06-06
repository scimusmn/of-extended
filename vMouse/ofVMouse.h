/*
 *  ofVMouse.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 5/26/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofExtended.h"

enum vMouseType {
	OF_VMOUSE_CLICK_DOWN, OF_VMOUSE_MOVE_TO, OF_VMOUSE_CLICK_UP
};

class ofVMouseEvent{
protected:
public:
	bool executed;
	unsigned long duration;
	vMouseType type;
	int xPos, yPos;
	ofInterObj * objPtr;
	ofVMouseEvent(vMouseType eventType, int _x, int _y, unsigned long time);
	ofVMouseEvent(vMouseType eventType, ofInterObj & k, unsigned long time);
	ofVMouseEvent(vMouseType eventType, ofInterObj & k, int _x, int _y, unsigned long time);
	int x();
	int y();
};

class ofVMouse{
protected:
	vector<ofVMouseEvent> events;
	bool mouseState;
	unsigned long startTime,elapsedAtPause;
	bool running;
	ofBaseApp * appPtr;
	int x0, y0;
public:
	int x, y;
	ofVMouse();
	~ofVMouse();
	void setup();
	void addEvent(vMouseType eventType, int _x, int _y, double time);
	void addEvent(vMouseType eventType, ofInterObj & k, double time);
	void addEvent(vMouseType eventType, ofInterObj & k, int xInc, int yInc, double time);
	void clearEvents(){ events.clear(); }
	bool isPlaying(){ return running;}
	bool isClicked(){ return mouseState;}
	void play();
	void pause();
	void reset();
	void update();
};