/*
 *  ofSlider.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 9/12/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofInterObj.h"
#include "ofButton.h"

class ofSlider : public ofInterObj{
protected:
  ofButton knob;
public:
  ofSlider();
  ofSlider(int knobW, int knobH);
  void setup(int knobW, int knobH);
  void draw(int _x, int _y, int _w, int _h);
  void draw(int _x, int _y);
  bool clickDown(int _x, int _y);
  bool clickUp();
  void drag(int _x, int _y);
  void update();
  double getPercent();
};