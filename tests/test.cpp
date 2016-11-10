/****************************************************************************
** Filename: test.cpp
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

#include <iostream>
#include <time.h>
#include <string>
#include "includes/sopool.h"

class Person
{
public:
    std::string             name;
    unsigned                age;
    unsigned                year;
    unsigned                month;
    unsigned                day;
    std::string             mothersName;
    std::string             city;
    std::string             street;
    unsigned                houseNumber;
    std::list<Person*>      friends;
public:
    Person() {}
    ~Person() {}
};

class Counter
{
public:
    unsigned value;
public:
    Counter() {
        for(int i = 0; i < 1000; i++)
        {
            value++;
        }
    }
    ~Counter() {}
};


int test()
{
    clock_t start;
    clock_t end;

    OPool<int> int_pool(25,false);
    OPool<std::string> string_pool(25,false);
    OPool<Person> person_pool(25,false);
    OPool<Counter> counter_pool(25,false);

    /* Testing OPool with integers
     * Integers are created and immediately destroyed at a rapid rate
     */
    std::cout << "Creation and immediate destruction of ints:" << std::endl;
    start = clock();
    for(int i = 0; i < 100000; i++) {
        int *p = new int;
        delete p;
    }
    end = clock();
    std::cout << "With new and delete: " << end-start << " ticks." << std::endl;

    start = clock();
    for(int i = 0; i < 100000; i++) {
        int *p = int_pool.getObject();
        int_pool.freeObject(p);
    }
    end = clock();
    std::cout << "With OPool: " << end-start << " ticks." << std::endl;
    std::cout << std::endl << std::endl;



    /* Testing OPool with std::strings
     * Strings are created and immediately destroyed at a rapid rate
     */
    std::cout << "Creation and immediate destruction of std::strings:" << std::endl;
    start = clock();
    for(int i = 0; i < 100000; i++) {
        std::string *p = new std::string;
        delete p;
    }
    end = clock();
    std::cout << "With new and delete: " << end-start << " ticks." << std::endl;

    start = clock();
    for(int i = 0; i < 100000; i++) {
        std::string *p = string_pool.getObject();
        string_pool.freeObject(p);
    }
    end = clock();
    std::cout << "With OPool: " << end-start << " ticks." << std::endl;
    std::cout << std::endl << std::endl;



    /* Testing OPool with Persons
     * Persons are created and immediately destroyed at a rapid rate
     */
    std::cout << "Creation and immediate destruction of Persons:" << std::endl;
    start = clock();
    for(int i = 0; i < 100000; i++) {
        Person *p = new Person;
        delete p;
    }
    end = clock();
    std::cout << "With new and delete: " << end-start << " ticks." << std::endl;

    start = clock();
    for(int i = 0; i < 100000; i++) {
        Person *p = person_pool.getObject();
        person_pool.freeObject(p);
    }
    end = clock();
    std::cout << "With OPool: " << end-start << " ticks." << std::endl;
    std::cout << std::endl << std::endl;



    /* Testing OPool with Counters
     * Counters are created and immediately destroyed at a rapid rate
     */
    std::cout << "Creation and immediate destruction of Counters:" << std::endl;
    start = clock();
    for(int i = 0; i < 100000; i++) {
        Counter *p = new Counter;
        delete p;
    }
    end = clock();
    std::cout << "With new and delete: " << end-start << " ticks." << std::endl;

    start = clock();
    for(int i = 0; i < 100000; i++) {
        Counter *p = counter_pool.getObject();
        counter_pool.freeObject(p);
    }
    end = clock();
    std::cout << "With OPool: " << end-start << " ticks." << std::endl;
    std::cout << std::endl << std::endl;


    return 0;
}
