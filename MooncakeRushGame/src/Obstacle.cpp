#include "Obstacle.h"
#include "ngl/Vec3.h"
#include <iostream>

Obstacle::Obstacle( ngl::Transformation _initial_transf)
{
    // setting tthe initial transormations
    m_transf.setPosition(_initial_transf.getPosition());
    m_transf.setScale(_initial_transf.getScale());
}

void Obstacle::offset(float _x, float _y, float _z)
{
    // this function offsets the possition of the objects by a certain ammount. I am also using it to check which
    // obstacles need to move in the y direction and then translate them accordingly
    m_transf.addPosition(_x, _y, _z);
    float treshold = 0.2;

    if(m_type == 1)
    {
        if(goUpY)
        {
            m_transf.addPosition(0.0, 0.1, 0.0);
            if(m_transf.getPosition().m_y- m_ground_offset >= m_transf.getScale().m_y/2-treshold)
            {
                goUpY = false;
            }
        }
        else
        {
            m_transf.addPosition(0.0, -0.1, 0.0);
            if(m_transf.getPosition().m_y- m_ground_offset <= treshold-m_transf.getScale().m_y/2)
            {
                goUpY = true;
            }
        }
    }
}

bool Obstacle::customCheckCollision(float _r) const
{
    // we check the collision between 2 restangles - one is the collision rectangle associated to the character
    // and the other one is the front face of the obstacle
    // although not that accurate, this is the way the original Jet Rush game works which helps boost the performance

    float treshold = 0.1;

    float obst_z = m_transf.getPosition().m_z + m_transf.getScale().m_z/2;
    if(abs(obst_z) < _r + treshold)
    {
        if(abs(m_transf.getPosition().m_x) < m_transf.getScale().m_x/2 + _r + treshold)
        {
            if(abs(m_transf.getPosition().m_y) < m_transf.getScale().m_y/2 + _r + treshold)
            {
                return true;
            }
        }
    }

    return false;
}
