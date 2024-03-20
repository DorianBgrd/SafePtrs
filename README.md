# SafePtrs
This header only library provides a simple way to create weak ptrs
over raw pointers. 
The class must inherit from the base class using the USING_SAFE_PTR macro.

Exemple :

``
class BaseClass: USING_SAFE_PTR(BaseClass) { }
``

Safe pointers can then be created using the `makeSafePtr` function.

``
BaseClass* ptr = new BaseClass();
SafePtr<BaseClass> sptr = makeSafePtr<BaseClass>(ptr);
``

The safe pointer can be checked at any time using the `valid()` member. 
It will return whether wrapped pointer is still alive.
