//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

class Constants {
public:
    static const chai3d::cVector3d GRAVITY;
    static const double AIR_DAMPING;
    static const size_t MAX_COLLISIONS;
    static const double TIME_STEP;
};
