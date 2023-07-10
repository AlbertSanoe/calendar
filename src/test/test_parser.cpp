#include "../include/test.h"
#include "../include/script.h"

void test_analyzer1()
{
    std::string fileName = "/home/su/Documents/Code/xcalendar/src/test/test_analyzer.txt";
    std::ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
    int a = 0, b = 0;
    Analyzer xx;
    int k = xx.scan_year(inFile, a, b);
    TEST << k << " " << a << " " << b << std::endl;
}

void test_analyzer2()
{
    std::string fileName = "/home/su/Documents/Code/xcalendar/src/test/test_analyzer.txt";
    std::ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
    int a = 0, b = 0;
    Analyzer xx;
    kw_logic l;
    int k = xx.scan_logic(inFile, l, b);
    TEST << k << " " << (int)l << " " << b << std::endl;
}

void test_pparser()
{
    TEST << "hello?" << std::endl;
    std::string fileName = "/home/su/Documents/Code/xcalendar/src/test/test_analyzer.txt";
    std::ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
    int offset = 0;
    Analyzer a;
    Preprocessor_table table;
    PreParser x(&table, &a);

    x.pre_define(inFile, offset);
    bool res;
    x.pre_ifne(inFile, offset, res);
    TEST << std::boolalpha << res << std::endl;

    // std::string value;
    // std::string m="m43_";
    // bool found = table.get(m, value);
    // TEST << "the result is"
    //      << " " << std::boolalpha << found << std::endl;
    // TEST << value << std::endl;

    // bool containsKey1 = table.contains(m);

    // TEST << "the result is"
    //      << " " << std::boolalpha << containsKey1 << std::endl;

    // table.move(m);

    // bool containsKey2 = table.contains(m);

    // TEST << "the result is"
    //      << " " << std::boolalpha << containsKey2 << std::endl;
}

void test_oparser()
{
    std::string fileName = "/home/su/Documents/Code/xcalendar/src/test/test_analyzer.txt";
    std::ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
    int offset = 0;
    Analyzer a;
    Output_table ot;
    CmdParser cmd(&ot, &a);

    cmd.cmd_set(inFile, offset);

    Date d1(1991, 3, 4);
    Time t1(12, 21, 13);

    bool res = ot.contains(d1, t1);

    TEST << std::boolalpha << res << std::endl;
    Place p2;
    Event e2;
    ot.get(d1, t1, p2, e2);

    TEST << p2 << " " << e2 << std::endl;

    ot.move(d1, t1);
    res = ot.contains(d1, t1);

    TEST << std::boolalpha << res << std::endl;
}

void test_parser1()
{
    std::string fileName = "/home/su/Documents/Code/xcalendar/src/test/test_analyzer.txt";
    std::ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
    int offset = 0;

    Analyzer a;
    Output_table ot;
    CmdParser cmd(&ot, &a);

    cmd.cmd_findset(inFile, offset);

    Date d1(1991, 3, 4);
    Time t1(12, 21, 13);

    bool res = ot.contains(d1, t1);

    TEST << std::boolalpha << res << std::endl;
    Place p2;
    Event e2;
    ot.get(d1, t1, p2, e2);

    TEST << p2 << " " << e2 << std::endl;

    ot.move(d1, t1);
    res = ot.contains(d1, t1);

    TEST << std::boolalpha << res << std::endl;
}
