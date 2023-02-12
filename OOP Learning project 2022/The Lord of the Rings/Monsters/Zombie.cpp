#include "Zombie.h"

Zombie::Zombie(int x, int y) : Monster(x, y)
{
    cur_hp = max_hp = 20;
    atk = 9, def = 3;
}

//write your code here

Zombie:: ~Zombie(){}

string Zombie:: get_monster_str() const
{
    string r={};
    if(cur_hp<10) 
    r =  '0' + to_string(cur_hp);
    else
    r = to_string(cur_hp);
    return ('Z' + r );
}

void Zombie:: action(Player &p, MapUnit *map[][MAP_SIZE])
{
    int p_x, p_y;
    p.get_position(p_x, p_y);
    if( (abs(p_x - x) + abs( p_y - y)) <= 1)
    p.attacked_by(atk);
    return;
}