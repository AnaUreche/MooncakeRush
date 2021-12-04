#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <ngl/Transformation.h>
#include <ngl/VAOPrimitives.h>

class Obstacle
{
    private:
        bool goUpY = true;

    public:
        ngl::Transformation m_transf;
        Obstacle();
        Obstacle(ngl::Transformation _initial_transf);
        int m_type = 0;
        float m_ground_offset = -4;
        float offsetX = 0;

        void offset(float _x, float _y, float _z);

        bool customCheckCollision(float _r) const;

        ~Obstacle() = default;

    private:
            void updateTransform();
            void resize();
};


#endif // OBSTACLE_H
