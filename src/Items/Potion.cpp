#include "Potion.h"

Potion::Potion(const std::string& item_name, const std::string& item_desc, int health): Item(item_name, item_desc), hp(health) {
    
}

std::string Potion::use() {
    return "Used " + get_name() + " (+" + std::to_string(hp) + " HP)";
}