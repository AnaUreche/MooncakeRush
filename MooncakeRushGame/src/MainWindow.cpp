#include "MainWindow.h"
#include "./ui_MainWindow.h"


#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    // opening the game loop widget inside the main window

    connect(m_ui->m_startButton, &QPushButton::clicked,
            [=]()
            {
                m_scene = new NGLScene(this);
                m_ui->m_mainWindowGridLayout->addWidget(m_scene,0,0,2,1);
                m_scene->show();
                m_scene->setFocusPolicy(Qt::StrongFocus);
                m_scene->raise();
            }
            );
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_scene;
}




