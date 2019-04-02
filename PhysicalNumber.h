#include "Unit.h"

using std::ostream, std::istream;

namespace ariel{

    class PhysicalNumber{
        private:
            int typeID;
            double units;
        public:
            PhysicalNumber(long units, int typeID); //constructor
            int getTypeID(); //getter
            double getUnits(); //getter
            PhysicalNumber& operator+(const PhysicalNumber& other);
            PhysicalNumber& operator+=(const PhysicalNumber& other);
            PhysicalNumber& operator+ ();
            PhysicalNumber& operator-(const PhysicalNumber& other);
            PhysicalNumber& operator-=(const PhysicalNumber& other);
            PhysicalNumber& operator- ();
            PhysicalNumber& operator++ ();
            PhysicalNumber& operator-- ();
            bool operator>(const PhysicalNumber& other);
            bool operator>=(const PhysicalNumber& other);
            bool operator== (const PhysicalNumber& other);
            bool operator!= (const PhysicalNumber& other);
            bool operator<(const PhysicalNumber& other);
            bool operator<=(const PhysicalNumber& other);
            PhysicalNumber& operator++ ();
            PhysicalNumber& operator-- ();
            friend ostream& operator<<(ostream& os, PhysicalNumber& pn);
            friend istream& operator>> (istream& is, PhysicalNumber& pn);
    };
};