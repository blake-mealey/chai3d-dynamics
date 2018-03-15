//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#include "Scene.h"
#include "SceneManager.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "RigidStatic.h"
#include "RigidDynamic.h"
#include "Constraint.h"
#include "Spring.h"

using namespace chai3d;

Scene::Scene() : m_manager(nullptr), m_loaded(false), m_killFloor(-1.0), m_cursor(nullptr),
                 m_cursorOffset(cVector3d(0.1, 0.0, 0.0)),
                 m_workspaceLocked(false), m_cameraOffset(cVector3d(0.25, 0.0, 0.0)) { }

Spring* Scene::CreateSpring(Rigidbody *a_body0, Rigidbody *a_body1, const double a_naturalLength, const double a_springStiffness, const double a_dampingConstant) {
    Spring* spring = new Spring(a_body0, a_body1, a_naturalLength, a_springStiffness, a_dampingConstant);
    AddConstraint(spring);
    return spring;
}

void Scene::AddConstraint(Constraint* a_constraint) {
    m_constraints.insert(a_constraint);
    if (m_loaded) m_manager->LoadConstraint(a_constraint);
}

void Scene::DestroyConstraint(Constraint* a_constraint) {
    m_constraintsToDelete.insert(a_constraint);
}

void Scene::DestroyConstraint(Rigidbody* a_body) {
    for (Constraint* constraint : m_constraints) {
        if (constraint->ConstrainsRigidbody(a_body)) {
            DestroyConstraint(constraint);
        }
    }
}

RigidStatic* Scene::CreateStatic(chai3d::cVector3d a_position) {
    RigidStatic* body = new RigidStatic(a_position);
    AddStatic(body);
    return body;
}

void Scene::AddStatic(RigidStatic* a_static) {
    m_statics.insert(a_static);
    if (m_loaded) m_manager->LoadRigidbody(a_static);
}

void Scene::DestroyStatic(RigidStatic* a_static) {
    DestroyConstraint(a_static);
    m_staticsToDelete.insert(a_static);
}

RigidDynamic* Scene::CreateDynamic(const double a_mass, const chai3d::cVector3d a_position, const chai3d::cVector3d a_velocity) {
    RigidDynamic* body = new RigidDynamic(a_mass, a_position, a_velocity);
    AddDynamic(body);
    return body;
}

void Scene::AddDynamic(RigidDynamic* a_dynamic) {
    m_dynamics.insert(a_dynamic);
    if (m_loaded) m_manager->LoadRigidbody(a_dynamic);
}

void Scene::DestroyDynamic(RigidDynamic* a_dynamic) {
    DestroyConstraint(a_dynamic);
    m_dynamicsToDelete.insert(a_dynamic);
}

void Scene::DestroyMarkedRenderObjects() {
    for (cGenericObject* object : m_objectsToDelete) {
        object->getParent()->deleteChild(object);
    }
    m_objectsToDelete.clear();
}

void Scene::DestroyMarkedObjects() {
    for (Constraint* constraint : m_constraintsToDelete) {
        m_objectsToDelete.insert(constraint->GetRenderMesh());
        m_constraints.erase(constraint);
        delete constraint;
    }
    m_constraintsToDelete.clear();

    for (RigidStatic* body : m_staticsToDelete) {
        if (body->GetCollider()) {
            m_objectsToDelete.insert(body->GetCollider()->GetRenderMesh());
        }
        m_statics.erase(body);
        delete body;
    }
    m_staticsToDelete.clear();

    for (RigidDynamic* body : m_dynamicsToDelete) {
        if (body->GetCollider()) {
            m_objectsToDelete.insert(body->GetCollider()->GetRenderMesh());
        }
        m_dynamics.erase(body);
        delete body;
    }
    m_dynamicsToDelete.clear();
}

void Scene::SetCursor(RigidStatic* a_cursor) {
    AddStatic(a_cursor);
    m_cursor = a_cursor;
}
