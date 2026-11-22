#ifndef INVENTORY_H
#define INVENTORY_H
#include "vector"
#include "Item.h"
#include <memory>
#include <string>
#include <vector>
class Inventory{
    private:
        std::vector<std::unique_ptr<Item>> items;
        std::unique_ptr<Item> equipped_item;
    public:
        Inventory() = default;
        Inventory& operator+=(std::unique_ptr<Item> item);
        std::string use_item(int index);
        void remove_item(int index);
        const std::vector<std::unique_ptr<Item>>& get_items() const { return items; }
        bool is_empty() const { return items.empty(); } 
        Item* get_equipped() const { return equipped_item.get(); }
        Item* get_item(int index) const { return items[index].get(); }
};

#endif