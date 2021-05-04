/* CSCI 261 Final Project - Double Pendulum
 *
 *  Simulation of a simple double pendulum (not a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 *
 *  MIT License
 *  Copyright (c) 2021 Vincent Marias
 */

#include "Pendulums.h"

#include <cmath>                                // for sin(), cos()

Pendulums::Pendulums() {
    // Data member definitions
    G = 0.5;                                    // default G
    _pend1 = Pendulum();                        // construct pendulums
    _pend2 = Pendulum();
    _xStart1 = 960;                             // default pin x-position
    _yStart1 = 540;                             // default pin y-position

    // Canvas setup
    ContextSettings settings;
    settings.antialiasingLevel = 16;            // set anti-aliasing for canvas
    _canvas.create( 1920, 1080, settings );     // default canvas is 1080p
    _canvas.clear( Color::Black );              // canvas starts out black
    // set the canvas texture as the texture of a sprite to actually display
    _canvasSprite.setTexture( _canvas.getTexture(), true );

    // Tracing circle setup (default is to use circles not lines)
    _traceCircle.setRadius( 3 );                // default trace circle radius
    _traceCircle.setPointCount( 100 );          // default circle point count
    _traceCircle.setOrigin( 3, 3 );             // origin = center, not corner
    _traceCircle.setFillColor( Color::Cyan );   // default tracing color

    updateXandY();                              // set initial x- and y-position
    updateEverything();                         // do math and update values
}

Pendulums::Pendulums( const unsigned int windowWidth,
                      const unsigned int windowHeight, const bool lineTracing,
                      const Color traceColor, const double traceRadius,
                      const double xStart1, const double yStart1,
                      const double angle1, const double armLen1,
                      const double bobMass1, const double angle2,
                      const double armLen2, const double bobMass2,
                      const double gravity, const unsigned int antiAliasing,
                      const unsigned int pointCount ) {
    // Data member definitions
    G = gravity;                                // set G
    // construct pendulums
    _pend1 = Pendulum( angle1, armLen1, bobMass1, pointCount );
    _pend2 = Pendulum( angle2, armLen2, bobMass2, pointCount );
    _xStart1 = xStart1;                         // set pin x-position
    _yStart1 = yStart1;                         // set pin y-position

    // Canvas setup
    ContextSettings settings;
    settings.antialiasingLevel = antiAliasing;  // set anti-aliasing for canvas
    // create canvas with correct dimensions
    _canvas.create( windowWidth, windowHeight, settings );
    _canvas.clear( Color::Black );              // canvas starts out black
    // set the canvas texture as the texture of a sprite to actually display
    _canvasSprite.setTexture( _canvas.getTexture(), true );

    // Tracing setup (lines or circles)
    _lineTracing = lineTracing;                 // set type of tracing

    if ( _lineTracing ) {                       // Line tracing
        _traceLine.setPrimitiveType( Lines );   // define trace as a line
        _traceLine.resize( 2 );                 // lines have 2 points
        _traceLine[0].color = traceColor;       // set line to trace color
        _traceLine[1].color = traceColor;

        _lastPos = this->getpend2XandY();
    } else {                                    // Circle tracing
        _traceCircle.setRadius( traceRadius );  // set circles radius
        // set circle point count
        _traceCircle.setPointCount( pointCount );
        // origin = center, not corner
        _traceCircle.setOrigin( traceRadius, traceRadius );
        // set circles to trace color
        _traceCircle.setFillColor( traceColor );
    }

    updateXandY();                              // set initial x- and y-position
    updateEverything();                         // do math and update values
}

RenderTexture& Pendulums::getcanvas() {
    return _canvas;                             // can only return a reference
}

Vector2f Pendulums::getpend2XandY() const {
    // build Vector2f out of x- and y-position
    return Vector2f( _pend2.getxPos(), _pend2.getyPos());
}

void Pendulums::updateEverything() {
    double angAcc1( 0.0 ), angAcc2( 0.0 );
    // only doing this to make expressions below shorter + more readable
    // unfortunately, they're still too long and completely unreadable (sorry)
    double m1( _pend1.getbobMass() ), m2( _pend2.getbobMass() );
    double l1( _pend1.getarmLen() ), l2( _pend2.getarmLen() );
    double a1( _pend1.getangleRads() ), a2( _pend2.getangleRads() );
    double v1( _pend1.getangVel() ), v2( _pend2.getangVel() );

    // calculate angular accelerations of both pendulums based on current values
    // AKA do gross physics math / magic
    angAcc1 = ( ( -G * ( 2 * m1 + m2 ) * sin( a1 ) )
              - ( m2 * G * sin( a1 - 2 * a2 ) ) - ( 2 * sin( a1 - a2 ) * m2
              * ( v2 * v2 * l2 + v1 * v1 * l1 * cos( a1 - a2 ) ) ) )
              / ( l1 * ( 2 * m1 + m2 - m2 * cos( 2 * a1 - 2 * a2 ) ) );
    angAcc2 = ( 2 * sin( a1 - a2 ) * ( v1 * v1 * l1 * ( m1 + m2 ) + G
              * ( m1 + m2 ) * cos( a1 ) + v2 * v2 * l2 * m2 * cos( a1 - a2 ) ) )
              / ( l2 * ( 2 * m1 + m2 - m2 * cos( 2 * a1 - 2 * a2 ) ) );

    _pend1.setangAcc( angAcc1 );                // set new angular accelerations
    _pend2.setangAcc( angAcc2 );

    updateXandY();                              // move bobs to new positions

    _pend1.setarmPos( _xStart1, _yStart1 );     // move arms to new positions
    _pend2.setarmPos( _xStart2, _yStart2 );

    _pend1.updateValues();                      // update ang. velocity + angles
    _pend2.updateValues();

    // Tracing
    if ( _lineTracing ) {                       // Line tracing
        // set first point of line at last position
        _traceLine[0].position = _lastPos;
        // set second point of line at current position
        _traceLine[1].position = this->getpend2XandY();
        // draw the line on the canvas
        _canvas.draw( _traceLine );
    } else {                                    // Circle tracing
        // set position of circle at the current bob position
        _traceCircle.setPosition( this->getpend2XandY() );
        // draw the circle on the canvas
        _canvas.draw( _traceCircle );
    }
    _canvas.display();                          // present the canvas
    _lastPos = this->getpend2XandY();           // set last position to current
}

void Pendulums::drawEverything( RenderWindow& window ) const {
    window.draw( _canvasSprite );               // draw canvas sprite to window
    window.draw( _pend1.getarm() );             // draw arms and bobs to window
    window.draw( _pend1.getbob() );
    window.draw( _pend2.getarm() );
    window.draw( _pend2.getbob() );
}

void Pendulums::updateXandY() {
    // grab lengths and angles into variables w/ shorter names
    double l1( _pend1.getarmLen() ), l2( _pend2.getarmLen() );
    double a1( _pend1.getangleRads() ), a2( _pend2.getangleRads() );

    // set position of bob 1 based on arm length and angle
    _pend1.setxPos( _xStart1 + ( l1 * sin( a1 ) ) );
    _pend1.setyPos( _yStart1 + ( l1 * cos( a1 ) ) );

    // set pin of pendulum 2 to position of bob 1
    _xStart2 = _pend1.getxPos();
    _yStart2 = _pend1.getyPos();

    // set position of bob 2 based on arm length and angle
    // now relative to position of bob 1
    _pend2.setxPos( _xStart2 + ( l2 * sin( a2 ) ) );
    _pend2.setyPos( _yStart2 + ( l2 * cos( a2 ) ) );
}