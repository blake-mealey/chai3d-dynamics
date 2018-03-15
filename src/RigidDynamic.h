//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

#include "Rigidbody.h"

class RigidDynamic : public Rigidbody {
public:
    RigidDynamic(double a_mass = 1.0,
        chai3d::cVector3d a_position = chai3d::cVector3d(0.0, 0.0, 0.0),
        chai3d::cVector3d a_linearVelocity = chai3d::cVector3d(0.0, 0.0, 0.0));

    void ApplyForces(double a_deltaTime) override;

    void SetMass(double a_mass);
    double GetMass() const override;

    void SetLinearVelocity(chai3d::cVector3d a_linearVelocity);
    chai3d::cVector3d GetLinearVelocity() const override;

    void SetAngularVelocity(chai3d::cVector3d a_angularVelocity);
    chai3d::cVector3d GetAngularVelocity() const override;
private:
    double m_mass;
    chai3d::cVector3d m_linearVelocity;
    chai3d::cVector3d m_angularVelocity;
    chai3d::cVector3d m_angularMomentum;
};
