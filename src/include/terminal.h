#ifndef TERMINAL_H
#define TERMINAL_H

#include <fstream>
#include <vector>
#include <string>

#include "macro.h"
#include "cal.h"
#include "print.h"
#include "table.h" /* Output_table */

void tofile();

void outputfile_demo(const Date &date);

void write_arrangement_header(const char *path);

void write_date(const char *path, const Date &date);

void write_time_place_event(const char *path, const Time &t, const Place &p, const Event &e);

void write_file_output(const char*file,Output_table*tbl);

// // todo!
// void write_long_arragement_header(const char*path, const Date &date, int lasting_day);

// // todo!
// void write_litem(const char*path, int sequence,const Date&date, const Time &t,const Place &p,const Event&e);

void xcal_process(int argc, const std::vector<std::string> &argv);

#endif