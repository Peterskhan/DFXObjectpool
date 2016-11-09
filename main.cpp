#include <iostream>
#include <time.h>
#include "opool.h"
#include "sopool.h"


class Test : public Poolable
{
public:
    Test() {}
    ~Test() {}
    Test(const Test& other) { val = other.val; }
    int val;
    void onGiven() {}
    void onReleased() {}
};

template <class T> class MyAllocator
{
public:
    MyAllocator() {}
    T* allocate(unsigned size)
    {
        std::cout << "alloc" << std::endl;

    }

    void construct(T* ptr,const T& other)
    {
        std::cout << "construct" << std::endl;
    }

    void destroy(T* mem)
    {
        std::cout << "destroy" << std::endl;
    }

    void deallocate(T* ptr, int num)
    {
        std::cout << "dealloc" << std::endl;
    }
};


// The name of the tested datatype
#define type Test

// Number of elements to test with
const unsigned ITEM_COUNT = 100000;

int main(void)
{


    std::allocator<Test> all;

    Test dummy;
    dummy.val = 8;

    SOPool<Test> pool(1,false,dummy);
    Test *tst = pool.getObject();
    std::cout << tst->val << std::endl;
    pool.freeObject(tst);


    return 0;
}

