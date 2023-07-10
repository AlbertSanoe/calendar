#include "../include/table.h"

void Output_table::insert(const Date &dt, const Time &tm, const Place &pla, const Event &eve)
{
    this->table.emplace(Date_Time(dt, tm), Place_Event(pla, eve));
}

bool Output_table::get(const Date &dt, const Time &tm, Place &pla, Event &eve)
{
    pla = Place();
    eve = Event();
    auto it = this->table.find(Date_Time(dt, tm));
    if (it == this->table.end())
    {
        return false;
    }
    else
    {
        pla = it->second.p;
        eve = it->second.e;
        return true;
    }
}

bool Output_table::contains(const Date &dt, const Time &tm)
{
    return this->table.find(Date_Time(dt, tm)) != this->table.end();
}

void Output_table::move(const Date &dt, const Time &tm)
{
    this->table.erase(Date_Time(dt, tm));
}

bool Output_table::empty() const
{
    return this->table.empty();
}

void Output_table::clear()
{
    this->table.clear();
}

void Output_table::iter_init()
{
    this->iter = table.begin();
}

bool Output_table::iter_traverse(Date &dt, Time &tm, Place &pla, Event &eve)
{
    if (iter != table.end())
    {
        dt = iter->first.date;
        tm = iter->first.time;
        pla = iter->second.p;
        eve = iter->second.e;
        ++iter;
        return true;
    }
    return false;
}