#ifndef RUN_BUFFEREDREADER_H_INCLUDED
#define RUN_BUFFEREDREADER_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include <String.h>

#define NAME    ((pBufferedReader*)bf.private)->name
#define BUFFER  ((pBufferedReader*)bf.private)->buffer
#define SIZE1   ((pBufferedReader*)bf.private)->size
#define PTR     ((pBufferedReader*)bf.private)->pointer
#define FP      ((pBufferedReader*)bf.private)->fp
#define INDEX   ((pBufferedReader*)bf.private)->index
#define ALL     ((pBufferedReader*)bf.private)->all
#define LINE2     ((pBufferedReader*)bf.private)->line

Class(BufferedReader) {
    void *private;
    int (*size)();
    string (*readLine)();
    string (*read)(int);
    char (*next)();
    void (*position)(int);
    string (*name)();
    void (*close)();
    string (*buffer)();
};

Class(pBufferedReader) {
    FILE *fp;
    string *name;
    int size;
    string buffer;
    string line;
    int pointer;
    int index;
    bool all;
};

#define BufferedReader(file) ({\
    BufferedReader bf;\
    bf.private = null;\
    try {\
        bf.private = (pBufferedReader*)malloc(sizeof(pBufferedReader));\
        if(bf.private==null)\
            throw(OUT_OF_MEMORY);\
        BUFFER=null;\
        SIZE1=0;\
        ALL=false;\
        FP = fopen(file,"rt");\
        if(FP==null)\
            throw(NO_FILE);\
        NAME = (string)malloc(strlen(file)+1);\
        strcpy(NAME,file);\
        fseek(FP,0,2);\
        SIZE1=ftell(FP);\
        fseek(FP,0,0);\
        if(SIZE1<=4096) {\
            BUFFER = (string) calloc(sizeof(char),SIZE1);\
            if(BUFFER==null)\
                throw(OUT_OF_MEMORY);\
            fread((string)BUFFER,sizeof(char),SIZE1,FP);\
            ALL = true;\
            INDEX = SIZE1;\
        } else {\
            BUFFER = (string) calloc(sizeof(char),4096);\
            if(BUFFER==null)\
                throw(OUT_OF_MEMORY);\
            fread((string)BUFFER,sizeof(char),4096,FP);\
            INDEX = 4096;\
            ALL=false;\
        }\
        PTR = 0;\
    } catch(EXCEPTION) {\
        return null;\
    }\
    string buff_name() {\
        return NAME;\
    } bf.name = buff_name;\
    string buff_buff() {\
        return BUFFER;\
    } bf.buffer = buff_buff;\
    char* buff_line(){\
        try {\
            if(bf.private==NULL)\
                throw(NULL_POINTER);\
            if(BUFFER==NULL)\
                throw(NULL_POINTER);\
            if(PTR+1>SIZE1)\
                return null;\
            int start = PTR;\
            while(BUFFER[PTR]!='\n' && BUFFER[PTR]!='\r' && BUFFER[PTR]!='\0')\
                PTR++;\
            int end = PTR;\
            int len = end - start;\
            if(LINE2!=null)\
                free(LINE2);\
            LINE2 = (char*)calloc(sizeof(char),len);\
            strncpy(LINE2, BUFFER + start, len);\
            PTR++;\
            return LINE2;\
        } catch(EXCEPTION) {\
            return NULL;\
        }\
    } bf.readLine = buff_line;\
    bf;\
})

#endif // RUN_BUFFEREDREADER_H_INCLUDED
