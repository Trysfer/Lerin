#include "Level.h"
#include <stdexcept>

Level::Level(const std::vector<std::string>& map_grid, int sx, int sy) : grid(map_grid), start_x(sx), start_y(sy){}

void Level::set_tile(int x, int y, char tile){
    if (y >= 0 && y < static_cast<int>(grid.size()) && x >= 0 && x < static_cast<int>(grid[y].size())) {
        grid[y][x] = tile;
    }
}

char Level::get_tile(int x, int y) const{
    if (y < 0 || y >= static_cast<int>(grid.size()) || x < 0 || x >= static_cast<int>(grid[y].size())) {
        throw std::out_of_range("Out of bounds!");
    }
    return grid[y][x];
}

bool Level::is_walkable(int x, int y) const{
    return get_tile( x, y) != '#';
}