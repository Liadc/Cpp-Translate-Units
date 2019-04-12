/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {



    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);

    //Our Bases:
    PhysicalNumber e(20, Unit::KM);
    PhysicalNumber f(30, Unit::M);
    PhysicalNumber g(20, Unit::HOUR);
    PhysicalNumber h(15, Unit::MIN);
    PhysicalNumber i(15, Unit::CM);
    PhysicalNumber j(10, Unit::M);
    PhysicalNumber k(1, Unit::SEC);
    PhysicalNumber l(3, Unit::TON);
    
    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(a, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(b+a, "2300[m]")
    .CHECK_OUTPUT((a+=b), "2.3[km]")
    .CHECK_OUTPUT(a, "2.3[km]")
    .CHECK_OUTPUT(a+a, "4.6[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "30[min]")
    .CHECK_OUTPUT(d+c, "150[min]")


    .setname("Incompatible dimensions")
    .CHECK_THROWS(a+c)
    .CHECK_THROWS(a+d)
    .CHECK_THROWS(b+c)
    .CHECK_THROWS(b+d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

    // YOUR TESTS - INSERT AS MANY AS YOU WANT
    //Our Tests:



    .setname("Our Tests:")
    .CHECK_OUTPUT(f+e, "20030[m]")
    .CHECK_OUTPUT((e-f), "19.97[km]")
    .CHECK_OUTPUT(e, "20[km]")
    .CHECK_OUTPUT(g+h, "20.25[hour]")
    .CHECK_OUTPUT(f-f, "0[m]")
    .CHECK_OUTPUT(g, "20[hour]")
    .CHECK_OUTPUT(h, "15[min]")
    .CHECK_OUTPUT(h+g, "1215[min]")
    .CHECK_OUTPUT(i+f, "30015[cm]")
    .CHECK_OUTPUT(i+e, "2e+07[cm]")
    .CHECK_OUTPUT(e+i, "20[km]")
    .CHECK_OUTPUT(e+i+f, "20.03[km]")
    .CHECK_OUTPUT(k+c, "7201[sec]")
    .CHECK_OUTPUT(k+k+k+k+k+k+k+k+k+k+k+k+k, "13[sec]")
    // .CHECK_OUTPUT((e++)++, "22[km]")  //does not compile on badkan website.
    
    

    //Check Throws
    .CHECK_THROWS(e+g)
    .CHECK_THROWS(e-g)
    .CHECK_THROWS(j-h)
    .CHECK_THROWS(f+h)
    .CHECK_THROWS(h+e)
    .CHECK_THROWS(i+g)
    .CHECK_THROWS(f-k)
    .CHECK_THROWS(i+h)
    .CHECK_THROWS(j-g)
    .CHECK_THROWS(h+j)
    .CHECK_THROWS(e-k)
    .CHECK_THROWS(h-i)
    .CHECK_THROWS(f+g)
    .CHECK_THROWS(a-g)
    .CHECK_THROWS(a-h)
    .CHECK_THROWS(k+e)
    .CHECK_THROWS(k+f)

      .CHECK_THROWS(istringstream("60[sc]") >> a)
      .CHECK_THROWS(istringstream("60") >> a)
      .CHECK_THROWS(istringstream("60[x]") >> a)

    .CHECK_OK(istringstream("60[sec]") >> k)
    .CHECK_OK(istringstream("1[ton]") >> l)
    .CHECK_OUTPUT((k += PhysicalNumber(1, Unit::HOUR)), "3660[sec]")
    .CHECK_OUTPUT((l += PhysicalNumber(1, Unit::TON)), "2[ton]")
    .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}