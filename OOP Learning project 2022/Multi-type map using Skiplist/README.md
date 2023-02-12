# Multi-type map using Skiplist

## Project overview
This project implements a Multi-type map data structure using a Skip List. The Multi-type map is a container that can store multiple key-value pairs of different data
types. The implementation uses the Skip List data structure to provide an efficient way of searching, inserting, and deleting elements.

## Features
Supports multiple data types: The Multi-type map supports storing key-value pairs of different data types including integers, floating-point numbers, strings, and other custom data types.
Efficient search, insert, and delete operations: The use of the Skip List data structure ensures that the search, insert, and delete operations have an average time complexity of O(log n).
User-defined key and value types: The user can define their own key and value types, as long as they meet the requirements for the comparison and hash functions.

## Technique

The implementation of the Multi-type map uses the Skip List data structure to efficiently store the key-value pairs.
The Skip List is a data structure that can provide fast search, insert, and delete operations, by using a probabilistic approach to balance the elements across
multiple levels. The Skip List uses a concept called "coin tossing" to randomly determine the height of each node, which allows it to achieve a balance between
the number of elements at each level.Each node in the Skip List contains the key-value pair and a set of forward pointers to the next node at each level.
The forward pointers are used to skip over several elements at once, which allows for faster search and traversal times. 
The height of each node is chosen randomly when it is inserted, and the height of the entire list is adjusted dynamically as elements are added or removed.
The Multi-type map uses a hash function to map each key to a unique integer value, which is used as the basis for the comparison and ordering of the elements.
The hash function is user-defined, and must be specified when creating a new Multi-type map.
