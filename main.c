#include "run.h"

#include <stdio.h>

Class(Object) {
    string name;
    string parent;
    int type;
};

int main() {
    BufferedReader in = BufferedReader("test.run");
    string line;
    while((line=in.readLine())!=null)
        puts(line);
    Array(Object) a = Array();
    for(int i=0;i<101;i++) {
        Object o;// = (Object*) malloc(sizeof(Object));
        o.type=i;
        o.parent = Strings.valueInt(i*99);
        a.add(o);
    }
    printf("%s\n",a.get(100).parent);
	Array(String*) b = Array();
	String s = String("ola");
    b.add(&s);
    puts(b.get(0)->to_string());
    return 0;

}
