#ifndef CXXLIB_H
#define CXXLIB_H

#include <stdint.h>
#include <utility>

namespace cxx {

struct ControlBlock
{
    ControlBlock()
        : usesCounter(0),
          isLocked(false),
          isAlive(true)
    {

    }

    size_t usesCounter;
    bool isLocked;
    bool isAlive;
};


template<class Type>
class Own
{
public:
    Own() = delete;

    Own(Type *object)
        : object(nullptr),
          block(new ControlBlock)
    {
        std::swap(this->object, object);
    }

    Own(Own &&other)
        : object(nullptr),
          block(nullptr)
    {
        std::swap(block, other.block);
        std::swap(object, other.object);
    }

    ~Own()
    {
        if (!object)
            return;

        while(block->isLocked) {}

        if (block->usesCounter == 0)
            delete block;

        delete object;
    }

    inline Type *operator->() { return object; }
    inline const Type *operator->() const { return object; }

    inline Type &operator*() { return *object; }
    inline const Type &operator*() const { return *object; }

private:
    Type *object;
    ControlBlock *block;
};


template<class Type, class... Args >
Own<Type> Make(Args&&... args)
{
    return Own<Type>(new Type(std::forward<Args>(args)...));
}


} // namespace cxx

#endif // CXXLIB_H
