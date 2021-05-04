/* CSCI 261 Final Project - Double Pendulum
 *
 *  Simulation of a simple double pendulum (not a Harmonograph / Blackburn
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

    /** @brief creates a default Pendulums object
     * @desc Creates a default Pendulums object with G = 0.5, pin at (960, 540),
     * antialiasing = x16, window dimensions 1920 x 1080, and circle tracing
     * with radius = 3, circle point count = 100, and color = Cyan. Calls
     * default Pendulum constructor twice.
     */
    Pendulums();
    /** @brief creates a parameterized Pendulums object
     * @desc Creates a Pendulums object with values set by parameters
     * @param windowWidth width of render window in pixels
     * @param windowHeight height of render window in pixels
     * @param lineTracing trace with lines (true), or circles (false)
     * @param traceColor color of lines OR circles used for tracing
     * @param traceRadius radius of circles used for tracing
     * @param xStart1 x-position of the stem of pendulum 1
     * @param yStart1 y-position of the stem of pendulum 2
     * @param angle1 starting angle from the vertical in radians for pendulum 1
     * (0 = vertical downwards, counter-clockwise = positive)
     * @param armLen1 length of pendulum arm 1 in pixels (no real units)
     * @param bobMass1 mass of pendulum bob 1 in pixels (no real units)
     * @param angle2 starting angle from the vertical in radians for pendulum 2
     * (0 = vertical downwards, counter-clockwise = positive)
     * @param armLen2 length of pendulum arm 1 in pixels (no real units)
     * @param bobMass2 mass of pendulum bob 1 in pixels (no real units)
     * @param gravity universal gravitational constant (not real-life value)
     * keep inverse ratio gravity=1 : FPS limit=60 for natural-looking motion
     * @param antiAliasing anti-aliasing level to apply to bob 2 tracing
     * @param pointCount number of points to use when constructing circles
     */
    Pendulums( const unsigned int windowWidth, const unsigned int windowHeight,
               const bool lineTracing, const Color traceColor,
               const double traceRadius, const double xStart1,
               const double yStart1, const double angle1, const double armLen1,
               const double bobMass1, const double angle2, const double armLen2,
               const double bobMass2, const double gravity,
               const unsigned int antiAliasing, const unsigned int pointCount );

    // Getters

    /** @brief return drawing canvas
     * @return reference to RenderTexture canvas where bob 2 trace is drawn
     */
    RenderTexture& getcanvas();
    /** @brief return position of pendulum 2 bob
     * @return vector containing x- and y-position of pendulum 2 bob
     */
    Vector2f getpend2XandY() const;

    // Helper functions

    /** @brief update all values related to double pendulum
     * @desc Update all values related each Pendulum object and update bob 2
     * path tracing. Performs all the math for pendulum movement. Do this once
     * per frame.
     */
    void updateEverything();
    /** @brief draw all parts of double pendulum to given RenderWindow
     * @desc Takes a reference to a RenderWindow object and draws each part of
     * the double pendulum to it, including path tracing.
     * @param window reference to an active RenderWindow object
     */
    void drawEverything( RenderWindow& window ) const;

private:
    double G;                           // universal gravitational constant
    Pendulum _pend1;                    // Pendulum 1 (top)
    Pendulum _pend2;                    // Pendulum 2 (bottom)
    double _xStart1;                    // x-position of pendulum 1 stem
    double _yStart1;                    // y-position of pendulum 1 stem
    double _xStart2;                    // x-position of pendulum 2 stem
    double _yStart2;                    // y-position of pendulum 2 stem
    RenderTexture _canvas;              // canvas to draw path tracing on
    Sprite _canvasSprite;               // sprite used to present canvas texture
    CircleShape _traceCircle;           // circle used for path tracing
    VertexArray _traceLine;             // line used for path tracing
    Vector2f _lastPos;                  // most recent previous bob 2 position
    bool _lineTracing;                  // use lines (true), or circles (false)

    /** @brief updates position of both pendulum bobs
     * @desc updates the position of pendulum 1 bob and pendulum 2 pin, then
     * position of pendulum 2 bob relative to bob 1
     */
    void updateXandY();
};

#endif //DOUBLE_PENDULUM_PENDULUMS_H