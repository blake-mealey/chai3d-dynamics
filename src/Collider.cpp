//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#include "Collider.h"
#include "Rigidbody.h"
#include "Constants.h"
#include "Collision.h"

using namespace chai3d;

Collider::Collider(double a_collisionStiffness, double a_dampingConstant, size_t a_collisionFlag, size_t a_collidesWithMask) :
    m_parent(nullptr), m_renderMesh(nullptr), m_collisionStiffness(a_collisionStiffness), m_dampingConstant(a_dampingConstant),
    m_collisionFlag(a_collisionFlag), m_collidesWithMask(a_collidesWithMask), m_currentCollisionCount(0) {}

void Collider::AddCollisionForces(Collider *a_collider, bool& a_result0, bool& a_result1) {
    // By default, no collisions
    a_result0 = false;
    a_result1 = false;

    // Check which colliders collide with each other
    bool body0CollidesWithBody1 = (m_collidesWithMask & a_collider->m_collisionFlag) != 0;
    bool body1CollidesWithBody0 = (a_collider->m_collidesWithMask & m_collisionFlag) != 0;
    if (!body0CollidesWithBody1 && !body1CollidesWithBody0) return;

    // Get the collision normal and return if there was no collision
    Collision collision = GetCollision(a_collider);
    if (!collision.valid) return;

    // Get stiffness and constants
    double collisionStiffness0 = m_collisionStiffness;
    double dampingConstant0 = m_dampingConstant;
    double collisionStiffness1 = a_collider->m_collisionStiffness;
    double dampingConstant1 = a_collider->m_dampingConstant;

    // Get the rigidbodies
    Rigidbody* body0 = m_parent;
    Rigidbody* body1 = a_collider->m_parent;

    // Get the relative velocity of the bodies
    cVector3d relativeVelocity = body1->GetLinearVelocity() - body0->GetLinearVelocity();

    // Calculate and add force on body0
    if (body0CollidesWithBody1 && m_currentCollisionCount < Constants::MAX_COLLISIONS) {
        // Increment collision count
        m_currentCollisionCount++;

        // Calculate and add force of collision (with damping)
        cVector3d collisionForce0 = -collisionStiffness0 * collision.normal;
        cVector3d collisionDampingForce0 = -dampingConstant0 * cProject(relativeVelocity, collision.normal);
        cVector3d netForce0 = collisionForce0 + collisionDampingForce0;
        body0->AddForce(-netForce0, collision.intersect0 - body0->GetPosition());

        // Return collision status
        a_result0 = true;
    }

    // Calculate and add force on body1
    if (body1CollidesWithBody0 && a_collider->m_currentCollisionCount < Constants::MAX_COLLISIONS) {
        // Increment collision count
        a_collider->m_currentCollisionCount++;

        // Calculate and add force of collision (with damping)
        cVector3d collisionForce1 = -collisionStiffness1 * collision.normal;
        cVector3d collisionDampingForce1 = -dampingConstant1 * cProject(relativeVelocity, collision.normal);
        cVector3d netForce1 = collisionForce1 + collisionDampingForce1;
        body1->AddForce(netForce1, collision.intersect1 - body1->GetPosition());

        // Return collision status
        a_result1 = true;
    }
}

void Collider::UpdateRenderMesh() const {
    if (!m_parent || !m_renderMesh) return;
    m_renderMesh->setLocalPos(m_parent->GetPosition());
}

cMesh* Collider::GetRenderMesh() const {
    return m_renderMesh;
}

void Collider::SetParent(Rigidbody* a_parent) {
    m_parent = a_parent;
}

Rigidbody* Collider::GetParent() const {
    return m_parent;
}

void Collider::SetCollisionFlag(size_t a_collisionFlag) {
    m_collisionFlag = a_collisionFlag;
}

size_t Collider::GetCollisionFlag() const {
    return m_collisionFlag;
}

void Collider::SetCollidesWithMask(size_t a_collidesWithMask) {
    m_collidesWithMask = a_collidesWithMask;
}

size_t Collider::GetCollidesWithMask() const {
    return m_collidesWithMask;
}

void Collider::SetCollisionStiffness(double a_collisionStiffness) {
    m_collisionStiffness = a_collisionStiffness;
}

double Collider::GetCollisionStiffness() const {
    return m_collisionStiffness;
}

void Collider::SetDampingConstant(double a_dampingConstant) {
    m_dampingConstant = a_dampingConstant;
}

double Collider::GetDampingConstant() const {
    return m_dampingConstant;
}

void Collider::ClearCollisionCount() {
    m_currentCollisionCount = 0;
}

size_t Collider::GetCollisionCount() const {
    return m_currentCollisionCount;
}
