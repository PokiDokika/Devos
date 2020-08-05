#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

#define MAX_BASE 36

char* __ntoa(unsigned long val, unsigned char base, bool negative, bool uppercase)
{
    if (base < 2 || base > MAX_BASE) return NULL;
    if (val == 0) return "0\0";

    static char str[32];

    char* ptr = str;
    if (val > __LONG_MAX__ && negative) {
        *ptr++ = '-';
        val = (unsigned long)(((long)val) * -1);
    }

    char* low = ptr;

    for (; val; val /= base)
    {
        char c = "0123456789abcdefghijklmnopqrstuvwxyz"[val % base];
        if (c >= 'a' && c <= 'z' && uppercase) c -= 32;
        *ptr++ = c;
    }
    
    *ptr-- = '\0';

    while (low < ptr)
    {
        char tmp = *ptr;
        *ptr-- = *low;
        *low++ = tmp;
    }

    return str;
}

/* [bjrkk] FIXME: This should be improved.

                  Uppercase is now set as unused 
                  until this gets proper scientific notation support.

                  Precision is only limited to 0-8.
*/
char* __ftoa(double value, unsigned int precision, __attribute__((unused)) bool uppercase)
{
    static long pow_10s[8] = 
    { 
        0, 10, 100, 1000, 10000, 100000, 1000000, 10000000
    };

    if (precision > 7)
        precision = 7;

    long high = (long)value;
    long low = (value - high) * pow_10s[precision];

    static char str[32];
    char* ptr = str;

    for (char* high_buf = __ntoa(high, 10, 0, 0); *high_buf; high_buf++) 
        *ptr++ = *high_buf;
    
    if (precision != 0)
    {
        *ptr++ = '.';
        char* low_buf = __ntoa(low, 10, 0, 0);
        for (; *low_buf; low_buf++) 
            *ptr++ = *low_buf;
    }

    *ptr++ = '\0';

    return str;
}