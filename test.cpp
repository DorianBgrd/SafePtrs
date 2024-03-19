# include "safeptr.h"
# include <iostream>
# include <memory>


class TestClass: USING_SAFE_PTR(TestClass)
{
public:
    TestClass() = default;
};


int main(int argc, char** argv)
{
    TestClass* v = new TestClass();

    SafePtr<TestClass> ptr = makeSafePtr(v);

    std::cout << "Before deletion : " << ptr.ptr() << std::endl;

    delete v;

    std::cout << "After deletion : " << ptr.ptr() << std::endl;

    TestClass* v1 = new TestClass();
    TestClass* v2 = new TestClass();

    SafePtr<TestClass> ptr1 = makeSafePtr(v1);

    ptr1.swap(v2);
    return 0;
}

