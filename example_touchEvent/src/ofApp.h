#pragma once

#include "ofMain.h"

#include "ofxTouchBoard.h"

class ofApp : public ofBaseApp{

	ofxTouchBoard touchBoard;

	public:
		void setup();
		void update();
		void draw();

		void touched(int& e);
		void released(int& e);
};
