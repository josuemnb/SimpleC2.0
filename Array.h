#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <malloc.h>

#define Array(...) VARARG(ARRAY_, __VA_ARGS__)

#define ARRAY_1(type) \
    struct UID(pArray) {\
        int length;\
        int capacity;\
        type* value;\
        type kind;\
    };\
	struct UID(array){\
        void *private;\
		int (*size)();\
		void (*add)(type);\
		type (*get)(int);\
		void (*set)(type,int);\
		void (*insert)(type,int);\
    }

#define ARRAY_0() ({\
    struct UID(array) a;\
    try {\
        a.private = (struct UID(pArray)*)malloc(sizeof(struct UID(pArray)));\
        if(a.private==null)\
            throw(OUT_OF_MEMORY);\
        ((struct UID(pArray)*)a.private)->length=0;\
        ((struct UID(pArray)*)a.private)->capacity=10;\
        ((struct UID(pArray)*)a.private)->value=(typeof(((struct UID(pArray)*)a.private)->kind)*) malloc(sizeof(((struct UID(pArray)*)a.private)->kind)*10);\
        if(((struct UID(pArray)*)a.private)->value==null)\
            throw(OUT_OF_MEMORY);\
    } catch(EXCEPTION) {\
        exit(-1);\
    }\
    void array_add(typeof(((struct UID(pArray)*)a.private)->kind) item) {\
        try {\
            if(((struct UID(pArray)*)a.private)->length+1>=((struct UID(pArray)*)a.private)->capacity) {\
                ((struct UID(pArray)*)a.private)->capacity *= 1.5;\
                ((struct UID(pArray)*)a.private)->value = realloc(((struct UID(pArray)*)a.private)->value,sizeof(((struct UID(pArray)*)a.private)->kind)*((struct UID(pArray)*)a.private)->capacity);\
                if(((struct UID(pArray)*)a.private)->value==null)\
                    throw(OUT_OF_MEMORY);\
            }\
            ((struct UID(pArray)*)a.private)->value[((struct UID(pArray)*)a.private)->length] = item;\
            ((struct UID(pArray)*)a.private)->length++;\
        } catch(EXCEPTION) {\
            exit(-1);\
        }\
    } a.add = array_add;\
    int array_size() {\
        try {\
            if(a.private==null)\
                throw(NULL_POINTER);\
            return ((struct UID(pArray)*)a.private)->length;\
        } catch(EXCEPTION) {\
            exit(-1);\
        }\
    } a.size = array_size;\
    typeof(((struct UID(pArray)*)a.private)->kind) array_get(int index) {\
        try {\
            if(a.private==null)\
                throw(NULL_POINTER);\
            if(((struct UID(pArray)*)a.private)->length<=index)\
                throw(OUT_OF_INDEX);\
            return (typeof(((struct UID(pArray)*)a.private)->kind))((struct UID(pArray)*)a.private)->value[index];\
        } catch(EXCEPTION) { \
            exit(-1);\
        }\
    } a.get = array_get;\
    a;\
})


#endif
