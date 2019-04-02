#include "PhysicalNumber.h"
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace ariel;

PhysicalNumber::PhysicalNumber(long units, int typeID){
    this->typeID = typeID;
    this->units = units;
};

int PhysicalNumber::getTypeID(){
    return this->typeID;
};

double PhysicalNumber::getUnits(){
    return this->units;
};

//adding same-types   +=
PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& other){
    if(this->typeID != other.typeID ){
        throw runtime_error("Tried to manipulate different types of data");
    }
    else{
        this->units = this->units + other.units;
    }
    return *this;
};

//unary plus
PhysicalNumber& PhysicalNumber::operator+(){
    if(units < 0){
        units = -units;
    }
    return *this;
};

//unary minus
PhysicalNumber& PhysicalNumber::operator-(){
    if(units > 0){
        units = -units;
    }
    return *this;
};