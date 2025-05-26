#include "../include/MainWindow.h"
#include "ui/ui_MainWindow.h"


// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , m_ui(new Ui::MainWindow)
// {
//     m_ui->setupUi(this);
//     m_gl = new  NGLScene(this);
//     m_ui->m_mainWindowGridLayout->addWidget(m_gl,0,0,2,1);
//     connect(m_ui->m_spread,SIGNAL(valueChanged(double)),
//             m_gl,SLOT(setSpread(double)));
//
//     connect(m_gl,&NGLScene::glInitialized,[=](){
//
//     auto Flock=m_gl->getFlock();
//     connect(m_ui->m_numPerFrame,SIGNAL(valueChanged(int)),
//             Flock,SLOT(setNumPerFrame(int)));
//     });
// }
//
// MainWindow::~MainWindow()
// {
//     delete m_ui;
// }

MainWindow::~MainWindow() = default;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    Q_ASSERT(m_ui->m_mainWindowGridLayout != nullptr);

    m_gl = new NGLScene(this);
    Q_ASSERT(m_gl != nullptr);

    m_ui->m_mainWindowGridLayout->addWidget(m_gl, 0, 0, 2, 1);

    connect(m_ui->m_spread, SIGNAL(valueChanged(double)),
            m_gl, SLOT(setSpread(double)));

    connect(m_gl, &NGLScene::glInitialized, [=]() {
        auto Flock = m_gl->getFlock();
        Q_ASSERT(Flock != nullptr);

        connect(m_ui->m_numPerFrame, SIGNAL(valueChanged(int)),
                Flock, SLOT(setNumPerFrame(int)));
    });
}
