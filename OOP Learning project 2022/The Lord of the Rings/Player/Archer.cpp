#include "Archer.h"

// Please do not change the following already implemented code
void Archer::level_up()
{
    max_hp += 2;
    cur_hp = max_hp;
    atk += 3;
    def += 2;
    max_mp += 1;
    level += 1;
    max_exp += 2;
}

//write your code here

Archer:: Archer(int x_, int y_, const string &name_): Player(x_, y_ , name_)
{
    atk =4;
    def =3;
    cur_hp =12;
    max_hp =12;
}

Archer:: ~Archer(){}

int Archer::get_range() const
{
    return 3;
}

int Archer:: skill(int &atk, int &range) 
{
    if(cur_mp ==0)
    return 1;
    
    atk = MAX_ATK;
    range = 3;
    cur_mp--;
    return 0;
} 

Role Archer:: get_role() const
{
    return Role::ARCHER;
}