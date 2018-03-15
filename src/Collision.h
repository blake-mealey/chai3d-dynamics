//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

struct Collision {
    chai3d::cVector3d intersect0;
    chai3d::cVector3d intersect1;
    chai3d::cVector3d normal;
    bool valid;
};
