#include "Commands.h"
#include "../Items/Sword.h"
#include <string>

std::string Commands::execute(GameEngine& engine, const std::string& input) {
    std::string cmd = input;
    std::string arg = "";

    int pos = input.find(' ');
    if (pos != -1) {
        cmd = input.substr(0, pos);
        arg = input.substr(pos + 1);
    }

    if (cmd == "use") {
        if (arg.empty()) {return "Usage: use <slot>";}
        int slot = std::stoi(arg);
        return engine.get_player().get_inventory().use_item(slot-1);
    }

    if (cmd == "drop") {
        if (arg.empty()) return "Usage: drop <slot>";
        int slot = std::stoi(arg);
        engine.get_player().get_inventory().remove_item(slot-1);
        return "Dropped item.";
    }

    if (cmd == "help") {
        return "Commands: use <slot>, drop <slot>";
    }

    if(cmd == "info"){
        if(!engine.get_player().get_inventory().get_equipped()){
            // return "Equiped: None | HP: "+std::to_string(engine.get_player().get_hp());
            return "Equiped: None | "+engine.get_player();
        }
        if(auto* sword = dynamic_cast<Sword*>(engine.get_player().get_inventory().get_equipped())){
            return "Equiped: "+sword->get_name()+" | Damage: "+std::to_string(sword->get_damage())+" | "+engine.get_player();;
        }
        return "Unregistered item";
    }

    return "Unknown command: " + cmd;
}