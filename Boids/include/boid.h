#ifndef BOID_H
#define BOID_H

#include <ngl/Vec3.h>
#include <vector>
#include <ngl/Mat4.h>

// Adapted from:
// https://github.com/NCCA/labcode-jmacey-2/tree/main/ParticleQt

class boid {
public:
    /// Initialize Boid with a position
    boid(ngl::Vec3 pos);
    /// Update Boid position based on velocity and acceleration
    void update(float dt);
    /// Apply force to the Boid
    void applyForce(const ngl::Vec3 &force);
    /// Calculate and apply flocking forces based on nearby Boids
    void flock(const std::vector<boid> &boids);
    /// Draw the Boid with given view and projection matrices
    void draw(const ngl::Mat4 &_view, const ngl::Mat4 &_proj) const;

    /// Calculate separation
    ngl::Vec3 separation(const std::vector<boid> &boids) const;
    /// Calculate alignment
    ngl::Vec3 alignment(const std::vector<boid> &boids) const;
    /// Calculate cohesion
    ngl::Vec3 cohesion(const std::vector<boid> &boids) const;
    /// Seek a target position and return steering force
    ngl::Vec3 seek(const ngl::Vec3 &target) const;

    /// Get position, velocity and acceleration of Boid
    ngl::Vec3 position;
    ngl::Vec3 velocity;
    ngl::Vec3 acceleration;

    /// Limit the magnitude of a vector to a max value
    ngl::Vec3 limit(const ngl::Vec3 &_vec, float _max) const;
};

#endif // BOID_H
