#ifndef S_H_
#define S_H_

typedef struct __attribute__((packed)) {
    uint64_t len;
    char *data;
} String;
 
static inline
String chop_line(String input, String *line) {
    uint64_t i = 0;
    while (i < input.len &&  input.data[i] != '\n'){
        ++i;
    }
    line->data = input.data;
    line->len = i;

    if (i == input.len) {
        input.data += input.len;
        input.len = 0;
    } else {
        input.data += i + 1;
        input.len -= i + 1;
    }

     return input;
}

#endif // S_H_