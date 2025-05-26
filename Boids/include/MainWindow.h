#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "NGLScene.h"

// QT_BEGIN_NAMESPACE
// namespace Ui {
// class MainWindow;
// }
// QT_END_NAMESPACE
//
// class MainWindow : public QMainWindow
// {
//     Q_OBJECT
//
// public:
//     MainWindow(QWidget *parent = nullptr);
//     ~MainWindow();
//
// private:
//     Ui::MainWindow *m_ui;
//     NGLScene *m_gl;
// };
// #endif // MAINWINDOW_H

namespace Ui {
    class MainWindow;  // forward declaration
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *m_ui;  // pointer to the UI class
    NGLScene* m_gl;
    // other members...
};

#endif // MAINWINDOW_H
