//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#include "SceneManager.h";
#include "Scene.h"
#include "Rigidbody.h"
#include "RigidStatic.h"
#include "RigidDynamic.h"
#include "Collider.h"
#include "Constraint.h"

using namespace chai3d;

SceneManager::SceneManager(cWorld *a_world) : m_currentIndex(-1) {
    m_sceneWorld = new cMesh();
    a_world->addChild(m_sceneWorld);
}

SceneManager::~SceneManager() {
    delete m_sceneWorld;
}

void SceneManager::AddScene(Scene *a_scene) {
    m_scenes.push_back(a_scene);
    a_scene->m_manager = this;
}

void SceneManager::SetScene(int a_index) {
    if (m_currentIndex >= 0) {
        GetCurrentScene()->m_loaded = false;
    }

    while (a_index < 0) a_index += m_scenes.size();		// Wrap negative values
    a_index = a_index % m_scenes.size();					// Wrap positive values

    m_currentIndex = a_index;							// Load new scene
    LoadCurrentScene();
    GetCurrentScene()->m_loaded = true;
}

void SceneManager::NextScene() {
    SetScene(m_currentIndex + 1);
}

void SceneManager::PreviousScene() {
    SetScene(m_currentIndex - 1);
}

Scene* SceneManager::GetCurrentScene() {
    return m_scenes[m_currentIndex];
}

void SceneManager::LoadCurrentScene() {
    m_sceneWorld->clearAllChildren();
    Scene* scene = GetCurrentScene();

    for (Constraint* object : scene->m_constraints) {
        LoadConstraint(object);
    }

    for (RigidStatic* object : scene->m_statics) {
        LoadRigidbody(object);
    }

    for (RigidDynamic* object : scene->m_dynamics) {
        LoadRigidbody(object);
    }
}

void SceneManager::LoadConstraint(Constraint* a_constraint) const {
    m_sceneWorld->addChild(a_constraint->GetRenderMesh());
}

void SceneManager::LoadRigidbody(Rigidbody* a_body) const {
    Collider *collider = a_body->GetCollider();
    if (!collider) return;
    m_sceneWorld->addChild(collider->GetRenderMesh());
}

std::vector<Scene*> SceneManager::GetScenes() const {
    return m_scenes;
}
