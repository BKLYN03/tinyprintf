#include <stdarg.h>
#include <stddef.h>
#include "tinyprintf.h"

// Helper function declarations
int print_decimal(int num);
int print_unsigned(unsigned int num);
int print_string(const char *str);
int print_octal(unsigned int num);
int print_hex(unsigned int num);

// Main tinyprintf function
int tinyprintf(const char *format, ...) 
{
    va_list args;
    va_start(args, format);
    
    int count = 0;  // To track the number of characters printed
    
    for (size_t i = 0; format[i] != '\0'; i++) 
    {
        if (format[i] == '%') 
        {
            // Handle the format specifiers
            i++;
            switch (format[i]) 
            {
                case '%':
                    putchar('%');
                    count++;
                    break;
                case 'd': 
                    int d = va_arg(args, int);
                    count += print_decimal(d);
                    break;
                case 'u': 
                    unsigned int u = va_arg(args, unsigned int);
                    count += print_unsigned(u);
                    break;
                case 's': 
                    char *s = va_arg(args, char *);
                    if (s == NULL) 
                    {
                        s = "(null)";
                    }
                    count += print_string(s);
                    break;
                case 'c': 
                    char c = (char)va_arg(args, int);
                    putchar(c);
                    count++;
                    break;
                case 'o': 
                    unsigned int o = va_arg(args, unsigned int);
                    count += print_octal(o);
                    break;
                case 'x':  
                    unsigned int x = va_arg(args, unsigned int);
                    count += print_hex(x);
                    break;
                default:
                    putchar('%');
                    putchar(format[i]);
                    count += 2;
                    break;
            }
        } 
        else 
        {
            putchar(format[i]);
            count++;
        }
    }
    
    va_end(args);
    return count;
}

// Helper functions

int print_decimal(int num) 
{
    int count = 0;
    if (num < 0) 
    {
        putchar('-');
        count++;
        num = -num;
    }
    count += print_unsigned((unsigned int)num);
    return count;
}

int print_unsigned(unsigned int num) 
{
    if (num == 0) 
    {
        putchar('0');
        return 1;
    }

    char buffer[10];
    int i = 0, count = 0;

    while (num > 0) 
    {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    while (i > 0) 
    {
        putchar(buffer[--i]);
        count++;
    }

    return count;
}

int print_string(const char *str) 
{
    int count = 0;
    while (*str) 
    {
        putchar(*str++);
        count++;
    }
    return count;
}

int print_octal(unsigned int num) 
{
    if (num == 0) 
    {
        putchar('0');
        return 1;
    }

    char buffer[12];
    int i = 0, count = 0;

    while (num > 0) 
    {
        buffer[i++] = (num % 8) + '0';
        num /= 8;
    }

    while (i > 0) 
    {
        putchar(buffer[--i]);
        count++;
    }

    return count;
}

int print_hex(unsigned int num) 
{
    if (num == 0) 
    {
        putchar('0');
        return 1;
    }

    char buffer[8];
    int i = 0, count = 0;

    while (num > 0) 
    {
        int digit = num % 16;
        if (digit < 10) 
        {
            buffer[i++] = digit + '0';
        } 
        else
        {
            buffer[i++] = digit - 10 + 'a';
        }
        num /= 16;
    }

    while (i > 0) 
    {
        putchar(buffer[--i]);
        count++;
    }

    return count;
}
