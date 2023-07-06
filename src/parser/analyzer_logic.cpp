#include <string>
#include <map>
#include "../include/analyzer.h"

enum kw_logic
{
    kwl_unknown,
    kwl_if,
    kwl_ifdef,
    kwl_ifeq,
    kwl_ifndef,
    kwl_ifneq,
    kwl_else,
    kwl_let
};

const std::map<std::string,kw_logic>kwl_map ={
    {"if",kwl_if},
    {"ifdef",kwl_ifdef},
    {"ifeq",kwl_ifeq},
    {"ifndef",kwl_ifndef},
    {"ifneq",kwl_ifneq},
    {"else",kwl_else},
    {"let",kwl_let}
};

static kw_logic __str_to_enum(const std::string& keyword){
    auto token= kwl_map.find(keyword);
    if(token!=kwl_map.end()){
        return token->second;
    }
    return kwl_unknown;
}

