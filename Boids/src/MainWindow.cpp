#include "../include/MainWindow.h"
#include "ui/ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    // Create OpenGL scene and add to layout
    m_gl = new  NGLScene(this);
    m_ui->m_mainWindowGridLayout->addWidget(m_gl,0,0,2,1);
    // Connect spread slider's value change to OpenGL scene slot
    connect(m_ui->m_spread,SIGNAL(valueChanged(double)),
            m_gl,SLOT(setSpread(double)));

    // Connect once OpenGL initializes, then connect Flock
    connect(m_gl,&NGLScene::glInitialized,[=](){


    // Connect number per frame spinner to flock slot
    auto Flock=m_gl->getFlock();
    connect(m_ui->m_numPerFrame,SIGNAL(valueChanged(int)),
            Flock,SLOT(setNumPerFrame(int)));
    });
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
