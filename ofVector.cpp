/*
 *  ofVector.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 1/24/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofVector.h"

ofVector::ofVector(double X, double Y, double Z){
	x=X,y=Y,z=Z;
}

ofVector::ofVector(const ofVector & B){
	x=B.x,y=B.y,z=B.z;
}

ofVector::ofVector(const ofPoint & P)
{
	x=P.x,y=P.y,z=P.z;
}

double ofVector::mag(){
	return sqrt(x*x+y*y+z*z);
}

void ofVector::operator=(ofVector A)
{
	x=A.x;
	y=A.y;
	z=A.z;
}

void ofVector::operator=(double c)
{
	x=c;
	y=c;
	z=c;
}

double ofVector::operator*(ofVector B)
{
	return x*B.x+y*B.y+z*B.z;
}

ofVector ofVector::operator^(ofVector B)
{
	return ofVector(y*B.z-z*B.y,z*B.x-x*B.z,x*B.y-y*B.x);
}

ofVector ofVector::operator*(double c)
{
	return ofVector(x*c, y*c,z*c);
}

ofVector ofVector::operator/(double c)
{
	return ofVector(x/c, y/c,z/c);
}

ofVector ofVector::operator+(ofVector A)
{
	return ofVector(x+A.x, y+A.y, z+A.z);
}

ofVector ofVector::operator-(ofVector A)
{
	return ofVector(x-A.x,y-A.y,z-A.z);
}

void ofVector::operator-=(ofVector A)
{
	x-=A.x;
	y-=A.y;
	z-=A.z;
}

void ofVector::operator+=(ofVector A)
{
	x+=A.x;
	y+=A.y;
	z+=A.z;
}

void ofVector::operator*=(double c)
{
	x*=c;
	y*=c;
	z*=c;
}

ofVector ofVector::rotate(double deg)
{
	deg=M_PI*deg/180.;
	
	double xTemp = (x* cos(deg)) - (y * sin(deg));
	y = (x* sin(deg)) + (y * cos(deg));
	x=xTemp;
  return *this;
}

double ofVector::angleDifference(ofVector b)
{
  
}

double ofVector::absoluteAngle()
{
  double ret=180*atan(x/y)/M_PI;
  if(y>0) ret+=180;
  return ret;
}

ofVector ofVector::operator-()
{
	return ofVector(-x,-y,-z);
}

double ofVector::slope(){
	return y/x;
}

ofVector ofVector::unit(){
	return ofVector(x/mag(), y/mag(),z/mag());
}

ofVector ofVector::ortho(){
	return ofVector (y,-x);
}

ofVector operator*(double c, ofVector B)
{
	return ofVector(B*c);
}

ofPoint operator+(ofPoint p, ofVector v){
	return ofPoint(p.x+v.x,p.y+v.y,p.z+v.z);
}

ofPoint operator-(ofPoint p, ofVector v){
	return p+(-v);
}

ofVector sqrt(ofVector k){
	return ofVector(sqrt(k.x),sqrt(k.y),sqrt(k.z));
}
