#include "boid.h"
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>


// Adapted from:
// https://github.com/NCCA/labcode-jmacey-2/tree/main/ParticleQt

namespace
{
constexpr float MAX_SPEED = 2.0f;
constexpr float MAX_FORCE = 0.05f;
constexpr float NEIGHBOR_RADIUS = 50.0f;
constexpr float DESIRED_SEPARATION = 20.0f;
}

// Code modified with assistance from AI Coding Assistants
// Prompt: "Write cpp code creating a boids flocking system."
// The AI helped structure the boid class methods for flocking behavior and movement updates, in which I altered to make it function.


// Constructor: initialize position and zero velocity and acceleration
boid::boid(ngl::Vec3 pos)
  : position(pos),
    velocity(ngl::Vec3::zero()),
    acceleration(ngl::Vec3::zero())
{
}

// Apply a steering force
void boid::applyForce(const ngl::Vec3 &force)
{
  acceleration += force;
}

// Update boid position and velocity, limit speed and reset acceleration
void boid::update(float dt)
{
  velocity += acceleration;

  if (velocity.length() > MAX_SPEED)
  {
    velocity.normalize();
    velocity *= MAX_SPEED;
  }

  position += velocity * dt;

  acceleration.set(0.0f, 0.0f, 0.0f);
}

// Calculate flocking forces to acceleration
void boid::flock(const std::vector<boid> &boids)
{
  ngl::Vec3 sep = separation(boids);
  ngl::Vec3 ali = alignment(boids);
  ngl::Vec3 coh = cohesion(boids);

  // Apply weights to each behavior
  sep *= 1.5f;
  ali *= 1.0f;
  coh *= 1.0f;

  applyForce(sep);
  applyForce(ali);
  applyForce(coh);
}

// Separation to avoid crowding other boids
ngl::Vec3 boid::separation(const std::vector<boid> &boids) const
{
  ngl::Vec3 steer(0.0f, 0.0f, 0.0f);
  int count = 0;

  for (const auto &other : boids)
  {
    float d = (position - other.position).length();
    if (d > 0.0f && d < DESIRED_SEPARATION)
    {
      ngl::Vec3 diff = position - other.position;
      diff.normalize();
      diff /= d; // Weight by distance
      steer += diff;
      ++count;
    }
  }

  if (count > 0)
  {
    steer /= static_cast<float>(count);
  }

  if (steer.length() > 0.0f)
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

// Alignment-- steer towards the average heading of other boids
ngl::Vec3 boid::alignment(const std::vector<boid> &boids) const
{
  ngl::Vec3 sum(0.0f, 0.0f, 0.0f);
  int count = 0;

  for (const auto &other : boids)
  {
    float d = (position - other.position).length();
    if (d > 0.0f && d < NEIGHBOR_RADIUS)
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

  return ngl::Vec3::zero();
}

// Cohesion-- move toward the average position of other boids
ngl::Vec3 boid::cohesion(const std::vector<boid> &boids) const
{
  ngl::Vec3 sum(0.0f, 0.0f, 0.0f);
  int count = 0;

  for (const auto &other : boids)
  {
    float d = (position - other.position).length();
    if (d > 0.0f && d < NEIGHBOR_RADIUS)
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

  return ngl::Vec3::zero();
}

// Calculate steering force towards target
ngl::Vec3 boid::seek(const ngl::Vec3 &target) const
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

// Draw the boid
void boid::draw(const ngl::Mat4 &_view, const ngl::Mat4 &_proj) const
{
  ngl::ShaderLib::use("BoidShader");

  ngl::Transformation tx;
  tx.setPosition(position);

  ngl::Mat4 model = tx.getMatrix();
  ngl::Mat4 MVP = _proj * _view * model;

  ngl::ShaderLib::setUniform("Model", model);
  ngl::ShaderLib::setUniform("MVP", MVP);

  ngl::VAOPrimitives::draw("boid");
}
