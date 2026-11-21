#include "GameEngine.h"
#include "Level.h"
#include <string>
#include <stdexcept>
#include <vector>


GameEngine::GameEngine(){
    std::vector<std::string> floor1 = {
        "################",
        "#.....#........#",
        "#.....#........#",
        "#.....##.##....#",
        "#.........#....#",
        "#.........#...>#",
        "################"
    };

    std::vector<std::string> floor2 = {
        "################",
        "#...#..........#",
        "#...#..####....#",
        "#......#..#....#",
        "###..###..#....#",
        "#.........#...>#",
        "################"
    };


    levels.emplace_back(floor1,1,1);
    levels.emplace_back(floor2,1,1);

    player.set_position(levels[0].get_start_x(), levels[0].get_start_y());
}

const Level& GameEngine::get_current_level() const{
    return levels[current_level];
}

std::string GameEngine::move_player(int x, int y){
    Level& level = levels[current_level];
    int next_x = player.get_x() + x;
    int next_y = player.get_y() + y;
    if(!level.is_walkable(next_x, next_y)){
        throw std::logic_error("Wall is blocking the way!");
    }
    player.set_position(next_x, next_y);
    if (level.get_tile(player.get_x(), player.get_y()) == '>') {
        if (current_level + 1 < static_cast<int>(levels.size())) {
            current_level++;
            player.set_position(levels[current_level].get_start_x(),levels[current_level].get_start_y());
            return "You've moved to the next level!";
        } else {
            return "You've reached the end of the dungeon! You won!";
        }
    }
    return "Move made.";
}
