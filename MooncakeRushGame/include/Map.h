#ifndef MAP_H
#define MAP_H

#include "Obstacle.h"
#include "Player.h"
#include <vector>
#include <ngl/Random.h>
#include <ngl/Vec3.h>

class Map
{
    private:
        float m_groundY;
        float m_overall_offsetX = 0.0f;
        ngl::Vec3 m_map_min_val;
        ngl::Vec3 m_map_max_val;

    public:
        bool m_lost = false;
        float offsetX = 0;
        unsigned int m_score = 0;
        std::vector<Obstacle> m_obstacles;
        std::unique_ptr<Player> m_player;

    public:
        Map();
        Map(ngl::Vec3 _map_min_values, ngl::Vec3 _map_max_values, float _player_radius, float _player_speed);

        void update_obstacles();
        void increase_score(unsigned int _increase);

        ~Map() = default;

    private:
        void generate_obstacles(float _zRow);
        void generate_obstacles_new_row(unsigned int _idx);
};


#endif // MAP_H
