#ifndef POTION_H
#define POTION_H
#include "../Engine/Item.h"
#include <string>

class Potion: public Item{
    private:
        int hp;
    public:
        Potion(const std::string& item_name, const std::string& item_desc, int health);
        int get_hp() const { return hp; };
        std::string use() override;
        bool is_potion() const override { return true; }
};

#endif