#include "../include/test.h"
#include "../include/terminal.h"
#include "../include/macro.h"
#include "../include/cal.h"
#include "../include/print.h"

const char *output_file_path = "/home/su/Documents/Code/xcalendar/cache/output1.txt";

void test_terminal1()
{
    write_arrangement_header(output_file_path);
    Date xx = Date(1999, 12, 31, 0);
    Time t1= Time(11,12,33);
    Place p=Place("Saint German District");
    Event e=Event("Doing some examination");
    write_date(output_file_path,xx);
    write_time_place_event(output_file_path,t1,p,e);

    Date meetingDate = Date(2022, 8, 15, 0);
    Time startTime = Time(9, 0, 0);
    Time endTime = Time(17, 0, 0);
    Place location1 = Place("Conference Room A");
    Event meeting = Event("Project planning meeting");

    //outputfile_demo(meetingDate);
    write_date(output_file_path,meetingDate);
    write_time_place_event(output_file_path, startTime, location1, meeting);
    write_time_place_event(output_file_path, endTime, location1, Event("Meeting ends"));

        // Scenario 2: Birthday party
    Date partyDate = Date(2022, 9, 22, 0);
    Time partyTime = Time(18, 30, 0);
    Place location2 = Place("Local Park");
    Event birthdayParty = Event("Alice's birthday party");

    //outputfile_demo(partyDate);
    write_date(output_file_path,partyDate);
    write_time_place_event(output_file_path, partyTime, location2, birthdayParty);

    // Scenario 3: Concert
    Date concertDate = Date(2022, 10, 5, 0);
    Time doorsOpen = Time(19, 0, 0);
    Time concertStart = Time(20, 0, 0);
    Place location3 = Place("City Concert Hall");
    Event concert = Event("Symphony Orchestra performance");

    //outputfile_demo(concertDate);
    write_date(output_file_path,concertDate);
    write_time_place_event(output_file_path, doorsOpen, location3, Event("Doors open"));
    write_time_place_event(output_file_path, concertStart, location3, concert);
}

void test_terminal2(){
    const char *output_file_path = "/home/su/Documents/Code/xcalendar/cache/output3.txt";
    const char *input="/home/su/Documents/Code/xcalendar/src/test/test_analyzer.txt";

    read(input,output_file_path);
}