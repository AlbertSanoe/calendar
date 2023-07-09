#include "../include/plan.h"

const char *arrangement_header = "#Arrangement#";

Place::Place(std::string pla) : place_name(pla) {}

Place::Place(const Place &other){
    this->place_name=other.place_name;
}

Event::Event(std::string eve) : event_name(eve) {}

Event::Event(const Event &other){
    this->event_name=other.event_name;
}