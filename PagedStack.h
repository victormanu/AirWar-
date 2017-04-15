//
// Created by gustavo on 4/6/17.
//
#include<cstdlib>
#include<iostream>
#include <fstream>
using namespace std;

#ifndef UNTITLED_STACK_H
#define UNTITLED_STACK_H


//   Creating a NODE Structure
struct node
{
    int data;
    struct node *next;
};

// Creating a class STACK
class PagedStack
{
    struct node *top;
public:
    PagedStack() // constructure
    {
        top=NULL;
    }
    void push(int, int, string, int, int,
              int, int, int, int); // to insert an element
    void pop();  // to delete an element
    void show(); // to show the stack
    bool Elements();
    int elementcount();

};
#endif //UNTITLED_STACK_H
