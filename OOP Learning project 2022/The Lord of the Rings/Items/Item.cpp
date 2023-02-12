#include "Item.h"


//write your codes here

Item:: Item(int x, int y): MapUnit(x, y) {}

Item:: ~Item(){}

UnitType Item:: get_unit_type() const
{
    return UnitType::ITEM;
}

bool Item:: is_blocked() const
{
    return false;
}

int Item:: attacked_by(int atk)
{
    invalidate();
    return 0;
}

string Item:: get_display_str() const
{
    if( is_valid() == false)
    return SYM_EMPTY;
    else if( is_discovered() ==false)
    return SYM_ITEM;
    else
    return get_item_str();
}
