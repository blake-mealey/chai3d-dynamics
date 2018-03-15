//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

#include "Rigidbody.h"

class RigidStatic : public Rigidbody {
public:
    explicit RigidStatic(chai3d::cVector3d a_position = chai3d::cVector3d(0.0, 0.0, 0.0));

    void ApplyForces(double a_deltaTime) override;

    double GetMass() const override;

    chai3d::cVector3d GetLinearVelocity() const override;
    chai3d::cVector3d GetAngularVelocity() const override;
};
