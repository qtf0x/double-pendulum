/* CSCI 261 Final Project - Double Pendulum
 *
 * Author: Vincent Marias
 *
 *  "Simulation" of a simple double pendulum (NOT a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 */

#include "Pendulums.h"

const double Pendulums::G = 6.67430E-11;

Pendulums::Pendulums() = default;

Pendulums::Pendulums( Pendulum& pend1, Pendulum& pend2 ) {
    _pend1 = pend1;
    _pend2 = pend2;
}

Pendulum Pendulums::getpend1() const {
    return _pend1;
}

Pendulum Pendulums::getpend2() const {
    return _pend2;
}

void Pendulums::updateValues() {
    // FIXME
}