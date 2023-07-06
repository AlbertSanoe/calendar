#include "../include/analyzer.h"

#define IS_WHITESPACE_OR_ENDLINE(ch) ((ch) == ' ' || (ch) == '\t' || (ch) == '\n')
#define IS_COLON(ch) ((ch) == ':')
#define IS_DOT_OR_HYPHEN(ch) ((ch) == '.' || (ch) == '-')

/*
 * @brief scan and generate a token of second
 * @param offset the distance from the initial position of the ifstream instance (when failed)
 *               or the distance from the last letter of the token
 * @return the status after scanning
 */
ERROR_CODE_A Analyzer::scan_second(std::ifstream &inFile, Second &sec, int &offset)
{
    offset = 0;
    char ch;            // the first character
    if (inFile.get(ch)) // get the first character
    {
        // offset is at least 1

        if (!isdigit(ch)) // validate if it is a digit
        {
            offset = 1;
            return ERROR_TYPE;
        }
        else
        {
            char next_ch; // the next character
            if (inFile.get(next_ch))
            {
                // offset is at least 2
                if (IS_WHITESPACE_OR_ENDLINE(next_ch))
                {
                    sec = ch - '0';
                    offset = 1; // the token is recognized, so the pointer increased
                    return FINE;
                }
                else if (isdigit(next_ch))
                {
                    if (ch >= '0' && ch <= '5')
                    {
                        char lookahead;
                        if (inFile.get(lookahead))
                        {
                            // offset is at least 3
                            if (IS_WHITESPACE_OR_ENDLINE(lookahead))
                            {
                                sec = (ch - '0') * 10 + next_ch - '0';
                                offset = 1;
                                return FINE;
                            }
                            else
                            {
                                offset = 3;
                                // something like 33p, 33!...
                                return NOT_A_TYPE;
                            }
                        }
                        else
                        {
                            offset = 2;
                            return FAILED_TO_READ;
                        }
                    }
                    else
                    {
                        // read a illegal value, no offset
                        // like 98, 89, 73...
                        offset = 2;
                        sec = (ch - '0') * 10 + next_ch - '0';
                        // illegal value, syntactically correct
                        return OUT_OF_RANGE;
                    }
                }
                else
                {
                    offset = 2;
                    // something like 1x, 2p, 3!...
                    return NOT_A_TYPE; // something is mixed together..
                }
            }
            else
            {
                offset = 1;
                // read a digit, and then failed to read
                return FAILED_TO_READ; // it should not be at the end of file
            }
        }
    }
    else
    {
        return FAILED_TO_READ; // offset=0
    }
}

/*
 * @brief scan and generate a token of minute
 * @param offset the distance from the initial position of the ifstream instance (when failed)
 *               or the distance from the last letter of the token
 * @return the status after scanning
 */
ERROR_CODE_A Analyzer::scan_minute(std::ifstream &inFile, Minute &min, int &offset)
{
    offset = 0;
    char ch;            // the first character
    if (inFile.get(ch)) // get the first character
    {
        if (!isdigit(ch)) // validate if it is a digit
        {
            offset = 1;
            return ERROR_TYPE;
        }
        else
        {
            char next_ch; // the next character
            if (inFile.get(next_ch))
            {
                if (IS_COLON(next_ch))
                {
                    min = ch - '0';
                    offset = 1;
                    return FINE;
                }
                else if (isdigit(next_ch))
                {
                    if (ch >= '0' && ch <= '5')
                    {
                        char lookahead;
                        if (inFile.get(lookahead))
                        {
                            if (IS_COLON(lookahead))
                            {
                                min = (ch - '0') * 10 + next_ch - '0';
                                offset = 1;
                                return FINE;
                            }
                            else
                            {
                                offset = 3;
                                // something like 33p, 33!...
                                return NOT_A_TYPE;
                            }
                        }
                        else
                        {
                            offset = 2;
                            return FAILED_TO_READ;
                        }
                    }
                    else
                    {
                        // read a illegal value, no offset
                        // like 98, 89, 73...
                        offset = 2;
                        min = (ch - '0') * 10 + next_ch - '0';
                        // illegal value, syntactically correct
                        return OUT_OF_RANGE;
                    }
                }
                else
                {
                    offset = 2;
                    // something like 1x, 2p, 3!...
                    return NOT_A_TYPE; // something is mixed together..
                }
            }
            else
            {
                offset = 1;
                // read a digit, and then failed to read
                return FAILED_TO_READ; // it should not be at the end of file
            }
        }
    }
    else
    {
        return FAILED_TO_READ; // I get nothing!
    }
}

/*
 * @brief scan and generate a token of hour
 * @param offset the distance from the initial position of the ifstream instance (when failed)
 *               or the distance from the last letter of the token
 * @return the status after scanning
 */
ERROR_CODE_A Analyzer::scan_hour(std::ifstream &inFile, Hour &hr, int &offset)
{
    offset = 0;
    char ch;            // the first character
    if (inFile.get(ch)) // get the first character
    {
        if (!isdigit(ch)) // validate if it is a digit
        {
            offset = 1;
            return ERROR_TYPE;
        }
        else
        {
            char next_ch; // the next character
            if (inFile.get(next_ch))
            {
                if (IS_COLON(next_ch))
                {
                    hr = ch - '0';
                    offset = 1;
                    return FINE;
                }
                else if (isdigit(next_ch))
                {
                    if (ch >= '0' && ch <= '1' || ch == '2' && next_ch >= '0' && next_ch <= '3')
                    {
                        char lookahead;
                        if (inFile.get(lookahead))
                        {
                            if (IS_COLON(lookahead))
                            {
                                hr = (ch - '0') * 10 + next_ch - '0';
                                offset = 1;
                                return FINE;
                            }
                            else
                            {
                                offset = 3;
                                // something like 33p, 33!...
                                return NOT_A_TYPE;
                            }
                        }
                        else
                        {
                            offset = 2;
                            return FAILED_TO_READ;
                        }
                    }
                    else
                    {
                        // read a illegal value, no offset
                        // like 25, 31, 89...
                        offset = 2;
                        hr = (ch - '0') * 10 + next_ch - '0';
                        return OUT_OF_RANGE;
                    }
                }
                else
                {
                    offset = 2;
                    // something like 1x, 2p, 3!...
                    return NOT_A_TYPE; // something is mixed together..
                }
            }
            else
            {
                offset = 1;
                // read a digit, and then failed to read
                return FAILED_TO_READ; // it should not be at the end of file
            }
        }
    }
    else
    {
        return FAILED_TO_READ; // I get nothing!
    }
}

/*
 * @brief scan and generate a token of day
 * @param offset the distance from the initial position of the ifstream instance (when failed)
 *               or the distance from the last letter of the token
 * @return the status after scanning
 */
ERROR_CODE_A Analyzer::scan_day(std::ifstream &inFile, Day &dd, int &offset)
{
    offset = 0;
    char ch;            // the first character
    if (inFile.get(ch)) // get the first character
    {
        if (!isdigit(ch)) // validate if it is a digit
        {
            offset = 1;
            return ERROR_TYPE;
        }
        else
        {
            char next_ch; // the next character
            if (inFile.get(next_ch))
            {
                if (IS_WHITESPACE_OR_ENDLINE(next_ch))
                {

                    if (ch == '0')
                    {
                        offset = 2;
                        dd = 0;              // illegal value, syntactically correct
                        return OUT_OF_RANGE; // no day 0
                    }
                    else
                    {
                        offset = 1;
                        dd = ch - '0';
                        return FINE;
                    }
                }
                else if (isdigit(next_ch))
                {
                    if (ch >= '0' && ch <= '2' || ch == '3' && next_ch >= '0' && next_ch <= '1')
                    {
                        char lookahead;
                        if (inFile.get(lookahead))
                        {
                            if (IS_WHITESPACE_OR_ENDLINE(lookahead))
                            {
                                dd = (ch - '0') * 10 + next_ch - '0';
                                offset = 1;
                                return FINE;
                            }
                            else
                            {
                                offset = 3;
                                // something like 33p, 33!...
                                return NOT_A_TYPE;
                            }
                        }
                        else
                        {
                            offset = 2;
                            return FAILED_TO_READ;
                        }
                    }
                    else
                    {
                        // read a illegal value, no offset
                        // like 25, 31, 89...
                        offset = 2;
                        dd = (ch - '0') * 10 + next_ch - '0';
                        // illegal value, syntactically correct
                        return OUT_OF_RANGE;
                    }
                }
                else
                {
                    offset = 2;
                    // something like 1x, 2p, 3!...
                    return NOT_A_TYPE; // something is mixed together..
                }
            }
            else
            {
                offset = 1;
                // read a digit, and then failed to read
                return FAILED_TO_READ; // it should not be at the end of file
            }
        }
    }
    else
    {
        return FAILED_TO_READ; // I get nothing!
    }
}

/*
 * @brief scan and generate a token of month
 * @param offset the distance from the initial position of the ifstream instance (when failed)
 *               or the distance from the last letter of the token
 * @return the status after scanning
 */
ERROR_CODE_A Analyzer::scan_month(std::ifstream &inFile, Month &mm, int &offset)
{
    offset = 0;
    char ch;            // the first character
    if (inFile.get(ch)) // get the first character
    {
        if (!isdigit(ch)) // validate if it is a digit
        {
            offset = 1;
            return ERROR_TYPE;
        }
        else
        {
            char next_ch; // the next character
            if (inFile.get(next_ch))
            {
                if (IS_DOT_OR_HYPHEN(next_ch))
                {

                    if (ch == '0')
                    {
                        offset = 2;
                        mm = 0;              // illegal value
                        return OUT_OF_RANGE; // no month 0
                    }
                    else
                    {
                        offset = 1;
                        mm = ch - '0';
                        return FINE;
                    }
                }
                else if (isdigit(next_ch))
                {
                    if (ch == '0' || ch == '1' && next_ch >= '0' && next_ch <= '2')
                    {
                        char lookahead;
                        if (inFile.get(lookahead))
                        {
                            if (IS_DOT_OR_HYPHEN(lookahead))
                            {
                                mm = (ch - '0') * 10 + next_ch - '0';
                                offset = 1;
                                return FINE;
                            }
                            else
                            {
                                offset = 3;
                                // something like 33p, 33!...
                                return NOT_A_TYPE;
                            }
                        }
                        else
                        {
                            offset = 2;
                            return FAILED_TO_READ;
                        }
                    }
                    else
                    {
                        // read a illegal value, no offset
                        // like 25, 31, 89...
                        offset = 2;
                        mm = (ch - '0') * 10 + next_ch - '0';
                        return OUT_OF_RANGE;
                    }
                }
                else
                {
                    offset = 2;
                    // something like 1x, 2p, 3!...
                    return NOT_A_TYPE; // something is mixed together..
                }
            }
            else
            {
                offset = 1;
                // read a digit, and then failed to read
                return FAILED_TO_READ; // it should not be at the end of file
            }
        }
    }
    else
    {
        return FAILED_TO_READ; // I get nothing!
    }
}

/*
 * @brief scan and generate a token of year
 * @param offset the distance from the initial position of the ifstream instance (when failed)
 *               or the distance from the last letter of the token
 * @return the status after scanning
 */
ERROR_CODE_A Analyzer::scan_year(std::ifstream &inFile, Year &yy, int &offset)
{

    // year>=1912
    char chs[5] = {0}; // nullptr

    inFile.read(chs, 5);
    offset = 5; // initial offset

    for (int i = 4; i >= 0; --i)
    {
        if (chs[i] != '\0')
        {
            break;
        }
        --offset;
    }

    for (size_t i = 0; i < 4; ++i)
    {
        // validate if the char is digit
        if (!isdigit(chs[i]))
        {
            if (i == 0)
            {
                return ERROR_TYPE;
            }
            else
            {
                return NOT_A_TYPE;
            }
        }
        else
        {
            if (i == 0)
            {
                if (chs[i] == '0')
                {
                    yy = 0;
                    return OUT_OF_RANGE;
                }
            }
        }
    }

    if (!IS_DOT_OR_HYPHEN(chs[4]))
    {
        return NOT_A_TYPE; // offset = 5
    }
    else
    {
        offset = 1;
        yy = (chs[0] - '0') * 1000 + (chs[1] - '0') * 100 + (chs[2] - '0') * 10 + (chs[3] - '0');
        if (yy >= 1912 && yy <= 9999)
        {
            return FINE;
        }
        else
        {
            offset = 5;

#ifdef TRY_DEBUG
            DEBUG("have come here, yy is %d\n", yy);
#endif
            return OUT_OF_RANGE;
        }
    }
}
