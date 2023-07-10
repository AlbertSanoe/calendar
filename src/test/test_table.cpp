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

void test_otable2()
{
     Output_table ot;

     const char *output_file_path = "/home/su/Documents/Code/xcalendar/cache/output2.txt";
     write_arrangement_header(output_file_path);
     Date xx = Date(1999, 12, 31, 0);
     xx.check_weekday();
     Time t1 = Time(11, 12, 33);
     Place p = Place("Saint German District");
     Event e = Event("Doing some examination");

     ot.insert(xx,t1,p,e);

     Date meetingDate = Date(2022, 8, 15, 0);
     Time startTime = Time(9, 0, 0);
     Time endTime = Time(17, 0, 0);
     Place location1 = Place("Conference Room A");
     Event meeting = Event("Project planning meeting");

     ot.insert(xx,startTime,location1,meeting);
     ot.insert(xx,startTime,location1,meeting);


     // Scenario 2: Birthday party
     Date partyDate = Date(2022, 9, 22, 0);
     Time partyTime = Time(18, 30, 0);
     Place location2 = Place("Local Park");
     Event birthdayParty = Event("Alice's birthday party");

     ot.insert(xx,partyTime,location2,birthdayParty);

     // Scenario 3: Concert
     Date concertDate = Date(2022, 10, 5, 0);
     Time doorsOpen = Time(19, 0, 0);
     Time concertStart = Time(20, 0, 0);
     Place location3 = Place("City Concert Hall");
     Event concert = Event("Symphony Orchestra performance");

     ot.insert(xx,doorsOpen,location3,concert);
     ot.insert(xx,concertStart,location3,concert);

     ot.iter_init();
     write_file_output(output_file_path,&ot);
}