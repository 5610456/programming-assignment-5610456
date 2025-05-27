#ifndef NGLSCENE_H_
#define NGLSCENE_H_

#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include "WindowParams.h"

// This must be included after NGL includes else we get a clash with OpenGL libs
#include <QOpenGLWidget>

#include "Flock.h"
#include <memory>
#include <chrono>
#include <QSet>
#include <ngl/Text.h>

//----------------------------------------------------------------------------------------------------------------------
/// @file NGLScene.h
///   This class inherits from the Qt QOpenGLWidget and allows us to use NGL to draw OpenGL.
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/9/13
/// Revision History:
///   Initial version for NGL6 / Qt5 demos.
/// @class NGLScene
///   Main GL window widget for NGL applications, all drawing elements reside here.
//----------------------------------------------------------------------------------------------------------------------


// Adapted from:
// https://github.com/NCCA/labcode-jmacey-2/tree/main/ParticleQt

class NGLScene : public QOpenGLWidget
{
    Q_OBJECT

public:
  
    ///   Constructor for NGL drawing class.
    ///  [in] _parent Parent QWidget, default nullptr.
   
    explicit NGLScene(QWidget *_parent = nullptr);

   
    ///   Destructor, cleans up NGL and OpenGL resources.
    ~NGLScene() override;
    
    ///   Called once when OpenGL context is ready, used to setup default GL stuff.
    void initializeGL() override;
    
    ///  Called every frame to render the scene.
    void paintGL() override;
    
    ///   Called when the window is resized.
    ///  [in] _w New width.
    ///  [in] _h New height.
    void resizeGL(int _w, int _h) override;
    
    ///   Accessor for the flock instance.
    /// @return Pointer to the Flock object.
    Flock *getFlock() { return m_Flock.get(); }

public slots:
    ///   Slot to set spread parameter of the flock.
    ///  [in] s Spread value.
    void setSpread(double s);
    
    ///   Slot to set the alignment weight parameter of the flock.
    ///  [in] _value Alignment weight value.
    void setAlignmentWeight(double _value);

signals:
    ///   Signal emitted once OpenGL is initialized.
    void glInitialized();

private:
    double m_spread = 5.5;  ///< Spread value for flock dispersion.
    
    ///   Qt key press event handler.
    ///   Key event.
    void keyPressEvent(QKeyEvent *_event) override;
    
    ///   Qt mouse move event handler.
    ///   Mouse event.
    void mouseMoveEvent(QMouseEvent *_event) override;
    
    ///   Qt mouse press event handler.
    ///   Mouse event.
    void mousePressEvent(QMouseEvent *_event) override;
    
    ///   Qt mouse release event handler.
    ///   Mouse event.
    void mouseReleaseEvent(QMouseEvent *_event) override;

    
    ///   Qt mouse wheel event handler.
    ///   Wheel event.
    void wheelEvent(QWheelEvent *_event) override;

    
    ///   Qt timer event handler.
    ///   Timer event.
    void timerEvent(QTimerEvent *_event) override;
    
    ///   Qt key release event handler.
    ///   Key event.
    void keyReleaseEvent(QKeyEvent *_event) override;
    
    ///   Process currently pressed keys for input handling.
    void process_keys();

    WinParams m_win;                ///< Window parameters for mouse control etc.
    ngl::Vec3 m_modelPos;           ///< Model position in world space.
    std::unique_ptr<Flock> m_Flock; ///< Smart pointer managing flock object.

    bool m_animate = true;          ///< Toggle animation on/off.

    ngl::Mat4 m_view;               ///< View matrix.
    ngl::Mat4 m_project;            ///< Projection matrix.

    std::chrono::steady_clock::time_point m_previousTime; ///< For delta time calculation.

    QSet<Qt::Key> m_keysPressed;    ///< Set of keys currently pressed.

    std::unique_ptr<ngl::Text> m_text; ///< NGL text renderer for on-screen info.
};

#endif // NGLSCENE_H_
