#include "ofApp.h"

void ofApp::setup(){
	touchBoard.setup();
}

void ofApp::update(){
	touchBoard.update();
}

void ofApp::draw(){
	ofBackground(ofColor(20));	

	ofSetColor(ofColor::white);
	
	touchBoard.printRawData(0, 0);
	touchBoard.draw(0, ofGetHeight());
}