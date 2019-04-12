#pragma once
#include "Unit.h"
#include <iostream>


namespace ariel{

    class PhysicalNumber{
        private:
            Unit typeID;
            double units;
        public:
            PhysicalNumber(double units, Unit type); //constructor
            Unit getTypeID(); //getter
            double getUnits(); //getter
            void setUnits(double units);
            PhysicalNumber operator+(const PhysicalNumber& other); //diff-types adding
            PhysicalNumber& operator+=(const PhysicalNumber& other); //adding
            PhysicalNumber& operator+ (); //unary plus.
            PhysicalNumber operator-(const PhysicalNumber& other); //diff-types minus
            PhysicalNumber& operator-=(const PhysicalNumber& other); //minus.
            PhysicalNumber operator- (); //unary minus.
            PhysicalNumber& operator++ ();
            PhysicalNumber& operator-- ();
            PhysicalNumber operator++ (int);
            PhysicalNumber operator-- (int);
            bool operator>(const PhysicalNumber& other);
            bool operator>=(const PhysicalNumber& other);
            bool operator== (const PhysicalNumber& other);
            bool operator!= (const PhysicalNumber& other);
            bool operator<(const PhysicalNumber& other);
            bool operator<=(const PhysicalNumber& other);
            friend std::ostream& operator<<(std::ostream& os, PhysicalNumber pn);
            friend std::istream& operator>>(std::istream& is, PhysicalNumber& pn);
        private:
            double translateOther(const PhysicalNumber& other); //returns the other.units with type of This.type
    };
};