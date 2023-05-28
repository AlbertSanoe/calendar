#ifndef MARCO_H
#define MARCO_H
#include <cstdio>
#include <cstdarg>

/* ERROR CODE */
#define E_OUT_OF_RANGE -1
#define E_WRONG_MATCH -2

#define GLOBAL_DEBUG 1

#define CURRENT_LINE __LINE__
#define CURRENT_FILE __FILE__
#define CURRENT_FUNC __func__

void info(const char *format, ...);

#define DEBUG(...)                                                              \
    do                                                                           \
    {                                                                            \
        char buffer[50];                                                         \
        int n = sprintf(buffer, "[DEBUG] (%s, %d)", CURRENT_FILE, CURRENT_LINE); \
        info("%-30s\t", buffer);                                                 \
        info(__VA_ARGS__);                                                       \
    } while (0)

#define INFO(...)                                                              \
    do                                                                          \
    {                                                                           \
        char buffer[50];                                                        \
        int n = sprintf(buffer, "[INFO] (%s, %d)", CURRENT_FILE, CURRENT_LINE); \
        info("%-30s\t", buffer);                                                \
        info(__VA_ARGS__);                                                      \
    } while (0)

#endif /* MACRO_H */