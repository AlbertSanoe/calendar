#include "../include/test.h"
#include "../include/script.h"

#include <iomanip>

void test_error1()
{
    TEST << std::hex << std::setw(8) << std::setfill('0') << A_FINE << std::endl;
    TEST << std::hex << std::setw(8) << std::setfill('0') << A_ERROR_TYPE << std::endl;
    TEST << std::hex << std::setw(8) << std::setfill('0') << A_OUT_OF_RANGE << std::endl;
    TEST << std::hex << std::setw(8) << std::setfill('0') << A_NOT_A_TYPE << std::endl;
    TEST << std::hex << std::setw(8) << std::setfill('0') << A_FAILED_TO_READ << std::endl;
    TEST << std::hex << std::setw(8) << std::setfill('0') << P_SCANNING_ERROR << std::endl;
    TEST << std::hex << std::setw(8) << std::setfill('0') << P_SCANNING_MISMATCHED << std::endl;
}

void test_error2(){
        // Test case 1: No error
    ERROR_CODE err1 = P_FINE | A_FINE;
    TEST<<error_handler(err1)<<std::endl;

    // Test case 2: Only high bits error (_P_SCANNING_MISMATCHED)
    ERROR_CODE err2 = P_SCANNING_MISMATCHED | A_FINE;
    TEST<<error_handler(err2)<<std::endl;

    // Test case 3: High bits error (_P_SCANNING_ERROR) with low bits error (_A_ERROR_TYPE)
    ERROR_CODE err3 = P_SCANNING_ERROR | A_ERROR_TYPE;
    TEST<<error_handler(err3)<<std::endl;

    // Test case 4: High bits error (_P_SCANNING_ERROR) with low bits error (_A_OUT_OF_RANGE)
    ERROR_CODE err4 = P_SCANNING_ERROR | A_OUT_OF_RANGE;
    TEST<<error_handler(err4)<<std::endl;

    // Test case 5: High bits error (_P_SCANNING_MISMATCHED) and (_P_SCANNING_ERROR) with low bits error (_A_FAILED_TO_READ)
    ERROR_CODE err5 = P_SCANNING_MISMATCHED | P_SCANNING_ERROR | A_FAILED_TO_READ;
    TEST<<error_handler(err5)<<std::endl;

}