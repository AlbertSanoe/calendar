#include "../include/script.h"

ERROR_CODE PreParser::pre_define(std::ifstream &inFile, int &offset)
{
    // production rule is $define ident = val;
    // after scanning the logical token "define"

    ERROR_CODE status;
    std::string ident;
    kw_punctuation kwa;
    std::string val;

    status = this->scanner->scan_pvarident(inFile, ident, offset);

#ifdef TRY_DEBUG
    DEBUG("the ident is %s\n", ident.c_str());
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kwa, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kwa != kwa_asn)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    status = this->scanner->scan_pvarval(inFile, val, offset);

#ifdef TRY_DEBUG
    DEBUG("val is %s\n", val.c_str());
    DEBUG("the offset is %d\n", offset);
#endif

    if (status != A_FINE || offset != 1)
    {

        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kwa, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
        // DEBUG("status and offset:%d %d\n", (int)status, offset);
        // DEBUG("kwa is %d\n", (int)kwa);
#endif
        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kwa != kwd_sc)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

#ifdef TRY_DEBUG
    DEBUG("before inset to table\n");
    DEBUG("the ident is %s\n", ident.c_str());
    DEBUG("the val is %s\n", val.c_str());
#endif

    this->tbl->insert(ident, val);

    return P_FINE;
}

ERROR_CODE PreParser::pre_if(std::ifstream &inFile, int &offset, bool &result)
{
    ERROR_CODE status;
    std::string ident;
    kw_punctuation kwa;
    std::string val;

    status = this->scanner->scan_pvarident(inFile, ident, offset);

#ifdef TRY_DEBUG
    DEBUG("the ident is %s\n", ident.c_str());
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kwa, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kwa != kwa_eq && kwa != kwa_ne)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    status = this->scanner->scan_pvarval(inFile, val, offset);

#ifdef TRY_DEBUG
    DEBUG("val is %s\n", val.c_str());
    DEBUG("the offset is %d\n", offset);
#endif

    if (status != A_FINE || offset != 1)
    {

        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    std::string lval;
    bool res = this->tbl->get(ident, lval);

    if (kwa == kwa_eq)
    {
        result = (lval == val);
    }

    if (kwa == kwa_ne)
    {
        result = (lval != val);
    }
    return P_FINE;

    // without parathesis yet
}

ERROR_CODE PreParser::pre_ifdef(std::ifstream &inFile, int &offset, bool &result)
{
    ERROR_CODE status;
    std::string ident;
    kw_punctuation kwa;

    status = this->scanner->scan_pvarident(inFile, ident, offset);

#ifdef TRY_DEBUG
    DEBUG("the ident is %s\n", ident.c_str());
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    result = this->tbl->contains(ident);
    return P_FINE;
}

ERROR_CODE PreParser::pre_ifndef(std::ifstream &inFile, int &offset, bool &result)
{
    ERROR_CODE status;
    std::string ident;
    kw_punctuation kwa;

    status = this->scanner->scan_pvarident(inFile, ident, offset);

#ifdef TRY_DEBUG
    DEBUG("the ident is %s\n", ident.c_str());
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    result = !this->tbl->contains(ident);
    return P_FINE;
}

ERROR_CODE PreParser::pre_ifeq(std::ifstream &inFile, int &offset, bool &result)
{
    ERROR_CODE status;
    std::string ident;
    kw_punctuation kwa;
    std::string val;

    status = this->scanner->scan_pvarident(inFile, ident, offset);

#ifdef TRY_DEBUG
    DEBUG("the ident is %s\n", ident.c_str());
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kwa, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kwa != kwd_cm)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    status = this->scanner->scan_pvarval(inFile, val, offset);

#ifdef TRY_DEBUG
    DEBUG("val is %s\n", val.c_str());
    DEBUG("the offset is %d\n", offset);
#endif

    if (status != A_FINE || offset != 1)
    {

        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    std::string lval;
    bool res = this->tbl->get(ident, lval);

    result = (lval == val);

    return P_FINE;
}

ERROR_CODE PreParser::pre_ifne(std::ifstream &inFile, int &offset, bool &result)
{
    ERROR_CODE status;
    std::string ident;
    kw_punctuation kwa;
    std::string val;

    status = this->scanner->scan_pvarident(inFile, ident, offset);

#ifdef TRY_DEBUG
    DEBUG("the ident is %s\n", ident.c_str());
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kwa, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kwa != kwd_cm)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    status = this->scanner->scan_pvarval(inFile, val, offset);

#ifdef TRY_DEBUG
    DEBUG("val is %s\n", val.c_str());
    DEBUG("the offset is %d\n", offset);
#endif

    if (status != A_FINE || offset != 1)
    {

        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

#ifdef TRY_DEBUG
    DEBUG("before inset to table\n");
    DEBUG("the ident is %s\n", ident.c_str());
    DEBUG("the val is %s\n", val.c_str());
#endif

    std::string lval;
    bool res = this->tbl->get(ident, lval);

    result = (lval != val);

    return P_FINE;
}

ERROR_CODE PreParser::pre_else(std::ifstream &inFile, int &offset)
{
    return P_FINE;
}

ERROR_CODE PreParser::pre_BooleanStat(std::ifstream &inFile, int &offset, bool &result)
{
    ERROR_CODE status;
    std::string ident;
    kw_punctuation kwa;
    std::string val;

    status = this->scanner->scan_pvarident(inFile, ident, offset);

#ifdef TRY_DEBUG
    DEBUG("the ident is %s\n", ident.c_str());
#endif

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    status = this->scanner->scan_punctuation(inFile, kwa, offset);

    if (status != A_FINE || offset != 1)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_ERROR\n");
#endif
        return P_SCANNING_ERROR;
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    if (kwa != kwa_eq && kwa != kwa_ne)
    {
#ifdef TRY_DEBUG
        DEBUG("P_SCANNING_MISMATCHED\n");
#endif
        return P_SCANNING_MISMATCHED;
    }

    status = this->scanner->scan_pvarval(inFile, val, offset);

#ifdef TRY_DEBUG
    DEBUG("val is %s\n", val.c_str());
    DEBUG("the offset is %d\n", offset);
#endif

    if (status != A_FINE || offset != 1)
    {

        return P_SCANNING_ERROR; //
    }

    inFile.seekg(-offset, std::ios::cur);
    offset = 0; // clear the previous value

    std::string lval;
    bool res = this->tbl->get(ident, lval);

    if (kwa == kwa_eq)
    {
        result = (lval == val);
    }

    if (kwa == kwa_ne)
    {
        result = (lval != val);
    }
    return A_FINE;
}