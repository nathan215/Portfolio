#include "Gem.h"


//write your codes here
Gem:: Gem(int x, int y, GemType gem_type) : Item(x, y), gtype(gem_type) {}

Gem:: ~Gem(){}

void Gem:: triggered_by(Player &p)
{
    if( is_valid() == false) return;

    if( (gtype == EMERALD) && ( p.get_role() == ARCHER) )
    p.charge_mp();
    else if( (gtype == RUBY ) && ( p.get_role() == WARRIOR) )
    p.charge_mp();
    else if ( (gtype == SAPPHIRE ) && ( p.get_role() == MAGE) )
    p.charge_mp();

    invalidate();
    return;
    
}

string Gem:: get_item_str() const
{
    if(gtype == RUBY) return SYM_RUBY;
    else if(gtype == EMERALD) return SYM_EMERALD;
    else return SYM_SAPPHIRE;
}