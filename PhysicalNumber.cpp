#include "PhysicalNumber.h"
#include <stdexcept>
#include <iostream>
#include <cmath>


using namespace std;
using namespace ariel;

PhysicalNumber::PhysicalNumber(double units, Unit typeID){
    this->typeID = typeID;
    this->units = units;
};

Unit PhysicalNumber::getTypeID(){
    return this->typeID;
};

double PhysicalNumber::getUnits(){
    return this->units;
};

PhysicalNumber& PhysicalNumber::translateUnit(const PhysicalNumber& other,bool opCode){
    if(this->typeID == other.typeID){ //same types. i don't think its even needed.
        return *this;
    }
    int dif = ((int)this->typeID - (int)other.typeID);
    if(dif % 3 != 0){
        throw runtime_error("Cannot convert");
    } else{
        dif /= 3;
        switch((int)other.typeID % 3){
            case 0:case 1: //Length or Mass cases
                if(opCode){ //opCode 1 for +
                    this->units += other.units*(pow(1000,(-dif)));
                }else{ //opCode 0 for -
                    this->units -= other.units*(pow(1000,(-dif)));
                }
                break;
            case 2: //Time case
                if(opCode){ //opCode 1 for +
                    this->units += other.units*(pow(60,(-dif)));
                }else{//opCode 0 for -
                    this->units -= other.units*(pow(60,(-dif)));
                }
                break;
            }
    }
    return *this;
};

PhysicalNumber& PhysicalNumber::operator+(const PhysicalNumber& other){ //add units same world
    Unit typeTemp(this->getTypeID());
    if(this == &other){
        double unitsTemp = this->getUnits()+this->getUnits();
        PhysicalNumber a(unitsTemp,typeTemp);
        return a;
    }
    double unitsTemp = this->getUnits();
    PhysicalNumber a(unitsTemp,typeTemp);
    return a.translateUnit(other,1);
};

PhysicalNumber& PhysicalNumber::operator-(const PhysicalNumber& other){ //decrease units same world
    Unit typeTemp(this->getTypeID());
    if(this == &other){
        double unitsTemp = this->getUnits()-this->getUnits();
        PhysicalNumber a(unitsTemp,typeTemp);
        return a;
    }
    double unitsTemp = this->getUnits();
    PhysicalNumber a(unitsTemp,typeTemp);
    return a.translateUnit(other,0);
};

//adding same-types   +=
PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& other){
    *this = *this+other;
    return *this;
};

PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& other){
    *this = *this-other;
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

bool PhysicalNumber::operator>(const PhysicalNumber& other){
    PhysicalNumber temp1(0,other.typeID);
    temp1 = (temp1-other);
    cout << temp1.getUnits() <<endl;
    temp1 = temp1- *this;
    cout << temp1.getUnits() <<endl;
    return temp1.getUnits() < 0;
 };

bool PhysicalNumber::operator>=(const PhysicalNumber& other){
        PhysicalNumber temp1(0,other.typeID);
    temp1+= other;
    temp1-= *this;
    return temp1.getUnits() <= 0;
 };

bool PhysicalNumber::operator<(const PhysicalNumber& other){
    PhysicalNumber temp1(0,other.typeID);
    temp1+= other;
    temp1-= *this;
    return temp1.getUnits() > 0;
};

bool PhysicalNumber::operator<=(const PhysicalNumber& other){
    PhysicalNumber temp1(0,other.typeID);
    temp1+= other;
    temp1-= *this;
    return temp1.getUnits() >= 0;
 };

bool PhysicalNumber::operator==(const PhysicalNumber& other){
    PhysicalNumber temp1(0,other.typeID);
    temp1+= other;
    temp1-= *this;
    return temp1.getUnits() == 0;
 };

bool PhysicalNumber::operator!=(const PhysicalNumber& other){
    PhysicalNumber temp1(0,other.typeID);
    temp1+= other;
    temp1-= *this;
    return temp1.getUnits() != 0;
 };

ostream& ariel::operator<<(ostream& os, PhysicalNumber pn){
    const char *types[] = { "cm","h","sec","m","kg","min","km","ton","hour" };
    return os << pn.getUnits() <<"[" << types[(int)pn.typeID] << "]";
 };
            
istream& ariel::operator>>(istream& is, PhysicalNumber pn){
    PhysicalNumber newInput
    is.getline('[')
    return is;
};


 