#ifndef OF_SHAPES
#define OF_SHAPES

#include<sstream>
#include<math.h>
#include<vector>
#include "ofGraphics.h"

using namespace std;

enum ofDirection {
	OF_UP,OF_DOWN,OF_LEFT,OF_RIGHT,OF_VERT,OF_HOR
};

void drawBox(double x, double y, double width, double height, float r=1, float g=1, float b=1, float a=1);

void shadeBox(double x, double y, double width, double height, float r,float g, float b, float perc=.2);

void ofShadeBox(double x, double y, double width, double height, ofDirection d=OF_DOWN, float perc=.2);

void ofShade(double x, double y, double span, double length, ofDirection d=OF_UP, float start=.5, bool black=true);

void shadeHor(double x, double y, double width, double height,float strt=.75, float r=0,float g=0, float b=0,float r1=0,float g1=0, float b1=0);

void shadeVer(double x, double y, double width, double height,float start=.75, float r=0,float g=0, float b=0,float rd=0,float gn=0, float bl=0);

void shadeBoxBottom(double x, double y, double width, double height, float r,float g, float b, float perc=.2);

void shadeBoxTop(double x, double y, double width, double height, float r,float g, float b, float perc=.2);

void shadeBoxSide(double x, double y, double width, double height, float r,float g, float b, float perc=.2);

void shadeCircle(int x, int y, int rad, float r, float g, float b, float perc=.2,bool overshade=false,int dir=1);

void ofRaisedCircle(int x, int y, int rad, float perc=.2);

void ofDentCircle(int x, int y, int rad, float perc=.2);
	
void shadeCircleSide(int x, int y, int rad, float r, float g, float b, float perc=.2);
	
void shinyCircle(int x, int y, int rad, float r, float g, float b, float perc=.2);

void shinyCircleInvert(int x, int y, int rad, float r, float g, float b, float perc=.2);

void roundedBox(double x, double y, double width, double height,double rad, float r,float g, float b, float perc=.2);

void ofRoundBox(double x, double y, double width, double height,double rad, double shade=.05);

void ofInvertBox(double x, double y, double width, double height,double rad, double shade=.05);

void ofRoundShape(double x, double y, double width, double height,double rad, bool fill);

void ofCircleShadow(double x, double y, double rad,double shade);

void ofRoundShade(double x, double y, double width, double height,double rad, float start, bool fadeOut=true);

void roundedBoxSide(double x, double y, double width, double height,double rad, float r,float g, float b, float perc=.2);
			
void roundedBoxInvert(double x, double y, double width, double height,double rad, float r,float g, float b, float perc=.2);

void darkCircleSection(int x, int y, int rad,float strt, float end,float a=1);

void drawCircle(int x, int y, int rad, float r, float g, float b,float a=1);

void drawLine(int sx,int sy, int fx, int fy,float r=1, float g=0, float b=0,float wid=3);

void drawCircleSlice(int x, int y, int rad,int rad1, float r, float g, float b,float r1=1, float g1=1, float b1=1,float a=1,float a1=1,float strt=0,float end=1);

void constrainCircleSlice(int x, int y, int rad,int rad1, float r, float g, float b,float a=1,float a1=1,int xint=0, int yint=0, int w=0, int h=0);

void drawSideCircle(int x, int y, int rad, float r, float g, float b,float a=1, int side=0);

void shadeSideCircle(int x, int y, int rad,float a=1,int side=0, float r=0, float g=0, float b=0);

void shine(double x, double y, double width, double height,double rad,float a,float c=1);

void shinyBox(double x, double y, double width, double height,double rad, float r,float g, float b, float perc=.2,float shn=.1);

void shadeBoxCenter(double x, double y, double width, double height, float r,float g, float b, float perc=.2);

void roundedShadow(double x, double y, double w, double h,double rad,double strt);

void ofRoundShadow(double x, double y, double w, double h,double rad,double strt);

void ofRing(double x, double y, double ir, double Or);

void ofRingSegment(double x, double y, double ir, double Or,double start, double finish);

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
