#include "Player.h"

Player::Player(float _radius, float _speed)
{
    m_radius = _radius;
    m_speed = _speed;
}

void Player::rotateL()
{
    if(m_rotateZ < 30)
    {
        m_rotateZ += 5.0f;
        updateTransform();
    }
    m_isReset = false;
}

void Player::rotateR()
{
    if(m_rotateZ > -30)
    {
        m_rotateZ -= 5.0f;
        updateTransform();
    }
    m_isReset = false;
}

void Player::rotateReset()
{
    if(m_rotateZ > 0.5f && m_isReset)
        m_rotateZ -= 5.0f;

    if(m_rotateZ < -0.5f && m_isReset)
        m_rotateZ += 5.0f;

    updateTransform();
}


 void Player::updateTransform()
 {
     m_transf.setRotation(0.0f,0.0f,m_rotateZ);
 }

 ngl::Transformation Player::getTranformation() const
 {
     return m_transf;
 }

 float Player::getRadius() const
 {
     return m_radius;
 }
 float Player::getSpeed() const
 {
     return m_speed;
 }

 void Player::setSpeed(float _speed)
 {
     m_speed = _speed;
 }
