#include "../include/test.h"

void test_cal1()
{
    TEST_STARTFUNCTION;
    Date xx = Date(1912, 1, 1);
    TEST_WRAPPER(res, xx.is_leapyear());
    TEST << res << '\n';
    xx.check_weekday();
    TEST << xx << '\n';
    Time sometime;

    TEST_WRAPPER(time_date, Date::get_today(&sometime));
    TEST << time_date << std::endl;
    TEST << sometime << std::endl;

    TEST_ENDFUNCTION;
}


void test_cal3()
{
    TEST_STARTFUNCTION;
    Month month = 6;
    Year year = 2023;
    int after = 1;
    int before = 1;
    Calendar *new_cal = Calendar::get_cal(&month, &year, &after, &before);
    TEST_WRAPPER(l, new_cal->has_header_on_month());
    TEST << "the result is " << l << std::endl;
    new_cal->generate();
    Date datee=Date(2023,2,1,3);
    TEST<<std::endl;
    std::cout<<new_cal->content<<std::endl;
    TEST_ENDFUNCTION;
}
