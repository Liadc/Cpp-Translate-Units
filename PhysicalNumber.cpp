#include "PhysicalNumber.h"
#include <stdexcept>
#include <iostream>
#include <regex>
#include <cmath>
#include <limits>
//Made by: Liad Cohen & Timor Sharabi.

using namespace std;
using namespace ariel;

PhysicalNumber::PhysicalNumber(double units, Unit typeID){
    this->typeID = typeID;
    this->units = units;
};

Unit PhysicalNumber::getTypeID(){ return this->typeID; };

double PhysicalNumber::getUnits(){ return 1.0f*this->units; };

void PhysicalNumber::setUnits(double units){ this->units = units; };

double PhysicalNumber::translateOther(const PhysicalNumber& other){
    int dif = ((int)this->typeID - (int)other.typeID);
    if(dif % 3 != 0){
        throw runtime_error("Cannot convert");
    } else{
        dif /= 3;
        double mult = 1000.0; 
        bool flag = false;
        switch((int)other.typeID % 3){
            case 0: //Length case
                if(((int)this->typeID == 0 && (int)other.typeID == 3) || ((int)this->typeID == 3 && (int)other.typeID == 0)){  
                    mult = 100.0;
                    flag = true;
                }else if(((int)this->typeID == 0 && (int)other.typeID == 6) || ((int)this->typeID == 6 && (int)other.typeID == 0)){  
                    mult = 100000.0;
                    flag = true;
                }
                if(flag){
                    if(dif<0){
                        return other.units*mult;
                        break;
                    }
                    else{
                        return other.units/mult;
                        break;
                    }
                }
                return other.units*(pow(1000.0,(-dif)));
                break;
            case 1: //Mass cases
                return other.units*(pow(1000.0,(-dif)));
                break;
            case 2: //Time case
                return other.units*(pow(60.0,(-dif)));
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

PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& other){ 
    return PhysicalNumber(1.0f*(this->units+translateOther(other)), this->typeID);
     }; //add units same world

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

ostream& ariel::operator<<(ostream& os,const  PhysicalNumber& pn){
    const char *types[] = { "cm","g","sec","m","kg","min","km","ton","hour" };
    os.precision(6);
    return os << pn.units <<"[" << types[(int)pn.typeID] << "]";
 };
            
istream& ariel::operator>>(istream& is, PhysicalNumber& pn){
    string input;
    is >> input;
    regex validate("([-])?([\\d]+([.][\\d]+)?)(\\[)((cm)|(m)|(km)|(g)|(kg)|(ton)|(sec)|(min)|(hour))(\\])");
    if(regex_match(input,validate)){
        const char *types[] = { "cm","g","sec","m","kg","min","km","ton","hour" };
        Unit unit;
        int start = input.find('[');
        int end = input.find(']');
        map<string,Unit> unitMap;
        unitMap["cm"] = Unit::CM;
        unitMap["g"] = Unit::G;
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