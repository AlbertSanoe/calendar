#include <string>
#include <map>

#include "../include/script.h"

#define IS_WHITESPACE_OR_ENDLINE(ch) ((ch) == ' ' || (ch) == '\t' || (ch) == '\n')

#define IS_DOLLAR(ch) ((ch) == '$')

const std::map<std::string, kw_punctuation> kwa_map = {
    {"!", kwa_not},
    {"==", kwa_eq},
    {"!=", kwa_ne},
    {"<", kwa_lt},
    {"<=", kwa_le},
    {">", kwa_gt},
    {">=", kwa_ge},
    {"&&", kwa_la},
    {"||", kwa_lo},
    {"=", kwa_asn},
    {"$", kwd_dol},
    {";", kwd_sc},
    {"{", kwd_lcb},
    {"}", kwd_rcb},
    {"(", kwd_lp},
    {")", kwd_rp},
    {",", kwd_cm},
    {".", kwd_dot},
    {"-", kwd_hyp},
    {":", kwd_col}};

static kw_punctuation __str_to_enum(const std::string &keyword)
{
    auto token = kwa_map.find(keyword);
    if (token != kwa_map.end())
    {
        return token->second;
    }
    return kwa_unknown;
}

ERROR_CODE Analyzer::scan_punctuation(std::ifstream &inFile, kw_punctuation &keyword, int &offset)
{

    std::string word;
    char ch;

    // Scan for the first non-space character
    while (inFile.get(ch))
    {

#ifdef TRY_DEBUG
        DEBUG("print ch: %c\n", ch);
#endif
        ++offset;
        if (!IS_WHITESPACE_OR_ENDLINE(ch))
        {
            if (std::ispunct(ch))
            {
                word += ch;
                break;
            }
            else
            {
                return A_ERROR_TYPE;
            }
        }
    }

    // Check if reached end of file while scanning for non-space character
    if (inFile.eof())
    {
#ifdef TRY_DEBUG
        DEBUG("A_FAILED_TO_READ\n");
#endif
        return A_FAILED_TO_READ;
    }

    // Read characters from the input file
    while (inFile.get(ch))
    {
        ++offset;
        // If the character is a whitespace or endline, stop reading
        if (IS_WHITESPACE_OR_ENDLINE(ch) || IS_DOLLAR(ch))
        {
            break;
        }

        if (std::isdigit(ch) && (word == "-" || word == "." || word == ":"))
        {
            break;
        }

        if (word == ")" && ch == ';')
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
            return A_ERROR_TYPE;
        }
    }

    // If we reached the end of the file
    if (inFile.eof())
    {
        if (!(word == ";" || word == "}" || word == ")"))
        {
            return A_FAILED_TO_READ;
        }
    }

    // If the 'word' string is empty
    if (word.empty())
    {
        return A_NOT_A_TYPE;
    }

    // Convert the 'word' string to the corresponding kw_punctuation enum value
    keyword = __str_to_enum(word);

    // If the keyword is unknown
    if (keyword == kwa_unknown)
    {
        return A_NOT_A_TYPE;
    }

    offset = 1;
    return A_FINE;
}
