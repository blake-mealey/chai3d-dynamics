//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#include "Rigidbody.h"
#include "Collider.h"

using namespace chai3d;

Rigidbody::~Rigidbody() {
    delete m_collider;
}

Rigidbody::Rigidbody(const cVector3d a_position) : m_position(a_position), m_rotation(cQuaternion(1.0, 0.0, 0.0, 0.0)),
    m_currentNetForce(cVector3d(0.0, 0.0, 0.0)), m_currentNetMoment(cVector3d(0.0, 0.0, 0.0)), m_collider(nullptr) { }

void Rigidbody::ClearForces() {
    m_currentNetForce = cVector3d(0.0, 0.0, 0.0);
    m_currentNetMoment = cVector3d(0.0, 0.0, 0.0);
}

void Rigidbody::AddForce(const cVector3d a_force, const cVector3d a_localPosition) {
    m_currentNetForce += a_force;
    m_currentNetMoment += cCross(a_localPosition, a_force);
}

cVector3d Rigidbody::GetCurrentNetForce() const {
    return m_currentNetForce;
}

void Rigidbody::SetPosition(const cVector3d a_position) {
    m_position = a_position;
}

cVector3d Rigidbody::GetPosition() const {
    return m_position;
}

void Rigidbody::SetRotation(const cQuaternion a_rotation) {
    m_rotation = a_rotation;
}

cQuaternion Rigidbody::GetRotation() const {
    return m_rotation;
}

chai3d::cMatrix3d Rigidbody::GetRotationMatrix() const {
    cMatrix3d mat;
    m_rotation.toRotMat(mat);
    return mat;
}

void Rigidbody::SetCollider(Collider* a_collider) {
    if (m_collider) delete m_collider;
    m_collider = a_collider;
    m_collider->SetParent(this);
}

Collider* Rigidbody::GetCollider() const {
    return m_collider;
}

void Rigidbody::UpdateInertiaMatrix() {
    if (m_collider) {
        m_inertiaMatrix = m_collider->GetInertiaMatrix();
    } else {
        m_inertiaMatrix.identity();
    }
    m_inertiaMatrix *= GetMass();
}
