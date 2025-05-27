#include "Flock.h"

#include <iostream>
#include <ngl/Random.h>
#include <algorithm>
#include <fstream>
#include <ngl/VAOPrimitives.h>
#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>

#include "boid.h"

// Code structure and implementation assisted by AI Coding Assistants
// Prompt: "cpp class to manage a flock of boids with physics and random spread."
// The AI helped design methods for boid management, physics updates, and rendering, which I then tweaked and fixed so it worked with the rest of my program.

// Adapted from:
// https://github.com/NCCA/labcode-jmacey-2/tree/main/ParticleQt

// Initialize flock with number of boids, max alive, particles per frame, and starting position
Flock::Flock(size_t _num, size_t _maxAlive, int _numPerFrame, ngl::Vec3 _pos)
  : m_maxParticles{_num},
    m_maxAlive{_maxAlive},
    m_numPerFrame{_numPerFrame},
    m_pos{_pos}
{
  for (size_t i = 0; i < m_maxParticles; ++i)
  {
    m_boids.emplace_back(boid(m_pos));
  }

  m_ppos.resize(m_maxParticles);
  m_pcolour.resize(m_maxParticles);
  m_pdir.resize(m_maxParticles);
  m_plife.resize(m_maxParticles);
  m_psize.resize(m_maxParticles);
  m_state.resize(m_maxParticles, ParticleState::Dead);
}

// Returns the number of particles in the flock
size_t Flock::size() const
{
  return m_maxParticles;
}

// Activate dead particles up to m_numPerFrame per update cycle, decided to not function if I don't keep these
void Flock::birthParticles()
{
  const int births = static_cast<int>(ngl::Random::randomPositiveNumber(m_numPerFrame));

  for (int i = 0; i < births; ++i)
  {
    for (size_t p = 0; p < m_maxParticles; ++p)
    {
      if (m_state[p] == ParticleState::Dead)
      {
        resetParticle(p);
        m_state[p] = ParticleState::Active;
        break;
      }
    }
  }
}

// Update the flock: update boids, birth new particles, and update particle state
void Flock::update(float _dt)
{
  static const ngl::Vec3 gravity(0.0f, -9.81f, 0.0f);

  // Update all boids behavior and position
  for (auto &b : m_boids)
  {
    b.flock(m_boids);
    b.update(_dt);
  }

  // Count active particles
  const auto numAlive = std::count_if(m_state.begin(), m_state.end(),
                                     [](auto state) { return state == ParticleState::Active; });

  if (numAlive < m_maxAlive)
  {
    birthParticles();
  }

  // Update physics and state
  for (size_t i = 0; i < m_maxParticles; ++i)
  {
    if (m_state[i] == ParticleState::Dead)
    {
      continue;
    }

    m_pdir[i] += gravity * _dt * 0.5f;
    m_ppos[i] += m_pdir[i] * 0.5f;

    m_psize[i] += 0.1f;
    m_psize[i] = std::clamp(m_psize[i], 0.0f, 10.0f);

    m_ppos[i].m_w = m_psize[i];

    if (--m_plife[i] <= 0 || m_ppos[i].m_y <= 0.0f)
    {
      m_state[i] = ParticleState::Dead;
    }
  }
}

// Reset particle to initial state for reuse
void Flock::resetParticle(size_t _i)
{
  static const ngl::Vec3 emitDir(0.0f, 1.0f, 0.0f);

  m_ppos[_i].set(m_pos.m_x, m_pos.m_y, m_pos.m_z, 0.0f);
  m_pdir[_i] = emitDir * ngl::Random::randomPositiveNumber() +
               randomVectorOnSphere() * m_spread;

  m_pdir[_i].m_y = std::abs(m_pdir[_i].m_y);

  m_psize[_i] = 0.01f;
  m_plife[_i] = 20 + static_cast<int>(ngl::Random::randomPositiveNumber(100));
  m_pcolour[_i] = ngl::Random::getRandomColour3();
}

// Generate a random vector on the surface of a sphere scaled by _radius
ngl::Vec3 Flock::randomVectorOnSphere(float _radius)
{
  const float phi = ngl::Random::randomPositiveNumber(M_PI * 2.0f);
  const float costheta = ngl::Random::randomNumber();
  const float u = ngl::Random::randomPositiveNumber();
  const float theta = std::acos(costheta);
  const float r = _radius * std::cbrt(u);

  return ngl::Vec3(r * std::sin(theta) * std::cos(phi),
                   r * std::sin(theta) * std::sin(phi),
                   r * std::cos(theta));
}

// Render all boids
void Flock::render(const ngl::Mat4 &_view, const ngl::Mat4 &_proj) const
{
  for (const auto &b : m_boids)
  {
    b.draw(_view, _proj);
  }
}

// Move the flock center position
void Flock::move(float _dx, float _dy, float _dz)
{
  m_pos.m_x += _dx;
  m_pos.m_y += _dy;
  m_pos.m_z += _dz;
}

// Move all boids by given delta amounts and update flock center position
void Flock::moveFlock(float _dx, float _dy, float _dz)
{
  move(_dx, _dy, _dz); // Update flock center position

  for (auto &b : m_boids)
  {
    b.position.m_x += _dx;
    b.position.m_y += _dy;
    b.position.m_z += _dz;
  }
}

// Set the spread factor affecting the random particle direction
void Flock::setSpread(float _value)
{
  m_spread = _value;
}

// Set the weight for alignment behavior (currently unused, add usage as needed)
void Flock::setAlignmentWeight(float _value)
{
  m_alignmentWeight = _value;
}
