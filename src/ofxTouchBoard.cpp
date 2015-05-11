#include "ofxTouchBoard.h"

void ofxTouchBoard::setup(){
	serial.setup();
	electrodes.resize(ELECTRODES_NB);
	jitter = 0.0;
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
}

void ofxTouchBoard::logData(){
	serial.printData();
}