/* CSCI 261 Final Project - Double Pendulum
 *
 * Author: Vincent Marias
 *
 *  "Simulation" of a simple double pendulum (NOT a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 */

#include "Pendulum.h"

Pendulum::Pendulum() {
    // FIXME
}

Pendulum::Pendulum( const double xPos, const double yPos, const double armLen,
                    const double bobMass ) {
    _xPos = xPos;
    _yPos = yPos;
    _armLen = armLen;
    _bobMass = bobMass;
    // FIXME
}

RectangleShape Pendulum::getarm() const {
    return _arm;
}

CircleShape Pendulum::getbob() const {
    return _bob;
}

void Pendulum::setangAcc( const double angAcc ) {
    _angAcc = angAcc;
    // FIXME
}