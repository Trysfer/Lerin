#ifndef ITEM_H
#define ITEM_H
#include <string>
class Item{
    private:
        std::string name;
        std::string description;
    public:
        Item(const std::string& item_name, const std::string& item_desc);
        virtual ~Item() = default;
        std::string get_name() const { return name; }
        std::string get_description() const { return description; }
        virtual std::string use() = 0;
        virtual bool is_equippable() const { return false; }
        virtual bool is_potion() const { return false; }
};

#endif