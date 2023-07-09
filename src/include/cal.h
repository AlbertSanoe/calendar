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

struct Monthline
{
    std::string yearline;
    std::string monthline;
    std::string weekline;
    std::string dayline[6];
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
};

class Calendar
{
private:
    Month month; /* when after= before=0, it only prints the specific month */
    Year year;
    int after;
    int before;

    static Calendar *instance;

private:
    Calendar() {}

public:
    std::vector<Monthline> content;
    int month_generate(Date *const yy_mm_1, int row, int column, bool has_header);
    void generate();

public:
    bool has_header_on_month();
    static Calendar *get_cal(Month *month, Year *year, int *after, int *before);
    static Calendar *get_cal()
    {
        return Calendar::get_cal(nullptr, nullptr, nullptr, nullptr);
    }
    std::vector<Monthline> get_content();
    Calendar(const Calendar &) = delete;
    Calendar &operator=(const Calendar &) = delete;
};

#endif /* CAL_H */