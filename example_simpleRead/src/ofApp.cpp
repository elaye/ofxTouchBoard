#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	touchBoard.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	touchBoard.update();
	// touchBoard.logData();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);	
	ofSetColor(ofColor::white);
	touchBoard.printRawData(0, 0);
	touchBoard.draw(0, ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}