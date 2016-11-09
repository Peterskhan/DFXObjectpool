/****************************************************************************
** Filename: opoolexceptions.h
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

#ifndef OPOOLEXCEPTIONS_H
#define OPOOLEXCEPTIONS_H

#include <exception>

// Object pool exceptions
class object_in_use : public std::exception
{
public:
    const char * what () const throw () {
          return "Some dinamically allocated objects are still in use.";
    }
};

#endif // OPOOLEXCEPTIONS_H
