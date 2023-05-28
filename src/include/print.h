#ifndef PRINT_H
#define PRINT_H

#include <iostream>


/****************** print the calendar ********************/
#include "cal.h" /* Date */

std::ostream &operator<<(std::ostream &out, const Date &obj);

std::ostream &operator<<(std::ostream &out, const Time &obj);

std::ostream &operator<<(std::ostream &out, const std::vector<Monthline>&cal);

#endif /* PRINT_H */