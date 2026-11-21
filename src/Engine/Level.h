#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>

class Level{
    private:
        std::vector<std::string> grid;
        int start_x;
        int start_y;
    public:
        Level(const std::vector<std::string>& map_grid, int sx, int sy);
        void set_tile(int x, int y, char tile);
        char get_tile(int x, int y) const;
        bool is_walkable(int x, int y) const;
        int get_start_x() const {return start_x;};
        int get_start_y() const {return start_y;};
        const std::vector<std::string>& get_grid() const { return grid; }
};

#endif