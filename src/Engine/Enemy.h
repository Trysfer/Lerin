#ifndef ENEMY_H
#define ENEMY_H
#include "string"
class Enemy{
    private:
        std::string name;
        int hp;
        int dmg;
    public:
        Enemy(const std::string& enemy_name, int health, int damage);
        std::string get_name() const { return name; }
        int get_hp() const { return hp; }
        int get_dmg() const { return dmg; }
        bool is_alive() const { return hp > 0; }
        void take_damage(int dmg);
};

#endif