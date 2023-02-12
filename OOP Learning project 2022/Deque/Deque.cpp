#include "Deque.h"
#include<iostream>
#include <fstream>
using namespace std;

//-----------------------------------------

Deque create_deque()
{
    Node  *sentinel= new Node;
    Node *n1 = new Node;
    sentinel->next = n1;
    n1 ->next = sentinel;
    sentinel->prev = n1;
    n1->prev = sentinel;

    Deque empty ;
    empty.sentinel = sentinel;
    set_node(empty.start, n1);
    empty.end = empty.start;
    empty.start.current = empty.start.first;
    empty.end.current = empty.start.current;
    empty.ll_size =1;
    return empty;

}

void destroy_deque(Deque& deque)
{



    while(deque.start.node != deque.sentinel)
    {
        deque.start.node -> prev -> next = deque.start.node -> next;
        deque.start.node -> next -> prev = deque.start.node -> prev;
        delete deque.start.node;
        set_node(deque.start, deque.sentinel->next);
    }

    delete deque.sentinel;
    deque.sentinel = nullptr;

}

//-----------------------------------------------

Iterator begin(const Deque& deque)
{

    Iterator start; 
    start.node = deque.start.node;
    start.first = deque.start.first;
    start.last = deque.start.last;
    start.current = deque.start.current;
    return start;

}

Iterator end(const Deque& deque)
{

    Iterator end; 
    end.node = deque.end.node;
    end.first = deque.end.first;
    end.last =  deque.end.last;
    end.current = deque.end.current;
    return end;

}


int front(const Deque& deque)
{

    if( deque.start.current != deque.end.current)
    return *deque.start.current;

    cout << "Cannot get front: deque is empty" << endl;
    return -1;

}

int back(const Deque& deque)
{

    if( deque.start.current != deque.end.current)
    {
        if(deque.end.current == deque.end.first)
        {
            return deque.end.node->prev->arr[7];
        }

        return *(deque.end.current-1);
    }

    cout << "Cannot get back: deque is empty" << endl;
    return -1;
}


//-----------------------------------------------

bool empty(const Deque& deque)
{

    if( deque.start.current == deque.end.current)
    return 1;
    
    return 0;
}

int size(const Deque& deque)
{
    if (empty(deque)== 1)
    return 0;
    

    int fr_er_num = (deque.start.last-deque.start.current) + (deque.end.current- deque.end.first);
    return((deque.ll_size-2)*8 + fr_er_num);

}


//-----------------------------------------------

void push_back(Deque& deque, int val)
{
    
    if(deque.end.current ==  deque.end.last)
    {
        Node *n1 = new Node;
        deque.sentinel->prev->next =n1;
        n1->prev = deque.sentinel->prev;
        deque.sentinel->prev = n1;
        n1->next = deque.sentinel;
        deque.ll_size++;
        set_node(deque.end, n1);
        deque.end.current = deque.end.first;
    }

    *deque.end.current = val;
    deque.end.current++;
    return;
    
}

void push_front(Deque& deque, int val)
{
    
    if(deque.start.current ==deque.start.first)
    {
        Node *n1 = new Node;
        deque.sentinel->next->prev =n1;
        n1->next = deque.sentinel->next;
        deque.sentinel->next = n1;
        n1->prev = deque.sentinel;
        deque.ll_size++;
        set_node(deque.start, n1);
        deque.start.current = deque.start.last;
    }

    deque.start.current--;
    *deque.start.current = val;
    return;
}

void pop_back(Deque& deque)
{

    if(empty(deque))
    {
        cout << "Cannot pop_back: deque is empty" << endl;
        return;
    }

    if( (deque.end.current-1) == deque.end.first)
    {
        if ((deque.end.current-1) == deque.start.current)
        {
            deque.end.current--;
            return;
        }

        deque.sentinel->prev = deque.end.node->prev;
        deque.end.node->prev->next = deque.sentinel;

        delete deque.end.node;

        set_node(deque.end, deque.sentinel->prev);
        deque.end.current= deque.end.last;
        deque.ll_size--;
        return;
    }

    deque.end.current--;
    return;
}

void pop_front(Deque& deque)
{
    if(empty(deque))
    {
        cout << "Cannot pop_front: deque is empty" << endl;
        return;
    }

    if( deque.start.current == (deque.start.last-1))
    {
        if ((deque.end.current-1) == deque.start.current)
        {
            deque.end.current--;
            return;
        }
            
        deque.sentinel->next = deque.start.node->next;
        deque.start.node->next->prev = deque.sentinel;

        delete deque.start.node;

        set_node(deque.start, deque.sentinel->next);
        deque.start.current= deque.start.first;
        deque.ll_size--;
        return;
    }

    deque.start.current++;
    return;
}


//-----------------------------------------------

void print_deque(const Deque& deque)
{

    Iterator track;
    set_node( track, deque.sentinel->next);
    track.current = deque.start.current;
    cout<< "[";
    if(size(deque)!=0)
    {
        cout<< *track.current;
        track.current++;
    }

    for(int i = 1; i < size(deque) ; ++i)
    {
        if(track.current == track.last)
        {
            track.current = &track.node->next->arr[0];
            set_node(track, track.node->next);
        }
        cout<< ", " << *track.current;
        track.current++;
    }

    cout<<']'<<endl;
    return;

}


//-----------------------------------------------

void insert(Deque& deque, const Iterator& pos, int val)
{
    if(pos.current == deque.start.current)
    {
        push_front(deque, val);
        return;
    }
    if( pos.current == deque.end.current)
    {
        if(pos.current == (deque.end.last-1))
        {
            Node *n1 = new Node;
            deque.sentinel->prev->next =n1;
            n1->prev = deque.sentinel->prev;
            deque.sentinel->prev = n1;
            n1->next = deque.sentinel;
            deque.ll_size++;

            set_node(deque.end, n1);
            deque.end.current = deque.end.first;

        }
        *deque.end.current = val;
        deque.end.current++;
        return; 
    }
    
    Iterator trace;
    set_node( trace , deque.sentinel->prev);
    trace.current = (deque.end.current-1);

    if(trace.current == &( trace.node->arr[7]))
    {
        Node *n1 = new Node;
        deque.sentinel->prev->next =n1;
        n1->prev = deque.sentinel->prev;
        deque.sentinel->prev = n1;
        n1->next = deque.sentinel;
        deque.ll_size++;
        set_node(deque.end, n1);

        deque.end.current = deque.end.first;
        *deque.end.current = *trace.current;
        deque.end.current++;
        trace.current--;
    }
    else
    {
        deque.end.current++;
    }
    
    while(trace.current != pos.current)
    {

        if( trace.current == &trace.node->arr[7])
        {
            trace.node->next->arr[0] = *trace.current;
        }
        else
        {          
            *(trace.current+1) = *trace.current;
        }


        if(trace.current == (&trace.node->arr[0]) )
        {
            trace.current = (&trace.node->prev->arr[7]);
            set_node(trace, (trace.node->prev));
            
        }
        else
        {
            trace.current--;
        }
    }

    if(pos.current==pos.first)
    {
        *(trace.current+1) = *trace.current;
        *(trace.current) = val;
        return;   
    }
    else
    {
        if( trace.current == &trace.node->arr[7])
        {
            trace.node->next->arr[0] = *trace.current;
        }
        else
        {          
            *(trace.current+1) = *trace.current;
        }

        *(trace.current) = val;
        return;
    }
    

}

void erase(Deque& deque, const Iterator& pos)
{
    if(pos.current == deque.start.current)
    {
        pop_front(deque);
        return;
    }
    else if(pos.current == (deque.end.current-1))
    {
        pop_back(deque);
        return;
    }

    Iterator trace;
    trace.node = pos.node;
    trace.first = pos.first;
    trace.last = pos.last;
    trace.current=pos.current;

    while(trace.current!=(deque.end.current-1))
    {
        if(trace.current!= (trace.last-1) )
        {
            *trace.current = *(trace.current+1);
            trace.current++;
        }
        else
        {
            *trace.current = trace.node->next->arr[0];
            set_node(trace, trace.node->next);
            trace.current = trace.first;
        }    
    }

    if(deque.end.current != &deque.end.node->arr[1])
    deque.end.current --;
    else
    {
        deque.sentinel->prev = deque.end.node->prev;
        deque.end.node->prev->next = deque.sentinel;
        delete deque.end.node;
        set_node(deque.end, deque.end.node->prev);
        deque.end.current = deque.end.last;
        deque.ll_size--;
        
    }
    return;

}


//-----------------------------------------------

void store_deque(const Deque& deque, const char* filename)
{
    Iterator track;
    set_node( track, deque.sentinel->next);
    track.current = deque.start.current;
    ofstream ofs(filename);
    int store[size(deque)];

    for(int i = 0; i < size(deque) ; ++i)
    {
        if(track.current == track.last)
        {
            track.current = &track.node->next->arr[0];
            set_node(track, track.node->next);
        }
        
        store[i]  ==  *track.current;
        ofs  << *track.current<<" ";
        track.current++;
    }

    ofs.close( );

    return;
}

Deque load_deque(const char* filename)
{
    ifstream ifs(filename);
    Deque load = create_deque();

    int num;
    while (ifs >> num) 
    {
        push_back( load, num);
    }

    ifs.close();
    return load;
}
