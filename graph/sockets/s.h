#ifndef S_H_
#define S_H_
#include <ctype.h>

typedef struct {
    uint64_t len;
    char *data;
} String;
 
static inline
String chop_line(String *input) {
    uint64_t i = 0;
    while (i < input->len &&  input->data[i] != '\n'){
        ++i;
    }
    String line;
    line.data = input->data;
    line.len = i;

    if (i == input->len) {
        input->data += input->len;
        input->len = 0;
    } else {
        input->data += i + 1;
        input->len -= i + 1;
    }

     return *input;
}
String trim_end(String s){
    while (s->len && isspace(s->data[s->len -1])) {
        s->len--;
    }
    return s;
}

#endif // S_H_