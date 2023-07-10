#include "../include/script.h"

const ERROR_CODE A_FINE = 0 << 0;
const ERROR_CODE A_ERROR_TYPE = 1 << 0;
const ERROR_CODE A_OUT_OF_RANGE = 2 << 0;
const ERROR_CODE A_NOT_A_TYPE = 3 << 0;
const ERROR_CODE A_FAILED_TO_READ = 4 << 0;

const ERROR_CODE P_FINE = 0 << 4;
const ERROR_CODE P_SCANNING_ERROR = 1 << 4;
const ERROR_CODE P_SCANNING_MISMATCHED = 2 << 4;

const std::string A_ERROR_TYPE_STR = "WRONG INPUT TYPE";
const std::string A_OUT_OF_RANGE_STR = "SOME VALUE IS OUT OF RANGE";
const std::string A_NOT_A_TYPE_STR = "NOT A LEGAL TYPE";
const std::string A_FAILED_TO_READ_STR = "END OF FILE";

const std::string P_SCANNING_ERROR_STR = "SCANNING ERROR";
const std::string P_SCANNING_MISMATCHED_STR = "MISMATCHED INPUT TYPE";

std::string error_handler(ERROR_CODE err)
{
    std::string result = "";

    // If both high and low bits of the error code are fine (0), return an empty string
    if (err == A_FINE && err == P_FINE)
    {
        return result;
    }

    // Flag to check if there is an error in the high bits (4-7)
    bool high_bits_error = false;

    // Check for _P_SCANNING_MISMATCHED (bit 5) and append the corresponding error string
    if ((err & P_SCANNING_MISMATCHED) == P_SCANNING_MISMATCHED)
    {
        result += "[ERROR]\t";
        result += P_SCANNING_MISMATCHED_STR;
        high_bits_error = true;
    }

    // Check for _P_SCANNING_ERROR (bit 4) and append the corresponding error string
    if ((err & P_SCANNING_ERROR) == P_SCANNING_ERROR)
    {
        // If there is already a high bits error, add a newline before the new error string
        if (high_bits_error)
        {
            result += "\n";
        }
        result += "[ERROR]\t";
        result += P_SCANNING_ERROR_STR;
        high_bits_error = true;

        // Get the low bits (0-3) of the error code
        ERROR_CODE low_bits = err & 0x0F;

        // If there is an error in the low bits and high bits, add ":\t" before the low bits error string
        if (low_bits != 0 && high_bits_error)
        {
            result += ":\t";
        }

        // Check for low bits errors and append the corresponding error strings
        switch (low_bits)
        {
        case A_ERROR_TYPE:
            result += A_ERROR_TYPE_STR;
            break;
        case A_OUT_OF_RANGE:
            result += A_OUT_OF_RANGE_STR;
            break;
        case A_NOT_A_TYPE:
            result += A_NOT_A_TYPE_STR;
            break;
        case A_FAILED_TO_READ:
            result += A_FAILED_TO_READ_STR;
            break;
        default:
            // You can add an error message for unknown error codes if you want
            break;
        }
    }

    // Return the generated error message string
    return result;
}

bool Analyzer::scan_whitespace(std::ifstream &inFile, int &offset)
{
    bool allWhitespace = true;
    char c;
    offset = 0;

    while (inFile.get(c))
    {
        ++offset;
        if (!std::isspace(static_cast<unsigned char>(c)))
        {
            allWhitespace = false;
            break;
        }
    }
    return allWhitespace;
}

bool Analyzer::ignore(std::ifstream &inFile, int &offset, char ch)
{
    char c;
    offset = 0;

    while (inFile.get(c))
    {
        if (c == ch)
        {
            offset = 1;
            return true;
        }
        offset++;
    }

    return false;
}