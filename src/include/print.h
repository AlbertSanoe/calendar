#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include "cal.h" /* Date, Time */
#include "plan.h" /* Place, Event, arrangement_header */

/****************** print the calendar ********************/

std::ostream &operator<<(std::ostream &out, const Date &obj);

std::ostream &operator<<(std::ostream &out, const Time &obj);

std::ostream &operator<<(std::ostream &out, const std::vector<Monthline>&cal);

std::ostream &operator<<(std::ostream &out, Place place);

std::ostream &operator<<(std::ostream &out, Event event_name);

// a demo
void print_arragement_header(const Date& date, const Time& time);

#endif /* PRINT_H */