#ifndef TEST_H
#define TEST_H

#include <iostream> /* cout, ostream */
#include <fstream>

#include "macro.h"
#include "print.h"
#include "cal.h"
#include "terminal.h"

/***************marcro for testing******************/

#define TEST                                                                     \
    do                                                                           \
    {                                                                            \
        char buffer[100];                                                         \
        int n = sprintf(buffer, "[TEST]  (%s, %d)", CURRENT_FILE, CURRENT_LINE); \
        info("%-50s\t", buffer);                                                 \
    } while (0);                                                                 \
    std::cout

#define TEST_STARTFUNCTION                                                              \
    do                                                                                  \
    {                                                                                   \
        char buffer[100];                                                               \
        int n = sprintf(buffer, "[TEST]##START##(%s, %s)", CURRENT_FILE, CURRENT_FUNC); \
        info("%-20s\n", buffer);                                                        \
    } while (0);

#define TEST_ENDFUNCTION                                                                \
    do                                                                                  \
    {                                                                                   \
        char buffer[100];                                                               \
        int n = sprintf(buffer, "[TEST]##END####(%s, %s)", CURRENT_FILE, CURRENT_FUNC); \
        info("%-20s\n", buffer);                                                        \
    } while (0);

#endif /* TEST_H */

#define TEST_WRAPPER(ident, stat) auto ident = stat



/******************for testing*********************/
void test_cal1();
void test_cal2();
void test_cal3();
void test_terminal1();
void test_analyzer1();
void test_analyzer2();

void test_error1();
void test_error2();

void test_ptable();
void test_otable();
void test_otable2();
void test_pparser();

void test_oparser();
