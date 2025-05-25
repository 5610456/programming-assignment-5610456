#ifndef Flock_H_
#define Flock_H_

#include <vector>
#include <memory>
#include <QObject>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <ngl/MultiBufferVAO.h>
#include "boid.h"

class Flock : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int numPerFrame WRITE setNumPerFrame)

public:
    Flock(size_t _numBoids, size_t _maxAlive, int _numPerFrame, ngl::Vec3 _pos);

    size_t size() const;

    void update(float _dt);
    void render() const;

    void move(float _dx, float _dy, float _dz);
    void setSpread(float spread);
    void addBoid(const ngl::Vec3 &pos);

    public slots:
        void setNumPerFrame(int _value) { m_numPerFrame = _value; }

private:
    void resetBoid(size_t _i);
    void birthBoids();
    ngl::Vec3 randomVectorOnSphere(float _radius = 1.0f);

    ngl::Vec3 m_pos;

    // Optional: If you still want to track these per-boid properties separately
    std::vector<ngl::Vec4> m_boidPositions;  // example: positions (with maybe w=life/size)
    std::vector<ngl::Vec3> m_boidDirections;
    std::vector<ngl::Vec3> m_boidColours;
    std::vector<float> m_boidSizes;
    std::vector<int> m_boidLife;

    enum class BoidState : bool { Active, Dead };
    std::vector<BoidState> m_state;

    size_t m_maxBoids{};
    size_t m_maxAlive = 1000;
    int m_numPerFrame = 120;

    float m_spread = 1.0f;

    std::vector<boid> m_boids;

    std::unique_ptr<ngl::MultiBufferVAO> m_vao;
};

#endif // Flock_H_
