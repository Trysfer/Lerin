#ifndef PLAYER_H
#define PLAYER_H

#include "Inventory.h"
#include "../Items/Potion.h"
#include <string>

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
        bool is_alive() const { return hp > 0; }
        void take_damage(int dmg){
            if (dmg > 0) {
                hp = std::max(0, hp - dmg);
            }
        }
        friend Player& operator+=(Player& p, int boost) {
            p.hp += boost;
            if (p.hp > p.max_hp) p.hp = p.max_hp;
            return p;
        }
        std::string use_inventory_item(int index) {
            const auto& items = inventory.get_items();
            if (index >= 0 && index < static_cast<int>(items.size())) {
                if (auto* potion = dynamic_cast<Potion*>(items[index].get())) {
                    *this += potion->get_hp();
                }
            }
            return inventory.use_item(index);
        }
};


#endif