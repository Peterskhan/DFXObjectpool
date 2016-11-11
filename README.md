# DFXObjectpool
  A generic object pool design

### Core concepts
DFXObjectpool is a generic Object Pool that can be used with almost any type of objects.
If you are not familiar with Object Pools, you can learn about them at the following URLs:   

https://en.wikipedia.org/wiki/Object_pool_pattern  
https://sourcemaking.com/design_patterns/object_pool  

Here is a brief explanation I have quoted from Wikipedia:  
 > The object pool pattern is a software creational design pattern that uses a set of initialized objects kept ready 
to use – a "pool" – rather than allocating and destroying them on demand. A client of the pool will request an object 
from the pool and perform operations on the returned object. When the client has finished, it returns the object to 
the pool rather than destroying it; this can be done manually or automatically.
Object pools are primarily used for performance: in some circumstances, object pools significantly improve performance. 
Object pools complicate object lifetime, as objects obtained from and returned to a pool are not actually created or 
destroyed at this time.  


### Functionalities
DFXObjectpool supports many different comfort features, such as:
- Can be used with almost any type of objects
- Size policies, such as initial size, growth permissions, temporary disabling of growth, etc.
- A prototype can be set at creation, so all objects in the pool will be the exact copy of the prototype at creation
- A function to check if there are objects not returned to the pool (useful to check, before the pool gets destroyed)
- The pool uses an allocator to handle memory allocation for it's objects (default is std::allocator, but you can use your own)
- A function to check if the pool currently has a free object to provide

### Structure of DFXObjectpool
DFXObjectpool currently has two object pool types. The basic OPool implements the core functionalities an Object pool 
should implement. The basic Object pool design lacks some of the features you might need, such as initializing (note: not constructing!)
the objects when they are pulled out of the pool, resetting the objects when they are released back to the pool, and checking
if the objects are actually meant to be released when the program attempts to do so. To provide this functionality, you can use
the SOPool class. SOPool is derived from OPool, and provides all of its functionality, adding some extra features listed above.
To use SOPool, you have to derive your objects from the interface class Poolable. Poolable is a basic skeleton with a few members,
and virtual functions SOPool uses to implement it's extra functionality. 
Deriving from Poolable gives you the following possibilities:
- A member variable and functions to keep track of the state of your objects.
- SOPool only accepts the release of an object, if it's state is set to inactive (mActive = false)
- The virtual functions onGiven() and onRelease() you can override, to behave as "constructor" and "destructor"
  (note: these functions are not invoked at actual construction and destruction, but you can use them to initialize
  and reset your objects, for example clearing all the sensitive data you have stored in them)  
  
Later I will provide some short examples for the usage of the pool and it's features.

### Motivation & Mechanism
DFXObjectpool (like any other well designed object pools) can exponentially increase performance, when used correctly.
Object pools can save you a significant amount of CPU time, when your objects are expensive to create, but have a short
lifespan, and a frequent creation and destruction sequence. The pool previously allocates memory for your objects, 
constructs them, and keeps them ready for future usage when you release them back to the pool. This way you can avoid
the potentially expensive operations occuring when constructing the objects, and the huge amount of context-switching
between your program and the operating system. Copy and assignment of the pool object is currently disabled. The objects 
stored in the pool have a lifespan as long as the pool itself usually. OPool and SOPool will free all of its resources 
when they are destroyed, but will not reclaim any resources still pending, used by other parts of the program. 
This can lead to a memory leak, if the pool is intentionally destroyed, or goes out of scope, before all of it's objects 
have been released back. In future versions I may provide options to fix this (such as shared_pointers), 
currently all you can do is to make sure to release all granted objects back to the pool yourself. You can check, 
if there are any pending objects by calling a function, which will throw an exception if such objects exist.

### Memory management
Please note that OPool and SOPool themselves do not implement low level memory management, such as taking care of memory
defragmentation and alignment (as they are not "memory pools"). In contrast, they support the usage of allocators, which
can provide these functionalities. Maybe later I will provide my own implementation of a memory pool and allocators for 
my projects. In this case the object pools will be modified to use these features by default (instead of the std::allocator).
Until that you are free to use your own allocators (as long as they implement the standard C++ allocator interface, described
here:  
http://en.cppreference.com/w/cpp/memory/allocator).

### Future plans
I intend to work on this project further, adding more functionality, stability, support and comfort features. These future 
modifications will be commited when they are trough test-phase. These modifications are experimental, as for the time being
I lack the academical knowledge about the subject, and I can only rely on articles found on the Internet. If those ideas are
proven to be dead-ends or misconceptions I will correct my mistakes accordingly.  
Ideas I currently have in mind for the future:  
- Making sure via smart pointers that no memory can leak, 
  if not all objects are returned to the pool
- Making the pool follow the singleton pattern, to
  store all type-identical objects in the same pool
  for the sake of effectiveness
- Making the pool safe to use across different threads, 
  when the objects are needed concurrently
- Making the pool exception-safe
- Handle non-copyable object types

### License
This project (alongside with all my future work) is released under the terms of the GNU General Public License v3.0. 
You can copy, modify and reuse it at your demand, as long as you release your code under the same license. You can find the
license in the LICENSE.md file, or visit the official page here:  
https://www.gnu.org/licenses/gpl-3.0.en.html

### Personal comments
I will update the code as I work on it, and make modifications. I'm not an experienced programmer, and my work can (and most
likely do) contain errors, mistakes and misconceptions. As I am still learning programming, trying to improve and widen my 
knowledge, any comments, recommendations and advices are welcome, as long as they are constructive and helpful. You can contact
me via e-mail, I will try to answer them as soon as I have the opportunity.  
Thank you for your attention!

### Contact
Peter Gyulai  
peterskhan1997@gmail.com  
Electric Engineer student at  
Budapest University of Technology and Economics  
Hungary  
2016.11.09.  
