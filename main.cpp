/* CSCI 261 Final Project - Double Pendulum
 *
 * Author: Vincent Marias
 *
 *  "Simulation" of a simple double pendulum (NOT a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 */

// TODO: Image processing
// TODO: User interaction (console or config file)
// TODO: Default constructors
// TODO: Dynamic window resizing
// TODO: Formatting + Documentation

#include "Pendulums.h"

#include <fstream>
#include <iostream>
using namespace std;

#include <cmath>

const int WIDTH = 1920;
const int HEIGHT = 1080;

int main() {
    // anti-aliasing to smooth out jagged edges
    ContextSettings settings;
    settings.antialiasingLevel = 16;

    // create a RenderWindow object
    // specify the size to be WIDTHxHEIGHT
    // set the title to be "Double Pendulum Simulation"
    // pass the settings object for antialiasing option
    RenderWindow window( VideoMode( WIDTH, HEIGHT ),
                         "Double Pendulum Simulation", Style::Default,
                         settings );

    window.setVerticalSyncEnabled( true );
    window.setFramerateLimit( 117 );

    Pendulums doublePendulum( WIDTH, HEIGHT, Color::Cyan, 3, 960, 540, (M_PI), 250, 20, (M_PI_2), 250, 20 );

    // while window is open, keep it open
    // this is the draw loop
    while ( window.isOpen() ) {
        window.clear( Color::Black );             // clear contents of old frame

        doublePendulum.drawEverything( window );

        window.display();

        doublePendulum.updateEverything();

        // Event Handling
        Event event;
        while ( window.pollEvent( event ) ) {  // aks if events occurred
            if ( event.type == Event::Closed ) {  // if event is Closed type,
                window.close();                   // then close the window
            }
        }
    }

    return EXIT_SUCCESS;
}