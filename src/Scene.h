//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"
#include <unordered_set>

class SceneManager;

class Rigidbody;
class RigidStatic;
class RigidDynamic;

class Constraint;
class Spring;

class Scene {
public:
    Scene();

    SceneManager* m_manager;
    bool m_loaded;

    std::unordered_set<chai3d::cGenericObject*> m_objectsToDelete;

    std::unordered_set<Constraint*> m_constraints;
    std::unordered_set<RigidStatic*> m_statics;
    std::unordered_set<RigidDynamic*> m_dynamics;

    std::unordered_set<Constraint*> m_constraintsToDelete;
    std::unordered_set<RigidStatic*> m_staticsToDelete;
    std::unordered_set<RigidDynamic*> m_dynamicsToDelete;

    double m_killFloor;

    RigidStatic* m_cursor;
    chai3d::cVector3d m_cursorOffset;

    bool m_workspaceLocked;
    chai3d::cVector3d m_cameraOffset;

    Spring* CreateSpring(Rigidbody *a_body0, Rigidbody *a_body1, double a_naturalLength = 0.05, double a_springStiffness = 200.0, double a_dampingConstant = 5.0);
    void AddConstraint(Constraint* a_constraint);
    void DestroyConstraint(Constraint* a_constraint);
    void DestroyConstraint(Rigidbody* a_body);

    RigidStatic* CreateStatic(chai3d::cVector3d a_position = chai3d::cVector3d(0.0, 0.0, 0.0));
    void AddStatic(RigidStatic* a_static);
    void DestroyStatic(RigidStatic* a_static);

    RigidDynamic* CreateDynamic(double a_mass = 1.0, chai3d::cVector3d a_position = chai3d::cVector3d(0.0, 0.0, 0.0), chai3d::cVector3d a_velocity = chai3d::cVector3d(0.0, 0.0, 0.0));
    void AddDynamic(RigidDynamic* a_dynamic);
    void DestroyDynamic(RigidDynamic* a_dynamic);

    void DestroyMarkedRenderObjects();
    void DestroyMarkedObjects();

    void SetCursor(RigidStatic* a_cursor);
};
