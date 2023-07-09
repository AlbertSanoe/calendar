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

void test_otable()
{
     Output_table ot;
     Date d1(2021, 1, 1);
     Time t1(12, 0, 0);
     Place p1("Place1");
     Event e1("Event1");

     ot.insert(d1, t1, p1, e1);

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