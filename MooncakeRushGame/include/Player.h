#ifndef PLAYER_H
#define PLAYER_H

#include <ngl/Transformation.h>

class Player
{
    private:
        ngl::Transformation m_transf;
        float m_rotateZ = 0.0f;
        float m_radius = 1.0f;
        float m_speed = 0.1f;

    public:
        bool m_isReset = true;
        Player();
        Player(float _radius, float _speed);

        void rotateL();
        void rotateR();
        void rotateReset();
        float getRadius() const;
        float getSpeed() const;
        void setSpeed(float _speed);
        ngl::Transformation getTranformation() const;

        ~Player() = default;

    private:
            void updateTransform();

};

#endif // PLAYER_H
