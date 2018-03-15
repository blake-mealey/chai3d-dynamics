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
    SceneManager(chai3d::cWorld *world);
    ~SceneManager();

    void AddScene(Scene *scene);
    void SetScene(int index);
    void NextScene();
    void PreviousScene();

    Scene* GetCurrentScene();

    std::vector<Scene*> GetScenes();

    void LoadCurrentScene();

    void LoadConstraint(Constraint* a_constraint);
    void LoadRigidbody(Rigidbody* a_body);
private:
    int currentIndex;
    std::vector<Scene*> scenes;
    chai3d::cMesh *sceneWorld;
};
