#include "../include/print.h"

std::ostream &operator<<(std::ostream &out, const Date &obj)
{
    out << "{" << obj.year << "." << obj.month << "." << obj.day << " " << obj.weekday << "}";
    return out;
}

std::ostream &operator<<(std::ostream &out, const Time &obj)
{
    out << "{" << obj.hour << "-" << obj.minute << "-" << obj.second << "}";
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
        //out << cal[row].yearline << std::endl;
        out << cal[row].monthline << std::endl;
        out << cal[row].weekline << std::endl;
        out << cal[row].dayline[0] << std::endl;
        out << cal[row].dayline[1] << std::endl;
        out << cal[row].dayline[2] << std::endl;
        out << cal[row].dayline[3] << std::endl;
        out << cal[row].dayline[4];
        //PREV_INDEX
        if (cal[row].dayline[5][0] != ' ' || cal[row].dayline[5][22] != ' ' || cal[row].dayline[5][44] != ' ')
        {
            out<<std::endl;
            out << cal[row].dayline[5];
        }

        if (row != size - 1)
        {
            out <<std::endl<<std::endl;
        }
        else{
            break;
        }
        
    }
    return out;
}
