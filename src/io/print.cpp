#include "../include/print.h"

std::ostream &operator<<(std::ostream &out, const Date &obj)
{
    out << obj.year << "."
        << std::setw(2) << std::setfill('0') << obj.month << "."
        << std::setw(2) << std::setfill('0') << obj.day << " "
        << obj.get_weekday_str();
    return out;
}

std::ostream &operator<<(std::ostream &out, const Time &obj)
{
    out << std::setw(2) << std::setfill('0') << obj.hour << ":"
        << std::setw(2) << std::setfill('0') << obj.minute << ":"
        << std::setw(2) << std::setfill('0') << obj.second;
    return out;
    return out;
}

std::ostream &operator<<(std::ostream &out, const std::vector<Monthline> &cal)
{
    size_t size = cal.size();
    for (size_t row = 0; row < size; ++row)
    {
        if (cal[row].yearline[28] != ' ') // YEAR_CENTER_POS
        {
            out << cal[row].yearline << std::endl;
        }
        // out << cal[row].yearline << std::endl;
        out << cal[row].monthline << std::endl;
        out << cal[row].weekline << std::endl;
        out << cal[row].dayline[0] << std::endl;
        out << cal[row].dayline[1] << std::endl;
        out << cal[row].dayline[2] << std::endl;
        out << cal[row].dayline[3] << std::endl;
        out << cal[row].dayline[4];
        // PREV_INDEX
        if (cal[row].dayline[5][0] != ' ' || cal[row].dayline[5][22] != ' ' || cal[row].dayline[5][44] != ' ')
        {
            out << std::endl;
            out << cal[row].dayline[5];
        }

        if (row != size - 1)
        {
            out << std::endl
                << std::endl;
        }
        else
        {
            break;
        }
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, Place place)
{
    out << place.place_name;
    return out;
}

std::ostream &operator<<(std::ostream &out, Event event_name)
{
    out << event_name.event_name;
    return out;
}

void print_arragement_header(const Date &date, const Time &time)
{
    std::cout << arrangement_header << ":\t";
    std::cout << date << " " << time << std::endl;
}
