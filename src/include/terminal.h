#ifndef TERMINAL_H
#define TERMINAL_H

#include <fstream>
#include "../include/print.h"


void tofile();

void outputfile_demo(const Date &date);

void write_arragement_header(const char *path, const Date &date);

void write_time_place_event(const char* path, const Time &t,const Place &p,const Event&e);

// // todo!
// void write_long_arragement_header(const char*path, const Date &date, int lasting_day);

// // todo!
// void write_litem(const char*path, int sequence,const Date&date, const Time &t,const Place &p,const Event&e);

#endif