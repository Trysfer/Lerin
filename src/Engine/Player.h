#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"

class Player{
    private:
        int x = 1;
        int y = 1;
        Inventory inventory;
        int hp = 100;
        int max_hp = 100;
    public:
        int get_x() const {return x;}
        int get_y() const {return y;}
        void set_position(int new_x, int new_y){
            x = new_x;
            y = new_y;
        }
        int get_hp() const {return hp;}
        Inventory& get_inventory() { return inventory; }
        const Inventory& get_inventory() const { return inventory; }
        friend std::string operator+(const std::string& text, const Player& p) {
            return text + "HP: " + std::to_string(p.hp) + "/" + std::to_string(p.max_hp);
        }
};


#endif