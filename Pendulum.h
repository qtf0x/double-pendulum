/* CSCI 261 Final Project - Double Pendulum
 *
 * Author: Vincent Marias
 *
 *  "Simulation" of a simple double pendulum (NOT a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 */

#ifndef DOUBLE_PENDULUM_PENDULUM_H
#define DOUBLE_PENDULUM_PENDULUM_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Pendulum {
public:
    // Constructors

    Pendulum();
    Pendulum( const double xPos, const double yPos, const double armLen,
              const double bobMass );

    // Getters + Setters

    RectangleShape getarm() const;
    CircleShape getbob() const;
    void setangAcc( const double angAcc );

private:
    RectangleShape _arm;
    CircleShape _bob;
    double _xPos;
    double _yPos;
    double _angleRads;
    double _angVel;
    double _angAcc;
    double _armLen;
    double _bobMass;
};


#endif //DOUBLE_PENDULUM_PENDULUM_H