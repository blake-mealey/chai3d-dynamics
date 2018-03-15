//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#include "RigidStatic.h"
#include "Collider.h"

using namespace chai3d;

RigidStatic::RigidStatic(cVector3d a_position) : Rigidbody(a_position) {}

void RigidStatic::ApplyForces(double a_deltaTime) {
    // We do not actually apply forces to ourselves because we are static

    // Clear the forces from this frame
    ClearForces();

    // Update colliders (clear collision count and update render mesh)
    if (m_collider) {
        m_collider->ClearCollisionCount();
        m_collider->GetRenderMesh()->setLocalPos(m_position);
    }
}

cVector3d RigidStatic::GetLinearVelocity() const {
    return cVector3d(0.0, 0.0, 0.0);	// Return the 0 vector because we are a static body
}

cVector3d RigidStatic::GetAngularVelocity() const {
    return cVector3d(0.0, 0.0, 0.0);	// Return the 0 vector because we are a static body
}

double RigidStatic::GetMass() const {
    return 0;	// Might as well be 0
}
