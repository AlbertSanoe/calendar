#ifndef SCRIPT_H
#define SCRIPT_H

#include <cstdint>
#include <fstream>
#include <cctype>

#include "macro.h" /* GLOBAL_DEBUG */
#include "cal.h"
#include "table.h"

#define LOCAL_DEBUG 1

#if (GLOBAL_DEBUG == 1) && (LOCAL_DEBUG == 1)

#define TRY_DEBUG

#endif

// enum ERROR_CODE_A
// {
//     A_FINE,
//     A_ERROR_TYPE,
//     A_OUT_OF_RANGE,
//     A_NOT_A_TYPE,
//     A_FAILED_TO_READ
// };

// enum ERROR_CODE_P
// {
//     P_FINE,
//     P_SCANNING_ERROR,     // ERROR_CODE_A != FINE
//     P_SCANNING_MISMATCHED // the scanning process is fine, the token is not appropriate
// };

typedef uint32_t ERROR_CODE;

extern const ERROR_CODE A_FINE;
extern const ERROR_CODE A_ERROR_TYPE;
extern const ERROR_CODE A_OUT_OF_RANGE;
extern const ERROR_CODE A_NOT_A_TYPE;
extern const ERROR_CODE A_FAILED_TO_READ;

extern const ERROR_CODE P_FINE;
extern const ERROR_CODE P_SCANNING_ERROR;      // ERROR_CODE_A != FINE
extern const ERROR_CODE P_SCANNING_MISMATCHED; // the scanning process is fine, the token is not appropriate

extern const std::string A_ERROR_TYPE_STR;
extern const std::string A_OUT_OF_RANGE_STR;
extern const std::string A_NOT_A_TYPE_STR;
extern const std::string A_FAILED_TO_READ_STR;

extern const std::string P_SCANNING_ERROR_STR;
extern const std::string P_SCANNING_MISMATCHED_STR;

std::string error_handler(ERROR_CODE err);

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

enum kw_punctuation
{
    // arithmetic
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

    kwa_asn, // assign

    // delimiter
    kwd_dol, // dollar
    kwd_sc,  // semicolon
    kwd_lcb, // left curly bracket
    kwd_rcb,  // right curly bracket
    kwd_lp,  // left parenthesis
    kwd_rp,   // right parenthesis
    kwd_cm    //comma
};

class Analyzer
{
public:
    ERROR_CODE status;
    const char *error_message;

    ERROR_CODE scan_logic(std::ifstream &inFile, kw_logic &keyword, int &offset);
    ERROR_CODE scan_command(std::ifstream &inFile, kw_command &keyword, int &offset);
    ERROR_CODE scan_arithmetic(std::ifstream &inFile, kw_punctuation &keyword, int &offset);

    ERROR_CODE scan_pvarident(std::ifstream &inFile, std::string &ident, int &offset);
    ERROR_CODE scan_pvarval(std::ifstream &inFile, std::string &val, int &offset);

    void generate_tokens();

    ERROR_CODE scan_second(std::ifstream &inFile, Second &sec, int &offset);
    ERROR_CODE scan_minute(std::ifstream &inFile, Minute &min, int &offset);
    ERROR_CODE scan_hour(std::ifstream &inFile, Hour &hr, int &offset);

    ERROR_CODE scan_day(std::ifstream &inFile, Day &dd, int &offset);
    ERROR_CODE scan_month(std::ifstream &inFile, Month &mm, int &offset);
    ERROR_CODE scan_year(std::ifstream &inFile, Year &yy, int &offset);

    ERROR_CODE scan_weekday(std::ifstream &inFile, Day &dd, int &offset);
};

class PreParser
{
private:
    ERROR_CODE status;
    const char *err_msg;
    Preprocessor_table *tbl;
    Analyzer *scanner;

public:
    PreParser(Preprocessor_table *table, Analyzer *analyzer)
    {
        this->tbl = table;
        this->scanner = analyzer;
    } // make it a singleton later

    // todo
    void logic_process();

    ERROR_CODE pre_define(std::ifstream &inFile, int &offset);
    ERROR_CODE pre_if(std::ifstream &inFile, int &offset,bool &result);
    ERROR_CODE pre_ifdef(std::ifstream &inFile, int &offset,bool &result);
    ERROR_CODE pre_ifndef(std::ifstream &inFile, int &offset,bool &result);
    ERROR_CODE pre_ifeq(std::ifstream &inFile, int &offset,bool &result);
    ERROR_CODE pre_ifneq(std::ifstream &inFile, int &offset,bool &result);
    ERROR_CODE pre_else(std::ifstream &inFile, int &offset);

    //bool parse_singlebool(std::ifstream &inFile, int &offset); // cut it
    ERROR_CODE pre_BooleanStat(std::ifstream &inFile, int &offset,bool &result);
};

class Parser
{
};

class Script
{
};

#endif /* ANALYZER_H */