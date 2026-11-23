#include "GameEngine.h"
#include "Enemy.h"
#include "Level.h"
#include "../Items/Sword.h"
#include "../Items/Potion.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <ctime>


GameEngine::GameEngine(){
    std::vector<std::string> floor1 = {
        "################",
        "#.....#........#",
        "#.....#........#",
        "#C....##.##....#",
        "#.........#....#",
        "#.........#...>#",
        "################"
    };

    std::vector<std::string> floor2 = {
        "################",
        "#...#..........#",
        "#...#..####....#",
        "#......#CC#....#",
        "###..###..#....#",
        "#.........#...>#",
        "################"
    };


    levels.emplace_back(floor1,1,1);
    levels.emplace_back(floor2,1,1);

    player.set_position(levels[0].get_start_x(), levels[0].get_start_y());
    player.get_inventory() += std::make_unique<Sword>("Wooden Sword", "Is it a stick?", 15);
    player.get_inventory() += std::make_unique<Potion>("Potion", "Healing Potion", 20);
    player.get_inventory() += std::make_unique<Potion>("Potion", "Healing Potion", 20);
}

const Level& GameEngine::get_current_level() const{
    return levels[current_level];
}

std::string GameEngine::move_player(int x, int y){
    Level& level = levels[current_level];
    int next_x = player.get_x() + x;
    int next_y = player.get_y() + y;
    if(is_in_fight()==true){
        return "You can't move!";
    }
    if(!level.is_walkable(next_x, next_y)){
        throw std::logic_error("Wall is blocking the way!");
    }
    player.set_position(next_x, next_y);
    if (level.get_tile(player.get_x(), player.get_y()) == '>') {
        if (current_level + 1 < static_cast<int>(levels.size())) {
            current_level++;
            player.set_position(levels[current_level].get_start_x(),levels[current_level].get_start_y());
            return "You've moved to the next level!";
        } else {
            player.take_damage(200);
            return "You've reached the end of the dungeon! You won!";
        }
    }
    if (level.get_tile(player.get_x(), player.get_y()) == 'C') {
        level.set_tile(player.get_x(), player.get_y(), '.');
        srand(time(0));
        int rand_num = rand() % 2;
        std::unique_ptr<Item> item;
        if(rand_num >= 1){
            int rand_sword = rand() % 5;
            switch (rand_sword) {
                case 0:{
                    item = std::make_unique<Sword>("Golden Sword", "Very Sharp", 35);
                    break;
                }
                case 1:{
                    item = std::make_unique<Sword>("Iron Sword", "Very Sturdy", 25);
                    break;
                }
                case 2:{
                    item = std::make_unique<Sword>("Excalibur", "MAGIC Sword", 65);
                    break;
                }
                case 3:{
                    item = std::make_unique<Sword>("Rusty Sword", "Not so Sharp", 20);
                    break;
                }
                case 4:{
                    item = std::make_unique<Sword>("Steel Sword", "Very Sharp", 30);
                    break;
                }
                default:{
                    item = std::make_unique<Sword>("Wooden Sword", "Is it a stick?", 15);
                    break;
                }
            }
        }else{
            item = std::make_unique<Potion>("Potion", "Healing Potion", 20);
        }      
        std::string name = item->get_name();
        player.get_inventory() += std::move(item);
        return "Opened chest: found "+name;
    }
    if(level.get_tile(player.get_x(), player.get_y()) == '.')   {
        srand(time(0));
        int rand_num = rand() % 20;
        if(rand_num <= 2){
            int rand_enemy = rand()%4;
            switch (rand_enemy) {
                case 0:{
                    current_enemy = Enemy("Skeleton",25,10);
                    break;
                }
                case 1:{
                    current_enemy = Enemy("Goblin",50,25);
                    break;
                }
                case 2:{
                    current_enemy = Enemy("Bat",5,2);
                    break;
                }
                case 3:{
                    current_enemy = Enemy("Giant Rat",25,35);
                    break;
                }
                default:{
                    current_enemy = Enemy("Skeleton",25,10);
                    break;
                }
            }
            
            in_fight = true;
            return "You've been attacked by a "+current_enemy.get_name()+"!";
        }
    }
    return "Move made.";
}
std::string GameEngine::use_item(int slot) {
    return player.use_inventory_item(slot-1);
}

std::string GameEngine::attack_enemy(){
    if(!in_fight){
        return "No enemy.";
    }
    if(!player.is_alive()){
        return "You are Dead!";
    }
    std::string msg;
    auto* sword = dynamic_cast<Sword*>(player.get_inventory().get_equipped());
    current_enemy.take_damage(sword->get_damage());
    if(!current_enemy.is_alive()){
        in_fight = false;
        return "You have defeated a "+current_enemy.get_name();
    }
    msg+= "You have hit a "+current_enemy.get_name()+". ";
    if(current_enemy.is_disabled_next_turn() == true){
        msg += current_enemy.get_name() + " has recovered.";
        current_enemy.set_disable(false);
    }else{
        srand(time(0));
        int rand_num = rand()%10;
        if(rand_num <= 5){
            player.take_damage(current_enemy.get_dmg());
            msg += current_enemy.get_name()+" has hit you!";
        }else{
            msg+= current_enemy.get_name()+" has missed.";
        }
    }
    return msg;
}
std::string GameEngine::wait(){
    if(!in_fight){
        return "No enemy.";
    }
    if(!player.is_alive()){
        return "You are Dead!";
    }
    std::string msg;
    msg+= "You have passed turn to the "+current_enemy.get_name()+". ";
    if(current_enemy.is_disabled_next_turn() == true){
        msg += current_enemy.get_name() + " has recovered.";
        current_enemy.set_disable(false);
    }else{
        srand(time(0));
        int rand_num = rand()%10;
        if(rand_num <= 5){
            player.take_damage(current_enemy.get_dmg());
            msg += current_enemy.get_name()+" has hit you!";
        }else{
            msg+= current_enemy.get_name()+" has missed.";
        }
    }
    return msg;
}
std::string GameEngine::guard(){
    if(!in_fight){
        return "No enemy.";
    }
    if(!player.is_alive()){
        return "You are Dead!";
    }
    std::string msg;
    msg+= "You've chosen to guard against a "+current_enemy.get_name()+". ";
    if(current_enemy.is_disabled_next_turn() == true){
        msg += current_enemy.get_name() + " has recovered.";
        current_enemy.set_disable(false);
    }else{
        srand(time(0));
        int rand_num = rand()%10;
        if(rand_num <= 4){
            player.take_damage(static_cast<int>(current_enemy.get_dmg()/2));
            msg += current_enemy.get_name()+" has hit you!";
        }else{
            msg+= current_enemy.get_name()+" has missed and is disable for the next turn.";
            current_enemy.set_disable(true);
        }
    }
    return msg;
}