#include "../include/table.h"

void Output_table::insert(const Date &dt, const Time &tm, const Place &pla, const Event &eve)
{
    this->table.emplace(Date_Time(dt, tm), Place_Event(pla, eve));
}

bool Output_table::get(const Date &dt, const Time &tm, Place &pla, Event &eve)
{
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
    return table.find(Date_Time(dt, tm)) != table.end();
}