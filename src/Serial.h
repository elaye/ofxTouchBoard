#pragma once

#include "ofMain.h"

#include "defs.h"

// class Serial : public ofThread {
class Serial {

	ofSerial serial;
	vector<Electrode> data;
	vector<Electrode> normalizedData;

	public:
		void setup();
		// void threadedFunction();
		void update();
		void flush(){ serial.flush(); serial.drain(); }
		int available(){ return serial.available(); }
		
		void readData();
		void readLine();
		// void normalizeData();
		void logData();

		vector<Electrode> getData();
		vector<Electrode> getNormalizedData();
		
};