#include "../include/table.h"

void Preprocessor_table::insert(const std::string &ident, const std::string &value){
    this->table.emplace(ident,value);
}

bool Preprocessor_table::get(const std::string &ident, std::string &value){
    value="";
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
    return this->table.find(ident)!= table.end();
}

void Preprocessor_table::move(const std::string &ident){
    this->table.erase(ident);
}

bool Preprocessor_table::empty() const {
    return this->table.empty();
}

void Preprocessor_table::clear() {
    this->table.clear();
}