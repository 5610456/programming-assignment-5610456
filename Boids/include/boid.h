#ifndef BOID_H
#define BOID_H

#include <ngl/Vec3.h>
#include <vector>
#include <ngl/Mat4.h>

class boid {
public:
    boid(ngl::Vec3 pos);
    void update(float dt);
    void applyForce(const ngl::Vec3 &force);
    void flock(const std::vector<boid> &boids);
    void draw(const ngl::Mat4 &_view, const ngl::Mat4 &_proj) const;


    ngl::Vec3 separation(const std::vector<boid> &boids) const;
    ngl::Vec3 alignment(const std::vector<boid> &boids) const;
    ngl::Vec3 cohesion(const std::vector<boid> &boids) const;
    ngl::Vec3 seek(const ngl::Vec3 &target) const;  // <-- 🔧 Add this line

    ngl::Vec3 position;
    ngl::Vec3 velocity;
    ngl::Vec3 acceleration;
};

#endif // BOID_H
