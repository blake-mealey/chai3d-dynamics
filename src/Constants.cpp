//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#include "Constants.h"

using namespace chai3d;

const cVector3d Constants::GRAVITY = cVector3d(0.0, 0.0, -9.81);	// m/s^2
const double Constants::AIR_DAMPING = 1.0;							// Ns/m
const size_t Constants::MAX_COLLISIONS = -1;						// Infinite
const double Constants::TIME_STEP = 1.0 / 1000.0;					// s
