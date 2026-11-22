#include "Commands.h"
#include "../Items/Sword.h"
#include "Player.h"
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
        if(!engine.get_player().is_alive()){
            return "You are Dead!";
        }
        if (arg.empty()) {return "Usage: use <slot>";}
        int slot = std::stoi(arg);
        return engine.get_player().use_inventory_item(slot-1);
    }

    if (cmd == "drop") {
        if(!engine.get_player().is_alive()){
            return "You are Dead!";
        }
        if (arg.empty()) return "Usage: drop <slot>";
        int slot = std::stoi(arg);
        engine.get_player().get_inventory().remove_item(slot-1);
        return "Dropped item.";
    }

    if (cmd == "help") {
        if(!engine.get_player().is_alive()){
            return "Command: quit";
        }
        if(engine.is_in_fight()){
            return "Commands: use <slot>, drop <slot>, info, attack, enemy, guard, wait";
        }
        return "Commands: use <slot>, drop <slot>, info";
    }

    if(cmd == "attack"){
        if(!engine.get_player().get_inventory().get_equipped()){
            return "First Equipe any weapon.";
        }
        return engine.attack_enemy();
    }
    if(cmd == "guard"){
        return engine.guard();
    }
    if(cmd == "wait"){
        return engine.wait();
    }
    if(cmd == "enemy"){
        if(!engine.is_in_fight()){
            return "No Enemy";
        }
        return engine.get_current_enemy().get_name()+": "+std::to_string(engine.get_current_enemy().get_hp())+" HP";
    }
    if(cmd == "info"){
        if(!engine.get_player().is_alive()){
            return "You are Dead!";
        }
        if(!engine.get_player().get_inventory().get_equipped()){
            return "Equiped: None | "+engine.get_player();
        }
        if(auto* sword = dynamic_cast<Sword*>(engine.get_player().get_inventory().get_equipped())){
            return "Equiped: "+sword->get_name()+" | Damage: "+std::to_string(sword->get_damage())+" | "+engine.get_player();
        }
        return "Unregistered item";
    }

    return "Unknown command: " + cmd;
}