#ifndef TABLE_H
#define TABLE_H

#include <unordered_map>
#include <map>

#include "macro.h"
#include "cal.h"
#include "plan.h"

#define LOCAL_DEBUG 1
#if (GLOBAL_DEBUG == 1) && (LOCAL_DEBUG == 1)
#define TRY_DEBUG
#endif

class Preprocessor_table
{
private:
    std::unordered_map<std::string, std::string> table;

public:
    void insert(const std::string &ident, const std::string &value);
    bool get(const std::string &ident, std::string &value);
    bool contains(const std::string &ident);
};

class Output_table
{
private:
    struct Place_Event
    {
        Place p;
        Event e;
        Place_Event(const Place &pp, const Event &ee) : p(pp), e(ee) {}
    };

    struct Date_Time
    {
        Date date;
        Time time;
        Date_Time(const Date &dd, const Time &tt) : date(dd), time(tt) {}
        bool operator<(const Date_Time &other) const
        {
            if (this->date != other.date)
            {
                return this->date < other.date;
            }

            return this->time < other.time;
        }

        bool operator==(const Date_Time &other) const
        {
            if (this->date != other.date)
            {
                return false;
            }
            else
            {
                return this->time == other.time;
            }
        }

        bool operator!=(const Date_Time &other) const
        {
            if (this->date != other.date)
            {
                return true;
            }
            else
            {
                return this->time != other.time;
            }
        }
    };

    std::map<Date_Time, Place_Event> table;

public:
    void insert(const Date &dt, const Time &tm, const Place &pla, const Event &eve);
    bool get(const Date &dt, const Time &tm, Place &pla, Event &eve);
    bool contains(const Date &dt, const Time &tm);
};

enum Output_Datatype
{
    dt_unknown,
    dt_boolean,
    dt_date_time,
    dt_place,
    dt_event
};

class Symbol_table
{
private:
    struct Date_Time
    {
        Date date;
        Time time;
        Date_Time(const Date &dd, const Time &tt) : date(dd), time(tt) {}
        bool operator<(Date_Time &other) const
        {
            if (this->date != other.date)
            {
                return this->date < other.date;
            }

            return this->time < other.time;
        }

        bool operator==(Date_Time &other) const
        {
            if (this->date != other.date)
            {
                return false;
            }
            else
            {
                return this->time == other.time;
            }
        }

        bool operator!=(Date_Time &other) const
        {
            if (this->date != other.date)
            {
                return true;
            }
            else
            {
                return this->time != other.time;
            }
        }
    };

    struct Symbol
    {
        Output_Datatype dt;
        union
        {
            bool boolean;
            Date_Time dt_tm;
            Place pla;
            Event eve;
        };

        Symbol(bool val) : dt(dt_boolean), boolean(val) {}
        Symbol(const Date &date, const Time &time) : dt(dt_date_time), dt_tm(Date_Time(date, time)) {}
        Symbol(const Place &p) : dt(dt_place), pla(p) {}
        Symbol(const Event &e) : dt(dt_event), eve(e) {}
        ~Symbol()
        {
            if (dt == dt_place)
            {
                pla.~Place();
            }
            else if (dt == dt_event)
            {
                eve.~Event();
            }
        }
        // Copy constructor
        Symbol(const Symbol &other) : dt(other.dt)
        {
            switch (dt)
            {
            case dt_boolean:
                boolean = other.boolean;
                break;
            case dt_date_time:
                new (&dt_tm) Date_Time(other.dt_tm);
                break;
            case dt_place:
                new (&pla) Place(other.pla);
                break;
            case dt_event:
                new (&eve) Event(other.eve);
                break;
            }
        }

        // Copy assignment operator
        Symbol &operator=(const Symbol &other)
        {
            if (this == &other)
                return *this;

            this->~Symbol();

            dt = other.dt;
            switch (dt)
            {
            case dt_boolean:
                boolean = other.boolean;
                break;
            case dt_date_time:
                new (&dt_tm) Date_Time(other.dt_tm);
                break;
            case dt_place:
                new (&pla) Place(other.pla);
                break;
            case dt_event:
                new (&eve) Event(other.eve);
                break;
            }

            return *this;
        }
    };

    std::unordered_map<std::string, Symbol> table;

public:
    void insert_dt(const std::string &ident, const Date &val1, const Time &val2);
    void insert_bl(const std::string &ident, const bool val);
    void insert_pl(const std::string &ident, const Place &val);
    void insert_ev(const std::string &ident, const Event &val);

    bool get(const std::string &ident, Output_Datatype od, bool* boolean, Date *dt, Time *tm, Place *pla, Event *eve);
    Output_Datatype contains(const std::string &ident);
};

#endif