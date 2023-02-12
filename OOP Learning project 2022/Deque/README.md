# Deque
## Project Overview

This project consists of a C++ implementation of a Deque (Double Ended Queue) data structure. A deque is a linear collection that supports adding and removing elements from both ends. The implementation includes five files:

    Deque.h: header file that defines the interface for the Deque class
    Deque.cpp: implementation file that implements the Deque class
    main.cpp: main file that tests the implementation of the Deque class
    Deque_Iterator.h: header file that defines the Node class used by the Deque class
    Deque_Iterator: implementation file that implements the Node class used by the Deque class

## Features


Implements a Deque class with the following methods:

    push_back: inserts an element at the back of the deque
    push_front: inserts an element at the front of the deque
    pop_back: removes the last element from the deque
    pop_front: removes the first element from the deque
    empty: returns true if the deque is empty, false otherwise
    size: returns the number of elements in the deque
    print: prints the elements of the deque, starting from the front

## Technique

The code makes use of the following techniques:

    Pointers to manipulate data
    Linked list implementation
    Structs to define new data types

The implementation of the Deque class makes use of a linked list variant, where each node contains an element and pointers to the previous and next nodes in the list. The linked list allows for constant time insertion and removal of elements from both ends of the deque. The use of pointers and structs makes the implementation efficient and flexible.
