/* CSCI 261 Final Project - Double Pendulum
 *
 * Author: Vincent Marias
 *
 *  "Simulation" of a simple double pendulum (NOT a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 */

#ifndef DOUBLE_PENDULUM_PENDULUMS_H
#define DOUBLE_PENDULUM_PENDULUMS_H

#include "Pendulum.h"

class Pendulums {
public:
    // Constructors

    Pendulums();
    Pendulums( const double xStart1, const double yStart1,
               const double angle1, const double armLen1,
               const double bobMass1, const double angle2,
               const double armLen2, const double bobMass2 );

    // Getters + Setters

    Pendulum getpend1() const;
    Pendulum getpend2() const;

    // Helper functions

    void updateEverything();

private:
    static const double G;
    Pendulum _pend1;
    Pendulum _pend2;
    double _xStart1;
    double _yStart1;
    double _xStart2;
    double _yStart2;
};

#endif //DOUBLE_PENDULUM_PENDULUMS_H