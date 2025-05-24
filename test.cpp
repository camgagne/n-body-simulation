// Copyright 2025 Cameron Gagne

#define BOOST_TEST_MODULE UniverseTest
#include <sstream>
#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "Universe.hpp"
#include "CelestialBody.hpp"

using NB::Universe;
using NB::CelestialBody;

BOOST_AUTO_TEST_CASE(Universe_DefaultConstructor) {
    Universe u;
    BOOST_TEST(u.size() == 0);
}

BOOST_AUTO_TEST_CASE(CelestialBody_StreamInputOperator) {
    std::istringstream input("1.0 2.0 3.0 4.0 5.0 earth.gif");
    CelestialBody body;
    input >> body;

    BOOST_TEST(body.position().x == 1.0f);
    BOOST_TEST(body.position().y == 2.0f);
}

BOOST_AUTO_TEST_CASE(CelestialBody_StreamOutputOperator) {
    CelestialBody body;
    std::ostringstream output;
    output << body;
    std::string result = output.str();
    BOOST_TEST(result.find("0.0") == std::string::npos);
}

BOOST_AUTO_TEST_CASE(Universe_NoAcceleration) {
    Universe universe;
    std::istringstream input("1\n1.0\n0.0 0.0 0.0 0.0 5.0 earth.gif");
    input >> universe;

    universe.step(1000);

    BOOST_TEST(universe[0].position().x == 0.0f);
    BOOST_TEST(universe[0].position().y == 0.0f);
}

BOOST_AUTO_TEST_CASE(Universe_Inverted) {
    Universe universe;

    std::istringstream input(
        "2\n"
        "1.50e+11\n"
        "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n"
        "0.0000e+00 0.0000e+00 0.0000e+00 0.0000e+00 1.9890e+30 sun.gif");

    input >> universe;

    for (int i = 0; i < 100; i++) {
        universe.step(50);

        auto pos = universe[0].position();
        auto vel = universe[0].velocity();

        if (pos.x > 0) {
            BOOST_TEST(vel.y > 0);
        }
        if (pos.y > 0) {
            BOOST_TEST(vel.x < 0);
        }
    }
}


BOOST_AUTO_TEST_CASE(Universe_Antigravity) {
    Universe universe;
    std::istringstream input("2\n1.0\n-1.0 0.0 0.0 0.0 5.0 earth.gif\n"
                             "1.0 0.0 0.0 0.0 5.0 mars.gif");

    input >> universe;


    double initialX1 = universe[0].position().x;
    double initialX2 = universe[1].position().x;

    universe.step(1000);

    BOOST_TEST(universe[0].position().x > initialX1);
    BOOST_TEST(universe[1].position().x < initialX2);
}


BOOST_AUTO_TEST_CASE(Universe_FixedDeltas) {
    Universe universe1;
    Universe universe2;
    std::istringstream input1("2\n1.0\n1.0 2.0 3.0 4.0 5.0 earth.gif\n"
                              "5.0 4.0 3.0 2.0 1.0 mars.gif");
    std::istringstream input2("2\n1.0\n1.0 2.0 3.0 4.0 5.0 earth.gif\n"
                              "5.0 4.0 3.0 2.0 1.0 mars.gif");
    input1 >> universe1;
    input2 >> universe2;

    universe1.step(100);
    double posAfter100 = universe1[0].position().y;

    universe2.step(500);
    double posAfter500 = universe2[0].position().y;

    BOOST_TEST(posAfter500 != posAfter100);
}

BOOST_AUTO_TEST_CASE(Universe_Leapfrog) {
    Universe universe;

    std::istringstream input("2\n1.00e+03\n0.0000e+00 0.0000e+00"
                             "0.0000e+00 0.0000e+00 1.0000e+30 earth.gif\n"
                             "1.0000e+01 0.0000e+00 0.0000e+00 0.0000e+00 1.0000e+30 mars.gif");
    input >> universe;

    universe.step(500.0);

    BOOST_TEST(universe[0].position().x == -universe[1].position().x,
               boost::test_tools::tolerance(1e-6));
    BOOST_TEST(universe[0].position().y == universe[1].position().y,
               boost::test_tools::tolerance(1e-6));
}



