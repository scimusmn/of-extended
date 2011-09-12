/*
 *  ofSlider.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 9/12/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofSlider.h"

ofSlider::ofSlider()
{
  knob.w=10;
  knob.h=10;
}

ofSlider::ofSlider(int knobW, int knobH)
{
  knob.h=knobH;
  knob.w=knobW;
}

void ofSlider::setup(int knobW, int knobH)
{
  knob.h=knobH;
  knob.w=knobW;
  knob.setAvailable(true);
}

void ofSlider::draw(int _x, int _y, int _w, int _h)
{
  //knob.h=knob.w=_h+10;
  w=_w;
  h=_h;
  draw(_x,_y);
}

void ofSlider::draw(int _x, int _y)
{
  x=_x, y=_y;
  knob.x=x-knob.w/2;
  knob.y=y-(knob.h-h)/2;
  ofInvertBox(x, y, w, h, h/4, .2);
  ofCircleShadow(knob.x+knob.relPos.x+knob.w/2, knob.y+knob.h/2, knob.w/2+5, .8);
  ofSetColor(200, 200, 200);
  ofRaisedCircle(knob.x+knob.relPos.x+knob.w/2, knob.y+knob.h/2, knob.w/2, .2);
  if(knob.pressed()) ofSetColor(0, 64, 200);
  else ofSetColor(128,128,128);
  ofDentCircle(knob.x+knob.relPos.x+knob.w/2, knob.y+knob.h/2, knob.w/3, .2);
}

bool ofSlider::clickDown(int _x, int _y)
{
  bool ret=false;
  if(knob.clickDown(_x-knob.relPos.x, _y)){
    ret=bPressed=true;
  }
  else if(over(_x, _y)){
    knob.setPressed(true);
    knob.relPos.x=(_x-x<=w)?_x-x:w;
    ret=bPressed=true;
  }
  return ret;
}

bool ofSlider::clickUp()
{
  bool ret=bPressed;
  knob.clickUp();
  bPressed=false;
  return ret;
}

void ofSlider::drag(int _x, int _y)
{
  if(bPressed||knob.pressed()){
    knob.relPos.x=(_x-x>=0)?(_x-x<=w)?_x-x:w:0;
  }
}

void ofSlider::update()
{
  
}

double ofSlider::getPercent()
{
  return knob.relPos.x/w;
}
