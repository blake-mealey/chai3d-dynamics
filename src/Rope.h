//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

#include "Spring.h"

class Rope : public Spring {
public:
    Rope(Rigidbody *a_body0, Rigidbody *a_body1, double a_naturalLength = 0.05, double a_springStiffness = 200.0, double a_dampingConstant = 5.0);
    Rope(Rigidbody *a_body0, chai3d::cVector3d a_pos0, Rigidbody *a_body1, chai3d::cVector3d a_pos1, double a_naturalLength = 0.05, double a_springStiffness = 200.0, double a_dampingConstant = 5.0);

    void AddForces() const override;
};
