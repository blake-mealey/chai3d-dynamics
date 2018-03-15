//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

class Collider;

class Rigidbody {
public:
    virtual ~Rigidbody();
    explicit Rigidbody(chai3d::cVector3d a_position = chai3d::cVector3d(0.0, 0.0, 0.0));

    void ClearForces();
    void AddForce(chai3d::cVector3d a_force, chai3d::cVector3d a_localPosition = chai3d::cVector3d(0.0, 0.0, 0.0));
    chai3d::cVector3d GetCurrentNetForce() const;
    virtual void ApplyForces(double a_deltaTime) = 0;

    virtual chai3d::cVector3d GetLinearVelocity() const = 0;
    virtual chai3d::cVector3d GetAngularVelocity() const = 0;
    virtual double GetMass() const = 0;

    void SetPosition(chai3d::cVector3d a_position);
    chai3d::cVector3d GetPosition() const;

    void SetRotation(chai3d::cQuaternion a_rotation);
    chai3d::cQuaternion GetRotation() const;
    chai3d::cMatrix3d GetRotationMatrix() const;

    // TODO: Should be add/get index
    void SetCollider(Collider* a_collider);
    Collider* GetCollider() const;

    void UpdateInertiaMatrix();
protected:
    chai3d::cVector3d m_position;
    chai3d::cQuaternion m_rotation;
    chai3d::cMatrix3d m_inertiaMatrix;

    chai3d::cVector3d m_currentNetForce;
    chai3d::cVector3d m_currentNetMoment;

    // TODO: Should really be a vector of colliders, but I don't think it is ever necessary for this assignment
    Collider* m_collider;
};
