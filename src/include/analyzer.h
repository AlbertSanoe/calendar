#ifndef ANALYZER_H
#define ANALYZER_H

#include <fstream>
#include <cctype>

#include "macro.h" /* GLOBAL_DEBUG */
#include "cal.h"

#define LOCAL_DEBUG 1

#if (GLOBAL_DEBUG == 1) && (LOCAL_DEBUG == 1)

#define TRY_DEBUG

#endif

enum ERROR_CODE_A
{
    FINE,
    ERROR_TYPE,
    OUT_OF_RANGE,
    NOT_A_TYPE,
    FAILED_TO_READ
};



enum kw_command{
    kwc_set,
    kwc_findset,
    kwc_clear,
    kwc_check,
    kwc_get
};

class Analyzer
{
public:
    ERROR_CODE_A status;
    const char *error_message;

    void generate_tokens();

    ERROR_CODE_A scan_second(std::ifstream &inFile, Second &sec, int &offset);
    ERROR_CODE_A scan_minute(std::ifstream &inFile, Minute &min, int &offset);
    ERROR_CODE_A scan_hour(std::ifstream &inFile, Hour &hr, int &offset);

    ERROR_CODE_A scan_day(std::ifstream &inFile, Day &dd, int &offset);
    ERROR_CODE_A scan_month(std::ifstream &inFile, Month &mm, int &offset);
    ERROR_CODE_A scan_year(std::ifstream &inFile, Year &yy, int &offset);

    ERROR_CODE_A scan_weekday(std::ifstream &inFile, Day &dd, int &offset);
};

#endif /* ANALYZER_H */