#ifndef STDIO_H
#define STDIO_H

#define FLOAT_SCALE 100

void PRINT(const char *fmt, ...);
void READ(const char *fmt, ...);
int float_div(int a, int b);
int have_decimal(const char *s);
int parse_float(const char *s);
int parse_int(const char *s);


#endif
