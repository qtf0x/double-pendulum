/* CSCI 261 Final Project - Double Pendulum
 *
 * Author: Vincent Marias
 *
 *  "Simulation" of a simple double pendulum (NOT a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 */

#include "Pendulums.h"

#include <cmath>

const double Pendulums::G = 0.5;

Pendulums::Pendulums() {
    // FIXME
}

Pendulums::Pendulums( const int windowWidth, const int windowHeight,
                      const Color traceColor, const double xStart1,
                      const double yStart1, const double angle1,
                      const double armLen1, const double bobMass1,
                      const double angle2, const double armLen2,
                      const double bobMass2 ) {
    _pend1 = Pendulum( angle1, armLen1, bobMass1 );
    _pend2 = Pendulum( angle2, armLen2, bobMass2 );
    _xStart1 = xStart1;
    _yStart1 = yStart1;
    updateEverything();

    // Set up tracing of bob 2
    _canvas.create( windowWidth, windowHeight );
    _canvas.clear( Color::Black );

    _canvasSprite.setTexture( _canvas.getTexture(), true );

    _traceLine.setPrimitiveType( Lines );
    _traceLine.resize( 2 );
    _traceLine[0].color = traceColor;
    _traceLine[1].color = traceColor;

    _lastPos = this->getpend2XandY();

    _lineTracing = true;
}

Pendulums::Pendulums( const int windowWidth, const int windowHeight,
                      const Color traceColor, const double traceRadius,
                      const double xStart1, const double yStart1,
                      const double angle1, const double armLen1,
                      const double bobMass1, const double angle2,
                      const double armLen2, const double bobMass2 ) {
    _pend1 = Pendulum( angle1, armLen1, bobMass1 );
    _pend2 = Pendulum( angle2, armLen2, bobMass2 );
    _xStart1 = xStart1;
    _yStart1 = yStart1;
    updateEverything();

    // Set up tracing of bob 2
    _canvas.create( windowWidth, windowHeight );
    _canvas.clear( Color::Black );

    _canvasSprite.setTexture( _canvas.getTexture(), true );

    _traceCircle.setRadius( traceRadius );
    _traceCircle.setPointCount( 100 );
    _traceCircle.setOrigin( traceRadius, traceRadius );
    _traceCircle.setFillColor( traceColor );

    _lastPos = this->getpend2XandY();

    _lineTracing = false;
}

Pendulum Pendulums::getpend1() const {
    return _pend1;
}

Pendulum Pendulums::getpend2() const {
    return _pend2;
}

Vector2f Pendulums::getpend2XandY() const {
    return Vector2f( _pend2.getxPos(), _pend2.getyPos() );
}

void Pendulums::updateEverything() {
    double angAcc1( 0.0 ), angAcc2( 0.0 );
    double m1( _pend1.getbobMass() ), m2( _pend2.getbobMass() );
    double l1( _pend1.getarmLen() ), l2( _pend2.getarmLen() );
    double a1( _pend1.getangleRads() ), a2( _pend2.getangleRads() );
    double v1( _pend1.getangVel() ), v2( _pend2.getangVel() );

    angAcc1 = ( ( -G * ( 2 * m1 + m2 ) * sin( a1 ) ) - ( m2 * G * sin( a1 - 2 * a2 ) ) - ( 2 * sin( a1 - a2 ) * m2 * ( v2 * v2 * l2 + v1 * v1 * l1 * cos( a1 - a2 ) ) ) ) / ( l1 * ( 2 * m1 + m2 - m2 * cos( 2 * a1 - 2 * a2 ) ) );
    angAcc2 = ( 2 * sin( a1 - a2 ) * ( v1 * v1 * l1 * ( m1 + m2 ) + G * ( m1 + m2 ) * cos( a1 ) + v2 * v2 * l2 * m2 * cos( a1 - a2 ) ) ) / ( l2 * ( 2 * m1 + m2 - m2 * cos( 2 * a1 - 2 * a2 ) ) );

    _pend1.setangAcc( angAcc1 );
    _pend2.setangAcc( angAcc2 );

    _pend1.setxPos( _xStart1 + ( l1 * sin( a1 ) ) );
    _pend1.setyPos( _yStart1 + ( l1 * cos( a1 ) ) );

    _xStart2 = _pend1.getxPos();
    _yStart2 = _pend1.getyPos();

    _pend2.setxPos( _xStart2 + ( l2 * sin( a2 ) ) );
    _pend2.setyPos( _yStart2 + ( l2 * cos( a2 ) ) );

    _pend1.setarmPos( _xStart1, _yStart1 );
    _pend2.setarmPos( _xStart2, _yStart2 );

    _pend1.updateValues();
    _pend2.updateValues();

    // Tracing
    if ( _lineTracing ) {
        _traceLine[0].position = _lastPos;
        _traceLine[1].position = this->getpend2XandY();
        _canvas.draw( _traceLine );
    } else {
        _traceCircle.setPosition( this->getpend2XandY() );
        _canvas.draw( _traceCircle );
    }
    _canvas.display();
    _lastPos = this->getpend2XandY();
}

void Pendulums::drawEverything( RenderWindow& window ) const {
    window.draw( _canvasSprite );
    window.draw( _pend1.getarm() );
    window.draw( _pend1.getbob() );
    window.draw( _pend2.getarm() );
    window.draw( _pend2.getbob() );
}