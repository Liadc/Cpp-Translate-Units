using std::ostream, std::istream;
#include "Unit.h"

namespace ariel{

    class PhysicalNumber{
        private:
            int typeID;
            double units;
        public:
            PhysicalNumber(long units, int typeID); //constructor
            int getTypeID(); //getter
            double getUnits(); //getter
            PhysicalNumber& operator+(const PhysicalNumber& other); //diff-types adding
            PhysicalNumber& operator+=(const PhysicalNumber& other); //adding
            PhysicalNumber& operator+ (); //unary plus.
            PhysicalNumber& operator-(const PhysicalNumber& other); //diff-types minus
            PhysicalNumber& operator-=(const PhysicalNumber& other); //minus.
            PhysicalNumber& operator- (); //unary minus.
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