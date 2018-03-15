//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

#include "NConstraint.h"

class TorsionSpring : public NConstraint<3> {
public:
    TorsionSpring(Rigidbody *a_body0, Rigidbody *a_body1, Rigidbody *a_body2, double a_naturalAngleRadians, double a_springStiffness = 200.0, double a_dampingConstant = 5.0);

    void AddForces() const override;

    void UpdateRenderMesh() const override;

protected:
    double m_naturalAngleRadians;
    double m_springStiffness;
    double m_dampingConstant;

    chai3d::cShapeLine* m_line1to0;
    chai3d::cShapeLine* m_line1to2;
};
