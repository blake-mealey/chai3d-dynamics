//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

class Collision;
class Rigidbody;

class Collider {
    friend class Rigidbody;
public:
    Collider(double a_collisionStiffness = 1000.0, double a_dampingConstant = 10.0, size_t a_collisionFlag = 1, size_t a_collidesWithMask = 1);
    virtual ~Collider() = default;

    virtual Collision GetCollision(Collider* a_collider) const = 0;
    void AddCollisionForces(Collider *a_collider, bool& a_result0, bool& a_result1);

    void UpdateRenderMesh() const;
    chai3d::cMesh* GetRenderMesh() const;

    Rigidbody* GetParent() const;

    void SetCollisionFlag(size_t a_collisionFlag);
    size_t GetCollisionFlag() const;

    void SetCollidesWithMask(size_t a_collidesWithMask);
    size_t GetCollidesWithMask() const;

    void SetCollisionStiffness(double a_collisionStiffness);
    double GetCollisionStiffness() const;

    void SetDampingConstant(double a_dampingConstant);
    double GetDampingConstant() const;

    void ClearCollisionCount();
    size_t GetCollisionCount() const;

    virtual chai3d::cMatrix3d GetInertiaMatrix() const = 0;
private:
    // Only the Rigidbody should use this
    void SetParent(Rigidbody* a_parent);
protected:
    Rigidbody* m_parent;
    chai3d::cMesh* m_renderMesh;

    double m_collisionStiffness;
    double m_dampingConstant;

    size_t m_collisionFlag;
    size_t m_collidesWithMask;

    size_t m_currentCollisionCount;
};
