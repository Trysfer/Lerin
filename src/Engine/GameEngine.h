#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Level.h"
#include "Player.h"
#include <string>
#include <vector>

class GameEngine{
    private:
        std::vector<Level> levels;
        int current_level = 0;
        Player player;
        std::string use_item(int slot);
    public:
        GameEngine();
        const Level& get_current_level() const;
        std::string move_player(int x, int y);
        const Player& get_player() const { return player; }
        Player& get_player() { return player; }
};

#endif