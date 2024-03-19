#ifndef SAFEPTRS_LIBRARY_H
#define SAFEPTRS_LIBRARY_H

#include <vector>


template<typename T> class SafePtr;


template<typename T>
class _SafePtrBase
{
    friend SafePtr<T>;
protected:
    std::vector<SafePtr<T>*> ptrs;
public:

    virtual ~_SafePtrBase()
    {
        for (int i = 0; i < ptrs.size(); i++) {
            SafePtr<T>* v = ptrs[i];
            v->_clear();
        }
    }

    std::vector<SafePtr<T>*> _ptrs() const
    {
        return ptrs;
    }

protected:
    void registerPtr(SafePtr<T>* ptr)
    {
        ptrs.push_back(ptr);
    }

    void deregisterPtr(SafePtr<T>* ptr)
    {
        if (ptrs.empty())
            return;

        auto idx = std::find(ptrs.begin(), ptrs.end(), ptr);
        if (idx == ptrs.end())
            return;

        ptrs.erase(idx);
    }
};


template <typename T>
class SafePtr
{
    friend _SafePtrBase<T>;
private:
    T* _ptr;

public:
    SafePtr()
    {
        _ptr = nullptr;
    }

    SafePtr(T* ptr)
    {
        _ptr = ptr;
        _register();
    }

    SafePtr(const SafePtr<T> &other)
    {
        _ptr = other.ptr();
        _register();
    }

    ~SafePtr()
    {
        _deregister();
    }

    T* ptr() const
    {
        return _ptr;
    }

    T* operator->() const
    {
        return _ptr;
    }

    void operator=(const SafePtr<T>& other)
    {
        if (_ptr)
            _deregister();

        _ptr = other.ptr();
        _register();
    }

    void swap(T* other)
    {
        if (_ptr)
            _deregister();

        _ptr = other;
        _register();
    }

    void reset()
    {
        _ptr = nullptr;
        _deregister();
    }

    operator bool() const
    {
        return valid();
    }

    bool valid() const
    {
        return (_ptr != nullptr);
    }

protected:
    void _register()
    {
        if (!_ptr)
            return;
        _ptr->registerPtr(this);
    }

    void _deregister()
    {
        if (!_ptr)
            return;
        _ptr->deregisterPtr(this);
    }

    void _clear()
    {
        _ptr = nullptr;
    }
};


class SafePtrException : public std::exception
{
public:
    char const* what() const override
    {
        return "Safe ptr exception";
    }
};


template <typename T>
SafePtr<T> makeSafePtr(T* value)
{
    if (!dynamic_cast<_SafePtrBase<T>*>(value))
    {
        throw SafePtrException();
    }

    return SafePtr<T>(value);
}


#define USING_SAFE_PTR(classname) public _SafePtrBase<classname>

#endif //SAFEPTRS_LIBRARY_H
