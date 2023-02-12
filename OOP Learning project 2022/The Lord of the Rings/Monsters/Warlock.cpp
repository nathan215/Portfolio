#include "Warlock.h"

Warlock::Warlock(int x, int y) : Monster(x, y)
{
    cur_hp = max_hp = 15;
    atk = 5, def = 1;
}

//write your code here

Warlock:: ~Warlock() {}

string Warlock:: get_monster_str() const
{
    string r={};
    if(cur_hp<10) 
    r =  '0' + to_string(cur_hp);
    else
    r = to_string(cur_hp);
    
    return ('W' + r );
}

void Warlock:: action(Player &p, MapUnit *map[][MAP_SIZE])
{
    int p_x, p_y;
    p.get_position(p_x, p_y);
    if( (abs(p_x - x) + abs( p_y - y)) <= 1)
    p.attacked_by(atk);

    for(int i =1; i>-2; i--)
    {
        if( (x +i)< MAP_SIZE && (x +i)>= 0)
        {
            for(int j=1; j>-2; j--)
            {
                if( (y+j)< MAP_SIZE && (y+j)>= 0)
                {
                    if(i!=0 || j!=0 )
                    {
                        if( x+i !=p_x || y+j !=p_y )
                        {
                            if( map[x+i][y+j]->is_blocked() == false )
                            {
                                delete map[x+i][y+j];
                                map[x+i][y+j] = new Zombie(x+i, y+j);
                            }
                        }
                    }
                }
            }
        }
    }    
    return;
}