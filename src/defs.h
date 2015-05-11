#pragma once

// TODO: check what is the 13th electrode
#define ELECTRODES_NB 13

#define DATA_NB_LINE 6

struct Electrode {
	// Touch
	bool touch;
	// Touch threshold
	float tths;
	// Release threshold
	float rths;
	// Filtered data
	float fdat;
	// Baseline val
	float bval;	
	// Difference
	float diff;
};