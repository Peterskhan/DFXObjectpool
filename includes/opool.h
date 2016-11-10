/****************************************************************************
** Filename: opool.h
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

#ifndef OPOOL_H
#define OPOOL_H

#include <list>
#include <memory>
#include "opoolexceptions.h"

typedef unsigned int size_t;


// Generic Object pool class
template <class T, class Alloc = std::allocator<T>> class OPool
{
private:
    OPool(OPool const &) = delete;
    void operator=(OPool const &x) = delete;
public:
    OPool(size_t size, bool expandable);
    OPool(size_t size, bool expandable, Alloc allocator);
    OPool(size_t size, bool expandable, const T prototype);
    OPool(size_t size, bool expandable, const T prototype, Alloc allocator);
    ~OPool();
    void            deletionCheck() const;
    size_t          getSize() const;
    size_t          getMaxSize() const;
    Alloc           getAllocator() const;
    bool            isExpandable() const;
    bool            hasAvailable() const;
    bool            hasPrototype() const;
    bool            hasAllocator() const;
    void            setMaxSize(const size_t maxSize);
    void            setExpandable(const bool expandable);
    virtual T*      getObject();
    virtual bool    freeObject(T* ptr);
protected:
    void            initialize(size_t size, bool expandable);
    T*              allocateObject();
    void            deallocateObject(T* ptr);
protected:
    size_t          mSize;
    size_t          mMaxSize;
    bool            mExpandable;
    T               mPrototype;
    bool            mHasPrototype;
    bool            mHasAllocator;
    Alloc           mAllocator;
    std::list<T*>   mFree;
    std::list<T*>   mUsed;
};

// Getters
template <class T, class Alloc> size_t OPool<T,Alloc>::getSize() const         { return mSize; }
template <class T, class Alloc> size_t OPool<T,Alloc>::getMaxSize() const      { return mMaxSize; }
template <class T, class Alloc> Alloc OPool<T,Alloc>::getAllocator() const     { return mAllocator; }
template <class T, class Alloc> bool OPool<T,Alloc>::isExpandable() const      { return mExpandable; }
template <class T, class Alloc> bool OPool<T,Alloc>::hasAvailable() const      { return !mFree.empty(); }
template <class T, class Alloc> bool OPool<T,Alloc>::hasPrototype() const      { return mHasPrototype; }
template <class T, class Alloc> bool OPool<T,Alloc>::hasAllocator() const      { return mHasAllocator; }

// Setters
template <class T, class Alloc> void OPool<T,Alloc>::setMaxSize(const size_t maxSize)        { mMaxSize = maxSize; }
template <class T, class Alloc> void OPool<T,Alloc>::setExpandable(const bool expandable)    { mExpandable = expandable; }

// Initializer
template <class T, class Alloc> void OPool<T,Alloc>::initialize(size_t size, bool expandable)
{
    // Setting initial properties
    mSize = 0;
    mMaxSize = size;
    mExpandable = expandable;
    mHasPrototype = false;
    mHasAllocator = false;
}

// Constructors
template <class T, class Alloc> OPool<T,Alloc>::OPool(size_t size, bool expandable)
{
    initialize(size,expandable);

    // Creating pool objects
    for(unsigned int i = 0; i < size; i++)
    {
        allocateObject();
    }
}

template <class T, class Alloc> OPool<T,Alloc>::OPool(size_t size, bool expandable, Alloc allocator)
{
    initialize(size,expandable);
    mHasAllocator = true;
    mAllocator = allocator;

    // Creating pool objects
    for(unsigned int i = 0; i < size; i++)
    {
        allocateObject();
    }
}

template <class T, class Alloc> OPool<T,Alloc>::OPool(size_t size, bool expandable, const T prototype)
{
    initialize(size,expandable);
    mHasPrototype = true;
    mPrototype = prototype;

    // Creating pool objects
    for(unsigned int i = 0; i < size; i++)
    {
        allocateObject();
    }
}

template <class T, class Alloc> OPool<T,Alloc>::OPool(size_t size, bool expandable, const T prototype, Alloc allocator)
{
    initialize(size,expandable);
    mHasPrototype = true;
    mPrototype = prototype;
    mHasAllocator = true;
    mAllocator = allocator;

    // Creating pool objects
    for(unsigned int i = 0; i < size; i++)
    {
        allocateObject();
    }
}

// Destructor
template <class T, class Alloc> OPool<T,Alloc>::~OPool()
{
    // Deleting free pool objects
    for(typename std::list<T*>::iterator it = mFree.begin(); it != mFree.end(); it++)
    {
        deallocateObject(*it);
    }
}

// Deletion check
template <class T, class Alloc> void OPool<T,Alloc>::deletionCheck() const
{
    // If there are objects still in use
    if(!mUsed.empty())
    {
        // Throwing exception
        object_in_use exc;
        throw exc;
    }
}

// Object managing functions
template <class T, class Alloc> T* OPool<T,Alloc>::allocateObject()
{
    T* element = std::allocator_traits<Alloc>::allocate(mAllocator,1,0);        // Allocate object
    std::allocator_traits<Alloc>::construct(mAllocator,element,mPrototype);     // Construct object

    mFree.push_front(element);
    mSize++;
    return element;
}

template <class T, class Alloc> void OPool<T,Alloc>::deallocateObject(T* ptr)
{
    if(ptr == nullptr)
    {
        return;
    }
    else
    {
        std::allocator_traits<Alloc>::destroy(mAllocator,ptr);        // Destroy object
        std::allocator_traits<Alloc>::deallocate(mAllocator,ptr,1);   // Deallocate memory
        mSize--;
    }
}

template <class T, class Alloc> T* OPool<T,Alloc>::getObject()
{
    // If there are free objects
    if(!mFree.empty())
    {
        mUsed.push_front(mFree.front());
        mFree.pop_front();
        return mUsed.front();
    }
    else
    {
        // If the pool can expand and hasn't reached its maximum size
        if(mExpandable && mSize < mMaxSize)
        {
            mUsed.push_front(allocateObject());
            mFree.pop_front();
            return mUsed.front();
        }
    }
    return nullptr;
}

template <class T, class Alloc> bool OPool<T,Alloc>::freeObject(T *ptr)
{
    // Searching the object in the list of used objects
    for(typename std::list<T*>::iterator it = mUsed.begin(); it != mUsed.end(); it++)
    {
        if(*it == ptr)
        {
            mUsed.remove(*it);
            if(mSize > mMaxSize)
            {
                deallocateObject(ptr);
            }
            else
            {
                mFree.push_front(ptr);
            }
            break;
        }
    }
    return true;
}


#endif // OPOOL_H
