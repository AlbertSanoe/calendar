#include "../include/test.h"
#include "../include/terminal.h"
#include "../include/macro.h"
#include "../include/cal.h"
#include "../include/print.h"

void test_terminal1()
{
    write_arrangement_header(nullptr);
    Date xx = Date(1999, 12, 31, 0);
    Time t1= Time(11,12,33);
    Place p=Place("Saint German District");
    Event e=Event("Doing some examination");
    write_date(nullptr,xx);
    write_time_place_event(nullptr,t1,p,e);

    Date meetingDate = Date(2022, 8, 15, 0);
    Time startTime = Time(9, 0, 0);
    Time endTime = Time(17, 0, 0);
    Place location1 = Place("Conference Room A");
    Event meeting = Event("Project planning meeting");

    //outputfile_demo(meetingDate);
    write_date(nullptr,meetingDate);
    write_time_place_event(nullptr, startTime, location1, meeting);
    write_time_place_event(nullptr, endTime, location1, Event("Meeting ends"));

        // Scenario 2: Birthday party
    Date partyDate = Date(2022, 9, 22, 0);
    Time partyTime = Time(18, 30, 0);
    Place location2 = Place("Local Park");
    Event birthdayParty = Event("Alice's birthday party");

    //outputfile_demo(partyDate);
    write_date(nullptr,partyDate);
    write_time_place_event(nullptr, partyTime, location2, birthdayParty);

    // Scenario 3: Concert
    Date concertDate = Date(2022, 10, 5, 0);
    Time doorsOpen = Time(19, 0, 0);
    Time concertStart = Time(20, 0, 0);
    Place location3 = Place("City Concert Hall");
    Event concert = Event("Symphony Orchestra performance");

    //outputfile_demo(concertDate);
    write_date(nullptr,concertDate);
    write_time_place_event(nullptr, doorsOpen, location3, Event("Doors open"));
    write_time_place_event(nullptr, concertStart, location3, concert);
}