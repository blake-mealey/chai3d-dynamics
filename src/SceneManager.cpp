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

SceneManager::SceneManager(cWorld *world) : currentIndex(-1) {
    sceneWorld = new cMesh();
    world->addChild(sceneWorld);
}

SceneManager::~SceneManager() {
    delete sceneWorld;
}

void SceneManager::AddScene(Scene *scene) {
    scenes.push_back(scene);
    scene->m_manager = this;
}

void SceneManager::SetScene(int index) {
    if (currentIndex >= 0) {
        GetCurrentScene()->m_loaded = false;
    }

    while (index < 0) index += scenes.size();		// Wrap negative values
    index = index % scenes.size();					// Wrap positive values

    currentIndex = index;							// Load new scene
    LoadCurrentScene();
    GetCurrentScene()->m_loaded = true;
}

void SceneManager::NextScene() {
    SetScene(currentIndex + 1);
}

void SceneManager::PreviousScene() {
    SetScene(currentIndex - 1);
}

Scene* SceneManager::GetCurrentScene() {
    return scenes[currentIndex];
}

void SceneManager::LoadCurrentScene() {
    sceneWorld->clearAllChildren();
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

void SceneManager::LoadConstraint(Constraint* a_constraint) {
    sceneWorld->addChild(a_constraint->GetRenderMesh());
}

void SceneManager::LoadRigidbody(Rigidbody* a_body) {
    Collider *collider = a_body->GetCollider();
    if (!collider) return;
    sceneWorld->addChild(collider->GetRenderMesh());
}

std::vector<Scene*> SceneManager::GetScenes() {
    return scenes;
}
