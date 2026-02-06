#include "stdio.h"
#include "../os/os.h"
#include "./string.h"

#include <stdarg.h>   //Este se usa para parametros dinamicos

#define FLOAT_SCALE 100
//Igual que el ejmplo
#define INPUT_BUF_SIZE 32

// Simple function to convert string to integer
int uart_atoi(const char *s) {
    int num = 0;
    int sign = 1;
    int i = 0;

    // Handle optional sign
    if (s[i] == '-') {
        sign = -1;
        i++;
    }

    for (; s[i] >= '0' && s[i] <= '9'; i++) {
        num = num * 10 + (s[i] - '0');
    }

    return sign * num;
}

// Function to convert integer to string
void uart_itoa(int num, char *buffer) {
    int i = 0;
    int is_negative = 0;

    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num > 0 && i < 14) { // Reserve space for sign and null terminator
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }

    if (is_negative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    // Reverse the string
    int start = 0, end = i - 1;
    char temp;
    while (start < end) {
        temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}

//Funcion para convertir integer a string
static void print_int(int value) {
    char buf[16];
    uart_itoa(value, buf);
    uart_puts(buf);
}

//Funcion para imprimir float a string aqui de 2010 - 20.10
static void print_float(int value) {
    int integer = value / FLOAT_SCALE;
    int decimal = value % FLOAT_SCALE;

    if (decimal < 0) decimal = -decimal; //Cabia signo si es negativo

    print_int(integer);
    uart_putc('.');

    // solo dos decimales
    if (decimal < 10) uart_putc('0');
    print_int(decimal);
}

//Apunta al inicio del puntero, le decimos el tipo con el %d %f o %s
void PRINT(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++; //despues de leer el de arriba se mueve al siguiente caracter
            if (*fmt == 'd') { //Un entero
                int val = va_arg(args, int);
                print_int(val); //Imprime el entero
            }
            else if (*fmt == 'f') { //Float
                int val = va_arg(args, int);
                print_float(val); //Imprime el float
            }
            else if (*fmt == 's') { //Texto
                char *s = va_arg(args, char *);
                uart_puts(s); //Imprime le texto
            }
            else { //Una opcion que no existe pero empieza con %
                uart_putc('%');
                uart_putc(*fmt); //Solo imprime el texto que le pasa
            }
        } else {
            uart_putc(*fmt); //Solo imprime
        }
        fmt++;
    }

    va_end(args);
}

void READ(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    if (*fmt == '%' && *(fmt + 1) == 'd') {
        int *out = va_arg(args, int *);
        char buf[INPUT_BUF_SIZE];
        uart_gets_input(buf, INPUT_BUF_SIZE);
        *out = uart_atoi(buf);
    }
    else if (*fmt == '%' && *(fmt + 1) == 's') {
        char *out = va_arg(args, char *);
        uart_gets_input(out, INPUT_BUF_SIZE);
    }

    va_end(args);
}

//ESTO DE AQUI SIRVE PARA LA DIVISIÓN
int int_div(int a, int b) {
    int sign = 1;
    int result = 0;

    if (b == 0)
        return 0;

    if (a < 0) {
        a = -a;
        sign = -sign;
    }

    if (b < 0) {
        b = -b;
        sign = -sign;
    }

    while (a >= b) {
        a -= b;
        result++;
    }

    return sign * result;
}

int float_div(int a, int b) {
    return int_div(a * FLOAT_SCALE, b);
}

int have_decimal(const char *s) {
    while (*s) {
        if (*s == '.') return 1;
        s++;
    }
    return 0;
}

//Lo mismo que teniamos solo que ahora acepta un valor desde afuera
int float_from_string(const char *buf) {
    int integer = 0;
    int decimal = 0;
    int sign = 1;
    int i = 0;

    if (buf[i] == '-') {
        sign = -1;
        i++;
    }

    while (buf[i] >= '0' && buf[i] <= '9') {
        integer = integer * 10 + (buf[i] - '0');
        i++;
    }

    if (buf[i] == '.') {
        i++;
        int factor = FLOAT_SCALE / 10;
        while (buf[i] >= '0' && buf[i] <= '9' && factor > 0) {
            decimal += (buf[i] - '0') * factor;
            factor /= 10;
            i++;
        }
    }

    return sign * (integer * FLOAT_SCALE + decimal);
}

int parse_float(const char *s) {
    return float_from_string(s);
}

int parse_int(const char *s){
    return uart_atoi(s);
}