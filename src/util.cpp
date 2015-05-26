#pragma once

#include "util.h"


float ofxTB::trunc(float n, int p){
    float e = pow(10.0, p);
    return int(n * e) / e; 
}