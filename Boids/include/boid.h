#ifndef BOID_H
#define BOID_H

#include <ngl/Vec3.h>
#include <vector>

// class boid {
// public:
//     boid(ngl::Vec3 pos);
//     void update(float dt);
//     void applyForce(const ngl::Vec3 &force);
//     void flock(const std::vector<boid> &boids);
//
//
//     void borders(float width, float height, float depth);  // <-- Add this line
//
//     ngl::Vec3 separation(const std::vector<boid> &boids);
//     ngl::Vec3 alignment(const std::vector<boid> &boids);
//     ngl::Vec3 cohesion(const std::vector<boid> &boids);
//     ngl::Vec3 seek(const ngl::Vec3 &target);  // <-- 🔧 Add this line
//
//     ngl::Vec3 position;
//     ngl::Vec3 velocity;
//     ngl::Vec3 acceleration;
// };
//
// #endif // BOID_H

class boid
{
public:
    explicit boid(ngl::Vec3 pos);

    void update(float dt);
    void applyForce(const ngl::Vec3 &force);
    void flock(const std::vector<boid> &boids);

    void borders(float width, float height, float depth);

    ngl::Vec3 separation(const std::vector<boid> &boids);
    ngl::Vec3 alignment(const std::vector<boid> &boids);
    ngl::Vec3 cohesion(const std::vector<boid> &boids);
    ngl::Vec3 seek(const ngl::Vec3 &target);

    ngl::Vec3 position;
    ngl::Vec3 velocity;
    ngl::Vec3 acceleration;

private:
    static constexpr float MAX_SPEED = 2.0f;
    static constexpr float MAX_FORCE = 0.05f;
    static constexpr float NEIGHBOR_RADIUS = 50.0f;
    static constexpr float DESIRED_SEPARATION = 20.0f;
};

#endif // BOID_H
