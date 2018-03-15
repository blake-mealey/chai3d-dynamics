//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

class Scene;

class Rigidbody;
class Constraint;

class SceneManager {
public:
    explicit SceneManager(chai3d::cWorld *a_world);
    ~SceneManager();

    void AddScene(Scene *a_scene);
    void SetScene(int a_index);
    void NextScene();
    void PreviousScene();

    Scene* GetCurrentScene();

    std::vector<Scene*> GetScenes() const;

    void LoadCurrentScene();

    void LoadConstraint(Constraint* a_constraint) const;
    void LoadRigidbody(Rigidbody* a_body) const;
private:
    int m_currentIndex;
    std::vector<Scene*> m_scenes;
    chai3d::cMesh *m_sceneWorld;
};
