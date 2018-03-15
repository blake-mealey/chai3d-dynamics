//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#include "TorsionSpring.h"
#include "Rigidbody.h"

using namespace chai3d;

TorsionSpring::TorsionSpring(Rigidbody *a_body0, Rigidbody *a_body1, Rigidbody *a_body2, const double a_naturalAngleRadians, const double a_springStiffness, const double a_dampingConstant) :
    NConstraint({ a_body0, a_body1, a_body2 }), m_naturalAngleRadians(a_naturalAngleRadians), m_springStiffness(a_springStiffness), m_dampingConstant(a_dampingConstant) {

    m_renderMesh = new cMesh();

    m_line1To0 = new cShapeLine();
    m_renderMesh->addChild(m_line1To0);

    m_line1To2 = new cShapeLine();
    m_renderMesh->addChild(m_line1To2);
}

void TorsionSpring::AddForces() const {
    // Get positions and angle diff
    const cVector3d pos0 = m_bodies[0]->GetPosition();
    const cVector3d pos1 = m_bodies[1]->GetPosition();
    const cVector3d pos2 = m_bodies[2]->GetPosition();
    const cVector3d pos1to0 = pos0 - pos1;
    const cVector3d pos1to2 = pos2 - pos1;
    const cVector3d torqueAxis = cCross(pos1to0, pos1to2);
    const double currentAngleRadians = cAngle(pos0 - pos1, pos2 - pos1);
    const double angleDiffRadians = currentAngleRadians - m_naturalAngleRadians;

    const cVector3d force0Dir = cNormalize(cCross(pos1to0, torqueAxis));
    const double force0Mag = -angleDiffRadians * m_springStiffness;
    m_bodies[0]->AddForce(force0Dir * force0Mag);

    const cVector3d force2Dir = cNormalize(cCross(pos1to2, torqueAxis));
    const double force2Mag = angleDiffRadians * m_springStiffness;
    m_bodies[2]->AddForce(force2Dir * force2Mag);
}

void TorsionSpring::UpdateRenderMesh() const {
    // Get positions and angle diff
    const cVector3d pos0 = m_bodies[0]->GetPosition();
    const cVector3d pos1 = m_bodies[1]->GetPosition();
    const cVector3d pos2 = m_bodies[2]->GetPosition();
    const double currentAngleRadians = cAngle(pos0 - pos1, pos2 - pos1);
    const double angleDiffRadians = currentAngleRadians - m_naturalAngleRadians;

    // Update the positions of the lines
    m_line1To0->m_pointA = pos1;
    m_line1To0->m_pointB = pos0;
    m_line1To2->m_pointA = pos1;
    m_line1To2->m_pointB = pos2;

    // Update the colour of the line
    constexpr double angleEps = 0.01;
    if (angleDiffRadians < -angleEps) {
        m_line1To0->m_colorPointA.setYellow();
        m_line1To0->m_colorPointB.setYellow();
        m_line1To2->m_colorPointA.setYellow();
        m_line1To2->m_colorPointB.setYellow();
    }
    else if (angleDiffRadians > angleEps) {
        m_line1To0->m_colorPointA.setRed();
        m_line1To0->m_colorPointB.setRed();
        m_line1To2->m_colorPointA.setRed();
        m_line1To2->m_colorPointB.setRed();
    }
    else {
        m_line1To0->m_colorPointA.setGreen();
        m_line1To0->m_colorPointB.setGreen();
        m_line1To2->m_colorPointA.setGreen();
        m_line1To2->m_colorPointB.setGreen();
    }
}
