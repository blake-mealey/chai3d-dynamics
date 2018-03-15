//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#include "RigidDynamic.h"
#include "Collider.h"

using namespace chai3d;

RigidDynamic::RigidDynamic(double a_mass, cVector3d a_position, cVector3d a_linearVelocity) :
    Rigidbody(a_position), m_mass(a_mass), m_linearVelocity(a_linearVelocity), m_angularVelocity(cVector3d(0.0, 0.0, 0.0)), m_angularMomentum(cVector3d(0.0, 0.0, 0.0)) {

    UpdateInertiaMatrix();
}

void RigidDynamic::ApplyForces(double a_deltaTime) {
    // POSITIONAL

    // Compute current linear acceleration from current forces (a = F/m)
    cVector3d acceleration = GetCurrentNetForce() / m_mass;

    // Integrate linear acceleration to linear velocity
    m_linearVelocity = m_linearVelocity + a_deltaTime * acceleration;

    // Integrate linear velocity to position using updated velocity (semi-implicit integration)
    m_position = m_position + a_deltaTime * m_linearVelocity;

    // ROTATIONAL

    // Integrate angular momentum from the current net moment
    m_angularMomentum = m_angularMomentum + a_deltaTime * m_currentNetMoment;

    // Compute angular velocity from angular momentum
    // NOTE: The 1/deltaTime seems necessary but I don't see it in my notes
    m_angularVelocity = cInverse(m_inertiaMatrix) * m_angularMomentum / a_deltaTime;

    // Take the derivative of the current rotation to get the next rotation
    cVector3d qV = cVector3d(m_rotation.x, m_rotation.y, m_rotation.z);
    double q0Derivative = -0.5 * cDot(m_angularVelocity, qV);
    cVector3d qVDerivative = 0.5 * (m_rotation.w * m_angularVelocity + cCross(m_angularVelocity, qV));
    cQuaternion derivative = cQuaternion(q0Derivative, qVDerivative.x(), qVDerivative.y(), qVDerivative.z());
    m_rotation = m_rotation + a_deltaTime * derivative;
    m_rotation.normalize();		// Fix wobblies at high speeds

                                // GRAPHICS

                                // Update colliders (clear collision count and update render mesh)
    if (m_collider) {
        m_collider->ClearCollisionCount();

        m_collider->GetRenderMesh()->setLocalPos(m_position);

        cMatrix3d rotMat;
        m_rotation.toRotMat(rotMat);
        m_collider->GetRenderMesh()->setLocalRot(rotMat);
    }

    // RESET

    // Clear the forces from this frame
    ClearForces();
}

void RigidDynamic::SetMass(double a_mass) {
    m_mass = a_mass;
}

double RigidDynamic::GetMass() const {
    return m_mass;
}

void RigidDynamic::SetLinearVelocity(cVector3d a_linearVelocity) {
    m_linearVelocity = a_linearVelocity;
}

cVector3d RigidDynamic::GetLinearVelocity() const {
    return m_linearVelocity;
}

void RigidDynamic::SetAngularVelocity(cVector3d a_angularVelocity) {
    m_angularVelocity = a_angularVelocity;
}

cVector3d RigidDynamic::GetAngularVelocity() const {
    return m_angularVelocity;
}
