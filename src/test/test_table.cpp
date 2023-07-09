#include "../include/test.h"
#include "../include/table.h"

void test_ptable()
{
    Preprocessor_table table;
    table.insert("KEY1", "VALUE1");
    std::string value;
    bool found = table.get("KEY1", value);
    TEST << "the result is"
         << " " << std::boolalpha << found << std::endl;
    TEST << value << std::endl;

    bool containsKey1 = table.contains("KEY1");

    TEST << "the result is"
         << " " << std::boolalpha << containsKey1 << std::endl;

    table.move("KEY1");

    bool containsKey2 = table.contains("KEY1");

    TEST << "the result is"
         << " " << std::boolalpha << containsKey2 << std::endl;
}