#pragma once

#include "ofMain.h"

#include "defs.h"

class Serial : public ofThread {

	ofSerial serial;

	vector<ofxTB::Electrode> data;
	vector<ofxTB::Electrode> normalizedData;

	int deviceNb;
	int baudRate;
	bool bConnected;

	public:
		void setup();
		void setup(int deviceId);
		void threadedFunction();
        int available();
		void logData();

		vector<ofxTB::Electrode> getData();
		vector<ofxTB::Electrode> getNormalizedData();
		
	private:
		void connect();
		void init();
		void readLine();
};