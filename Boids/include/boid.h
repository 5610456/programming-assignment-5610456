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
    ngl::Vec3 position;
    ngl::Vec3 velocity;
    ngl::Vec3 acceleration;

    explicit boid(const ngl::Vec3 &_pos);

    void applyForce(const ngl::Vec3 &force);
    void flock(const std::vector<boid> &neighbors);
    void update(float dt);

    // Optional, add if you implement
    // void borders(float width, float height, float depth);

private:
    ngl::Vec3 alignment(const std::vector<boid> &neighbors);
    ngl::Vec3 cohesion(const std::vector<boid> &neighbors);
    ngl::Vec3 separation(const std::vector<boid> &neighbors);
    ngl::Vec3 seek(const ngl::Vec3 &target);
};

#endif // BOID_H

