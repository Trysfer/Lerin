#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include <string>
#include <vector>

class GameEngine{
    private:
        std::vector<Level> levels;
        int current_level = 0;
        Player player;
        std::string use_item(int slot);
        Enemy current_enemy{"None", 0, 0};
        bool in_fight = false;
    public:
        GameEngine();
        bool is_in_fight() const { return in_fight; }
        const Level& get_current_level() const;
        std::string move_player(int x, int y);
        const Player& get_player() const { return player; }
        Player& get_player() { return player; }
        const Enemy& get_current_enemy() const { return current_enemy; }
        std::string attack_enemy();
        std::string wait();
        std::string guard();
};

#endif