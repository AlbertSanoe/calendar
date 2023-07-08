#include "../include/table.h"

void Preprocessor_table::insert(const std::string &ident, const std::string &value){
    this->table.emplace(ident,value);
}

bool Preprocessor_table::get(const std::string &ident, std::string &value){
    auto it=this->table.find(ident);
    if(it!=table.end()){
        value= it->second;
        return true;
    }
    else{
        return false;
    }
}

bool Preprocessor_table::contains(const std::string &ident){
    return table.find(ident)!= table.end();
}