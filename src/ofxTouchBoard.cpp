#include "ofxTouchBoard.h"

void ofxTouchBoard::setup(int deviceId){
	serial.setup(deviceId);
	init();
}

void ofxTouchBoard::setup(){
	serial.setup();
	init();
}

void ofxTouchBoard::init(){
	ofAddListener(ofEvents().exit, this, &ofxTouchBoard::exit);
	serial.startThread(false);
	electrodes.resize(ofxTB::ELECTRODES_NB);

	graphHeight = 200;
	graphBarSpace = 10;
	graphBarWidth = 20; 
	jitter = 0.0;

	bBoardThresholds = true;

	setupThresholds();

	touchStatus = vector<bool>(ofxTB::ELECTRODES_NB, false);
}

void ofxTouchBoard::setupThresholds(){
	touchThresholds.resize(ofxTB::ELECTRODES_NB);
	releaseThresholds.resize(ofxTB::ELECTRODES_NB);

	for(int i = 0; i < ofxTB::ELECTRODES_NB; ++i){
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
	serial.lock();
		vector<ofxTB::Electrode> rawData(serial.getNormalizedData());
	serial.unlock();
	
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
		bool touchEvent;
		bool releaseEvent; 

		if(bBoardThresholds){
			touchEvent = electrodes[i].touch && !touchStatus[i];
			releaseEvent = !electrodes[i].touch && touchStatus[i]; 
		}
		else{
			touchEvent = electrodes[i].diff > touchThresholds[i] && !touchStatus[i];
			releaseEvent = electrodes[i].diff < releaseThresholds[i] && touchStatus[i];
		}

		if(touchEvent){
			touchStatus[i] = true;
			// ofLog() << "touch " << i;
			ofNotifyEvent(touched, i, this);
		}
		if(releaseEvent){
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
		ofxTB::Electrode e(electrodes[i]);

		// Draw filter data graph bar
		ofSetColor(ofColor(35, 255, 106, 100));
		drawGraphBar(x, y, i, e.fdat, graphBarWidth/2.0, -graphBarWidth/4.0);	
		// Draw base value graph bar
		ofSetColor(ofColor(35, 106, 255, 100));
		drawGraphBar(x, y, i, e.bval, graphBarWidth/2.0, graphBarWidth/4.0);

	}
}

void ofxTouchBoard::drawGraphBar(float x0, float y0, int i, float val, float width, float xOffset){
	float y = y0 - (val * graphHeight)/2.0;
	float x = x0 + graphBarWidth + xOffset + (graphBarWidth + graphBarSpace) * i;
	ofDrawPlane(x, y, width, val * graphHeight);
}

void ofxTouchBoard::printData(float x, float y){
	printData(electrodes, x, y);
}

void ofxTouchBoard::printRawData(float x, float y){
	serial.lock();
		vector<ofxTB::Electrode> raw(serial.getData());
	serial.unlock();
	
	printData(raw, x, y);
}

void ofxTouchBoard::printData(vector<ofxTB::Electrode>& e, float x, float y){
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

	for(int i = 0; i < e.size(); ++i){
		xOffset = x;
		printDataLine(i, xOffset, yOffset);
		xOffset += 2 * charWidth;
		printDataLine(e[i].touch, xOffset, yOffset);
		xOffset += 5 * charWidth;
		printDataLine(e[i].tths, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(e[i].rths, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(e[i].fdat, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(e[i].bval, xOffset, yOffset);
		xOffset += 4 * charWidth;
		printDataLine(e[i].diff, xOffset, yOffset);
		yOffset += charHeight;
	}
}

void ofxTouchBoard::printDataLine(float val, float x, float y){
	ofDrawBitmapString(ofToString(ofxTB::trunc(val, 2)), x, y);
}

void ofxTouchBoard::printDataLine(int val, float x, float y){
	ofDrawBitmapString(ofToString(val), x, y);
}

void ofxTouchBoard::exit(ofEventArgs& e){
	serial.waitForThread();
}

void ofxTouchBoard::useBoardThresholds(bool b){
    bBoardThresholds = b;
}

const vector<ofxTB::Electrode>& ofxTouchBoard::getData(){
    return electrodes;
}

const vector<ofxTB::Electrode>& ofxTouchBoard::getRawData(){
    return serial.getData();
}

const vector<ofParameter<float> >& ofxTouchBoard::getTouchThresholds(){
    return touchThresholds;
}

const vector<ofParameter<float> >& ofxTouchBoard::getReleaseThresholds(){
    return releaseThresholds;
}

const ofParameterGroup& ofxTouchBoard::getTouchThresholdsParams(){
    return touchThresholdsParams;
}

const ofParameterGroup& ofxTouchBoard::getReleaseThresholdsParams(){
    return releaseThresholdsParams;
}

const vector<bool>& ofxTouchBoard::getTouchStatus(){
    return touchStatus;
}



