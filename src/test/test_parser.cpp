#include "../include/test.h"
#include "../include/analyzer.h"

void test_analyzer1()
{
    std::string fileName = "/home/su/Documents/Code/xcalendar/src/test/test_analyzer.txt";
    std::ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
    int a=0,b=0;
    Analyzer xx;
    int k=xx.scan_year(inFile,a,b);
    TEST<<k<<" "<<a<<" "<<b<<std::endl;
}