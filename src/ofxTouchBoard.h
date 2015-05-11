#pragma once

#include "util.h"
#include "Serial.h"

class ofxTouchBoard {

	Serial serial;
	vector<Electrode> electrodes;

	float graphHeight, graphBarWidth, graphBarSpace;
	float jitter;

	public:
		void setup();
		void update();
		void logData();
		void printData(float x, float y);
		void draw(float x, float y);

		const vector<Electrode>& getData(){
			return electrodes;
		}
	
	private:
		void drawGraphBar(float x0, float y0, int i, float val, float width, float xOffset);
		void printDataLine(float val, float x, float y);
		void printDataLine(int val, float x, float y);
};