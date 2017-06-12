#ifndef RUN_H_INCLUDED
#define RUN_H_INCLUDED

#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(X,##__VA_ARGS__, 4, 3, 2, 1, 0)
#define VARARG_IMPL2(base, count, ...) base##count(__VA_ARGS__)
#define VARARG_IMPL(base, count, ...) VARARG_IMPL2(base, count, __VA_ARGS__)
#define VARARG(base, ...) VARARG_IMPL(base, VA_NARGS(__VA_ARGS__), __VA_ARGS__)

#define MERGE_(a,b)  __##a##b
#define LABEL_(a,b) MERGE_(a,b)
#define UID(b) LABEL_(b,__LINE__)

typedef char* string;
typedef unsigned char bool;

#define false 0
#define true !0
#define and &&
#define or ||
#define xor ^
#define not !=
#define null NULL

#define Class(name) typedef struct name name;typedef struct  __attribute__((packed)) name
#define new(Class,...) Class##_new(__VA_ARGS__)

#include "Exception.h"
#include "Array.h"
#include "Stack.h"
#include "String.h"
#include "Tokenizer.h"
#include "Scanner.h"
#include "BufferedReader.h"
//#include "Reader.h"


#endif // RUN_H_INCLUDED
