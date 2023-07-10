#include <string>
#include <map>
#include "../include/script.h"

const std::map<std::string, kw_logic> kwl_map = {
    {"if", kwl_if},
    {"ifdef", kwl_ifdef},
    {"ifeq", kwl_ifeq},
    {"ifndef", kwl_ifndef},
    {"ifneq", kwl_ifneq},
    {"else", kwl_else},
    {"define", kwl_define},
    {"endif", kwl_endif},
    {"let", kwl_let}};

static kw_logic __str_to_enum(const std::string &keyword)
{
    auto token = kwl_map.find(keyword);
    if (token != kwl_map.end())
    {
        return token->second;
    }
    return kwl_unknown;
}

#define IS_WHITESPACE_OR_ENDLINE(ch) ((ch) == ' ' || (ch) == '\t' || (ch) == '\n')

ERROR_CODE Analyzer::scan_logic(std::ifstream &inFile, kw_logic &keyword, int &offset)
{

    // the function is invoked when the analyzer read an '$'

    std::string word; // the target
    char ch;          // get from file

    // Read and ignore whitespace characters
    while (inFile.get(ch))
    {
#ifdef TRY_DEBUG
        DEBUG("ch is %c\n", ch);
#endif
        ++offset;
        if (!IS_WHITESPACE_OR_ENDLINE(ch))
        {
            word += ch;
#ifdef TRY_DEBUG
            DEBUG("the value of ch is:  %c\n", ch);

#endif
            break;
        }
    }

    // accepts input until gets whitespace or endline
    while (inFile.get(ch))
    {
#ifdef TRY_DEBUG
        DEBUG("the value of ch is:  %c\n", ch);

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

    if (keyword == kwl_unknown)
    {
        return A_NOT_A_TYPE;
    }

    offset = 1;
    return A_FINE;
}