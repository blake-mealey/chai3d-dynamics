//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#include "Rope.h"

using namespace chai3d;

Rope::Rope(Rigidbody *a_body0, Rigidbody *a_body1, double a_naturalLength, double a_springStiffness, double a_dampingConstant) :
    Spring(a_body0, a_body1, a_naturalLength, a_springStiffness, a_dampingConstant) { }

Rope::Rope(Rigidbody *a_body0, cVector3d a_pos0, Rigidbody *a_body1, cVector3d a_pos1, double a_naturalLength, double a_springStiffness, double a_dampingConstant) :
    Spring(a_body0, a_pos0, a_body1, a_pos1, a_naturalLength, a_springStiffness, a_dampingConstant) { }

void Rope::AddForces() const {
    // Get the normal of the spring
    cVector3d pos0 = GetPos0();
    cVector3d pos1 = GetPos1();
    cVector3d springNormal = pos1 - pos0;

    // Calculate the length difference of the spring
    double currentLength = springNormal.length();
    double lengthDiff = currentLength - m_naturalLength;

    // Only add spring forces when the rope is over-extended
    if (lengthDiff > 0) {
        Spring::AddForces();
    }
}
