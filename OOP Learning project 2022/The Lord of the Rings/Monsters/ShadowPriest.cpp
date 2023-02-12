#include "ShadowPriest.h"

ShadowPriest::ShadowPriest(int x, int y) : Monster(x, y)
{
    cur_hp = max_hp = 15;
    atk = 5, def = 2;
}

//write your code here

ShadowPriest:: ~ShadowPriest() {}

string ShadowPriest:: get_monster_str() const
{
    string r;
    if(cur_hp<10) 
    r =  '0' + to_string(cur_hp);
    else
    r = to_string(cur_hp);

    return ('S' + r);
}

void ShadowPriest:: action(Player &p, MapUnit *map[][MAP_SIZE])
{
    int p_x, p_y;
    p.get_position(p_x, p_y);

    if( (abs(p_x - x) + abs( p_y - y)) <= 1)
    p.attacked_by(atk);

    Monster* m;

    for(int i =1; i>-2; i--)
    {
        if( (x+i)< MAP_SIZE && (x +i)>= 0)
        {
            for(int j=1; j>-2; j--)
            {
                if( (y+j)< MAP_SIZE && (y+j)>= 0)
                {
                    if(i!=0 || j!=0)
                    {
                        if( x+i != p_x || y+j !=p_y )
                        {
                            if( map[x+i][y+j]->get_unit_type() == MONSTER )
                            {
                                m  = static_cast<Monster*>(map[x+i][y+j]);
                                m->recover_hp(5);
                            }
                        }  
                    }
                }
            }
        }
    }      
    return;
}