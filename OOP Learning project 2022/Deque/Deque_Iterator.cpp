#include "Deque_Iterator.h"


//--------------------------------------------
int value(const Iterator& it)
{
    return(*it.current);
}

bool equal(const Iterator& it1, const Iterator& it2)
{
    if( it1.first != it2.first)
    return 0;
    if(it1.last != it2.last)
    return 0;
    if(it1.current != it2.current)
    return 0;
    if(it1.node != it2.node)
    return 0;

    return 1;
}

//-----------------------------------------

void set_node(Iterator& it, Node* new_node)
{
    it.node = new_node;
    it.first = &(new_node->arr[0]);
    it.last = &(new_node->arr[8]);
}

Iterator next(const Iterator& it)
{
    Iterator nextt;

    if( it.current == (it.last-1))
    {

        set_node(nextt, it.node->next);
        nextt.current = nextt.first;
        return nextt;
    }

    nextt.node =  it.node;
    nextt.first = it.first;
    nextt.last  = it.last;
    nextt.current = (it.current+1);
    return nextt;
    
}

Iterator prev(const Iterator& it)
{
    Iterator prevv;
    if( it.current == it.first)
    {
        set_node(prevv, it.node->prev);
        prevv.current = (prevv.last-1);
        return prevv;
    }

    prevv.node =  it.node;
    prevv.first = it.first;
    prevv.last  = it.last;
    prevv.current = (it.current-1);
    return prevv;
    
}