#ifndef FLOCK_H_
#define FLOCK_H_

#include <vector>
#include <memory>
#include <QObject>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/MultiBufferVAO.h>
#include "boid.h"


// Adapted from:
// https://github.com/NCCA/labcode-jmacey-2/tree/main/ParticleQt

/// \brief Class representing a flock of boids as a QObject for Qt integration.
/// Manages a collection of boids and particle state for rendering and update.
class Flock : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int numPerFrame WRITE setNumPerFrame)

public:
    /// \brief Constructor
    /// \param _num Maximum number of boids/particles
    /// \param _maxAlive Maximum number of alive particles allowed
    /// \param _numPerFrame Number of new particles born per frame
    /// \param _pos Initial position of the flock center
    explicit Flock(size_t _num, size_t _maxAlive, int _numPerFrame, ngl::Vec3 _pos);

    /// \brief Returns the maximum number of particles/boids
    size_t size() const;

    /// \brief Update all boids and particles
    /// \param _dt Delta time since last update
    void update(float _dt);

    /// \brief Render boids with given view and projection matrices
    /// \param _view View matrix
    /// \param _proj Projection matrix
    void render(const ngl::Mat4 &_view, const ngl::Mat4 &_proj) const;

    /// \brief Set alignment weight influencing flocking behavior
    /// \param _value New alignment weight
    void setAlignmentWeight(float _value);

    /// \brief Move the flock center position by given deltas
    void move(float _dx, float _dy, float _dz);

    /// \brief Move all boids relative to the current position
    void moveFlock(float _dx, float _dy, float _dz);

    /// \brief Set the spread parameter influencing initial particle velocity variance
    /// \param _value New spread value
    void setSpread(float _value);

    /// \brief Add a boid at a specified position to the flock
    /// \param pos Position to add the new boid
    void addBoid(const ngl::Vec3 &pos);

public slots:
    /// \brief Set number of new particles born per frame (Qt slot)
    void setNumPerFrame(int _value) { m_numPerFrame = _value; }

private:
    /// \brief Reset particle data at index _i to initial state
    /// \param _i Particle index to reset
    void resetParticle(size_t _i);

    /// \brief Spawn new particles if under the max alive count
    void birthParticles();

    /// \brief Generate a random vector on a sphere with given radius
    /// \param _radius Sphere radius (default 1.0f)
    /// \return Random vector on sphere surface
    ngl::Vec3 randomVectorOnSphere(float _radius = 1.0f);

    // Member variables

    ngl::Vec3 m_pos;                            ///< Flock center position
    std::vector<ngl::Vec4> m_ppos;              ///< Particle positions + size in w component
    std::vector<ngl::Vec3> m_pdir;              ///< Particle velocities/directions
    std::vector<ngl::Vec3> m_pcolour;           ///< Particle colors
    std::vector<float> m_psize;                  ///< Particle sizes
    std::vector<int> m_plife;                    ///< Particle life counters

    enum class ParticleState : bool { Active, Dead };
    std::vector<ParticleState> m_state;          ///< State of each particle

    size_t m_maxParticles;                        ///< Maximum number of particles
    size_t m_maxAlive = 1000;                     ///< Maximum number of alive particles
    int m_numPerFrame = 120;                       ///< Number of new particles per frame

    float m_spread = 5.5f;                        ///< Spread factor for initial velocity randomness
    float m_alignmentWeight = 1.0f;               ///< Weight for alignment in flocking behavior

    std::vector<boid> m_boids;                    ///< Container of boid objects

    std::unique_ptr<ngl::MultiBufferVAO> m_vao;   ///< OpenGL VAO for rendering
};

#endif // FLOCK_H_
