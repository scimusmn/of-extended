#ifndef OF_SHAPES
#define OF_SHAPES

#include<sstream>
#include<math.h>
#include<vector>
#include "ofGraphics.h"
#include "ofNewShapes.h"

using namespace std;


class numberBar {
public:
	double x,y,w,h;
	numberBar(double size);
	~numberBar(){}
	void draw(double x_, double y_, bool vert);
};


class numberTemplate{
public:
	vector<numberBar> temp;
	double x,y,w,h;
	numberTemplate(double size);
	~numberTemplate();
	void draw(double _x, double _y, int num);
	void drawBar(int bar);
};

class digitDisplay {
	vector<numberTemplate> numTemp;
public:
	double x, y, w, h, size;
	digitDisplay(){}
	void setup(double width, int numDigits);
	digitDisplay(double width, int numDigits);
	void draw(string k,double _x, double _y);
};
    	
#endif
