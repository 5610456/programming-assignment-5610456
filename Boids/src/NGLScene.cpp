#include <QMouseEvent>
#include <QGuiApplication>
#include "NGLScene.h"
#include "Flock.h" // <- Include Flock class

#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>
#include <ngl/Util.h>
#include <iostream>

// Code structure and integration assisted by AI Coding Assistants
// Prompt: "Help fix my code so that it renders Boids."
// The AI helped with methods like initializeGL, paintGL and input handling.

// Adapted from:
// https://github.com/NCCA/labcode-jmacey-2/tree/main/ParticleQt



NGLScene::NGLScene(QWidget *_parent) : QOpenGLWidget(_parent)
{
}

NGLScene::~NGLScene()
{
  std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(int _w, int _h)
{
  m_win.width = static_cast<int>(_w * devicePixelRatio());
  m_win.height = static_cast<int>(_h * devicePixelRatio());
  m_project = ngl::perspective(45.0f, float(m_win.width) / float(m_win.height), 0.1f, 500.0f);
}

void NGLScene::initializeGL()
{
  ngl::NGLInit::initialize();
  glClearColor(0.2f, 0.3f, 0.4f, 1.0f); // Slightly darker blue-gray background
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);

  // Create some basic geometry
  // ngl::VAOPrimitives::createSphere("boid", 0.5f, 10);
  // ngl::VAOPrimitives::instance()->createSphere("sphere", 0.1f, 20);
  // ngl::VAOPrimitives::createLineGrid("floor", 100, 100, 50);
  //ngl::VAOPrimitives *prim = ngl::VAOPrimitives::instance();
  ngl::VAOPrimitives::createSphere("boid", 0.5f, 10);
  ngl::VAOPrimitives::createSphere("sphere", 0.1f, 20);
  ngl::VAOPrimitives::createLineGrid("floor", 100, 100, 50);
//test
  ngl::VAOPrimitives::createSphere("debugSphere", 10.0f, 20);







  // Load and use custom shader for Boids
  ngl::ShaderLib::loadShader("BoidShader",
                             "../shaders/BoidVertex.glsl",
                             "../shaders/BoidFragment.glsl");
  ngl::ShaderLib::use("BoidShader");

  // Set up camera/view
  m_view = ngl::lookAt({0, 50, 100}, {0, 0, 0}, {0, 1, 0});

  // Initialize Boid system
  m_Flock = std::make_unique<Flock>(200, 200, 10, ngl::Vec3(0.0f, 0.0f, 0.0f));

  m_previousTime = std::chrono::steady_clock::now();
  startTimer(16); // ~60fps

  emit glInitialized();
}

void NGLScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, m_win.width, m_win.height);

  auto rotX = ngl::Mat4::rotateX(m_win.spinXFace);
  auto rotY = ngl::Mat4::rotateY(m_win.spinYFace);
  auto transform = rotX * rotY;
  transform.m_m[3][0] = m_modelPos.m_x;
  transform.m_m[3][1] = m_modelPos.m_y;
  transform.m_m[3][2] = m_modelPos.m_z;

  // ngl::ShaderLib::use("BoidShader");
  // ngl::Mat4 modelMatrix = transform; // or ngl::Mat4::identity();
  // ngl::ShaderLib::setUniform("Model", modelMatrix);
  // ngl::ShaderLib::setUniform("MVP", m_project * m_view * transform);
  //

  // Render boids
  ngl::ShaderLib::use("BoidShader");
  ngl::ShaderLib::setUniform("MVP", m_project * m_view * transform);
  // ngl::Mat4 m_proj;
  // m_Flock->render(m_view, m_proj);
  m_Flock->render(m_view, m_project);


  // Render ground
  ngl::ShaderLib::use(ngl::nglColourShader);
  ngl::ShaderLib::setUniform("MVP", m_project * m_view * transform);
  ngl::ShaderLib::setUniform("Colour", 0.5f, 0.8f, 0.8f, 1.0f);
  ngl::VAOPrimitives::draw("floor");
  ngl::VAOPrimitives::draw("sphere");
  ngl::VAOPrimitives::draw("boid");

  //cube
  // Draw debug cube
  ngl::ShaderLib::use(ngl::nglColourShader);
  ngl::Mat4 cubeTransform = ngl::Mat4::translate(0.0f, 1.0f, 0.0f); // 1 unit above ground
  ngl::ShaderLib::setUniform("MVP", m_project * m_view * cubeTransform);
  ngl::ShaderLib::setUniform("Colour", 1.0f, 0.0f, 0.0f, 1.0f); // Bright red
  ngl::VAOPrimitives::draw("debugSphere");



}

void NGLScene::keyReleaseEvent(QKeyEvent *_event)
{
  m_keysPressed -= static_cast<Qt::Key>(_event->key());
}

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  m_keysPressed += static_cast<Qt::Key>(_event->key());

  switch (_event->key())
  {
    case Qt::Key_Escape:
      QGuiApplication::exit(EXIT_SUCCESS);
      break;

    case Qt::Key_Space:
      m_win.spinXFace = 0;
      m_win.spinYFace = 0;
      m_modelPos.set(0, 0, 0);
      break;

    case Qt::Key_A:
      m_animate ^= true;
      break;

    default:
      break;
  }

  update();
}

void NGLScene::process_keys()
{
  float dx = 0.0f, dy = 0.0f, dz = 0.0f;
  const float inc = 0.5f;

  for (auto key : m_keysPressed)
  {
    switch (key)
    {
      case Qt::Key_Left: dx -= inc; break;
      case Qt::Key_Right: dx += inc; break;
      case Qt::Key_Up: dz += inc; break;
      case Qt::Key_Down: dz -= inc; break;
      default: break;
    }
  }

  m_Flock->moveFlock(dx, dy, dz);
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
  auto now = std::chrono::steady_clock::now();
  float deltaTime = std::chrono::duration<float>(now - m_previousTime).count();
  m_previousTime = now;

  if (m_animate)
  {
    process_keys();
    m_Flock->update(deltaTime);
  }

  update();
}

void NGLScene::setAlignmentWeight(double _value)
{
  m_Flock->setAlignmentWeight(static_cast<float>(_value));
  update();
}

void NGLScene::setSpread(double s)
{
  // your code here, e.g.
  m_spread = s;
}

