/*
 *  ofTimer.h
 *  SonicTracker
 *
 *  Created by SMM Exhibits on 3/8/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#ifndef _OF_TIMER
#define _OF_TIMER

#include "ofMain.h"

class ofTimer {
	long remaining;
	long originalTime;
	long elapsed;
	long timeSet;
	long alarm;
	bool bSet;
	bool bPaused;
public:
	ofTimer();
	void set(float delay);
	void setPosition(double pos);
	void setPercent(double elpsd);
	void pause();
	void run();
	void reset();
	bool expired();
	bool running();
	double getElapsedf();
	long getElapsed();
	long getRemaining();
	bool justExpired();
};

#endif