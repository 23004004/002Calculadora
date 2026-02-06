#include "../lib/stdio.h"

void main()
{
    int option, a, b, r, isFloat;
    int running = 1;

    PRINT(" ***** CALCULADORA ***** \n");

    while (running)
    {
        PRINT("\n***** Seleccione una opción *****\n");
        PRINT("1) Suma\n");
        PRINT("2) Resta\n");
        PRINT("3) Multiplicación\n");
        PRINT("4) División\n");
        PRINT("5) Salir\n");
        PRINT("Ingrese su opción: ");

        READ("%d", &option);

        char buffer1[32];
        char buffer2[32];


        switch (option)
        {
        case 1:
            PRINT("Ingrese el primer número: ");
            READ("%s", buffer1);

            PRINT("Ingrese el segundo número: ");
            READ("%s", buffer2);

            isFloat = have_decimal(buffer1) || have_decimal(buffer2);

            if (isFloat) {
                a = parse_float(buffer1);
                b = parse_float(buffer2);

                r = a + b;

                PRINT("%f + %f = %f\n", a, b, r);
            } else {
                a = parse_int(buffer1);
                b = parse_int(buffer2);

                r = a + b;

                PRINT("%d + %d = %d\n", a, b, r);
            }

            break;

        case 2:
            PRINT("Ingrese el primer número: ");
            READ("%s", buffer1);

            PRINT("Ingrese el segundo número: ");
            READ("%s", buffer2);

            isFloat = have_decimal(buffer1) || have_decimal(buffer2);

            if (isFloat) {
                a = parse_float(buffer1);
                b = parse_float(buffer2);

                r = a - b;
                PRINT("%f - %f = %f\n", a, b, r);
            } else {
                a = parse_int(buffer1);
                b = parse_int(buffer2);

                r = a - b;
                PRINT("%d - %d = %d\n", a, b, r);
            }

            break;
        case 3:
            PRINT("Ingrese el primer número: ");
            READ("%s", buffer1);

            PRINT("Ingrese el segundo número: ");
            READ("%s", buffer2);

            isFloat = have_decimal(buffer1) || have_decimal(buffer2);

            if (isFloat) {
                a = parse_float(buffer1);
                b = parse_float(buffer2);

                r = (a * b) / FLOAT_SCALE;

                PRINT("%f * %f = %f\n", a, b, r);
            } else {
                a = parse_int(buffer1);
                b = parse_int(buffer2);

                r = a * b;

                PRINT("%d * %d = %d\n", a, b, r);
            }
            break;
        case 4:
            PRINT("Ingrese el primer número: ");
            READ("%s", buffer1);

            PRINT("Ingrese el segundo número: ");
            READ("%s", buffer2);

            isFloat = have_decimal(buffer1) || have_decimal(buffer2);

            if (isFloat) {
                a = parse_float(buffer1);
                b = parse_float(buffer2);

                if (b == 0) {
                    PRINT("Error: división entre cero\n");
                    break;
                } 

                r = float_div(a, b);
                PRINT("%f / %f = %f\n", a, b, r);
            } else {
                a = parse_int(buffer1);
                b = parse_int(buffer2);

                if (b == 0) {
                    PRINT("Error: división entre cero\n");
                    break;
                }

                r = float_div(a, b);
                PRINT("%d / %d = %f\n", a, b, r);
            }
            break;
        case 5:
        {
            PRINT("Saliendo del programa...\n");
            running = 0;
            break;
        }
        default:
            PRINT("Invalid option\n");
            break;
        }
    }
}
