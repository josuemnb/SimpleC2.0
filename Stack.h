#ifndef RUN_STACK_H_INCLUDED
#define RUN_STACK_H_INCLUDED

#include <stdio.h>

#define Stack(...) VARARG(STACK_, __VA_ARGS__)

#define STACK_1(type) \
    struct UID(pStack) {\
        int length;\
        int capacity;\
        type* value;\
        type kind;\
    };\
	struct UID(stack){\
        void *private;\
		int (*size)();\
		void (*push)(type);\
		type (*pop)(void);\
		type (*peek)(void);\
		type (*get)(int);\
		void (*clear)();\
    }

#define STACK_0() ({\
    struct UID(stack) s;\
    s.private=NULL;\
    try {\
        s.private = malloc(sizeof(struct UID(pStack)));\
        if(s.private==NULL) \
            throw(NULL_POINTER);\
        ((struct UID(pStack)*)s.private)->length = 0;\
        ((struct UID(pStack)*)s.private)->capacity = 10;\
        ((struct UID(pStack)*)s.private)->value = malloc(10 * sizeof(void*));\
        if(((struct UID(pStack)*)s.private)->value==NULL) \
            throw(OUT_OF_MEMORY);\
    } catch(EXCEPTION) {\
        return;\
    }\
    int stack_size() {\
        try {\
            if(s.private==NULL)\
               throw(NULL_POINTER);\
            return ((struct UID(pStack)*)s.private)->length;\
        } catch(EXCEPTION){\
        	exit(-1);\
        }\
    } s.size = stack_size;\
    void stack_push(typeof(((struct UID(pStack)*)s.private)->kind) value) {\
        try {\
            if(s.private==NULL)\
               throw(NULL_POINTER);\
            if(((struct UID(pStack)*)s.private)->length+1>((struct UID(pStack)*)s.private)->capacity) {\
                ((struct UID(pStack)*)s.private)->capacity *= 1.5;\
                ((struct UID(pStack)*)s.private)->value = realloc(((struct UID(pStack)*)s.private)->value,((struct UID(pStack)*)s.private)->capacity);\
                if(((struct UID(pStack)*)s.private)->value==NULL)\
                    throw(OUT_OF_MEMORY);\
            }\
            ((struct UID(pStack)*)s.private)->value[((struct UID(pStack)*)s.private)->length] = value;\
            ((struct UID(pStack)*)s.private)->length++;\
        } catch(EXCEPTION){\
        	exit(-1);\
        }\
    } s.push = stack_push;\
    typeof(((struct UID(pStack)*)s.private)->kind) stack_pop() {\
        try {\
            if(s.private==NULL)\
                throw(NULL_POINTER);\
            if(((struct UID(pStack)*)s.private)->length==0)\
                throw(OUT_OF_INDEX);\
            if(((struct UID(pStack)*)s.private)->capacity-10>((struct UID(pStack)*)s.private)->length) {\
                ((struct UID(pStack)*)s.private)->capacity -=10;\
                ((struct UID(pStack)*)s.private)->value = realloc(((struct UID(pStack)*)s.private)->value,((struct UID(pStack)*)s.private)->capacity);\
                if(((struct UID(pStack)*)s.private)->value==NULL) \
                    throw(OUT_OF_MEMORY);\
            }\
            ((struct UID(pStack)*)s.private)->length--;\
            return (typeof(((struct UID(pStack)*)s.private)->kind))((struct UID(pStack)*)s.private)->value[((struct UID(pStack)*)s.private)->length];\
        } catch(EXCEPTION) {\
        	exit(-1);\
        }\
    } s.pop = stack_pop;\
    typeof(((struct UID(pStack)*)s.private)->kind) stack_get(int index) {\
        try {\
            if(s.private==NULL)\
                throw(NULL_POINTER);\
            if(((struct UID(pStack)*)s.private)->length<index)\
                throw(NULL_POINTER);\
            return (typeof(((struct UID(pStack)*)s.private)->kind))((struct UID(pStack)*)s.private)->value[index];\
        } catch(EXCEPTION) {\
        	exit(-1);\
        }\
    } s.get = stack_get;\
    typeof(((struct UID(pStack)*)s.private)->kind) stack_peek() {\
        try {\
            if(s.private==NULL)\
                throw(NULL_POINTER);\
            return (typeof(((struct UID(pStack)*)s.private)->kind))((struct UID(pStack)*)s.private)->value[((struct UID(pStack)*)s.private)->length-1];\
        } catch(EXCEPTION) {\
        	exit(-1);\
        }\
    } s.peek = stack_peek;\
    void stack_clear() {\
        try {\
            ((struct UID(pStack)*)s.private)->length = 0;\
            ((struct UID(pStack)*)s.private)->capacity = 10;\
            free(((struct UID(pStack)*)s.private)->value);\
            ((struct UID(pStack)*)s.private)->value = calloc(10,sizeof(void*));\
            if(((struct UID(pStack)*)s.private)->value==NULL) \
                throw(OUT_OF_MEMORY);\
        } catch(EXCEPTION) {\
        	exit(-1);\
        }\
    } s.clear = stack_clear;\
    s;\
})



#endif // STACK_H_INCLUDED
