/*
 *  ofButton.h
 *  openFrameworksLib
 *
 *  Created by Exhibits on 1/5/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofInterObj.h"
#include "ofImage.h"

#ifndef _ofButton
#define _ofButton

class ofButton : public ofInterObj {
protected:
	ofImage		background;
	ofImage		pressImage;
	bool		bAvailable;
	string		img;
	string		img2;
public:
	ofFont		arial;
	string		title;
	ofButton():ofInterObj(){
		title="Default";
	}
	ofButton(int _x, int _y, int _w, int _h):ofInterObj(_x,_y,_w,_h){}
	~ofButton(){}
	void setup(int _x, int _y, int _w, int _h,string imageName="", string prsImage="");
	void setPressImage(string title2);
	void setup(int _w, int _h,string imageName="", string prsImage="");
  void setup(int dimension, ofDirection dir,string imageName, string prsImage="");
	void setup(string title, string font="Arial.ttf",int size=10);
	virtual void draw(int _x, int _y);
	virtual void draw(int _x, int _y,int _w, int _h);
	void drawTextButton(int _x, int _y);
	bool clickDown(double _x, double _y);
	bool toggle(double _x, double _y);
	bool clickUp();
	void setAvailable(bool b);
	bool getAvailable(){ return bAvailable;}
	void setPressed(bool t);
	void setTitle(string ttl);
	void setTextSize(int pt);
	virtual void motion(int _x, int _y){};
	virtual void keyboard(char k){};
	virtual void update(){};
};

#endif //_ofButton