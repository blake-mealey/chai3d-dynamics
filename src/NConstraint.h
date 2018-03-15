//==============================================================================
/*
\author    T. Blake Mealey
*/
//==============================================================================

#pragma once

#include <array>

#include "Constraint.h"

template <size_t N>
class NConstraint : public Constraint {
public:
    virtual ~NConstraint() = default;
    NConstraint(std::array<Rigidbody*, N> a_bodies) : Constraint(), m_bodies(a_bodies) {}

    size_t GetRigidbodyCount() const override {
        return N;
    }

    Rigidbody* GetRigidbody(size_t index) const override {
        return m_bodies[index];
    }

    bool ConstrainsRigidbody(Rigidbody* a_body) const override {
        for (Rigidbody* body : m_bodies) {
            if (body == a_body) return true;
        }
        return false;
    }

    void AddForces() const override = 0;
    void UpdateRenderMesh() const override = 0;
protected:
    std::array<Rigidbody*, N> m_bodies;
};
