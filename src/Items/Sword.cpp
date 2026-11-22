#include "Sword.h"

Sword::Sword(const std::string& item_name, const std::string& item_desc, int dmg): Item(item_name, item_desc), damage(dmg) {
    
}

std::string Sword::use() {
    return "Equipped " + get_name() + " (+" + std::to_string(damage) + " DMG)";
}