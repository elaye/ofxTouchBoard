#include "ofApp.h"

void ofApp::setup(){
	touchBoard.setup();
}

void ofApp::update(){
	touchBoard.update();
}

void ofApp::draw(){
	ofBackgroundGradient(ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);	

	ofSetColor(ofColor::white);
	
	touchBoard.printRawData(0, 0);
	touchBoard.draw(0, ofGetHeight());
}