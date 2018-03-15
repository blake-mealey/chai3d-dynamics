//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#include "SphereCollider.h"
#include "Collision.h"
#include "Rigidbody.h"

using namespace chai3d;

SphereCollider::SphereCollider(double a_radius, double a_collisionStiffness, double a_dampingConstant,
    size_t a_collisionFlag, size_t a_collidesWithMask) :
    Collider(a_collisionStiffness, a_dampingConstant, a_collisionFlag, a_collidesWithMask), m_radius(a_radius) {

    m_renderMesh = new cMesh();
    CreateRenderMesh();
}

Collision SphereCollider::GetCollision(Collider* a_collider)const {
    Collision collision;
    if (!m_parent || !a_collider->GetParent()) {
        collision.valid = false;
        return collision;
    }

    // Get the positions of the bodies and the collision normal
    cVector3d pos0 = m_parent->GetPosition();
    cVector3d pos1 = a_collider->GetParent()->GetPosition();
    cVector3d intersectionNormal = cNormalize(pos1 - pos0);

    // This ruins the purpose of inheritance
    // TODO: Find a better way to do this
    SphereCollider* sphereCollider = static_cast<SphereCollider*>(a_collider);

    // Get the radii of the colliders
    double radius0 = m_radius;
    double radius1 = sphereCollider->m_radius;

    // Get the intersection positions
    cVector3d intersect0 = pos0 + intersectionNormal * radius0;
    cVector3d intersect1 = pos1 - intersectionNormal * radius1;

    // Check if there was an intersection
    if ((intersect0 - pos1).length() <= radius1) {
        collision.valid = true;
        collision.intersect0 = intersect0;
        collision.intersect1 = intersect1;
        collision.normal = intersect1 - intersect0;
        return collision;
    }

    // Return the zero vector if there was no intersection
    collision.valid = false;
    return collision;
}

void SphereCollider::SetRadius(double a_radius) {
    m_radius = a_radius;
    m_renderMesh->getParent()->deleteChild(m_renderMesh);
    CreateRenderMesh();
    m_parent->UpdateInertiaMatrix();
}

double SphereCollider::GetRadius() const {
    return m_radius;
}

cMatrix3d SphereCollider::GetInertiaMatrix() const {
    // From: http://scienceworld.wolfram.com/physics/MomentofInertiaSphere.html
    cMatrix3d mat;
    mat.identity();
    mat *= (2.0 / 5.0) * m_radius * m_radius;
    return mat;
}

void SphereCollider::CreateRenderMesh() {
    cCreateSphere(m_renderMesh, m_radius);
}