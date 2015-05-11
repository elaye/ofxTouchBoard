#pragma once

#include "Serial.h"

class ofxTouchBoard {

	Serial serial;
	vector<Electrode> electrodes;

	float jitter;

	public:
		void setup();
		void update();
		void logData();
};