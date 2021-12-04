#include "Map.h"

Map::Map(ngl::Vec3 map_min_values_, ngl::Vec3 map_max_values_, float player_radius_, float player_speed_)
{
    m_map_min_val = map_min_values_;
    m_map_max_val = map_max_values_;
    m_player = std::make_unique<Player>(player_radius_, player_speed_);
    generate_obstacles(1.0f);
}

void Map::generate_obstacles(float _zRow)
{
    // this function generates obstacles relative to a z value
    // x and z are shifted in such way that the random function still leaves
    // place for the player's movement
    std::unique_ptr<Obstacle> new_obstacle;
    ngl::Transformation temp_transf;
    float z = _zRow;
    float x = m_map_min_val.m_x;

    while(x < m_map_max_val.m_x)
    {
        x = ngl::Random::randomPositiveNumber(17.0f) + x;
        z = ngl::Random::randomPositiveNumber(15.0f) + _zRow;

        float x_s = ngl::Random::randomPositiveNumber(3.0f) + 0.1f;
        float y_s = ngl::Random::randomPositiveNumber(m_map_max_val.m_y - m_map_min_val.m_y) + 5.0f;
        float z_s = ngl::Random::randomPositiveNumber(2.0f) + 0.1f;

        // using a temporary transformation matrix and a temporary objct to add to the vector
        temp_transf.addPosition(x,y_s/2.0f-4,z);
        temp_transf.addScale(x_s, y_s, z_s);
        Obstacle new_obstacle(temp_transf);
        if(m_score % 2000  < 1000 && m_score > 1000)
        {
            new_obstacle.m_type = 1;
            new_obstacle.offset(0.0f, ngl::Random::randomNumber(temp_transf.getScale().m_y/10)-0.2, 0.0f);
        }
        m_obstacles.push_back(new_obstacle);
        temp_transf.reset();
    }
}

void Map::update_obstacles()
{
    // updates all the obstacles in the vector if collision did not occur

    for(int i = 0; i < m_obstacles.size(); i++)
    {
        // if an obstacke is out of the area we render it is erased from the vector

        if(m_obstacles[i].m_transf.getPosition().m_z > 4 || (m_obstacles[i].m_transf.getPosition().m_x < -70 + m_overall_offsetX) || (m_obstacles[i].m_transf.getPosition().m_x > 70 + m_overall_offsetX) )
        {
            m_obstacles.erase(m_obstacles.begin() + i);
        }
        else
        {
            m_obstacles[i].offset(m_player->getSpeed()* 0.2 * offsetX , 0.0f, m_player->getSpeed() );

            // if player collides force return
            if(m_obstacles[i].customCheckCollision(m_player->getRadius()))
            {
                m_lost = true;
                return;
            }
        }
    }

    // spawn new obstacles every 30 units in the z direction

    if(m_score % 30 == 0)
    {
        generate_obstacles(-200);
    }
}

void Map::increase_score(unsigned int _increase)
{
    // updating the score and increasing the speed every 1000 units
    m_score += _increase;
    if(m_score % 1000 == 0)
    {
        m_player->setSpeed(m_player->getSpeed() + 0.1);
    }
}


