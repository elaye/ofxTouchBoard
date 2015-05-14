#include "ofxTouchBoard.h"

void ofxTouchBoard::setup(){
	serial.setup();
	electrodes.resize(ELECTRODES_NB);

	graphHeight = 200;
	graphBarSpace = 10;
	graphBarWidth = 20; 
	jitter = 0.0;

	setupThresholds();

	touchStatus = vector<bool>(ELECTRODES_NB, false);
}

void ofxTouchBoard::setupThresholds(){
	touchThresholds.resize(ELECTRODES_NB);
	releaseThresholds.resize(ELECTRODES_NB);

	for(int i = 0; i < ELECTRODES_NB; ++i){
		ofParameter<float> t;
		t.set("TTHS" + ofToString(i), 0.15625, 0.0, 1.0);
		ofParameter<float> r;
		r.set("RTHS" + ofToString(i), 0.078125, 0.0, 1.0);
		touchThresholds[i] = t;
		releaseThresholds[i] = r;
	
		touchThresholdsParams.add(touchThresholds[i]);
		releaseThresholdsParams.add(releaseThresholds[i]);
	}
}

void ofxTouchBoard::update(){
	serial.update();

	vector<Electrode> rawData(serial.getNormalizedData());

	if(electrodes.size() == rawData.size()){
		for(int i = 0; i < electrodes.size(); ++i){
			electrodes[i].touch = rawData[i].touch;
			electrodes[i].diff = (1.0 - jitter) * rawData[i].diff + jitter * electrodes[i].diff;
			electrodes[i].bval = (1.0 - jitter) * rawData[i].bval + jitter * electrodes[i].bval;
			electrodes[i].fdat = (1.0 - jitter) * rawData[i].fdat + jitter * electrodes[i].fdat;
			electrodes[i].tths = rawData[i].tths;
			electrodes[i].rths = rawData[i].rths;
		}
	}
	else{
		ofLog() << "electrodes.size() != rawData.size()";
	}
	updateStatus();
}

void ofxTouchBoard::updateStatus(){
	for(int i = 0; i < touchStatus.size(); ++i){
		if(electrodes[i].diff > touchThresholds[i] && !touchStatus[i]){
			touchStatus[i] = true;
			// ofLog() << "touch " << i;
			ofNotifyEvent(touched, i, this);
		}
		if(electrodes[i].diff < releaseThresholds[i] && touchStatus[i]){
			touchStatus[i] = false;
			// ofLog() << "release " << i;
			ofNotifyEvent(released, i, this);
		}
	}
}

void ofxTouchBoard::logData(){
	serial.logData();
}



void ofxTouchBoard::draw(float x, float y){
	for(int i = 0; i < electrodes.size(); ++i){
		Electrode e(electrodes[i]);

		// ofSetColor(ofColor(147, 147, 147, 100));
		// if(e.touch){
			ofSetColor(ofColor(35, 255, 106, 100));
		// }
		// else{
			// ofSetColor(ofColor(147, 147, 147, 100));
		// }
		// Draw filter data graph bar
		drawGraphBar(x, y, i, e.fdat, graphBarWidth/2.0, -graphBarWidth/4.0);	
		// Draw base value graph bar
		ofSetColor(ofColor(35, 106, 255, 100));
		drawGraphBar(x, y, i, e.bval, graphBarWidth/2.0, graphBarWidth/4.0);
		// Draw touch threshold graph bar
		// drawGraphBar(i, e.tths, graphBarWidth);

		// Draw diff graph bar
		// if(e.touch){
		// 	ofSetColor(ofColor(35, 255, 106));
		// }
		// else{
		// 	ofSetColor(ofColor(35, 106, 255));
		// }
		// drawGraphBar(i, e.diff, graphBarWidth);

		// Draw release threshold graph bar
		// ofSetColor(ofColor(147, 147, 147, 100));
		// drawGraphBar(i, e.rths, graphBarWidth);
	}
}

void ofxTouchBoard::drawGraphBar(float x0, float y0, int i, float val, float width, float xOffset){
	float y = y0 - (val * graphHeight)/2.0;
	float x = x0 + graphBarWidth + xOffset + (graphBarWidth + graphBarSpace) * i;
	ofDrawPlane(x, y, width, val * graphHeight);
}

void ofxTouchBoard::printData(float x, float y){
	float charWidth = 11;
	float charHeight = 15;
	float xOffset = x;
	float yOffset = y + charHeight;
	float colWidth = 30;
	float rowHeight = 20;
	ofDrawBitmapString("E", x, yOffset);
	xOffset += 2 * charWidth;
	ofDrawBitmapString("TOUCH", xOffset, yOffset);
	xOffset += 5 * charWidth;
	ofDrawBitmapString("TTHS", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("RTHS", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("FDAT", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("BVAL", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("DIFF", xOffset, yOffset);
	yOffset += charHeight;

	for(int i = 0; i < electrodes.size(); ++i){
		xOffset = x;
		printDataLine(i, xOffset, yOffset);
		xOffset += 2 * charWidth;
		printDataLine(electrodes[i].touch, xOffset, yOffset);
		xOffset += 5 * charWidth;
		printDataLine(electrodes[i].tths, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(electrodes[i].rths, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(electrodes[i].fdat, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(electrodes[i].bval, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(electrodes[i].diff, xOffset, yOffset);
		yOffset += charHeight;
	}
}

void ofxTouchBoard::printRawData(float x, float y){
	vector<Electrode> raw(serial.getData());
	float charWidth = 11;
	float charHeight = 15;
	float xOffset = x;
	float yOffset = y + charHeight;
	float colWidth = 30;
	float rowHeight = 20;
	ofDrawBitmapString("E", x, yOffset);
	xOffset += 2 * charWidth;
	ofDrawBitmapString("TOUCH", xOffset, yOffset);
	xOffset += 5 * charWidth;
	ofDrawBitmapString("TTHS", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("RTHS", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("FDAT", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("BVAL", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("DIFF", xOffset, yOffset);
	yOffset += charHeight;

	for(int i = 0; i < raw.size(); ++i){
		xOffset = x;
		printDataLine(i, xOffset, yOffset);
		xOffset += 2 * charWidth;
		printDataLine(raw[i].touch, xOffset, yOffset);
		xOffset += 5 * charWidth;
		printDataLine(raw[i].tths, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(raw[i].rths, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(raw[i].fdat, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(raw[i].bval, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(raw[i].diff, xOffset, yOffset);
		yOffset += charHeight;
	}
}

void ofxTouchBoard::printDataLine(float val, float x, float y){
	ofDrawBitmapString(ofToString(ofxTB::trunc(val, 2)), x, y);
}

void ofxTouchBoard::printDataLine(int val, float x, float y){
	ofDrawBitmapString(ofToString(val), x, y);
}



