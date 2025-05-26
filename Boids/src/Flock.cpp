#include "Flock.h"
#include <iostream>
#include <ngl/Random.h>
#include <algorithm>
#include <fstream>
#include <ngl/VAOPrimitives.h>
#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include "boid.h"

// Flock::Flock(size_t _num, size_t _maxAlive, int _numPerFrame, ngl::Vec3 _pos) :
//   m_maxParticles{_num},
//   m_maxAlive{_maxAlive},
//   m_numPerFrame{_numPerFrame},
//   m_pos{_pos}
// {
//   // Initialize Boids
//   for (size_t i = 0; i < m_maxParticles; ++i)
//   {
//     m_boids.emplace_back(boid(m_pos));
//   }
//
//   // Allocate and initialize particle system vectors
//   m_ppos.resize(m_maxParticles);
//   m_pcolour.resize(m_maxParticles);
//   m_pdir.resize(m_maxParticles);
//   m_plife.resize(m_maxParticles);
//   m_psize.resize(m_maxParticles);
//   m_state.resize(m_maxParticles, ParticleState::Dead);
// }
//
// size_t Flock::size() const
// {
//   return m_maxParticles;
// }
//
// void Flock::birthParticles()
// {
//   auto births = static_cast<int>(ngl::Random::randomPositiveNumber(m_numPerFrame));
//
//   for (int i = 0; i < births; ++i)
//   {
//     for (size_t p = 0; p < m_maxParticles; ++p)
//     {
//       if (m_state[p] == ParticleState::Dead)
//       {
//         resetParticle(p);
//         m_state[p] = ParticleState::Active;
//         break;
//       }
//     }
//   }
// }
//
// void Flock::update(float _dt)
// {
//   const ngl::Vec3 gravity(0.0f, -9.81f, 0.0f);
//
//   // --- Update Boids ---
//   for (auto &b : m_boids)
//   {
//     b.flock(m_boids);
//     b.update(_dt);
//   }
//
//   // --- Birth new particles if needed ---
//   auto numAlive = std::count_if(m_state.begin(), m_state.end(),
//                                  [](auto p) { return p == ParticleState::Active; });
//
//   if (numAlive < m_maxAlive)
//   {
//     birthParticles();
//   }
//
//   // --- Update particles ---
//   for (size_t i = 0; i < m_maxParticles; ++i)
//   {
//     if (m_state[i] == ParticleState::Dead)
//       continue;
//
//     m_pdir[i] += gravity * _dt * 0.5f;
//     m_ppos[i] += m_pdir[i] * 0.5f;
//     m_psize[i] += 0.1f;
//     m_psize[i] = std::clamp(m_psize[i], 0.0f, 10.0f);
//     m_ppos[i].m_w = m_psize[i];
//
//     if (--m_plife[i] <= 0 || m_ppos[i].m_y <= 0.0f)
//     {
//       m_state[i] = ParticleState::Dead;
//     }
//   }
// }
//
// void Flock::resetParticle(size_t _i)
// {
//   ngl::Vec3 emitDir(0.0f, 1.0f, 0.0f);
//   m_ppos[_i].set(m_pos.m_x, m_pos.m_y, m_pos.m_z, 0.0f);
//   m_pdir[_i] = emitDir * ngl::Random::randomPositiveNumber() +
//                randomVectorOnSphere() * m_spread;
//   m_pdir[_i].m_y = std::abs(m_pdir[_i].m_y);
//   m_psize[_i] = 0.01f;
//   m_plife[_i] = 20 + static_cast<int>(ngl::Random::randomPositiveNumber(100));
//   m_pcolour[_i] = ngl::Random::getRandomColour3();
//   // m_state[_i] is set to Active in birthParticles()
// }
//
// ngl::Vec3 Flock::randomVectorOnSphere(float _radius)
// {
//   auto phi = ngl::Random::randomPositiveNumber(M_PI * 2.0f);
//   auto costheta = ngl::Random::randomNumber();
//   auto u = ngl::Random::randomPositiveNumber();
//   auto theta = std::acos(costheta);
//   auto r = _radius * std::cbrt(u);
//
//   return ngl::Vec3(r * std::sin(theta) * std::cos(phi),
//                    r * std::sin(theta) * std::sin(phi),
//                    r * std::cos(theta));
// }
//
// void Flock::render() const
// {
//   //ngl::ShaderLib::use("Phong");
//   ngl::ShaderLib::use("MVP");
//
//   for (const auto &b : m_boids)
//   {
//     ngl::Mat4 model = ngl::Mat4::translate(b.position.m_x, b.position.m_y, b.position.m_z); // ✅ correct
//     ngl::ShaderLib::setUniform("MVP", model);
//     ngl::VAOPrimitives::draw("sphere");
//   }
// }
//
// void Flock::move(float _dx, float _dy, float _dz)
// {
//   m_pos.m_x += _dx;
//   m_pos.m_y += _dy;
//   m_pos.m_z += _dz;
// }
//
// void Flock::setSpread(float _value)
// {
//   m_spread = _value;
// }

Flock::Flock(const size_t _numBoids, const size_t _maxAlive, const int _numPerFrame, const ngl::Vec3 _pos) :
  m_pos{_pos},
  m_maxBoids{_numBoids},
  m_maxAlive{_maxAlive},
  m_numPerFrame{_numPerFrame}
{
    for (size_t i = 0; i < m_maxBoids; ++i)
    {
        m_boids.emplace_back(boid(m_pos));
    }

    m_boidPositions.resize(m_maxBoids);
    m_boidColours.resize(m_maxBoids);
    m_boidDirections.resize(m_maxBoids);
    m_boidLife.resize(m_maxBoids);
    m_boidSizes.resize(m_maxBoids);
    m_state.resize(m_maxBoids, BoidState::Dead);
}


// Flock::Flock(size_t _num, size_t _maxAlive, int _numPerFrame, ngl::Vec3 _pos)
//   : m_maxBoids(_num), m_maxAlive(_maxAlive), m_numPerFrame(_numPerFrame), m_pos(_pos)
// {
//     // Initialize boids at starting position
//     for (size_t i = 0; i < m_maxBoids; ++i)
//     {
//         m_boids.emplace_back(boid(m_pos));
//     }
// }

size_t Flock::size() const
{
    return m_boids.size();  // Current number of boids
}

void Flock::update(float _dt)
{
    for (size_t i = 0; i < m_maxAlive; ++i)
    for (auto& b : m_boids)
    {
        b.flock(m_boids);
        b.update(_dt);
    }
}


void Flock::render() const
{
    ngl::ShaderLib::use("MVP");

    // Temporary: Use identity matrix or actual view-projection matrix
    ngl::Mat4 viewProj; // This is already an identity matrix by default




    for (const auto &b : m_boids)
    {
        ngl::Mat4 model = ngl::Mat4::translate(b.position.m_x, b.position.m_y, b.position.m_z);
        ngl::Mat4 mvp = viewProj * model;
        ngl::ShaderLib::setUniform("MVP", mvp);
        ngl::VAOPrimitives::draw("sphere");
    }
}


void Flock::move(float _dx, float _dy, float _dz)
{
    m_pos.m_x += _dx;
    m_pos.m_y += _dy;
    m_pos.m_z += _dz;

    // Optionally move all boids relative to flock origin:
    for (auto &b : m_boids)
    {
        b.position.m_x += _dx;
        b.position.m_y += _dy;
        b.position.m_z += _dz;
    }
}


void Flock::setSpread(float spread)
{
    m_spread = spread; // or however you want to store it
}

void Flock::addBoid(const ngl::Vec3& pos)
{
    // Create a new Boid at position pos and add it to the flock
    boid newBoid(pos);
    m_boids.push_back(newBoid);
}

void Flock::resetBoid(size_t _i)
{
    // TODO: reset the boid at index _i to initial state
    // Example:
    m_boids[_i].setPosition(ngl::Vec3(0,0,0));
    m_boids[_i].setVelocity(ngl::Vec3(0,0,0));
}

void Flock::birthBoids()
{
    // TODO: add logic to "birth" or create new boids
    Example:
        {
            ngl::Mat3 someRadius;
            addBoid(randomVectorOnSphere() * someRadius);
        }
}

ngl::Vec3 Flock::randomVectorOnSphere(float _radius)
{
    // Generate a random point on a sphere of radius _radius

    // Simple example using spherical coordinates:
    float theta = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI;  // [0, 2pi]
    float phi = acos(2.0f * (static_cast<float>(rand()) / RAND_MAX) - 1.0f);  // [0, pi]

    float x = _radius * sin(phi) * cos(theta);
    float y = _radius * sin(phi) * sin(theta);
    float z = _radius * cos(phi);

    return ngl::Vec3(x, y, z);
}


