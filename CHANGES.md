Big rebuild finally ended!
So, how it works now?

The biggest chages are that:
-Project was split into separate files and functions.
-Replacing "global_size" idea by two pointers

Let's take a look who is who!

----------------------------------------------------------------------------------------------------------------------------

main:
---
|Just connecting everything and initialize size,threads and mutex.|

DoubleLinkedList:
---  
|Contains the functions to create Double Linked List.|
Every list node has value and pointers to next and previous Nodes. The whole system is bounded by start and end nodes,  which always has special values: start = 0 and end = INT_MAX. This idea is also protect project from mistakeble counting boundary nodes. If first thread try "eat" end node, it will not find any "0" bits in end node value. And the same situation for second thread, but opposite.

eater:
---
|Contains realization of thread function and everything it needs.|
So, firstly every thread initialize some variables for the work. Then it identifies which of threads it is? The first or the Second one? The result of identification goes to variable mode and rule all thread life. After identification thread tries to make first safe step and if everything OK, start cycle with steps and countings.

Every trying to step thread checks the space to go and if it exists, the current pointer go to next element and memory of, now, previous become freed. If there is no space to move, the only one thing thread needs to do, is freeing up memory of current element and nullify pointer to this memory in next element (of course if it's exists). All operations in trying move are protected by mutex.

Actually, how works checking space: The thread checks that the pointer to next element not NULL and then checks by the same way element next to next. Why: When 2 threads still alive and standing nearby, first of them who will try to move need to understand that it impossible. And the way to understand it - look at the element after next: it will not exist if in front of you stands the another one thread. So now first one thread stop work and the second only need to look the next element to stop.

debug:
---
|Some tools for development|<br>
There're some check functions and "#ifdef DEBUG " tools like printing some information or for example replacing random filling of nodes, by range from 1 to size - to check is everything good.


