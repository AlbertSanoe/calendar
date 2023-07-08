#include <string>
#include <map>

#include "../include/analyzer.h"

#define IS_WHITESPACE_OR_ENDLINE(ch) ((ch) == ' ' || (ch) == '\t' || (ch) == '\n')

#define IS_DOLLAR(ch) ((ch) == '$')

const std::map<std::string, kw_arithemetic> kwa_map = {
    {"!", kwa_not},
    {"==", kwa_eq},
    {"!=", kwa_ne},
    {"<", kwa_lt},
    {"<=", kwa_le},
    {">", kwa_gt},
    {">=", kwa_ge},
    {"&&", kwa_la},
    {"||", kwa_lo},
    {"=", kwa_asn}};

static kw_arithemetic __str_to_enum(const std::string &keyword)
{
    auto token = kwa_map.find(keyword);
    if (token != kwa_map.end())
    {
        return token->second;
    }
    return kwa_unknown;
}

ERROR_CODE_A Analyzer::scan_arithmetic(std::ifstream &inFile, kw_arithemetic &keyword, int &offset)
{
    std::string word;
    char ch;

    // Read characters from the input file
    while (inFile.get(ch))
    {
        ++offset;
        // If the character is a whitespace or endline, stop reading
        if (IS_WHITESPACE_OR_ENDLINE(ch)|| IS_DOLLAR(ch))
        {
            break;
        }

        // If the character is a punctuation symbol, add it to the 'word' string
        if (std::ispunct(ch))
        {
            word += ch;
        }
        else
        {
            return ERROR_TYPE;
        }
    }

    // If we reached the end of the file
    if (inFile.eof())
    {
        return FAILED_TO_READ;
    }

    // If the 'word' string is empty
    if (word.empty())
    {
        return NOT_A_TYPE;
    }

    // Convert the 'word' string to the corresponding kw_arithemetic enum value
    keyword = __str_to_enum(word);

    // If the keyword is unknown
    if (keyword == kwa_unknown)
    {
        return NOT_A_TYPE;
    }

    offset = 1;
    return FINE;
}
