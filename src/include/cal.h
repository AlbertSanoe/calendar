#ifndef CAL_H
#define CAL_H

#include <string> /* std::string */
#include <vector>
#include "macro.h" /* GLOBAL_DEBUG */

#define LOCAL_DEBUG 1

#if (GLOBAL_DEBUG == 1) && (LOCAL_DEBUG == 1)

#define TRY_DEBUG

#endif

typedef int Month;   /* 1-12 indicates January-December */
typedef int Year;    /* Year X indicates exactly the year of X */
typedef int Day;     /* starting from 1 */
typedef int Weekday; /* Sunday indicates 0 */

typedef int Second; /* 0-60, leap seconds are applied to adjust human calendars */
typedef int Minute; /* 0-59 */
typedef int Hour;   /* 0-23 */

// for print the whole month in format, like
// example:                        1934
//            July                 August              September
//    Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa
//              1  2  3  4                     1         1  2  3  4  5
//     5  6  7  8  9 10 11   2  3  4  5  6  7  8   6  7  8  9 10 11 12
//    12 13 14 15 16 17 18   9 10 11 12 13 14 15  13 14 15 16 17 18 19
//    19 20 21 22 23 24 25  16 17 18 19 20 21 22  20 21 22 23 24 25 26
//    26 27 28 29 30 31     23 24 25 26 27 38 29  27 28 29 30
//                          30 31
//
//
struct Monthline
{
    std::string yearline; // store the line of the year "1934"
    std::string monthline; // store the line of the month 
    std::string weekline;  // store the weekday line
    std::string dayline[6]; // store the days
    Monthline();
};

class Time
{
public:
    Hour hour;
    Minute minute;
    Second second;

public:
    Time(Hour hr, Minute min, Second sec);
    Time(const Time &other)
    {
        this->hour = other.hour;
        this->minute = other.minute;
        this->second = other.second;
    }
    Time(){};
    bool operator<(const Time &other) const;
    bool operator==(const Time &other) const;
    bool operator!=(const Time &other) const;
};

class Date
{
public:
    Year year;
    Month month;
    Day day;
    Weekday weekday;

public:
    void check_weekday();
    const std::string get_weekday_str() const;

public:
    /* inplementations are in cal.c */
    Date(Year yy, Month mm);
    Date(Year yy, Month mm, Day dd);
    Date(Year yy, Month mm, Day dd, Weekday wd);
    Date(){};
    Date(const Date &other)
    {
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
        this->weekday=other.weekday;
    }
    bool operator<(const Date &other) const;
    bool operator==(const Date &other) const;
    bool operator!=(const Date &other) const;
    void increase_month();
    const bool is_leapyear();
    int get_daystamp();
    static Date get_today(Time *exact_time);
    static Year get_currentyear();
};

class Calendar
{
private:
    Month month; /* when after= before=0, it only prints the specific month */
    Year year;
    int after;
    int before;

    static Calendar *instance; // use the singleton design pattern

private:
    Calendar() {}

public:
    // a vector that stores the monthline instances
    std::vector<Monthline> content;

    //the function is to generate a month figure to display in terminal
    int month_generate(Date *const yy_mm_1, int row, int column, bool has_header);
    void generate();

public:
    bool has_header_on_month(); // whether it is necessary to print the year

    // get the unique instance
    static Calendar *get_cal(Month *month, Year *year, int *after, int *before);

    static Calendar *get_cal()
    {
        return Calendar::get_cal(nullptr, nullptr, nullptr, nullptr);
    }
    //std::vector<Monthline> get_content();
    Calendar(const Calendar &) = delete;
    Calendar &operator=(const Calendar &) = delete;
};

#endif /* CAL_H */