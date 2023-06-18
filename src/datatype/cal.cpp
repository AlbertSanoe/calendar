#include <sys/time.h> /* gettimeofday */
#include <time.h>     /* localtime */
#include <cstddef>    /* size_t */
#include "../include/cal.h"

#define CAL_FOR_CHINA_ONLY

#ifdef CAL_FOR_CHINA_ONLY
#define STARTING_YEAR (Year)1912
#define STARTING_MONTH (Month)1
#define STARTING_DAY (Day)1
#define STARTING_WEEKDAY (Weekday)1 /* Monday */
/* the first day that China applied Gregorian calendar */
#else
#define STARTING_YEAR (Year)1582
#define STARTING_MONTH (Month)10
#define STARTING_DAY (Day)4
#define STARTING_WEEKDAY (Weekday)2 /* Tuesday */
/* the starting day of Gregorian calendar */
#endif

#define STARTING_DAY_STAMP 0

#define LEAP_YEAR_DAY_NUM 366
#define COMMON_YEAR_DAY_NUM 365

/* used to validate a date value is legal or not */
#define MAX_DAY_IN_MONTH_VAL 31
#define MIN_DAY_IN_MONTH_VAL 1

/* used to validate a weekday is legal or not */
#define MAX_WEEKDAY_VAL 6
#define MIN_WEEKDAY_VAL 0

/* used to validate a month is legal or not */
#define MAX_MONTH_VAL 12
#define MIN_MONTH_VAL 1

#define LEAP_MONTH_VAL 2
#define LEAP_YEAR_MDAY_VAL 29
#define COMMON_YEAR_MDAY_VAL 28

#define EARILER (bool)true
#define LATER (bool)false

/* "equal" condition is not included */
#define IS_EARLIER(val, ref) (bool)((val) < (ref))
#define IS_SAME(val, ref) (bool)((val) == (ref))

/* validate the values */
#define VALIDATE_YEAR(yy) (bool)((yy) >= STARTING_YEAR && (yy) <= 9999)

#define VALIDATE_MONTH(mm) (bool)((mm) >= MIN_MONTH_VAL && (mm) <= MAX_MONTH_VAL)

#define VALIDATE_DAY(dd) (bool)((dd) >= MIN_DAY_IN_MONTH_VAL && (dd) <= MAX_DAY_IN_MONTH_VAL)

#define VALIDATE_WEEKDAY(wd) (bool)((wd) >= MIN_WEEKDAY_VAL && (wd) <= MAX_WEEKDAY_VAL)

#define MAX_MONTH_PER_LINE 3

const int day_val_in_month_leap[13] = {
    1,  // placeholder
    31, // January
    29, // February
    31, // March
    30, // April
    31, // May
    30, // June
    31, // July
    31, // August
    30, // September
    31, // October
    30, // November
    31  // December
};

const int day_val_in_month_common[13] = {
    0,  // placeholder
    31, // January
    28, // February
    31, // March
    30, // April
    31, // May
    30, // June
    31, // July
    31, // August
    30, // September
    31, // October
    30, // November
    31  // December
};

Time::Time(Hour hr, Minute min, Second sec)
    : hour(hr), minute(min), second(sec) {}

/* the construction function of the class Date */
Date::Date(Year val, Month mm, Day dd)
    : year(val), month(mm), day(dd), weekday(0){}

/* the construction function of the class Date, with the weekday value */
Date::Date(Year val, Month mm, Day dd, Weekday ww)
    : year(val), month(mm), day(dd), weekday(ww) {}

/* for special use */
Date::Date(Year yy, Month mm) : year(yy), month(mm), day(-1), weekday(-1)
{
}

void Date::increase_month()
{
    if ((++this->month) == 13)
    {
        this->month = 1;
        this->year += 1;
    }
}

static const inline bool __is_leapyear(Year val)
{
    if (val % 100 == 0)
    {
        // #ifdef TRY_DEBUG
        //         DEBUG("go to the branch: val % 100 == 0\n");
        // #endif
        if (val % 400 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    } // the year is XX00
    else
    {
        if (val % 4 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

/*
 * @brief to compare two date values with format mm-dd
 * @return true: current date is earlier
 */
static inline bool __date_cmp2(Month mm, Day dd, Month mref, Day dref)
{
    if (IS_EARLIER(mm, mref) || IS_SAME(mm, mref) && IS_EARLIER(dd, dref))
    {
        return EARILER;
    }
    else
    {
        return LATER;
    }
}

/*
 * @brief determine whether the year is a leap year or not
 */
const bool Date::is_leapyear()
{
    return __is_leapyear(this->year);
}

static int __get_daystamp(Year yy, Month mm, Day dd)
{
    // calculate the day of the year for a given date
    bool leap_year = __is_leapyear(yy);
    int sum = 0;
    if (leap_year)
    {
        for (size_t i = 1; i < (size_t)mm; i++)
        {
            sum += (int)day_val_in_month_leap[i];
        }
        sum += (int)dd;
    }
    else
    {
        for (size_t i = 1; i < (size_t)mm; i++)
        {
            sum += (int)day_val_in_month_common[i];
        }
        sum += (int)dd;
    }

    for (size_t j = (size_t)STARTING_YEAR; j < (size_t)yy; j++)
    {
        if (__is_leapyear((Year)j))
        {
            sum += (int)LEAP_YEAR_DAY_NUM;
        }
        else
        {
            sum += (int)COMMON_YEAR_DAY_NUM;
        }
    }
    return sum - STARTING_DAY_STAMP; /* the starting day is day 0 */
}

static Weekday __cal_weekday(Year yy, Month mm, Day dd)
{
    int timestamp = __get_daystamp(yy, mm, dd);
#ifdef TRY_DEBUG
    DEBUG("the value of timestamp is %d\n", timestamp);
#endif
    return (Weekday)((timestamp - STARTING_DAY_STAMP) % 7);
}

/*
 * @brief get the time stamp of the date
 * @note assuming that the starting day is the first day
 */
int Date::get_daystamp()
{
    return __get_daystamp(this->year, this->month, this->day);
}

void Date::check_weekday()
{
    this->weekday = __cal_weekday(this->year, this->month, this->day);
}

Date Date::get_today(Time *exact_time)
{
    struct timeval t_sec;
    int result = gettimeofday(&t_sec, nullptr);
    struct tm *ptr_time;
    ptr_time = localtime(&t_sec.tv_sec);
#ifdef TRY_DEBUG
    DEBUG("the second value is %d\n", t_sec.tv_sec);
    DEBUG("the value of the date is %d, %d, %d, %d\n", ptr_time->tm_year, ptr_time->tm_mon, ptr_time->tm_mday, ptr_time->tm_wday);
#endif
    Date today = Date((Year)ptr_time->tm_year + 1900, (Month)(ptr_time->tm_mon + 1), (Day)ptr_time->tm_mday, (Weekday)ptr_time->tm_wday);
    // tm_year calculates the differ value from now to 1900
    if (exact_time)
    {
        exact_time->hour = (Hour)ptr_time->tm_hour;
        exact_time->minute = (Minute)ptr_time->tm_min;
        exact_time->second = (Second)ptr_time->tm_sec;
    }
    return today;
}

static void __adjust_months(int *mm_ptr, int *before_ptr, int *after_ptr)
{
    if (mm_ptr == nullptr || after_ptr == nullptr || before_ptr == nullptr)
    {
        // ERROR
    }
    else
    {
        // how many months after the first month
        *after_ptr = *after_ptr + *before_ptr;

        // find out the "the first month"
        int before = *before_ptr;

        int mm = *mm_ptr - before;

        int first_year = 0; // the current year is assumed to be 0

        for (; mm <= 0; mm = mm + 12, --first_year)
        {
        }

        *mm_ptr = mm;
        *before_ptr = first_year;
    }
#ifdef TRY_DEBUG
    DEBUG("the values month, first_year, lasted_months are %d, %d, %d.\n", *mm_ptr, *before_ptr, *after_ptr);
#endif
}

bool Calendar::has_header_on_month()
{

    __adjust_months(&this->month, &this->before, &this->after);
    bool need_header;

    if (this->month + this->after > MAX_MONTH_VAL)
    {
        //  1    2    3
        //  4    5    6
        //  7    8    9
        // 10   11   12
        if (this->month == 1 || this->month == 4 || this->month == 7 || this->month == 10)
        {
            need_header = false;
        }
        else
        {
            need_header = true;
        }
    } // the months are not in the same year
    else
    {
        if (this->after + 1 >= MAX_MONTH_PER_LINE)
        {
            need_header = false;
        }
        else
        {
            need_header = true;
        }
    }

    return need_header;
}

const std::string wds_str = "Su Mo Tu We Th Fr Sa";

const std::string wds_long_str[7]={
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
};

const std::string Date::get_weekday_str() const{
    return wds_long_str[this->weekday];
}

const std::string day_in_month_str = " 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31";

const std::string month_str[13] = {
    "",          // placeholder
    "January",   // 1
    "February",  // 2
    "March",     // 3
    "April",     // 4
    "May",       // 5
    "June",      // 6
    "July",      // 7
    "August",    // 8
    "September", // 9
    "October",   // 10
    "November",  // 11
    "December"   // 12
};

#define NO_HEADER_POS_1 (6)
#define NO_HEADER_POS_2 (6)
#define NO_HEADER_POS_3 (7)
#define NO_HEADER_POS_4 (7)
#define NO_HEADER_POS_5 (8)
#define NO_HEADER_POS_6 (8)
#define NO_HEADER_POS_7 (8)
#define NO_HEADER_POS_8 (7)
#define NO_HEADER_POS_9 (5)
#define NO_HEADER_POS_10 (6)
#define NO_HEADER_POS_11 (6)
#define NO_HEADER_POS_12 (6)

const int no_header_pos[13] = {
    0, // placeholder
    NO_HEADER_POS_1,
    NO_HEADER_POS_2,
    NO_HEADER_POS_3,
    NO_HEADER_POS_4,
    NO_HEADER_POS_5,
    NO_HEADER_POS_6,
    NO_HEADER_POS_7,
    NO_HEADER_POS_8,
    NO_HEADER_POS_9,
    NO_HEADER_POS_10,
    NO_HEADER_POS_11,
    NO_HEADER_POS_12};

/*

      January               February               March
Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa

       April                  May                   June
Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa

        July                 August              September
Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa

      October               November              December
Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa

*/
#define CONCAT(a, b) a##b
#define HEADER_POS(val) CONCAT(HEADER_POS_, val)

#define HEADER_POS_1 (4)
#define HEADER_POS_2 (3)
#define HEADER_POS_3 (5)
#define HEADER_POS_4 (5)
#define HEADER_POS_5 (6)
#define HEADER_POS_6 (5)
#define HEADER_POS_7 (5)
#define HEADER_POS_8 (4)
#define HEADER_POS_9 (3)
#define HEADER_POS_10 (4)
#define HEADER_POS_11 (3)
#define HEADER_POS_12 (3)

const int header_pos[13] = {
    0,
    HEADER_POS_1,
    HEADER_POS_2,
    HEADER_POS_3,
    HEADER_POS_4,
    HEADER_POS_5,
    HEADER_POS_6,
    HEADER_POS_7,
    HEADER_POS_8,
    HEADER_POS_9,
    HEADER_POS_10,
    HEADER_POS_11,
    HEADER_POS_12};

/*

   December 2021          January 2022         February 2022
Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa

     March 2022            April 2022             May 2022
Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa

     June 2022             July 2022            August 2022
Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa

   September 2022         October 2022         November 2022
Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa

*/

#define PREV_INDEX(day) (3 * (day)-3)
#define REAR_INDEX(day) (3 * (day)-2)

#define SPACE_BETWEEN_MONTH_PRINT (2)
#define EACH_ROW_LENGTH (6 * 3 + 2)
#define TOTAL_ROW_LENGTH (EACH_ROW_LENGTH * 3 + SPACE_BETWEEN_MONTH_PRINT * 2)

/* column val ranges from 0 to 2 */
#define PREV_COLUMN_INDEX(column) ((column) * (EACH_ROW_LENGTH + SPACE_BETWEEN_MONTH_PRINT))

/* column val ranges from 0 to 2 */
#define REAR_COLUMN_INDEX(column) (((column) + 1) * (EACH_ROW_LENGTH)-1 + (column)*SPACE_BETWEEN_MONTH_PRINT)

#define PLACEHOLDER_SIGN std::string(1, '#')
#define YEAR_CENTER_POS (EACH_ROW_LENGTH + SPACE_BETWEEN_MONTH_PRINT + NO_HEADER_POS_2)

Monthline::Monthline()
{
    this->yearline = std::string(TOTAL_ROW_LENGTH, ' ');
    this->monthline = std::string(TOTAL_ROW_LENGTH, ' ');
    this->weekline = std::string(TOTAL_ROW_LENGTH, ' ');
    this->dayline[0] = std::string(TOTAL_ROW_LENGTH, ' ');
    this->dayline[1] = std::string(TOTAL_ROW_LENGTH, ' ');
    this->dayline[2] = std::string(TOTAL_ROW_LENGTH, ' ');
    this->dayline[3] = std::string(TOTAL_ROW_LENGTH, ' ');
    this->dayline[4] = std::string(TOTAL_ROW_LENGTH, ' ');
    this->dayline[5] = std::string(TOTAL_ROW_LENGTH, ' ');
}

static std::string __weekday_generate(int month_per_line)
{
    // ERROR month_per_line>=1 && month_per_line <=3

    std::string blank = " ";
    std::string wds = wds_str;
    for (int num = 1; num < month_per_line; num++)
    {
        wds += blank + blank;
        wds += wds_str;
    }
    return wds;
}

/*
 * @brief            the function is to generate a month figure to display in terminal
 * @param yy_mm_1    it is to tell the specific value of the year and month, day value is
 *                   assigned to 1
 * @param row        it is to tell the position of the month in the terminal
 * @param column     it is to tell the position of the month in the terminal
 * @param has_header it is to tell whether it is necessary to print the year value
 */
int Calendar::month_generate(Date *const yy_mm_1, int row, int column, bool has_header)
{

    // get first index
    int content_first_index = PREV_COLUMN_INDEX(column);

    // get the last index
    int content_last_index_included = REAR_COLUMN_INDEX(column);

#ifdef TRY_DEBUG
    DEBUG("the row is, column is %d, %d\n", row, column);
    DEBUG("the first_index, last_index is %d, %d\n", content_first_index, content_last_index_included);
#endif

    if (yy_mm_1 == nullptr)
    {
    }

    int last_mday; // last_day == 28 || 29 || 30 || 31
    // later used for comparation to break the loop

    if (yy_mm_1->is_leapyear())
    {
        last_mday = day_val_in_month_leap[yy_mm_1->month];
    }
    else
    {
        last_mday = day_val_in_month_common[yy_mm_1->month];
    }

#ifdef TRY_DEBUG
    DEBUG("in yy-mm %d %d the last day number is %d\n", yy_mm_1->year, yy_mm_1->month, last_mday);
#endif

    // example:
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

    // the length of the row of each element

    int placeholder = (int)(yy_mm_1->weekday) * 3;
#ifdef TRY_DEBUG
    DEBUG("the val of the placeholder: %d\n", placeholder);
#endif

    std::string month_header(EACH_ROW_LENGTH, ' ');

    bool print_center_year = false;

    if (has_header)
    {
        int first_pos = header_pos[yy_mm_1->month];
        std::string header = month_str[yy_mm_1->month] + std::string(1, ' ') + std::to_string(yy_mm_1->year);
        month_header.replace(first_pos, header.size(), header);

        // print_center_year=false;
    }
    else
    {
        int first_pos = no_header_pos[yy_mm_1->month];
        std::string header = month_str[yy_mm_1->month];
        month_header.replace(first_pos, header.size(), header);
        if (row == 0 && column == 0)
        {
            print_center_year = true;
        }
        else if (yy_mm_1->month == 1)
        {
            print_center_year = true;
        }
    }

    if (print_center_year)
    {
        // the string form of the year
        std::string year_str = std::to_string(yy_mm_1->year);
        // add the year into the yearline
        this->content[row].yearline.replace(YEAR_CENTER_POS, year_str.size(), year_str);
    }

#ifdef TRY_DEBUG
    DEBUG("size of the monthline %d\n", this->content[row].monthline.size());
#endif

    this->content[row].monthline.replace(content_first_index, EACH_ROW_LENGTH, month_header);

#ifdef TRY_DEBUG
    DEBUG("the %c line is: |%s\n", 'm', month_header.c_str());
#endif

    std::string wds_header = __weekday_generate(1);

#ifdef TRY_DEBUG
    DEBUG("the %c line is: |%s\n", 'c', wds_header.c_str());
#endif
    // add the weekline into the content
    this->content[row].weekline.replace(content_first_index, EACH_ROW_LENGTH, wds_header);

    // first_day of the line, Saturday or the last day of month

    // the first day of the line
    int first_mday = (int)yy_mm_1->day;
    // the first day in each line
    int first_day_line = first_mday;
    // its correspondant weekday
    int weekday_first_day_line = (int)yy_mm_1->weekday;
    // day_val for Saturday for each line
    int day_for_Saturday = MAX_WEEKDAY_VAL - weekday_first_day_line + first_mday;
    // #ifdef TRY_DEBUG

    //     DEBUG("the value of first day in month:%d\n",first_mday);
    //     DEBUG("the first day in the line:%d\n",first_day_line);
    //     DEBUG("the weekday_first_day_line: %d\n",weekday_first_day_line);
    //     DEBUG("the day for Sat: %d\n",day_for_Saturday);
    // #endif

    // the loop started

    int weekday_last_day;
    for (int _row = 0; _row < 6; _row++)
    {
        // line for a week
        std::string day_line_str;

        // first index
        int first_index = PREV_INDEX(first_day_line);

        // in some condition last_day may be equal to first index, but it is fine
        int last_day = day_for_Saturday < last_mday ? day_for_Saturday : last_mday;

        int last_index_included = REAR_INDEX(last_day);
        // #ifdef TRY_DEBUG

        //         DEBUG("first index:        %d\n", first_index);
        //         DEBUG("last index_included:%d\n", last_index_included);
        // #endif
        if (first_day_line == first_mday)
        {
            std::string placeholder_str(placeholder, ' ');
            day_line_str = placeholder_str + day_in_month_str.substr(first_index, last_index_included - first_index + 1);
        }
        else
        {
            day_line_str = day_in_month_str.substr(first_index, last_index_included - first_index + 1);
        }
#ifdef TRY_DEBUG
        DEBUG("the size of the dayline %d: %d\n", _row, this->content[row].dayline[_row].size());
#endif
        this->content[row].dayline[_row].replace(content_first_index, day_line_str.size(), day_line_str);

#ifdef TRY_DEBUG
        DEBUG("the %d line is: |%s\n", _row, day_line_str.c_str());
        // DEBUG("the first_day_line, last day is %d, %d\n", first_day_line, last_day);
#endif
        if (last_day == last_mday)
        {
            weekday_last_day = last_day - first_day_line;
            break;
        }
        first_day_line = day_for_Saturday + 1;
        day_for_Saturday += 7;
    }
    return weekday_last_day;
}

void Calendar::generate()
{

    /* suppose that all the values are initialized */

    // it changes the value of month, after and before
    // and their meaning changes
    bool has_header = this->has_header_on_month();

    // the adjusted value of the first year
    int adjusted_first_year = this->year + this->before;

    // how many months are to print
    // after indicats that how many months there are after the first one
    int all_months_value = this->after + 1;

    // the first month
    int first_month = this->month;

    int row_number = all_months_value / MAX_MONTH_PER_LINE;

    if (all_months_value % MAX_MONTH_PER_LINE)
    {
        row_number += 1;
    }

    // vector initialization
    this->content = std::vector<Monthline>(row_number);

    int col = 0; // col ranges from 0 to 2

    //  a pretended date, used to print the month
    Date yy_mm_1 = Date(adjusted_first_year, first_month, 1);

    // calculate its correspondant weekday
    yy_mm_1.check_weekday();

    // there are two situations that need to print the year in the center
    //
    // the first time
    // when the year changes

    for (int i = 0, row_index = 0; i < all_months_value; ++i)
    {
        // if header is false, it is the duty of the first month of year
        // to print year_str in the center
        // two situations:
        // (I)  row_index == 0 && col == 0
        // (II) yy_mm_1 -> month == 1

        int first_weekday = (this->month_generate(&yy_mm_1, row_index, col, has_header) + 1) % 7;

        ++col;
#ifdef TRY_DEBUG
        DEBUG("the value of column is %d\n\n", col);
#endif
        if (!(col % 3))
        {
            col = 0;
            row_index += 1;
        }
#ifdef TRY_DEBUG
        DEBUG("the value of new column is %d, new row is %d\n", col, row_index);
#endif

        if (row_index == row_number)
        {
            // can never be inside
            break;
        }
        if ((++yy_mm_1.month) == 13)
        {
            yy_mm_1.month = 1;
            yy_mm_1.year += 1;
        }
        yy_mm_1.weekday = first_weekday;
    }
}

Calendar *Calendar::instance = nullptr;

Calendar *Calendar::get_cal(Month *month, Year *year, int *after, int *before)
{
    if (Calendar::instance)
    {
        if (month != nullptr)
        {
            Calendar::instance->month = *month;
        }
        if (year != nullptr)
        {
            Calendar::instance->year = *year;
        }
        if (after != nullptr)
        {
            Calendar::instance->after = *after;
        }
        if (before != nullptr)
        {
            Calendar::instance->before = *before;
        }
        return Calendar::instance;
    }
    else
    {
        if (!(month && year && after && before))
        {
            return nullptr;
        }

        Calendar::instance = new Calendar;
        Calendar::instance->month = *month;
        Calendar::instance->year = *year;
        Calendar::instance->after = *after;
        Calendar::instance->before = *before;
        return Calendar::instance;
    }
}
