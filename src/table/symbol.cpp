#include "../include/table.h"

void Symbol_table::insert_dt(const std::string &ident, const Date &val1, const Time &val2)
{
    this->table.emplace(ident, Symbol(val1, val2));
}

void Symbol_table::insert_bl(const std::string &ident, const bool val)
{
    this->table.emplace(ident, Symbol(val));
}

void Symbol_table::insert_pl(const std::string &ident, const Place &val)
{
    this->table.emplace(ident, Symbol(val));
}

void Symbol_table::insert_ev(const std::string &ident, const Event &val)
{
    this->table.emplace(ident, Symbol(val));
}

bool Symbol_table::get(const std::string &ident, Output_Datatype od, bool *boolean, Date *dt, Time *tm, Place *pla, Event *eve)
{
    auto it = table.find(ident);
    // Find ident in the table

    // If the ident corresponding to the Symbol is found
    if (it != table.end())
    {
        // Check if the given Output_Datatype matches the Output_Datatype of the found Symbol
        if (it->second.dt == od)
        {
            // Assign the value of the Symbol to the corresponding pointer parameter based on the Output_Datatype
            switch (od)
            {
            case dt_boolean:
                if (boolean != nullptr)
                {
                    *boolean = it->second.boolean;
                }
                break;
            case dt_date_time:
                if (dt != nullptr && tm != nullptr)
                {
                    *dt = it->second.dt_tm.date;
                    *tm = it->second.dt_tm.time;
                }
                break;
            case dt_place:
                if (pla != nullptr)
                {
                    *pla = it->second.pla;
                }
                break;
            case dt_event:
                if (eve != nullptr)
                {
                    *eve = it->second.eve;
                }
                break;
            default:
                // If the given Output_Datatype is invalid, return false
                return false;
            }

            // If reaching this point, the retrieval is successful
            return true;
        }
    }

    // If the corresponding Symbol is not found or the Output_Datatype does not match, return false
    return false;
}

Output_Datatype Symbol_table::contains(const std::string &ident)
{
    auto it = this->table.find(ident);

    if (it != this->table.end())
    {
        return it->second.dt;
    }

    return dt_unknown;
}