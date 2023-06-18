#include "../include/terminal.h"
#include "../include/macro.h"
#include "../include/cal.h"
#include "../include/print.h"
void test_terminal1()
{
    Date xx = Date(1999, 12, 31, 0);
    Time t1= Time(11,12,33);
    Place p=Place("Saint German District");
    Event e=Event("Doing some examination");
    outputfile_demo(xx);
    write_arragement_header(nullptr,xx);
    write_time_place_event(nullptr,t1,p,e);
}