#ifndef TABLE_H
#define TABLE_H


#include <unordered_map>

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
    std::string get(const std::string &ident);
    bool contains(const std::string &ident);
};

class Output_table
{
private:
    struct Place_Event
    {
        place p;
        event e;

        Place_Event(const place &pp, const event &ee) : p(pp), e(ee) {}
    };

    std::unordered_map<Time,Place_Event> table; // change to be map

};

class Symbol_table
{
    private:
    enum datatype{
        
    };
};

#endif