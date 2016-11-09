/****************************************************************************
** Filename: sopool.h
** This file is part of DFXObjectpool.
**
** DFXObjectpool is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** DFXObjectpool is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with DFXObjectpool.  If not, see http://www.gnu.org/licenses
****************************************************************************/


#ifndef SOPOOL_H
#define SOPOOL_H

#include "opool.h"
#include "poolable.h"


// Smart Object pool class
template <class T, class Alloc = std::allocator<T>> class SOPool : public OPool<T,Alloc>
{
public:
    SOPool(size_t size, bool expandable) : OPool<T,Alloc>(size,expandable) {}
    SOPool(size_t size, bool expandable, Alloc allocator) : OPool<T,Alloc>(size,expandable,allocator) {}
    SOPool(size_t size, bool expandable, const T& prototype)
        : OPool<T,Alloc>(size,expandable,prototype) {}
    SOPool(size_t size, bool expandable, const T &prototype, Alloc allocator)
        : OPool<T,Alloc>(size,expandable,prototype,allocator) {}
    virtual T*      getObject();
    virtual bool    freeObject(T* ptr);
};

template <class T, class Alloc> T* SOPool<T,Alloc>::getObject()
{
    // If there are free objects
    if(!this->mFree.empty())
    {
        this->mUsed.push_front(this->mFree.front());
        this->mFree.pop_front();
        this->mUsed.front()->onGiven();
        return this->mUsed.front();
    }
    else
    {
        // If the pool can expand and hasn't reached its maximum size
        if(this->mExpandable && this->mSize < this->mMaxSize)
        {
            this->mUsed.push_front(this->allocateObject());
            this->mFree.pop_front();
            this->mUsed.front()->onGiven();
            return this->mUsed.front();
        }
    }
    return nullptr;
}

template <class T, class Alloc> bool SOPool<T,Alloc>::freeObject(T *ptr)
{
    if(ptr->isActive()) return false;

    // Searching the object in the list of used objects
    for(typename std::list<T*>::iterator it = this->mUsed.begin(); it != this->mUsed.end(); it++)
    {
        if(*it == ptr)
        {
            this->mUsed.remove(*it);
            if(this->mSize > this->mMaxSize)
            {
                ptr->onReleased();
                this->deallocateObject(ptr);
            }
            else
            {
                ptr->onReleased();
                this->mFree.push_front(ptr);
            }
            break;
        }
    }
    return true;
}


#endif // SOPOOL_H
