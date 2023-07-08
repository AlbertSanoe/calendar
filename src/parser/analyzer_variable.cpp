#include "../include/analyzer.h"

#define IS_WHITESPACE_OR_ENDLINE(ch) ((ch) == ' ' || (ch) == '\t' || (ch) == '\n')

ERROR_CODE_A Analyzer::scan_pvarident(std::ifstream &inFile, std::string &ident, int &offset)
{
    char ch;
    ident = "";

    // Read and ignore whitespace characters
    while (inFile.get(ch))
    {
        ++offset;
        if (!IS_WHITESPACE_OR_ENDLINE(ch))
        {
            break;
        }
    }

    // Check if the current character is valid for the start of a variable name
    if (!std::isalpha(ch) && ch != '_')
    {
        return ERROR_TYPE; // Invalid variable name
    }

    // Read the first character of the variable name
    ident += ch;

    // Read the remaining characters of the variable name
    while (inFile.get(ch))
    {
        ++offset;
        if ((std::isalnum(ch) || ch == '_'))
        {
            ident += ch;
        }
        else
        {
            break;
        }
    }

    if (inFile.eof())
    {
        return FAILED_TO_READ;
    }

    if (!IS_WHITESPACE_OR_ENDLINE(ch))
    {
        return NOT_A_TYPE;
    }

    offset = 1;

    return FINE; // Successfully read the variable name
}

ERROR_CODE_A scan_pvarval(std::ifstream &inFile, std::string &val, int &offset)
{
    char ch;
    val = "";

    // Read and ignore whitespace characters
    while (inFile.get(ch))
    {
        ++offset;
        if (!IS_WHITESPACE_OR_ENDLINE(ch))
        {
            break;
        }
    }

    // Check if the current character is valid for the start of a string
    if (!std::isalnum(ch) && ch != '_')
    {
        return ERROR_TYPE; // Invalid string start
    }

    // Read the string characters
    do
    {
        val += ch;

        if (!inFile.get(ch))
        {
            return FAILED_TO_READ; // Reached end of file before semicolon
        }
        ++offset;
    } while (std::isalnum(ch) || ch == '_');

    // Check if the current character is a semicolon
    if (ch != ';')
    {
        return NOT_A_TYPE; // Expecting a semicolon at the end of the string
    }

    offset = 1; // Account for the read semicolon

    return FINE; // Successfully read the string
}

