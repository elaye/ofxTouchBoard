#include "Disk.h"

void Disk::setup(){
	basePos = ofPoint(ofGetWidth()/2.0, ofGetHeight()/2.0);
	pos = ofPoint(0.0);
	radius = 50.0;

	bShivering = false;
	shiveringTime = 0.5;
	shiveringStart = 0.0;

	hueAngle = 0;
	color = ofColor(ofColor::red);

	ofSetCircleResolution(30);
}

void Disk::update(){
	if(bShivering){
		float t = ofGetElapsedTimef();
		float s = 100;
		float x = ofMap(t, shiveringStart, shiveringStart +shiveringTime, 1.0, 0.0);
		float a = 3.0 * (1 - exp(-3 * x));
		pos.x = a * sin(17 * t * s);
		pos.y = a * sin(5 * t * s + 3);
		if(t - shiveringStart > shiveringTime){
			bShivering = false;
		}
	}
}

void Disk::draw(){
	ofFill();
	ofSetColor(color);
	ofCircle(basePos + pos, radius);
}

void Disk::shiver(){
	bShivering = true;
	shiveringStart = ofGetElapsedTimef();
}

void Disk::nextColor(){
	hueAngle += 40;
	hueAngle = hueAngle % 360;
	color.setHueAngle(hueAngle);
}

void Disk::prevColor(){
	hueAngle -= 40;
	if(hueAngle < 0){
		hueAngle += 360;
	}
	color.setHueAngle(hueAngle);
}

void Disk::move(float x, float y){
	ofPoint newPos = basePos + ofPoint(x, y);
	if(newPos.x < ofGetWidth() && newPos.x > 0 && newPos.y < ofGetHeight() && newPos.y > 0){
		basePos = newPos;
	}
	
}