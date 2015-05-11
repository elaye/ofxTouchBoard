#pragma once

#include "ofMain.h"

namespace ofxTB {
	float trunc(float n, int p){
		float e = pow(10.0, p);
		return int(n * e) / e; 
	}
}