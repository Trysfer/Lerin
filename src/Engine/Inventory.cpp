#include "Inventory.h"
#include "Item.h"
#include <stdexcept>

Inventory& Inventory::operator+=(std::unique_ptr<Item> item) {
    if (!item) {
        throw std::invalid_argument("Cannot add a null item to inventory!");
    }
    items.push_back(std::move(item));
    return *this;
}

std::string Inventory::use_item(int index) {
    if (index < 0 || index >= static_cast<int>(items.size())) {
        throw std::out_of_range("No item in that inventory slot!");
    }
    if (items[index]->is_equippable()) {
        if (equipped_item) {
            items.push_back(std::move(equipped_item));
        }
        equipped_item = std::move(items[index]);
        remove_item(index);
        return equipped_item->use();
    }
    if( items[index]->is_potion()){
        remove_item(index);
    }
    return items[index]->use();
}

void Inventory::remove_item(int index) {
    if (index < 0 || index >= static_cast<int>(items.size())) {
        throw std::out_of_range("Cannot remove item: invalid slot!");
    }
    items.erase(items.begin() + index);
}

