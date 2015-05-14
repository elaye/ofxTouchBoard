#pragma once

#include "util.h"
#include "Serial.h"

class ofxTouchBoard {

	Serial serial;
	vector<Electrode> electrodes;

	vector<ofParameter<float> > touchThresholds;
	vector<ofParameter<float> > releaseThresholds;

	ofParameterGroup touchThresholdsParams;
	ofParameterGroup releaseThresholdsParams;



	vector<bool> touchStatus;
	// vector<ofEvent> touchEvents;

	float graphHeight, graphBarWidth, graphBarSpace;
	float jitter;

	public:
		void setup();
		void setupThresholds();

		void update();
		void updateStatus();

		void logData();
		void printData(float x, float y);
		void printRawData(float x, float y);
		void draw(float x, float y);

		const vector<Electrode>& getData(){
			return electrodes;
		}
	
		const vector<Electrode>& getRawData(){
			return serial.getData();
		}

		const vector<ofParameter<float> >& getTouchThresholds(){
			return touchThresholds;
		}

		const vector<ofParameter<float> >& getReleaseThresholds(){
			return releaseThresholds;
		}		

		const ofParameterGroup& getTouchThresholdsParams(){
			return touchThresholdsParams;
		}

		const ofParameterGroup& getReleaseThresholdsParams(){
			return releaseThresholdsParams;
		}
	
		ofEvent<int> touched;
		ofEvent<int> released;
	
	private:
		void drawGraphBar(float x0, float y0, int i, float val, float width, float xOffset);
		void printDataLine(float val, float x, float y);
		void printDataLine(int val, float x, float y);
};