//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

#include "Collider.h"

class SphereCollider : public Collider {
public:
    SphereCollider(double a_radius = 0.01, double a_collisionStiffness = 1000.0, double a_dampingConstant = 10.0, size_t a_collisionFlag = 1, size_t a_collidesWithMask = 1);

    Collision GetCollision(Collider* a_collider) const override;

    void SetRadius(double a_radius);
    double GetRadius() const;

    chai3d::cMatrix3d GetInertiaMatrix() const override;
private:
    void CreateRenderMesh();

    double m_radius;
};
