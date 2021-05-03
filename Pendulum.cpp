/* CSCI 261 Final Project - Double Pendulum
 *
 * Author: Vincent Marias
 *
 *  Simulation of a simple double pendulum (NOT a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 */

#include "Pendulum.h"

Pendulum::Pendulum() {
    // FIXME: Implement default constructor
}

Pendulum::Pendulum( const double angleRads, const double armLen,
                    const double bobMass ) {
    _angleRads = angleRads;
    _armLen = armLen;
    _bobMass = bobMass;

    _angVel = 0.0;

    _bob.setPointCount( 100 );
    _bob.setRadius( _bobMass );
    _bob.setFillColor( Color::White );
    _bob.setOrigin( _bobMass, _bobMass );

    _arm.setPrimitiveType( Lines );
    _arm.resize( 2 );
    _arm[0].color = Color::White;
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
    _arm[0].position = Vector2f( armPosx, armPosy );
    _arm[1].position = Vector2f( _xPos, _yPos );
}

void Pendulum::updateValues() {
    _angVel += _angAcc;
    _angleRads += _angVel;

    // FIXME: circle position at top left!!
    _bob.setPosition( _xPos, _yPos );
}