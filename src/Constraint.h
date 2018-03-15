//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include "chai3d.h"

class Rigidbody;

class Constraint {
public:
    virtual ~Constraint() = default;
    Constraint() : m_renderMesh(nullptr) {}

    virtual void AddForces() const = 0;

    virtual size_t GetRigidbodyCount() const = 0;
    virtual Rigidbody* GetRigidbody(size_t index) const = 0;
    virtual bool ConstrainsRigidbody(Rigidbody* a_body) const = 0;

    chai3d::cGenericObject* GetRenderMesh() const;
    virtual void UpdateRenderMesh() const = 0;
protected:
    chai3d::cGenericObject* m_renderMesh;
};
