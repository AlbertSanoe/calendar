#include "../include/script.h"

ERROR_CODE CmdParser::cmd_set(std::ifstream &inFile, int &offset)
{
    ERROR_CODE status;

    kw_punctuation kw;

    Year yy;
    Month mm;
    Day dd;

    Hour hr;
    Minute min;
    Second sec;

    Place pla;
    Event eve;

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_lp) // (
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_year(inFile, yy, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

#ifdef TRY_DEBUG
    DEBUG("the year is %d\n", (int)yy);
#endif

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kw, offset); // "-"/"."

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kw != kwd_dot && kw != kwd_hyp)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED; //
    }

    // month
    status = this->scanner->scan_month(inFile, mm, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the month is %d\n", (int)mm);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset); // "-"/"."

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kw != kwd_dot && kw != kwd_hyp)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED; //
    }

    // day
    status = this->scanner->scan_day(inFile, dd, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the day is %d\n", (int)dd);
#endif

    // hour
    status = this->scanner->scan_hour(inFile, hr, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the hour is %d\n", (int)hr);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_col)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be :

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    // minute
    status = this->scanner->scan_minute(inFile, min, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the minute is %d\n", (int)min);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_col)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be :

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value
    // second
    status = this->scanner->scan_second(inFile, sec, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the second is %d\n", (int)sec);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_cm)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be ,

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    std::string pla_str;

    status = this->scanner->scan_pvarval(inFile, pla_str, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

#ifdef TRY_DEBUG
    DEBUG("Place: %s\n", pla_str.c_str());
#endif

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    pla = Place(pla_str);

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_cm)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be ,

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    std::string eve_str;

    status = this->scanner->scan_pvarval(inFile, eve_str, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

#ifdef TRY_DEBUG
    DEBUG("Event: %s\n", eve_str.c_str());
#endif

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_rp) // (
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_sc) // ;
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    eve = Event(eve_str);

    Date date = Date(yy, mm, dd);

    Time time = Time(hr, min, sec);

    this->tbl->insert(date, time, pla, eve);

    return P_FINE;
}

ERROR_CODE CmdParser::cmd_findset(std::ifstream &inFile, int &offset)
{
    ERROR_CODE status;

    kw_punctuation kw;

    Year yy;
    Month mm;
    Day dd;

    Hour hr;
    Minute min;
    Second sec;

    Place pla;
    Event eve;

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_lp) // (
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_year(inFile, yy, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

#ifdef TRY_DEBUG
    DEBUG("the year is %d\n", (int)yy);
#endif

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kw, offset); // "-"/"."

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kw != kwd_dot && kw != kwd_hyp)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED; //
    }

    // month
    status = this->scanner->scan_month(inFile, mm, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the month is %d\n", (int)mm);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset); // "-"/"."

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kw != kwd_dot && kw != kwd_hyp)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED; //
    }

    // day
    status = this->scanner->scan_day(inFile, dd, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the day is %d\n", (int)dd);
#endif

    // hour
    status = this->scanner->scan_hour(inFile, hr, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the hour is %d\n", (int)hr);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_col)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be :

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    // minute
    status = this->scanner->scan_minute(inFile, min, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the minute is %d\n", (int)min);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_col)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be :

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value
    // second
    status = this->scanner->scan_second(inFile, sec, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the second is %d\n", (int)sec);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_cm)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be ,

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    std::string pla_str;

    status = this->scanner->scan_pvarval(inFile, pla_str, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

#ifdef TRY_DEBUG
    DEBUG("Place: %s\n", pla_str.c_str());
#endif

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    pla = Place(pla_str);

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_cm)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be ,

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    std::string eve_str;

    status = this->scanner->scan_pvarval(inFile, eve_str, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

#ifdef TRY_DEBUG
    DEBUG("Event: %s\n", eve_str.c_str());
#endif

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_rp) // (
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_sc) // ;
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    eve = Event(eve_str);

    Date date = Date(yy, mm, dd);

    Time time = Time(hr, min, sec);

    if (!this->tbl->contains(date, time))
    {
        this->tbl->insert(date, time, pla, eve);
    }

    return P_FINE;
}

ERROR_CODE CmdParser::cmd_clear(std::ifstream &inFile, int &offset)
{
    ERROR_CODE status;
    kw_punctuation kw;

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_lp) // (
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_rp) // )
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

        status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_sc) // ;
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    this->tbl->clear();

    return P_FINE;

}

ERROR_CODE CmdParser::cmd_check(std::ifstream &inFile, int &offset, bool &result)
{
    ERROR_CODE status;

    kw_punctuation kw;

    Year yy;
    Month mm;
    Day dd;

    Hour hr;
    Minute min;
    Second sec;

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_lp) // (
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_year(inFile, yy, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

#ifdef TRY_DEBUG
    DEBUG("the year is %d\n", (int)yy);
#endif

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kw, offset); // "-"/"."

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kw != kwd_dot && kw != kwd_hyp)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED; //
    }

    // month
    status = this->scanner->scan_month(inFile, mm, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the month is %d\n", (int)mm);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset); // "-"/"."

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kw != kwd_dot && kw != kwd_hyp)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED; //
    }

    // day
    status = this->scanner->scan_day(inFile, dd, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the day is %d\n", (int)dd);
#endif

    // hour
    status = this->scanner->scan_hour(inFile, hr, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the hour is %d\n", (int)hr);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_col)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be :

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    // minute
    status = this->scanner->scan_minute(inFile, min, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the minute is %d\n", (int)min);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_col)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be :

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value
    // second
    status = this->scanner->scan_second(inFile, sec, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the second is %d\n", (int)sec);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_rp) // )
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_sc) // ;
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    Date date = Date(yy, mm, dd);

    Time time = Time(hr, min, sec);

    result = this->tbl->contains(date, time);

    return P_FINE;
}

ERROR_CODE CmdParser::cmd_get(std::ifstream &inFile, int &offset, Place *p, Event *e)
{
    ERROR_CODE status;

    kw_punctuation kw;

    Year yy;
    Month mm;
    Day dd;

    Hour hr;
    Minute min;
    Second sec;

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_lp) // (
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_year(inFile, yy, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

#ifdef TRY_DEBUG
    DEBUG("the year is %d\n", (int)yy);
#endif

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kw, offset); // "-"/"."

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kw != kwd_dot && kw != kwd_hyp)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED; //
    }

    // month
    status = this->scanner->scan_month(inFile, mm, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the month is %d\n", (int)mm);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset); // "-"/"."

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kw != kwd_dot && kw != kwd_hyp)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED; //
    }

    // day
    status = this->scanner->scan_day(inFile, dd, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the day is %d\n", (int)dd);
#endif

    // hour
    status = this->scanner->scan_hour(inFile, hr, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the hour is %d\n", (int)hr);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_col)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be :

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    // minute
    status = this->scanner->scan_minute(inFile, min, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("status and offset: %d %d\n", (int)status, offset);
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the minute is %d\n", (int)min);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    if (kw != kwd_col)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    } // it must be :

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value
    // second
    status = this->scanner->scan_second(inFile, sec, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("the second is %d\n", (int)sec);
#endif

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_rp) // )
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kw, offset);

#ifdef TRY_DEBUG
    DEBUG("the kw is %d\n", (int)kw);
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    if (kw != kwd_sc) // ;
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    Date date = Date(yy, mm, dd);

    Time time = Time(hr, min, sec);
    Place pla;
    Event eve;
    this->tbl->get(date, time, pla, eve);

    if (p != nullptr)
    {
        *p = pla;
    }
    if (e != nullptr)
    {
        *e = eve;
    }
    return P_FINE;
}

