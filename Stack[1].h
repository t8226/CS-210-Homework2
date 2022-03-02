#pragma once
#include "List.h"

template <typename Object>
class Stack
{
public:
    bool isEmpty() const
    {
        return theList.empty();
    }
    const Object& top() const   // FILO so seeing the most recent push
    {
        return theList.front();
    }
    void push(const Object& x)  // FILO so pushes to the "top" of the stack
    {
        theList.push_front(x);
    }
    Object& pop()               // Pops the top element off of the stack
    {
        Object x = theList.front();
        theList.pop_front();
        return x;
    }
private:
    List<Object> theList;
};