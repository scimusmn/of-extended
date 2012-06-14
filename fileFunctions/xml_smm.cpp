/*
 *  xml_smm.cpp
 *  robotBlocks_redux
 *
 *  Created by Exhibits on 1/31/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "xml_smm.h"
#include "ofMain.h"

xmlParse::xmlParse(const char * l ,xmlParse * p,const char * n,const char * v){
	parent=p;
	name=n;
	value=v;
	label=l;
	prop="";
	read=false;
	nodePtr=0;
}
xmlParse::~xmlParse(){
	child.clear();
}
void xmlParse::addChild(const char * l ,const char * n,const char * v){
	child.push_back(xmlParse(l,this,n,v));
}
void xmlParse::addName(const char * n){
	name=n;
}
void xmlParse::addValue(const char* v){
	value=v;
}

void xmlParse::addAttribute(string aName, string aValue){
	attribName=aName;
	attrib=aValue;
}

void xmlParse::addProperty(const char* p){
	prop=p;
}
xmlParse * xmlParse::stepDown(unsigned int next){
	if(child.size()>(next-1)){
		return &child[next-1];
	}
	else return this;
}
bool xmlParse::isChild(){
	return parent!=0;
}
xmlParse * xmlParse::stepUp(){
	return parent;
}
int xmlParse::numChildren(){
	return child.size();
}
bool xmlParse::lastGeneration(){
	return child.empty();
}
int xmlParse::size(){
	return child.size();
}
string xmlParse::getSubNode(string k){
	bool found=false;
	string ret;
	for (unsigned int i=0; i<child.size(); i++) {
		if (k.compare(child[i].label)==0&&!child[i].read) {
			ret=child[i].value;
			child[i].read=true;
			found=true;
		}
		else if(i==child.size()-1&&!found){
			printf("Invalid search parameter; returning null string \n");
			ret="";
		}
	}
	return ret;
}

void xmlParse::write(){
	cout << label <<endl;
	for (unsigned int i=0; i< child.size(); i++) {
		cout << "\t";
		child[i].write();
	}
}

string * xmlParse::getNextSubnode(){
	string * ret;
	if(nodePtr<size()){
		*ret = child[nodePtr].label;
		*(++ret) = child[nodePtr].value;
		nodePtr++;
	}
	else{
		ret=0;
	}
	return ret;
}
string * xmlParse::getSubnode(int i){
	string * ret;
	ret = new string[2];
	if(i<size()){
		ret[0] = child[i].label;
		ret[1] = child[i].value;
	}
	else{
		ret[0]="0";
	}
	return ret;
}

xmlParse * parseFile(const char * filename){
	ifstream doc(ofToDataPath(filename).c_str());
	xmlParse * cur;
	char buffer[256];
	int strtCrs=0;
	int endCrs=0;
	if(doc==NULL){
		printf("Invalid filestream\n");
		return NULL;
	}
	doc.getline(buffer,256);
	bool first=true;
	for (int i=0; i<256; i++) {
		if(buffer[i]=='<'){
			if(buffer[i+1]!='/'){
				strtCrs=endCrs=++i;
				while (buffer[endCrs]!=' ') {
					endCrs++;
				}
				string label(buffer,strtCrs,endCrs-strtCrs);
				cur = new xmlParse(label.c_str());
				i=strtCrs=++endCrs;
				if(buffer[i]=='f'&&buffer[i+1]=='o'&&buffer[i+2]=='n'){
					while (buffer[strtCrs]!='"') {
						strtCrs++;
					}
					endCrs=++strtCrs;
					while (buffer[endCrs]!='"') {
						endCrs++;
					}
					string prop(buffer,strtCrs,endCrs-strtCrs);
					cur->addProperty(prop.c_str());
				}
				first=false;
				i=256;
			}
		}
		else if(first){
			printf("Invalid file type; expected < \n");
			return NULL;
		}
	}
	while (doc.peek()!=EOF) {
		doc.getline(buffer,256);
		strtCrs=endCrs=0;
		if(buffer[0]!='#'){
			for (int i=0; buffer[i]; i++) {
				switch (buffer[i]) {
					case '<':{
						if(buffer[i+1]!='/'){
							strtCrs=endCrs=++i;
							while (buffer[endCrs]!=' '&&buffer[endCrs]!='>') {
								endCrs++;
							}
							string label(buffer,strtCrs,endCrs-strtCrs);
							cur->addChild(label.c_str());
							//cout <<cur->label << "::" << cur->child[cur->child.size()-1].label<<endl;
							cur=cur->stepDown(cur->numChildren());
							//cout << "\nMoving to " << cur->label << endl;
						}
						else if(buffer[i+1]=='/'){
							if (cur->isChild()) {
								//cout << "ending " << cur->label <<endl;
								cur=cur->stepUp();
								//cout<<"Moving to " << cur->label <<endl;
							}
							else {
								//cout << cur->label << " is the current name" <<endl;
							}
							
						}}
						break;
					case ' ':{
						if (i==endCrs||buffer[i-1]=='"') {
							i++;
							strtCrs=endCrs=i;
							char inter[4];
							for (int j=0; j<4; j++) {
								inter[j]=buffer[i+j];
							}
							if(inter[0]=='n'&&inter[1]=='a'&&inter[2]=='m'){
								while (buffer[strtCrs]!='"') {
									strtCrs++;
								}
								endCrs=++strtCrs;
								while (buffer[endCrs]!='"') {
									endCrs++;
								}
								i=endCrs;
								string name(buffer,strtCrs,endCrs-strtCrs);
								cur->addName(name.c_str());
							}
							else if (inter[0]=='c'&&inter[1]=='o'&&inter[2]=='l') {
								while (buffer[strtCrs]!='"') {
									strtCrs++;
								}
								endCrs=++strtCrs;
								while (buffer[endCrs]!='"') {
									endCrs++;
								}
								i=endCrs;
								string prop(buffer,strtCrs,endCrs-strtCrs);
								cur->addProperty(prop.c_str());
							}
						}}
						break;
					case '>':
						if(buffer[i+1]&&buffer[i+1]!='\n'&&buffer[i+1]!='\r'){
							strtCrs=endCrs=++i;
							while (buffer[endCrs]!='<') {
								endCrs++;
							}
							string value(buffer,strtCrs,endCrs-strtCrs);
							cur->addValue(value.c_str());
						}
						break;
					case '\n':
						break;
						
					default:
						break;
				}
			}
		}
	}
	return cur;
}
