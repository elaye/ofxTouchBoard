#include "ofApp.h"

void ofApp::setup(){
	touchBoard.setup();

	ofAddListener(touchBoard.touched, this, &ofApp::touched);
	ofAddListener(touchBoard.released, this, &ofApp::released);
}

void ofApp::update(){
	touchBoard.update();
}

void ofApp::draw(){
	ofBackground(ofColor(20));

	int n = ofxTB::ELECTRODES_NB;
	float radius = 20.0;
	float space = (ofGetWidth() - 2 * n * radius) / (n + 1);
	
	for(int i = 0; i < ofxTB::ELECTRODES_NB; ++i){
		if(touchBoard.getTouchStatus()[i]){
			ofSetHexColor(0x82D87F);
		}
		else{
			ofSetHexColor(0x959595);
		}
		ofCircle(space + (2*radius + space) * i + radius, ofGetHeight()/2.0, radius);
	}
}

void ofApp::touched(int& id){
	ofLog() << "Electrode " << id << " touched";
}

void ofApp::released(int& id){
	ofLog() << "Electrode " << id << " released";
}