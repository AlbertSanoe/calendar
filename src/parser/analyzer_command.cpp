#include <string>
#include <map>
#include "../include/script.h"

const std::map<std::string, kw_command> kwc_map = {
    {"SET", kwc_set},
    {"FINDSET", kwc_findset},
    {"CLEAR", kwc_clear},
    {"CHECK", kwc_check},
    {"GET", kwc_get}};

static kw_command __str_to_enum(const std::string &keyword)
{
    auto token = kwc_map.find(keyword);
    if (token != kwc_map.end())
    {
        return token->second;
    }
    return kwc_unknown;
}

#define IS_WHITESPACE_OR_ENDLINE(ch) ((ch) == ' ' || (ch) == '\t' || (ch) == '\n')

ERROR_CODE Analyzer::scan_command(std::ifstream &inFile, kw_command &keyword, int &offset)
{

    // the function is invoked when the analyzer read an '$'

    std::string word; // the target
    char ch;          // get from file

    // accepts input until gets whitespace or endline
    while (inFile.get(ch))
    {

#ifdef TRY_DEBUG
        DEBUG("the value of ch is:%c\n", ch);
#endif
        ++offset;
        if (IS_WHITESPACE_OR_ENDLINE(ch))
        {
            break;
        }

        if (std::isalpha(ch))
        {
            word += ch;
        } // validate if it is alphabet
        else
        {
            if (ch == '(')
            {
                break;
            }
            return A_ERROR_TYPE;
        }
    }

#ifdef TRY_DEBUG
    DEBUG("the value of word is :%s\n", word.c_str());
#endif

    // If we reached the end of the file
    if (inFile.eof())
    {
#ifdef TRY_DEBUG
        DEBUG("the value of word is :%s\n", word.c_str());
#endif
        return A_FAILED_TO_READ;
    }

    if (word.empty())
    {
#ifdef TRY_DEBUG
        DEBUG("the value of word is :%s\n", word.c_str());
#endif
        return A_NOT_A_TYPE;
    }
#ifdef TRY_DEBUG
    DEBUG("before lookup: the value of word is :%s\n", word.c_str());
#endif
    keyword = __str_to_enum(word);

    if (keyword == kwc_unknown)
    {
        return A_NOT_A_TYPE;
    }

    offset = 1;
    return A_FINE;
}