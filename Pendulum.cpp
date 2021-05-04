/* CSCI 261 Final Project - Double Pendulum
 *
 *  Simulation of a simple double pendulum (not a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 *
 *  MIT License
 *  Copyright (c) 2021 Vincent Marias
 */

#include "Pendulum.h"                           // include class header

#include <cmath>                                // for constants, math functions

Pendulum::Pendulum() {
    // Data member definitions
    _angleRads = M_PI_2;                        // default angle
    _armLen = 250;                              // default arm length
    _bobMass = 20;                              // default bob mass
    _angVel = 0.0;                              // default angular velocity

    // Bob stuff
    _bob.setPointCount( 100 );                  // default circle point count
    _bob.setRadius( _bobMass );                 // default bob radius
    _bob.setFillColor( Color::White );          // default bob color
    _bob.setOrigin( _bobMass, _bobMass );       // origin = center, not corner

    // Arm stuff
    _arm.setPrimitiveType( Lines );             // define arm as a line
    _arm.resize( 2 );                           // lines have two points
    _arm[0].color = Color::White;               // default arm color
    _arm[1].color = Color::White;
}

Pendulum::Pendulum( const double angleRads, const double armLen,
                    const double bobMass, const unsigned int pointCount ) {
    // Data member definitions
    _angleRads = angleRads;                     // set angle
    _armLen = armLen;                           // set arm length
    _bobMass = bobMass;                         // set bob mass
    _angVel = 0.0;                              // set angular velocity

    // Bob stuff
    _bob.setPointCount( pointCount );           // set circle point count
    _bob.setRadius( _bobMass );                 // set bob radius
    _bob.setFillColor( Color::White );          // set bob color
    _bob.setOrigin( _bobMass, _bobMass );       // origin = center, not corner

    // Arm stuff
    _arm.setPrimitiveType( Lines );             // define arm as a line
    _arm.resize( 2 );                           // lines have two points
    _arm[0].color = Color::White;               // set arm color
    _arm[1].color = Color::White;
}

VertexArray Pendulum::getarm() const {
    return _arm;
}

CircleShape Pendulum::getbob() const {
    return _bob;
}

double Pendulum::getxPos() const {
    return _xPos;
}

double Pendulum::getyPos() const {
    return _yPos;
}

double Pendulum::getangleRads() const {
    return _angleRads;
}

double Pendulum::getangVel() const {
    return _angVel;
}

double Pendulum::getarmLen() const {
    return _armLen;
}

double Pendulum::getbobMass() const {
    return _bobMass;
}

void Pendulum::setxPos( const double xPos ) {
    _xPos = xPos;
}

void Pendulum::setyPos( const double yPos ) {
    _yPos = yPos;
}

void Pendulum::setangAcc( const double angAcc ) {
    _angAcc = angAcc;
}

void Pendulum::setarmPos( const double armPosx, const double armPosy ) {
    // set first point at new location
    _arm[0].position = Vector2f( armPosx, armPosy );
    // set second point at current location (soon to be previous location)
    _arm[1].position = Vector2f( _xPos, _yPos );
}

void Pendulum::updateValues() {
    // angular acceleration = change in angular velocity
    _angVel += _angAcc;
    // angular velocity = change in angle
    _angleRads += _angVel;

    _bob.setPosition( _xPos, _yPos );           // move bob to new location
}