#ifndef BASE_H
#define BASE_H

#include <inttypes.h>

//////////////////////////////////////////////////
// Clang OS/Arch Cracking

#if defined(__clang__)

# define COMPILER_CLANG 1

# if defined(_WIN32)
#  define OS_WINDOWS 1
# elif defined(__gnu_linux__) || defined(__linux__)
#  define OS_LINUX 1
# elif defined(__APPLE__) && defined(__MACH__)
#  define OS_MAC 1
# else
#  error This compiler/OS combination is not supported.
#endif

# if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#  define ARCH_X64 1
# elif defined(i386) || defined(__i386) || defined(__i386__)
#  define ARCH_X86 1
# elif defined(__aarch64__)
#  define ARCH_ARM64 1
# elif defined(__arm__)
#  define ARCH_ARM32 1
# else
#  error Architecture not supported.
# endif

////////////////////////////////////////////////////////
// MSVC OS/Arch Cracking

#elif defined(_MSC_VER)

# define COMPILER_MSVC 1

# if _MSC_VER >= 1920
#  define COMPILER_MSVC_YEAR 2019
# elif _MSC_VER >= 1910
#  define COMPILER_MSVC_YEAR 2017
# elif _MSC_VER >= 1900
#  define COMPILER_MSVC_YEAR 2015
# elif _MSC_VER >= 1800
#  define COMPILER_MSVC_YEAR 2013
# elif _MSC_VER >= 1700
#  define COMPILER_MSVC_YEAR 2012
# elif _MSC_VER >= 1600
#  define COMPILER_MSVC_YEAR 2010
# elif _MSC_VER >= 1500
#  define COMPILER_MSVC_YEAR 2008
# elif _MSC_VER >= 1400
#  define COMPILER_MSVC_YEAR 2005
# else
#  define COMPILER_MSVC_YEAR 0
# endif

# if defined(_WIN32)
#  define OS_WINDOWS 1
# else
#  error This compiler/OS combination is not supported.

# if defined(_M_AMD64)
#  define ARCH_X64 1
# elif defined(_M_IX86)
#  define ARCH_X86 1
# elif defined(_M_ARM64)
#  define ARCH_ARM64 1
# elif defined(_M_ARM)
#  define ARCH_ARM32 1
# else
#  error Architecture not supported.
# endif

/////////////////////////////////////////////////////////
// GCC OS/Arch Cracking

#elif defined(__GNUC__) || defined(__GNUG__)

# define COMPILER_GCC 1

# if defined(__gnu_linux__) || defined(__linux__)
#  define OS_LINUX 1
# else
#  error This compiler/OS combo is not supported.
# endif

# if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
#  define ARCH_X64 1
# elif defined(i386) || defined(__i386) || defined(__i386__)
#  define ARCH_X86 1
# elif defined(__aarch64__)
#  define ARCH_ARM64 1
# elif defined(__arm__)
#  define ARCH_ARM32 1
# else
#  error Architecture not supported.
# endif

#else
# error Compiler not supported.
#endif

///////////////////////////////////////////////////////
// Arch Cracking

#if defined(ARCH_X64)
# define ARCH_64BIT 1
#elif defined(ARCH_X86)
# define ARCH_32BIT 1
#endif

#if ARCH_ARM32 || ARCH_ARM64 || ARCH_X64 || ARCH_X86
# define ARCH_LITTLE_ENDIAN 1
#else
# error Endianness of this architecture not understood by context cracker.
#endif

////////////////////////////////////////////////////
// Language Cracking

#if defined(__cplusplus)
# define LANG_CPP 1
#else
# define LANG_C 1
#endif

///////////////////////////////////////////////////
// Zero All Undefined Options

#if !defined(ARCH_32BIT)
# define ARCH_32BIT 0
#endif
#if !defined(ARCH_64BIT)
# define ARCH_64BIT 0
#endif
#if !defined(ARCH_X64)
# define ARCH_X64 0
#endif
#if !defined(ARCH_X86)
# define ARCH_X86 0
#endif
#if !defined(ARCH_ARM64)
# define ARCH_ARM64 0
#endif
#if !defined(ARCH_ARM32)
# define ARCH_ARM32 0
#endif
#if !defined(COMPILER_MSVC)
# define COMPILER_MSVC 0
#endif
#if !defined(COMPILER_GCC)
# define COMPILER_GCC 0
#endif
#if !defined(COMPILER_CLANG)
# define COMPILER_CLANG 0
#endif
#if !defined(OS_WINDOWS)
# define OS_WINDOWS 0
#endif
#if !defined(OS_LINUX)
# define OS_LINUX 0
#endif
#if !defined(OS_MAC)
# define OS_MAC 0
#endif
#if !defined(LANG_CPP)
# define LANG_CPP 0
#endif
#if !defined(LANG_C)
# define LANG_C 0
#endif

///////////////////////////////////////////////////
// Codebase Keywords

#define internal static
#define global   static
#define persist  static

////////////////////////////////////////////////////
// Base Types

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t  S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

typedef float  F32;
typedef double F64;

typedef struct U128 U128;
struct U128
{
    U64 u64[2];
};

typedef void VoidProc(void);

///////////////////////////////////////////////////
// Units

#define KB(n) (((U64)(n)) << 10)
#define MB(n) (((U64)(n)) << 20)
#define GB(n) (((U64)(n)) << 30)
#define TB(n) (((U64)(n)) << 40)

///////////////////////////////////////////////////
// Mins, Maxes

#define Min(A,B) (((A)<(B))?(A):(B))
#define Max(A,B) (((A)>(B))?(A):(B))

////////////////////////////////////////////////////
// Compiler -> Alignment

#if COMPILER_MSVC
# define AlignOf(T) __alignof(T)
#elif COMPILER_CLANG
# define AlignOf(T) __alignof(T)
#elif COMPILER_GCC
# define AlignOf(T) __alignof__(T)
#else
# error AlignOf not defined for this compiler.
#endif

///////////////////////////////////////////////////
// Asserts

#if COMPILER_MSVC
# define Trap() __debugbreak()
#elif COMPILER_CLANG || COMPILER_GCC
# define Trap() __builtin_trap()
#else
# error Unknown trap intrinsic for this compiler.
#endif

#define AssertAlways(x) do{if(!(x)) {Trap();}}while(0);

/////////////////////////////////////////////////////
// String Types

typedef struct String8 String8;
struct String8
{
    U8 *str;
    U64 size;
};

typedef struct String16 String16;
struct String16
{
    U16 *str;
    U64 size;
};

typedef struct String32 String32;
struct String32
{
    U32 *str;
    U64 size;
};

typedef struct String8Array String8Array;
struct String8Array
{
    String8 *v;
    U64 count;
};

internal String8
str8(U8 *str, U64 size)
{
    String8 result = {str, size};
    return(result);
}

internal String8
str8_zero(void)
{
    String8 result = {0};
    return(result);
}

internal String16
str16(U16 *str, U64 size)
{
    String16 result = {str, size};
    return(result);
}

internal String16
str16_zero(void)
{
    String16 result = {0};
    return(result);
}

internal String32
str32(U32 *str, U64 size)
{
    String32 result = {str, size};
    return(result);
}

internal String32
str32_zero(void)
{
    String32 result = {0};
    return(result);
}

internal U64
cstring8_length(U8 *c)
{
    U8 *p = c;
    for (;*p != 0; p += 1);
    return(p - c);
}

internal U64
cstring16_length(U16 *c)
{
    U16 *p = c;
    for (;*p != 0; p += 1);
    return(p - c);
}

internal U64
cstring32_length(U32 *c)
{
    U32 *p = c;
    for (;*p != 0; p += 1);
    return(p - c);
}

//////////////////////////////////////////////////////////
// Character Classification

internal S32
char_is_space(U8 c)
{
    return(c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f' || c == '\v');
}

internal S32
char_is_upper(U8 c)
{
    return('A' <= c && c <= 'Z');
}

internal S32
char_is_lower(U8 c)
{
    return('a' <= c && c <= 'z');
}

internal S32
char_is_alpha(U8 c)
{
    return(char_is_upper(c) || char_is_lower(c));
}

internal S32
char_is_slash(U8 c)
{
    return(c == '/' || c == '\\');
}

#endif // BASE_H