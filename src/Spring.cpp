//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#include "Spring.h"
#include "Rigidbody.h"

using namespace chai3d;

Spring::Spring(Rigidbody *a_body0, Rigidbody *a_body1, double a_naturalLength, double a_springStiffness, double a_dampingConstant) :
    Spring(a_body0, cVector3d(0.0, 0.0, 0.0), a_body1, cVector3d(0.0, 0.0, 0.0), a_naturalLength, a_springStiffness, a_dampingConstant) { }

Spring::Spring(Rigidbody *a_body0, cVector3d a_pos0, Rigidbody *a_body1, cVector3d a_pos1, double a_naturalLength, double a_springStiffness, double a_dampingConstant) :
    NConstraint({ a_body0, a_body1 }), m_naturalLength(a_naturalLength), m_springStiffness(a_springStiffness), m_dampingConstant(a_dampingConstant) {

    m_localPositions[0] = a_pos0;
    m_localPositions[1] = a_pos1;

    m_renderMesh = new cShapeLine();
}

void Spring::AddForces() const {
    // Get the normal of the spring
    cVector3d pos0 = GetPos0();
    cVector3d pos1 = GetPos1();
    cVector3d springNormal = pos1 - pos0;

    // Calculate the length difference of the spring
    double currentLength = springNormal.length();
    double lengthDiff = currentLength - m_naturalLength;

    // Normalize the spring normal
    if (springNormal.length() == 0.0) {
        springNormal = cVector3d(0.0, 0.0, -1.0);
    }
    else {
        springNormal.normalize();
    }

    // Get the relative velocity of the bodies
    cVector3d vel0 = m_bodies[0]->GetLinearVelocity();
    cVector3d vel1 = m_bodies[1]->GetLinearVelocity();
    cVector3d relativeVel = vel1 - vel0;

    // Project the relative velocity onto the spring normal
    cVector3d projectedVel;
    if (springNormal.equals(relativeVel)) {
        projectedVel = relativeVel;
    }
    else {
        projectedVel = cProject(relativeVel, springNormal);
    }

    // Compute forces
    cVector3d springForce = -m_springStiffness*lengthDiff * springNormal;		// F = -k(l-l_0)(p-q/||p-q||)
    cVector3d dampingForce = -m_dampingConstant * projectedVel;					// F = -bv
    cVector3d netForce = springForce + dampingForce;

    // Add forces to bodies
    m_bodies[0]->AddForce(-netForce, pos0 - m_bodies[0]->GetPosition());
    m_bodies[1]->AddForce(netForce, pos1 - m_bodies[1]->GetPosition());
}

void Spring::SetNaturalLength(double a_naturalLength) {
    m_naturalLength = a_naturalLength;
}

double Spring::GetNaturalLength() const {
    return m_naturalLength;
}

void Spring::SetSpringStiffness(double a_springStiffness) {
    m_springStiffness = a_springStiffness;
}

double Spring::GetSpringStiffness() const {
    return m_springStiffness;
}

void Spring::SetDampingConstant(double a_dampingConstant) {
    m_dampingConstant = a_dampingConstant;
}

double Spring::GetDampingConstant() const {
    return m_dampingConstant;
}

void Spring::UpdateRenderMesh() const {
    // Get positions and length diff
    cVector3d pos0 = GetPos0();
    cVector3d pos1 = GetPos1();
    double currentLength = (pos1 - pos0).length();
    double lengthDiff = currentLength - m_naturalLength;

    cShapeLine* line = static_cast<cShapeLine*>(m_renderMesh);

    // Update the positions of the line
    line->m_pointA = pos0;
    line->m_pointB = pos1;

    // Update the colour of the line
    constexpr double lengthEps = 0.01;
    if (lengthDiff < -lengthEps) {
        line->m_colorPointA.setYellow();
        line->m_colorPointB.setYellow();
    }
    else if (lengthDiff > lengthEps) {
        line->m_colorPointA.setRed();
        line->m_colorPointB.setRed();
    }
    else {
        line->m_colorPointA.setGreen();
        line->m_colorPointB.setGreen();
    }
}

cVector3d Spring::GetPos0() const {
    Rigidbody* body = m_bodies[0];
    cMatrix3d rotMat = body->GetRotationMatrix();
    return body->GetPosition() + rotMat * m_localPositions[0];
}

cVector3d Spring::GetPos1() const {
    Rigidbody* body = m_bodies[1];
    cMatrix3d rotMat = body->GetRotationMatrix();
    return body->GetPosition() + rotMat * m_localPositions[1];
}
