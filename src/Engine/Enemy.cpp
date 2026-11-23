#include "Enemy.h"

Enemy::Enemy(const std::string& enemy_name, int health, int damage): name(enemy_name), hp(health), dmg(damage) {}

void Enemy::take_damage(int dmg) {
    if (dmg > 0) {
        hp = std::max(0, hp - dmg);
    }
}

void Enemy::set_disable(bool value){
    disabled_next_turn = value;
}