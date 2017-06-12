#ifndef RUN_EXCEPTION_H_INCLUDED
#define RUN_EXCEPTION_H_INCLUDED

#include <setjmp.h>
#include <string.h>

#define try  buf_status = setjmp(ex_buf__); if(buf_status==0)
#define catch(excp) else if(buf_status==((Exception)excp).id || ((Exception)excp).id==1000)
#define finally else
#define throw(excp) ({\
		printf("EXCEPTION \'%s\' \n\tAT FILE \'%s\' \n\tIN LINE \'%d\' \n\tCALLED BY \'%s\'\n",((Exception)excp).msg, __FILE__, __LINE__,__FUNCTION__);\
		longjmp(ex_buf__, ((Exception)excp).id);\
})

Class(Exception) {
    int id;
    const char * msg;
};

Exception EXCEPTION = {.msg = "Exception",.id=1000};
Exception NULL_POINTER= {.msg = "Null Pointer",.id=__COUNTER__ + 1};
Exception OUT_OF_MEMORY = {.msg = "Out of Memory",.id=__COUNTER__ + 1};
Exception OUT_OF_INDEX = {.msg = "Out of Index",.id=__COUNTER__ + 1};
Exception MISMATCH = {.msg = "Mismatch",.id=__COUNTER__ + 1};
Exception NO_FILE = {.msg = "No Such File",.id=__COUNTER__ + 1};

int buf_status=-1;
jmp_buf ex_buf__;

#endif // RUN_EXCEPTION_H_INCLUDED
