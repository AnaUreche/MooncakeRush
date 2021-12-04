/// @brief a simple C++ example
/// Modified from :-
/// Jon Macey (February 18, 2021). ObjDemo [online].
/// [Accessed 2021]. Available from: "https://github.com/NCCA/ObjDemo".


#include <QMouseEvent>
#include <QGuiApplication>
#include <QFont>
#include <QFileDialog>

#include "NGLScene.h"
#include "Obstacle.h"
#include <ngl/Transformation.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>


NGLScene::NGLScene(QWidget *_parent) : QOpenGLWidget(_parent)
{
  m_showBBox=true;
  m_showBSphere=true;
  m_objFileName="models/mooncake.obj";
  m_textureFileName="textures/mooncake_base.tif";
  m_map_min = ngl::Vec3(-70.0f, -2.0f, -100.0f);
  m_map_max = ngl::Vec3(70.0f, 7.0f, 5.0f);
  m_player_radius = 0.5f;
  m_inistial_player_speed = 1.2;
  this->grabKeyboard();
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";

}

void NGLScene::resizeGL( int _w, int _h )
{
  m_project=ngl::perspective( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

void NGLScene::initializeGL()
{
    /// @brief
    /// we must call this first before any other GL commands to load and link the
    /// gl commands from the lib, if this is not done program will crash
    ngl::NGLInit::initialize();

    glClearColor(1.0f, 0.4f, 0.4f, 1.0f);			   // Grey Background
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);
    // enable multisampling for smoother drawing
    glEnable(GL_MULTISAMPLE);

    // Now we will create a basic Camera from the graphics library
    // This is a static camera so it only needs to be set once
    // First create Values for the camera position
    ngl::Vec3 from(0,1,8);
    ngl::Vec3 to(0,1,0);
    ngl::Vec3 up(0,1,0);
    m_view=ngl::lookAt(from,to,up);
    // set the shape using FOV 45 Aspect Ratio based on Width and Height
    // The final two are near and far clipping planes of 0.5 and 10
    m_project=ngl::perspective(45.0f,720.0f/576.0f,0.05f,200.0f);

    ngl::ShaderLib::createShaderProgram("TextureShader");

    ngl::ShaderLib::attachShader("TextureVertex",ngl::ShaderType::VERTEX);
    ngl::ShaderLib::attachShader("TextureFragment",ngl::ShaderType::FRAGMENT);
    ngl::ShaderLib::loadShaderSource("TextureVertex","shaders/TextureVertex.glsl");
    ngl::ShaderLib::loadShaderSource("TextureFragment","shaders/TextureFragment.glsl");

    ngl::ShaderLib::compileShader("TextureVertex");
    ngl::ShaderLib::compileShader("TextureFragment");
    ngl::ShaderLib::attachShaderToProgram("TextureShader","TextureVertex");
    ngl::ShaderLib::attachShaderToProgram("TextureShader","TextureFragment");

    // link the shader no attributes are bound
    ngl::ShaderLib::linkProgramObject("TextureShader");
    ngl::ShaderLib::use("TextureShader");


    ngl::ShaderLib::use(ngl::nglColourShader);

    ngl::ShaderLib::setUniform("Colour",1.0f,1.0f,1.0f,1.0f);

    // first we create a mesh from an obj passing in the obj file and texture
    m_mesh.reset(  new ngl::Obj(m_objFileName,m_textureFileName));
    // now we need to create this as a VAO so we can draw it
    m_mesh->createVAO();
    m_mesh->calcBoundingSphere();
    //  we create another mesh for our obstacles
    m_cube_mesh.reset(  new ngl::Obj("models/cube.obj", "textures/cube_base.tif"));
    // now we need to create this as a VAO so we can draw it
    m_cube_mesh->createVAO();
    m_cube_mesh->calcBoundingSphere();

    m_map = std::make_unique<Map>(m_map_min, m_map_max, m_player_radius, m_inistial_player_speed);
    //m_obstacle = std::make_unique<Obstacle>("models/cube.obj");

    // as re-size is not explicitly called we need to do this.
    glViewport(0,0,width(),height());
    m_text.reset(new ngl::Text("fonts/Arial.ttf",16));
    m_text->setScreenSize(width(),height());
    m_text->setColour(1,1,1);
    startTimer(1);
}


void NGLScene::loadMatricesToShader()
{

  ngl::Mat4 MVP=m_project * m_view *
                m_transform.getMatrix();

  ngl::ShaderLib::setUniform("MVP",MVP);
}

void NGLScene::paintGL()
{
    if(!m_map->m_lost)
    {
        m_map->m_player->rotateReset();
        m_map->increase_score(1);
        m_map->update_obstacles();
    }

    // clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,m_win.width,m_win.height);

    ngl::ShaderLib::use("TextureShader");
    m_transform.reset();

    m_transform.setRotation(m_map->m_player->getTranformation().getRotation());
    m_transform.setScale(0.5f, 0.5f, 0.5f);
    loadMatricesToShader();
    // draw the mesh for the player's character
    m_mesh->draw();

    ngl::ShaderLib::use("nglColourShader");


    ngl::ShaderLib::setUniform("Colour",0.6f,0.1f,0.1f,1.0f);

    m_transform.reset();
    m_transform.setScale(140.0f,1.0f,200.0f);
    m_transform.setPosition(0.0,-4.0,-90);
    loadMatricesToShader();
    // drawing the cube which serves as floor
    m_cube_mesh->draw();

    ngl::ShaderLib::use("TextureShader");
    m_transform.reset();


    for(int i = 0; i < m_map->m_obstacles.size();i++)
    {
        //m_transform.setMatrix(m_map->m_obstacles[i].m_transf.getMatrix());
        m_transform.setPosition(m_map->m_obstacles[i].m_transf.getPosition());
        m_transform.setScale(m_map->m_obstacles[i].m_transf.getScale());
        loadMatricesToShader();
        m_cube_mesh->draw();
    }

    // keeping track of the score
    m_text->renderText(10,50,"Score : ");

    int input = m_map->m_score;
    char buffer[100] = {0};
    int number_base = 10;
    std::string output = itoa(input, buffer, number_base);

    m_text->renderText(65,50,output);
}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
    // this method is called every time the main window recives a key event.
    // we then switch on the key value and set the camera in the GLWindow
    switch (_event->key())
    {
    // escape key to quite
    case Qt::Key_Escape :this->close(); break;
    // show full screen
    case Qt::Key_F : showFullScreen(); break;
    // show windowed
    case Qt::Key_Left :
    {
        m_map->m_player->rotateL();
        m_map->offsetX = 1.0f;
        m_map->m_player->m_isReset = false;
        break;
    }
    case Qt::Key_Right :
    {
        m_map->m_player->rotateR();
        m_map->offsetX = -1.0f;
        m_map->m_player->m_isReset = false;
        break ;
    }

    default : break;
    }
}

/// end of adapted base code

void NGLScene::keyReleaseEvent(QKeyEvent *_event)
{
    // when the keys are released the character comes back to the initial rotation
    switch (_event->key())
    {
    case Qt::Key_Left : m_map->m_player->m_isReset = true; m_map->offsetX = 0; break;
    case Qt::Key_Right : m_map->m_player->m_isReset = true; m_map->offsetX = 0; break;

    default : break;
    }
}

void NGLScene::timerEvent( QTimerEvent *event_)
{
    // we update the scene every time the timer ticks
    if(!(m_map->m_lost))
        update();
    else
    {
        this->lower();
    }
}
