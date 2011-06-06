/*
 *  ofXMLParse.cpp
 *  openFrameworksLib
 *
 *  Created by Exhibits on 5/5/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofXMLParse.h"
#include "ofParsing.h"

ofTag::ofTag(string lbl)
{
	label=lbl;
}

void ofTag::writeOut(ofstream &k, int t)
{
	for(int i=0; i<t; i++) k<<"\t";
	k<< "<"+label;
	for (unsigned int i=0; i<attributes.size(); i++) {
		k<< " "+attributes[i].name+"=\""+attributes[i].value+"\"";
	}
	k<<">";
	if(value.length()) k<< value;
	for (unsigned int i=0; i<subnodes.size(); i++) {
		k<< "\n";
		subnodes[i].writeOut(k, t+1);
	}
	if(subnodes.size()){
		k<<endl;
		for(int i=0; i<t; i++) k<<"\t";
	}
	k<<"</"+label+">";
}

/*void ofTag::writeOut(ofstream &k, int t)
{
	for(int i=0; i<t; i++) cout<<"\t";
	cout<< "<"+label;
	for (unsigned int i=0; i<attributes.size(); i++) {
		cout<< " "+attributes[i].name+"=\""+attributes[i].value+"\"";
	}
	cout<<">";
	if(value.length()) cout<< value;
	for (unsigned int i=0; i<subnodes.size(); i++) {
		cout<< "\n";
		subnodes[i].writeOut(k, t+1);
	}
	if(subnodes.size()){
		cout<<endl;
		for(int i=0; i<t; i++) cout<<"\t";
	}
	cout<<"</"+label+">";
}*/

int ofTag::getNumAttributes()
{
	return attributes.size();
}

string ofTag::getAttributeName(int i)
{
	return attributes[i].name;
}

string ofTag::getAttribute(string attributeName)
{
	string ret;
	for (unsigned int i=0; i<attributes.size(); i++) {
		if(!attributes[i].name.compare(attributeName)){
			ret=attributes[i].value;
			break;
		}
	}
	return ret;
}

string ofTag::getLabel()
{
	return label;
}

void ofTag::addAttribute(string name,string val)
{
	attributes.push_back(xmlAttribute(name,val));
}

int ofTag::addNode(string lbl)
{
	int ret=0;
	subnodes.push_back(ofTag(lbl));
	for (unsigned int i=0; i<subnodes.size(); i++) {
		if(!subnodes[i].label.compare(lbl))
			ret++;
	}
	return ret;
}

ofTag & ofTag::getNode(string lbl, int which)
{
	ofTag * node;
	int cnt=0;
	for (unsigned int i=0; i<subnodes.size(); i++) {
		if(!subnodes[i].label.compare(lbl)){
			node=&subnodes[i];
			if(which==cnt) return subnodes[i];
			else cnt++;
		}
	}
	return *node;
}

ofTag & ofTag::getNode(int which)
{
	return subnodes[which];
}

void ofTag::setValue(string val)
{
	value=val;
}

int ofTag::getNumTags(string label)
{
	int ret=0;
	for (int i=0; i<subnodes.size(); i++) {
		if(!subnodes[i].label.compare(label))
			ret++;
	}		
	return ret;
}

void ofXML::loadFile(string file)
{
	nodes.clear();
	while (prevLevel.size()) prevLevel.pop();
	currentLevel=0;
	filename=file;
	ifstream input(ofToDataPath(file).c_str());
	string buffer;
	bool tagOpen=false;
	while (input.peek()!=EOF) {
		getline(input, buffer);
		for (unsigned int i=0; i<buffer.length(); i++) {
			if(!tagOpen&&buffer[i]=='<'){
				tagOpen=true;
				i++;
				try {
					if(buffer[i]=='/'){
						i++;
						string close=getWord(buffer, i, " >");
						if(!currentTag().compare(close)){
							popTag();
							i--;
						}
						else ofLog(OF_LOG_WARNING, "Tags don't match");
					}
					else {
						string newLabel=getWord(buffer, i, " >");
						i--;
						int n=addTag(newLabel);
						pushTag(newLabel, n);
					}

				}
				catch (string except) {
					ofLog(OF_LOG_WARNING, except);
				}
			}
			else if(tagOpen){
				i=buffer.find_first_not_of(" ",i);
				if(buffer[i]=='>'){
					//writeOut();
					tagOpen=false;
				}
				else if(buffer[i]=='/'&&i<buffer.length()-1&&buffer[i+1]=='>'){
					popTag();
				}
				else {
					string aName=getWord(buffer, i, " =");
					i=buffer.find_first_not_of("=\"",i);
					string aValue=getWord(buffer, i, "\"");
					addAttribute(aName,aValue);
				}
			}
			else if(!tagOpen&&buffer[i]!='\t'&&buffer[i]!='\n'){
				string val=getWord(buffer,i,"<");
				i--;
				currentLevel->setValue(val);
			}
		}
	}
}

ofTag & ofXML::getTag(int i)
{
	ofTag * node; 
	if(currentLevel)
		node=&currentLevel->getTag(i);
	else {
		node=&nodes[i];
	}
	return *node;
}

vector<int> ofTag::findTag(ofTag * find){
	vector<int> ret;
	for (unsigned int i=0; i<subnodes.size(); i++) {
		if(subnodes[i].findTag(find).size()){
			ret=subnodes[i].findTag(find);
		}
		else if(find==&subnodes[i]) ret.push_back(i);
	}
	return ret;
}

void ofXML::addValue(string label,string value)
{
	newCurrentTag(label);
	currentLevel->setValue(value);
	popTag();
}

int ofXML::addTag(string label)
{
	int ret=0;
	if(!currentLevel){
		nodes.push_back(ofTag(label));
		for (int i=0; i<nodes.size(); i++) {
			if(!nodes[i].label.compare(label))
				ret++;
		}
	}
	else {
		ret=currentLevel->addNode(label);
	}
	return ret-1;
}

void ofXML::newCurrentTag(string label)
{
	pushTag(label, addTag(label));
}

void ofXML::addAttribute(string name,string val)
{
	if(currentLevel)
		currentLevel->addAttribute(name, val);
}

void ofXML::removeAttribute(string label)
{
	
}

string ofXML::getAttribute(string name)
{
	string ret;
	if(currentLevel)
		ret=currentLevel->getAttribute(name);
	return ret;
}

void ofXML::removeTag(string label, int which)
{
	
}



int ofXML::getNumTag(string label){
	int ret=0;
	if(!currentLevel)
		for (int i=0; i<nodes.size(); i++) {
			if(!nodes[i].label.compare(label))
				ret++;
		}
	else {
		ret=currentLevel->getNumTags(label);
	}
	return ret;
}

int ofXML::getNumTags(string fullPath, ...)
{
	bool found=false;
	int ret=0;
	bool isRelative=true;
	if (fullPath[0]==';') {
		isRelative=false;
		while (prevLevel.size()>0) {
			popTag();
		}
		fullPath=string(fullPath,1,fullPath.length()-1);
	}
	vector<string> tags=ofSplitString(fullPath, ":");
	int which;
	va_list vl;
	va_start(vl,tags.size());
	for (unsigned int i=0; i<tags.size()-1; i++) {
		which=va_arg(vl,int);
		found=pushTag(tags[i], which);
	}
	va_end(vl);
	if(found) ret=currentLevel->getNumTags(tags[tags.size()-1]);
	else ret=0;
	return ret;
}

ofTag & ofXML::getTag(string lbl, int which)
{
	ofTag * node=0;
	if(currentLevel){
		//cout << currentLevel->label << endl;
		//ofTag & cur=*currentLevel;
		//node= &cur.getNode(lbl, which);
		return currentLevel->getNode(lbl, which);
	}
	else {
		int cnt=0;
		for (unsigned int i=0; i<nodes.size(); i++) {
			if(!nodes[i].label.compare(lbl)){
				node=&nodes[i];
				if(which==cnt) return nodes[i];//node=&nodes[i];
				else cnt++;
			}
		}
	}
	return *node;
}

bool ofXML::pushTag(string lbl,int which)
{
	bool ret=false;
	if(getNumTag(lbl)){
		ret=true;
		prevLevel.push(currentLevel);
		currentLevel=&getTag(lbl, which);
	}
	else ofLog(OF_LOG_WARNING, "Tag not found");
	return ret;
}

bool ofXML::pushTag(int pos)
{
	bool ret=true;
	prevLevel.push(currentLevel);
	if(currentLevel) currentLevel=&currentLevel->subnodes[pos];
	else currentLevel=&nodes[pos];
	return ret;
}

void ofXML::popTag()
{
	if(prevLevel.size()>0){
		currentLevel=prevLevel.top();
		prevLevel.pop();
	}
	else ofLog(OF_LOG_WARNING, "at root of file");
}

string ofXML::parentTag()
{
	string ret;
	if(prevLevel.top()){
		ret=prevLevel.top()->label;
	}
	return ret;
}

string ofXML::currentTag()
{
	string ret;
	if(currentLevel){
		ret=currentLevel->label;
	}
	return ret;
}

void ofXML::pushToTag(ofTag * tagToFind)
{
	vector<int> ret;
	while (prevLevel.size()>0) {
		popTag();
	}
	for (unsigned int i=0; i<nodes.size(); i++) {
		if (tagToFind==&nodes[i]) pushTag(i);
		else if(nodes[i].findTag(tagToFind).size()){
			ret=nodes[i].findTag(tagToFind);
			while (ret.size()) {
				pushTag(ret[ret.size()-1]);
				ret.pop_back();
			}
		}
	}
}

void ofXML::pushToParent(string fullPath)
{
	
}

ofTag & ofXML::getCurrentTag()
{
	ofTag * ret=0;
	if(currentLevel) ret=currentLevel;
	else if(nodes.size()) ret=&nodes[0];
	else ofTag("empty file");
	return *ret;
}

bool ofXML::setCurrentTag(string fullPath, ...)
{
	bool ret=false;
	bool isRelative=true;
	if (fullPath[0]==';') {
		isRelative=false;
		while (prevLevel.size()>0) {
			popTag();
		}
		fullPath=string(fullPath,1,fullPath.length()-1);
	}
	vector<string> tags=ofSplitString(fullPath, ":");
	int which;
	va_list vl;
	va_start(vl,tags.size());
	for (unsigned int i=0; i<tags.size(); i++) {
		which=va_arg(vl,int);
		ret=pushTag(tags[i], which);
	}
	va_end(vl);
	return ret;
}

void ofXML::saveFile(){
	for (unsigned int i=0; i<nodes.size(); i++) {
		ofstream k(ofToDataPath(filename+"test").c_str());
		nodes[i].writeOut(k,0);
		k.close();
	}
}

void ofXML::writeFile(string file){
	ofstream k(ofToDataPath(file).c_str());
	for (unsigned int i=0; i<nodes.size(); i++) {
		nodes[i].writeOut(k,0);
	}
	k.close();
}
