/* CSCI 261 Final Project - Double Pendulum
 *
 *  Simulation of a simple double pendulum (NOT a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 *
 *  MIT License
 *  Copyright (c) 2021 Vincent Marias
 */

#ifndef DOUBLE_PENDULUM_PENDULUM_H
#define DOUBLE_PENDULUM_PENDULUM_H

#include <SFML/Graphics.hpp>                    // include SFML graphics library
using namespace sf;

class Pendulum {
public:
    // Constructors

    /** @brief creates a default Pendulum object
     * @desc Creates a default Pendulum object with arm length = 250,
     * bob mass = 20, starting angle = PI/2, and circle point count = 100
     */
    Pendulum();
    /** @brief creates a parameterized Pendulum object
     * @desc Creates a Pendulum object with values set by parameters
     * @param angleRads starting angle from the vertical in radians
     * (0 = vertical downwards, counter-clockwise = positive)
     * @param armLen length of the pendulum arm in pixels (no real units)
     * @param bobMass mass of the pendulum bob in pixels (no real units)
     * @param pointCount number of points to use to create circle for bob
     */
    Pendulum( const double angleRads, const double armLen,
              const double bobMass, const unsigned int pointCount );

    // Getters

    /** @brief return the pendulum arm
     * @return copy of VertexArray object representing pendulum arm
     */
    VertexArray getarm() const;
    /** @brief return the pendulum bob
     * @return copy of CircleShape object representing pendulum bob
     */
    CircleShape getbob() const;
    /** @brief return bob x-position
     * @return current x-position of pendulum bob
     */
    double getxPos() const;
    /** @brief return bob y-position
     * @return current y-position of pendulum bob
     */
    double getyPos() const;
    /** @brief return pendulum arm angle
     * @return current angle of pendulum arm in radians
     * (0 = vertical downwards, counter-clockwise = positive)
     */
    double getangleRads() const;
    /** @brief return angular velocity
     * @return current angular velocity of pendulum arm in radians/frame
     */
    double getangVel() const;
    /** @brief return length of pendulum arm
     * @return length of pendulum arm in pixels (no real units)
     */
    double getarmLen() const;
    /** @brief return mass of bob
     * @return mass of pendulum bob in pixels (no real units)
     */
    double getbobMass() const;

    // Setters

    /** @brief set bob x-position
     * @param xPos new x-position of pendulum bob
     */
    void setxPos( const double xPos );
    /** @brief set bob y-position
     * @param yPos new y-position of pendulum bob
     */
    void setyPos( const double yPos );
    /** @brief set angular acceleration
     * @param angAcc new angular acceleration of pendulum arm
     */
    void setangAcc( const double angAcc );
    /** @brief set position of pendulum arm's free end
     * @param armPosx new x-position of pendulum arm's free end
     * @param armPosy new y-position of pendulum arm's free end
     */
    void setarmPos( const double armPosx, const double armPosy );

    // Helper functions

    /** @brief update physical values of pendulum
     * @desc Update angular velocity and arm angle of the pendulum, then move
     * the bob to it's new location
     */
    void updateValues();

private:
    VertexArray _arm;                           // pendulum arm
    CircleShape _bob;                           // pendulum bob
    double _xPos;                               // x-position of bob
    double _yPos;                               // y-position of bob
    double _angleRads;                          // arm angle (radians)
    double _angVel;                             // angular velocity (rads/frame)
    double _angAcc;                             // angular acceleration
                                                // (rads/frame/frame)
    double _armLen;                             // arm length (pixels)
    double _bobMass;                            // bob mass (pixels)
};


#endif //DOUBLE_PENDULUM_PENDULUM_H