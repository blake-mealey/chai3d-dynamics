//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

#include "NConstraint.h"

class Spring : public NConstraint<2> {
public:
    Spring(Rigidbody *a_body0, Rigidbody *a_body1, double a_naturalLength = 0.05, double a_springStiffness = 200.0, double a_dampingConstant = 5.0);
    Spring(Rigidbody *a_body0, chai3d::cVector3d a_pos0, Rigidbody *a_body1, chai3d::cVector3d a_pos1, double a_naturalLength = 0.05, double a_springStiffness = 200.0, double a_dampingConstant = 5.0);

    void AddForces() const override;

    void UpdateRenderMesh() const override;

    void SetNaturalLength(double a_naturalLength);
    double GetNaturalLength() const;

    void SetSpringStiffness(double a_springStiffness);
    double GetSpringStiffness() const;

    void SetDampingConstant(double a_dampingConstant);
    double GetDampingConstant() const;
protected:
    chai3d::cVector3d GetPos0() const;
    chai3d::cVector3d GetPos1() const;

    double m_naturalLength;
    double m_springStiffness;
    double m_dampingConstant;

    chai3d::cVector3d m_localPositions[2];
};
