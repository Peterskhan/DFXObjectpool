/****************************************************************************
** Filename: poolable.h
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

#ifndef POOLABLE_H
#define POOLABLE_H


// Smart poolable object class
class Poolable
{
public:
    Poolable();
    virtual         ~Poolable();
    bool            isActive();
    void            setActive(const bool isActive);
    virtual void    onGiven();
    virtual void    onReleased();
protected:
    bool            mActive;
};

Poolable::Poolable()                            { mActive = false; }
Poolable::~Poolable()                           {}
bool Poolable::isActive()                       { return mActive; }
void Poolable::setActive(const bool isActive)   { mActive = isActive; }
void Poolable::onGiven()                        {}
void Poolable::onReleased()                     {}


#endif // POOLABLE_H
