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

enum kw_logic
{
    kwl_unknown,
    kwl_if,
    kwl_ifdef,
    kwl_ifeq,
    kwl_ifndef,
    kwl_ifneq,
    kwl_else,
    kwl_define,
    kwl_endif,
    kwl_let
};

enum kw_command
{
    kwc_unknown,
    kwc_set,
    kwc_findset,
    kwc_clear,
    kwc_check,
    kwc_get
};

enum kw_arithemetic
{
    kwa_unknown,
    kwa_not, // not
    kwa_eq,  // equal
    kwa_ne,  // not equal

    kwa_lt, // less than
    kwa_le, // less or equal
    kwa_gt, // greater than
    kwa_ge, // greater or equal

    kwa_la, // logical and
    kwa_lo, // logical or

    kwa_asn // assign
};

class Analyzer
{
public:
    ERROR_CODE_A status;
    const char *error_message;

    ERROR_CODE_A scan_logic(std::ifstream &inFile, kw_logic &keyword, int &offset);
    ERROR_CODE_A scan_command(std::ifstream &inFile, kw_command &keyword, int &offset);
    ERROR_CODE_A scan_arithmetic(std::ifstream &inFile, kw_arithemetic &keyword, int &offset);

    ERROR_CODE_A scan_pvarident(std::ifstream &inFile, std::string &ident, int &offset);
    ERROR_CODE_A scan_pvarval(std::ifstream &inFile, std::string &val, int &offset);

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