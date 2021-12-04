#ifndef NGLSCENE_H_
#define NGLSCENE_H_
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Obj.h>
#include <ngl/Text.h>
#include <ngl/Transformation.h>
#include "WindowParams.h"
#include <QOpenGLWidget>
#include <memory>

#include "Map.h"
#include "Obstacle.h"

/// @brief a simple C++ example
/// Modified from :-
/// Jon Macey (September 20, 2020). ObjDemo [online].
/// [Accessed 2021]. Available from: "https://github.com/NCCA/ObjDemo".


class NGLScene : public QOpenGLWidget
{
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for our NGL drawing class
    /// @param [in] parent the parent window to the class
    //----------------------------------------------------------------------------------------------------------------------
    NGLScene(QWidget *_parent);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor must close down ngl and release OpenGL resources
    //----------------------------------------------------------------------------------------------------------------------
    ~NGLScene() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the initialize class is called once when the window is created and we have a valid GL context
    /// use this to setup any default GL stuff
    //----------------------------------------------------------------------------------------------------------------------
    void initializeGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called everytime we want to draw the scene
    //----------------------------------------------------------------------------------------------------------------------
    void paintGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief called when window is resized
    //----------------------------------------------------------------------------------------------------------------------
    void resizeGL(int _w, int _h) override;


private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the windows params
    //----------------------------------------------------------------------------------------------------------------------
    WinParams m_win;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Our Camera
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Mat4 m_view;
    ngl::Mat4 m_project;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief transformation stack for the gl transformations etc
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Transformation m_transform;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the model position for mouse movement
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 m_modelPos;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief our model
    //----------------------------------------------------------------------------------------------------------------------
    std::unique_ptr<ngl::Obj> m_mesh;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to show bounding box
    //----------------------------------------------------------------------------------------------------------------------
    bool m_showBBox;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief flag to show bounding sphere
    //----------------------------------------------------------------------------------------------------------------------
    bool m_showBSphere;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief text for rendering
    //----------------------------------------------------------------------------------------------------------------------
    std::unique_ptr<ngl::Text> m_text;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief method to load transform matrices to the shader
    //----------------------------------------------------------------------------------------------------------------------
    void loadMatricesToShader();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Qt Event called when a key is pressed
    /// @param [in] _event the Qt event to query for size etc
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *_event) override;

    // Qt Event called when a key is released
    void keyReleaseEvent(QKeyEvent *_event) override;

    // initial variables needed for the level
    float m_player_radius;
    float m_inistial_player_speed;
    ngl::Vec3 m_map_min;
    ngl::Vec3 m_map_max;
    std::string m_objFileName;
    std::string m_textureFileName;
    std::unique_ptr<Map> m_map;
    std::unique_ptr<Obstacle> m_obstacle;
    std::unique_ptr<ngl::Obj> m_cube_mesh;

    private:
        // using he qt timer event to update the scene
        void timerEvent(QTimerEvent *_event) override;



};



#endif

/// end of adapted base code
