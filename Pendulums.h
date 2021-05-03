/* CSCI 261 Final Project - Double Pendulum
 *
 *  Simulation of a simple double pendulum (NOT a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 *
 *  MIT License
 *  Copyright (c) 2021 Vincent Marias
 */

#ifndef DOUBLE_PENDULUM_PENDULUMS_H
#define DOUBLE_PENDULUM_PENDULUMS_H

#include "Pendulum.h"

class Pendulums {
public:
    // Constructors

    Pendulums();
    Pendulums( const unsigned int windowWidth, const unsigned int windowHeight,
               const bool lineTracing, const Color traceColor, const double traceRadius,
               const double xStart1, const double yStart1,
               const double angle1, const double armLen1,
               const double bobMass1, const double angle2,
               const double armLen2, const double bobMass2, const double gravity,
               const unsigned int antiAliasing, const unsigned int pointCount );

    // Getters + Setters

    Pendulum getpend1() const;
    Pendulum getpend2() const;
    RenderTexture& getcanvas();
    Vector2f getpend2XandY() const;

    // Helper functions

    void updateEverything();
    void drawEverything( RenderWindow& window ) const;

private:
    double G;
    Pendulum _pend1;
    Pendulum _pend2;
    double _xStart1;
    double _yStart1;
    double _xStart2;
    double _yStart2;
    RenderTexture _canvas;
    Sprite _canvasSprite;
    CircleShape _traceCircle;
    VertexArray _traceLine;
    Vector2f _lastPos;
    bool _lineTracing;

    void updateXandY();
};

#endif //DOUBLE_PENDULUM_PENDULUMS_H