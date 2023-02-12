#include "Monster.h"
#include <cmath>

// write your code here

Monster:: Monster(int x, int y) :MapUnit( x, y ){}

Monster:: ~Monster() {}

bool Monster:: is_active() const { return active; }

void Monster:: set_active()
{
    if( is_valid() == true)
    active = true;
    return;
}

void Monster:: recover_hp(int hp)
{
    cur_hp += hp;
    if (cur_hp > max_hp)
    cur_hp = max_hp;
    return;
}

UnitType Monster:: get_unit_type() const { return MONSTER;}

bool Monster:: is_blocked() const
{
    if( is_valid() == true)
    return true;
    else
    return false;    
}

int Monster:: attacked_by(int atk_)
{
    if( is_valid()== false)
    return 0;

    int damage = atk_ - def;
    if (damage > 0)
    {
        cur_hp -= damage;
        if(cur_hp<=0)
        {
            invalidate();
            active = false;
            return 1;
        }
    }
    return 0;
}

string Monster:: get_display_str() const
{
    if( is_valid() == false)
    return SYM_EMPTY;
    else if (is_discovered() == false)
    return SYM_DANGER;
    else
    return get_monster_str();
}

void Monster:: follow(const Player &p, MapUnit *map[][MAP_SIZE])
{
    int p_x, p_y;
    p.get_position(p_x, p_y);
    if( abs(p_x - x) + abs( p_y - y) == 1) return;

    int h_sign=0;
    if(x- p_x > 0 )
    h_sign =1;
    else if(x -p_x <0)
    h_sign = -1;
    int v_sign =0 ;
    if( y-p_y > 0 )
    v_sign =1;
    else if( y-p_y <0)
    v_sign = -1;

    if( (abs(p_x - x)>0) && (map[x- h_sign][y]->is_blocked() == false) )
    {
        delete map[x- h_sign][y];
        map[x- h_sign][y] = this;
        map[x][y] = new EmptyLand(x,y);
        x -= h_sign;
        return;
    }
    else if( (abs(p_y - y)>0) && (map[x][y - v_sign]->is_blocked() == false) )
    {
        delete map[x][y - v_sign];
        map[x][y - v_sign] = this;
        map[x][y]  = new EmptyLand(x,y);
        y-= v_sign;
        return;
    }
    return;

}
