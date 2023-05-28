#include "../include/macro.h"

void info(const char *format, ...) __attribute__((format(printf, 1, 2)));

void info(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);
}