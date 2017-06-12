#ifndef RUN_STRING_H_INCLUDED
#define RUN_STRING_H_INCLUDED

//#include "run.h"

#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define VAL     ((pString*)s.private)->value
#define CAP      ((pString*)s.private)->capacity
#define LEN      ((pString*)s.private)->length

Class(String){
	void *private;
	int (*size)();
	string (*to_string)();
	string (*from)(int);
	string (*fromTo)(int,int);
	char (*charAt)(int);
	bool (*equals)(string);
	bool (*contains)(string);
	int (*resize)(int);
	string (*append)(string);
	int (*lastIndexOf)(char);
	int (*lastIndexOfFrom)(char,int);
	int (*indexOf)(char);
	int (*indexOfFrom)(char,int);
	void (*set)(string);
	string (*trim)();
	bool (*empty)();
	void (*clear)();
	char (*first)();
	char (*last)();
	string (*replace)(string,string);
	string (*insert)(string,int);
//	Array (*split)(char);
	string (*toLowerCase)();
	string (*toUpperCase)();
	bool (*starts)(string);
	bool (*ends)(string);
	int (*occurences)(string);
	string (*after)(string);
	string (*before)(string);
	void (*destroy)();
	int (*getType)();
	string (*class)();
};

Class(pString) {
	unsigned int length;
	char* value;
	int capacity;
};

#define String(val) ({\
    String s; \
    s.private = null;\
    try {\
        s.private = (pString*)malloc(sizeof(pString));\
        if(s.private==null)\
            throw(NULL_POINTER);\
        LEN = 0;\
        CAP = 0;\
        VAL = null;\
        if(val!=null) {\
            LEN = strlen(val);\
            if(LEN>0) {\
                CAP = LEN +1;\
                VAL = val;\
            }\
        }\
    } catch (EXCEPTION) {\
        exit(-1);\
    }\
    string to_string() {\
        try {\
            if(s.private==null)\
                throw(NULL_POINTER);\
            return VAL;\
        } catch (EXCEPTION) {\
            return null;\
        }\
    } s.to_string = to_string;\
    string string_from(int start) {\
        try {\
            if(start>=LEN)\
                return "";\
            string ret = (string) malloc(LEN - start + 1);\
            if(ret==null)\
                throw(NULL_POINTER);\
            int j=0,i;\
            for(i=start; i<LEN; i++, j++)\
                ret[j] = VAL[i];\
            ret[j]='\0';\
            return ret;\
        } catch(EXCEPTION) {\
            return null;\
        }\
    } s.from = string_from;\
    string string_fromTo(int start, int end) {\
        try {\
            if(s.private==null)\
                throw(NULL_POINTER);\
            if(start>=LEN)\
                return "";\
            if(end>=LEN)\
                end=LEN;\
            string ret = malloc(end - start + 1);\
            if(ret==null)\
                throw(EXCEPTION);\
            int j=0,i;\
            for(i=start; i<end; i++, j++)\
                ret[j] = VAL[i];\
            ret[j]='\0';\
            return ret;\
        } catch(EXCEPTION) {\
            return null;\
        }\
    } s.fromTo = string_fromTo;\
    char string_charAt(int index) {\
        if(index>=LEN)\
            return -1;\
        return VAL[index];\
    } s.charAt = string_charAt;\
    bool string_equals(string str) {\
        return strcmp(VAL,str)?false:true;\
    } s.equals = string_equals;\
    \
    int string_resize(int size) {\
        if(LEN>=size) return -1;\
        CAP = size;\
        VAL = realloc(VAL,size);\
        if(VAL==null)\
            throw(EXCEPTION);\
        return size;\
    } s.resize = string_resize;\
    \
    bool string_contains(string str) {\
        return strstr(VAL,str)?true:false;\
    } s.contains = string_contains;\
    string string_append(string str) {\
        if(str==null)\
            return VAL;\
        int len = strlen(str);\
        if(LEN + len + 1>=CAP) {\
            CAP += len + 16;\
            VAL = realloc(VAL,CAP);\
        }\
        strcat(VAL,str);\
        return VAL;\
    } s.append = string_append;\
    int string_size() {\
        return LEN;\
    } s.size = string_size;\
    int string_indexOf(char ch) {\
        int i;\
        for(i=0;i<LEN;i++) {\
            if(VAL[i]==ch)\
                return i;\
        }\
        return -1;\
    } s.indexOf = string_indexOf;\
    int string_lastIndexOf(char ch) {\
        int i;\
        for(i=LEN;i>=0;i--) {\
            if(VAL[i]==ch)\
                return i;\
        }\
        return -1;\
    } s.lastIndexOf = string_lastIndexOf;\
    int string_indexOfFrom(char ch,int pos) {\
        int i;\
        for(i=pos;i<LEN;i++) {\
            if(VAL[i]==ch)\
                return i;\
        }\
        return -1;\
    } s.indexOfFrom = string_indexOfFrom;\
    int string_lastIndexOfFrom(char ch, int pos) {\
        int i;\
        for(i=LEN-pos;i>=0;i--) {\
            if(VAL[i]==ch)\
                return i;\
        }\
        return -1;\
    } s.lastIndexOfFrom = string_lastIndexOfFrom;\
    void string_set(string str) {\
        int len = strlen(str)+1;\
        char *temp;\
        if(CAP<len) {\
            temp = malloc(len);\
            if(!temp) {\
                puts("Erro no set da String");\
                return;\
            }\
            strcpy(temp,str);\
            free(VAL);\
            VAL = temp;\
        } else \
            strcpy(VAL, str);\
        LEN= len;\
        CAP = len;\
    } s.set = string_set;\
    string string_trim() {\
        int start, end;\
        end = LEN;\
        for(start=0;start<end && isspace(VAL[start]);start++);\
        end-=2;\
        for(;end>=0 && isspace(VAL[end]);end--);\
        string ret = calloc(1,end-start);\
        if(!ret) {\
            puts("Erro ao criar string temporaria");\
            return VAL;\
        }\
        strncpy(ret,VAL + start,end-start);\
        return ret;\
    } s.trim = string_trim;\
    bool string_empty() {\
        return LEN>0;\
    } s.empty = string_empty;\
    void string_clear() {\
        free(VAL);\
        LEN = 0;\
        VAL = realloc(NULL,32);\
        CAP = 32;\
    } s.clear = string_clear;\
    char string_first() {\
        if(VAL==null)\
            return 0;\
        return VAL[0];\
    } s.first = string_first;\
    char string_last() {\
        if(VAL==null)\
            return 0;\
        return VAL[LEN-1];\
    } s.last = string_last;\
    string string_replace(string oldStr,string newStr) {\
        if(!oldStr)\
            return VAL;\
        int oldLen=strlen(oldStr);\
        int newLen=0;\
        if(newStr)\
            newLen = strlen(newStr);\
        if(oldLen==0)\
            return VAL;\
        if(LEN<=oldLen)\
            return null;\
        char *ret=null;\
        char *tmp = VAL;\
        int count=0, total;\
        while(*tmp!='\0' && (tmp = strstr(tmp, oldStr))) {\
           count++;\
           tmp+=oldLen;\
        }\
        if(count>0) {\
            if(newLen>oldLen) \
                total = LEN + count * (newLen - oldLen);\
            else if(oldLen>newLen) \
                total = LEN - count * (oldLen - newLen) + 1;\
            else\
                total = LEN + 1;\
            ret = malloc(total);\
            if(!ret) {\
                puts("Erro no append");\
                return VAL;\
            }\
            tmp = VAL;\
            count = 0;\
            while (*tmp) {\
                if (strstr(tmp, oldStr) == tmp) {\
                    strcpy(&ret[count], newStr);\
                    count += newLen;\
                    tmp += oldLen;\
                } else\
                    ret[count++] = *tmp++;\
            }\
            ret[count] = '\0';\
        }\
        return ret;\
    } s.replace = string_replace;\
    string string_insert(string str,int pos) {\
        if(!str) return null;\
        int len = strlen(str);\
        char *ret = malloc(LEN + len);\
        if(!ret) {\
            puts("Erro no append");\
            return null;\
        }\
        strncpy(ret,VAL,pos);\
        strncpy(ret+pos,str,len);\
        strncpy(ret+pos+len,VAL + pos,VAL -pos);\
        return ret;\
    } s.insert = string_insert;\
    string string_toLowerCase() {\
        int i;\
        char *temp = malloc(LEN + 1);\
        for(i=0;i<=LEN;i++)\
            temp[i]=tolower(VAL[i]);\
        temp[i]='\0';\
        return temp;\
    } s.toLowerCase = string_toLowerCase;\
    string string_toUpperCase() {\
        int i;\
        char *temp = malloc(LEN + 1);\
        for(i=0;i<=LEN;i++)\
            temp[i]=toupper(VAL[i]);\
        temp[i]='\0';\
        return temp;\
    } s.toUpperCase = string_toUpperCase;\
    void string_destroy() {\
        free(s.private);\
    } s.destroy = string_destroy;\
    bool string_starts(string start) {\
        if(start==null)\
            return 0;\
        int len = strlen(start);\
        if(LEN<len)\
            return 0;\
        int i;\
        for(i=0;i<strlen(start);i++) {\
            if(VAL[i]!=start[i])\
                return 0;\
        }\
        return 1;\
    } s.starts = string_starts;\
    bool string_ends(string end) {\
        if(end==null)\
            return 0;\
        int len = strlen(end);\
        if(LEN<len)\
            return 0;\
        int j=0,i;\
        for(i=LEN-len - 1;i<LEN;i++, j++) {\
            if(VAL[i]!=end[j])\
                return 0;\
        }\
        return 1;\
    } s.ends = string_ends;\
    int string_occurences(string str) {\
        int count=0;\
        int oldLen = strlen(str);\
        string tmp = VAL;\
        while(*tmp!='\0' && (tmp = strstr(tmp, str))) {\
           count++;\
           tmp+=oldLen;\
        }\
        return count;\
    } s.occurences = string_occurences;\
    string string_after(string str) {\
        if(str==null)\
            return null;\
        int len = strlen(str);\
        if(len==0) {\
            puts("no string");\
            return null;\
        }\
        string tmp;\
        tmp = strstr(VAL,str);\
        if(tmp==null){\
            puts("not founded");\
            return null;\
        }\
        len += tmp - VAL;\
        string ret = malloc(LEN - len);\
        if(ret==null) {\
            puts("Erro de alocação no after");\
            return null;\
        }\
        int i,j=0;\
        for(i=len;i<LEN;i++, j++) {\
            ret[j] = VAL[i];\
        }\
        ret[i]='\0';\
        return ret;\
    } s.after = string_after;\
    string string_before(string str) {\
        if(str==null)\
            return null;\
        int len = strlen(str);\
        if(len==0) {\
            puts("no string");\
            return null;\
        }\
        string tmp;\
        tmp = strstr(VAL,str);\
        if(tmp==null){\
            puts("not founded");\
            return null;\
        }\
        len = tmp - VAL;\
        string ret = malloc(len);\
        if(ret==null) {\
            puts("Erro de alocação no after");\
            return null;\
        }\
        int i;\
        for(i=0;i<len;i++)\
            ret[i] = VAL[i];\
        ret[i]='\0';\
        return ret;\
    } s.before = string_before;\
    s;\
})


string __value_char__(char);
string __value_double__(double);
string __value_float__(float);
string __value_int__(int);
string __build__(string,...);
bool __compare__(string,string);

struct {
	string (*valueInt)(int);
	string (*valueFloat)(float);
	string (*valueDouble)(double);
	string (*valueChar)(char);
	string (*toHex)(void*);
	bool (*compare)(string,string);
	string (*build)(string,...);
}Strings = {
	.valueInt = __value_int__,
	.valueFloat = __value_float__,
	.valueDouble = __value_double__,
	.valueChar = __value_char__,
	.build = __build__,
	.compare = __compare__
};

string __value_int__(int value) {
	char *str = malloc(24);
	sprintf(str,"%d",value);
	return str;
}

string __value_float__(float value) {
	string str = malloc(30);
	sprintf(str,"%0.4f",value);
	return str;
}

string __value_double__(double value) {
	string str = malloc(36);
	sprintf(str,"%0.8f",value);
	return str;
}

string __value_char__(char value) {
	char *str = malloc(2);
	str[0] = value;
	str[1] = '\0';
	return str;
}

string __build__(string str, ...) {
	int len = strlen(str);
	int size=len;
	string st,cmp=0;
	int capacity = len + 32;
	string s = (string)malloc(capacity);
	strcpy(s,str);
	va_list list;
	va_start(list,str);
	while(1) {
		st = va_arg(list,string);
		if(st==null)
			break;
		else if(cmp>0 && cmp>st)
			break;
		len = strlen(st);
		if(!len)
			break;
        else if(len+1>=capacity) {
			capacity *= 1.5;
            s = realloc(s,capacity);
        }
		cmp = st;
        size +=len;
        strcat(s,st);
	}
	va_end(list);
	s[size]='\0';
	return s;
}

bool __compare__(string s1, string s2) {
	return strcmp(s1,s2)!=0;
}

#endif // RUN_STRING_H_INCLUDED
