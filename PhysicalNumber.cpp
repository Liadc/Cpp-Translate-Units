#include "PhysicalNumber.h"
#include <stdexcept>
#include <iostream>
#include <regex>
#include <cmath>
//Made by: Liad Cohen & Timor Sharabi.

using namespace std;
using namespace ariel;

PhysicalNumber::PhysicalNumber(double units, Unit typeID){
    this->typeID = typeID;
    this->units = units;
};

Unit PhysicalNumber::getTypeID(){ return this->typeID; };

double PhysicalNumber::getUnits(){ return this->units; };

void PhysicalNumber::setUnits(double units){ this->units = units; };

double PhysicalNumber::translateOther(const PhysicalNumber& other){
    int dif = ((int)this->typeID - (int)other.typeID);
    if(dif % 3 != 0){
        throw runtime_error("Cannot convert");
    } else{
        dif /= 3;
        switch((int)other.typeID % 3){
            case 0:case 1: //Length or Mass cases
                return other.units*(pow(1000,(-dif)));
                break;
            case 2: //Time case
                return other.units*(pow(60,(-dif)));
                break;
            }
    }
    return -1; //never gets here.
};
PhysicalNumber& PhysicalNumber::operator++(){ //prefix
    ++units;
    return *this;
};

PhysicalNumber PhysicalNumber::operator++(int){
    PhysicalNumber old(*this);
    ++units;
    return old;
};

PhysicalNumber& PhysicalNumber::operator--(){
    --units;
    return *this;
};

PhysicalNumber PhysicalNumber::operator--(int){
    PhysicalNumber old(*this);
    --units;
    return old;
};

PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& other){ return PhysicalNumber(this->units+translateOther(other), this->typeID); }; //add units same world

PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& other){ return PhysicalNumber(this->units-translateOther(other), this->typeID); }; //decrease units same world

PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& other){ //adding  +=
    setUnits(this->units + translateOther(other));
    return *this;
};

PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& other){
    setUnits(this->units - translateOther(other));
    return *this;
};

PhysicalNumber& PhysicalNumber::operator+(){ return *this; }; //unary plus

PhysicalNumber PhysicalNumber::operator-(){ return PhysicalNumber(-this->units, this->typeID); };

bool PhysicalNumber::operator>(const PhysicalNumber& other){ return this->units > translateOther(other); };

bool PhysicalNumber::operator>=(const PhysicalNumber& other){ return this->units >= translateOther(other); };

bool PhysicalNumber::operator<(const PhysicalNumber& other){ return this->units < translateOther(other); };

bool PhysicalNumber::operator<=(const PhysicalNumber& other){ return this->units <= translateOther(other); };

bool PhysicalNumber::operator==(const PhysicalNumber& other){ return this->units == translateOther(other); };

bool PhysicalNumber::operator!=(const PhysicalNumber& other){ return this->units != translateOther(other); };

ostream& ariel::operator<<(ostream& os, PhysicalNumber pn){
    const char *types[] = { "cm","h","sec","m","kg","min","km","ton","hour" };
    return os << pn.getUnits() <<"[" << types[(int)pn.typeID] << "]";
 };
            
istream& ariel::operator>>(istream& is, PhysicalNumber& pn){
    string input;
    is >> input;
    regex validate("([-])?([\\d]+([.][\\d]+)?)(\\[)((cm)|(m)|(km)|(g)|(kg)|(ton)|(sec)|(min)|(hour))(\\])");
    if(regex_match(input,validate)){
        const char *types[] = { "cm","h","sec","m","kg","min","km","ton","hour" };
        Unit unit;
        int start = input.find('[');
        int end = input.find(']');
        map<string,Unit> unitMap;
        unitMap["cm"] = Unit::CM;
        unitMap["h"] = Unit::HOUR;
        unitMap["sec"] = Unit::SEC;
        unitMap["m"] = Unit::M;
        unitMap["kg"] = Unit::KG;
        unitMap["min"] = Unit::MIN;
        unitMap["km"] = Unit::KM;
        unitMap["ton"] = Unit::TON;
        unitMap["hour"] = Unit::HOUR;
 
        double value = stod(input.substr(0,start));
        string type = input.substr(start+1,end-start-1);
        unit = unitMap.find(type)->second;

        pn.units = value;
        pn.typeID = unit;

    }
    else{
        is.setstate(ios::failbit);
    }
    return is;
};