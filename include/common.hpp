#ifndef __COMMON_HPP__
#define __COMMON_HPP__
#include <stddef.h>

#define DISABLE_MOVE_CONSTRUCTOR(classname) \
        classname(classname&&) = delete; \
        classname& operator=(classname&&) = delete

#define DISABLE_COPY_CONSTRUCTOR(classname) \
        classname(const classname&) = delete; \
        classname& operator=(const classname&) = delete

// ZDC - ZeroDayCoding namespace
namespace ZDC
{
    typedef char          sint8_t;
    typedef short         sint16_t;
    typedef int           sint32_t;
    typedef long long int sint64_t;
    
    typedef unsigned char          uint8_t;
    typedef unsigned short         uint16_t;
    typedef unsigned int           uint32_t;
    typedef unsigned long long int uint64_t;

    typedef ::size_t size_t;
    typedef void* vptr_t;

} // namespace ZDC
#endif//__COMMON_HPP__