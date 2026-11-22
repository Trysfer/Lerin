#ifndef SWORD_H
#define SWORD_H
#include "../Engine/Item.h"
#include <string>

class Sword: public Item{
    private:
        int damage;
    public:
        Sword(const std::string& item_name, const std::string& item_desc, int dmg);
        int get_damage() const { return damage; };
        std::string use() override;
        bool is_equippable() const override { return true; }
};

#endif