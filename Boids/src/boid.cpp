#include "boid.h"
#include <cmath>
#include <cstdlib> // for rand()
#include <ctime>   // for seeding rand()
#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Random.h>

constexpr float MAX_SPEED = 2.0f;
constexpr float MAX_FORCE = 0.05f;
constexpr float NEIGHBOR_RADIUS = 50.0f;
constexpr float DESIRED_SEPARATION = 20.0f;

boid::boid(const ngl::Vec3 &_pos)
    : position(_pos)
{
  velocity = ngl::Vec3::zero();
  acceleration = ngl::Vec3::zero();
}


void boid::applyForce(const ngl::Vec3 &force)
{
  acceleration += force;
}

void boid::update(float dt)
{
  velocity += acceleration;
  if (velocity.length() > MAX_SPEED)
  {
    velocity.normalize();
    velocity *= MAX_SPEED;
  }

  position += velocity * dt;
  acceleration.set(0, 0, 0);
}

void boid::flock(const std::vector<boid> &boids)
{
  ngl::Vec3 sep = separation(boids);
  ngl::Vec3 ali = alignment(boids);
  ngl::Vec3 coh = cohesion(boids);

  // Weight the forces
  sep *= 1.5f;
  ali *= 1.0f;
  coh *= 1.0f;

  applyForce(sep);
  applyForce(ali);
  applyForce(coh);
}

ngl::Vec3 boid::separation(const std::vector<boid> &boids)
{
  ngl::Vec3 steer(0, 0, 0);
  int count = 0;

  for (const auto &other : boids)
  {
    float d = (position - other.position).length();
    if (d > 0 && d < DESIRED_SEPARATION)
    {
      ngl::Vec3 diff = position - other.position;
      diff.normalize();
      diff /= d;
      steer += diff;
      ++count;
    }
  }

  if (count > 0)
  {
    steer /= static_cast<float>(count);
  }

  if (steer.length() > 0)
  {
    steer.normalize();
    steer *= MAX_SPEED;
    steer -= velocity;
    if (steer.length() > MAX_FORCE)
    {
      steer.normalize();
      steer *= MAX_FORCE;
    }
  }

  return steer;
}

ngl::Vec3 boid::alignment(const std::vector<boid> &boids)
{
  ngl::Vec3 sum(0, 0, 0);
  int count = 0;

  for (const auto &other : boids)
  {
    float d = (position - other.position).length();
    if (d > 0 && d < NEIGHBOR_RADIUS)
    {
      sum += other.velocity;
      ++count;
    }
  }

  if (count > 0)
  {
    sum /= static_cast<float>(count);
    sum.normalize();
    sum *= MAX_SPEED;
    ngl::Vec3 steer = sum - velocity;
    if (steer.length() > MAX_FORCE)
    {
      steer.normalize();
      steer *= MAX_FORCE;
    }
    return steer;
  }

  return ngl::Vec3(0, 0, 0);
}

ngl::Vec3 boid::cohesion(const std::vector<boid> &boids)
{
  ngl::Vec3 sum(0, 0, 0);
  int count = 0;

  for (const auto &other : boids)
  {
    float d = (position - other.position).length();
    if (d > 0 && d < NEIGHBOR_RADIUS)
    {
      sum += other.position;
      ++count;
    }
  }

  if (count > 0)
  {
    sum /= static_cast<float>(count);
    return seek(sum);
  }

  return ngl::Vec3(0, 0, 0);
}

ngl::Vec3 boid::seek(const ngl::Vec3 &target)
{
  ngl::Vec3 desired = target - position;
  desired.normalize();
  desired *= MAX_SPEED;
  ngl::Vec3 steer = desired - velocity;
  if (steer.length() > MAX_FORCE)
  {
    steer.normalize();
    steer *= MAX_FORCE;
  }
  return steer;
}
