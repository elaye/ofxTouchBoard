#pragma once

#include "util.h"
#include "Serial.h"

class ofxTouchBoard {

	Serial serial;
	vector<ofxTB::Electrode> electrodes;

	vector<ofParameter<float> > touchThresholds;
	vector<ofParameter<float> > releaseThresholds;

	ofParameterGroup touchThresholdsParams;
	ofParameterGroup releaseThresholdsParams;

	bool bBoardThresholds;

	vector<bool> touchStatus;

	float graphHeight, graphBarWidth, graphBarSpace;
	float jitter;

	public:
		void setup();
		void setup(int deviceId);

		void update();

		void logData();

		void printData(float x, float y);
		void printRawData(float x, float y);
		
		void draw(float x, float y);

		void useBoardThresholds(bool b){ bBoardThresholds = b; }

		const vector<ofxTB::Electrode>& getData(){
			return electrodes;
		}
	
		const vector<ofxTB::Electrode>& getRawData(){
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

		const vector<bool>& getTouchStatus(){
			return touchStatus;
		}
	
		ofEvent<int> touched;
		ofEvent<int> released;
	
	private:
		void init();
		void setupThresholds();
		void updateStatus();
		void drawGraphBar(float x0, float y0, int i, float val, float width, float xOffset);
		void printData(vector<ofxTB::Electrode>& e, float x, float y);
		void printDataLine(float val, float x, float y);
		void printDataLine(int val, float x, float y);
		void exit(ofEventArgs& e);
};