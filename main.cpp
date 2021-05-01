/* CSCI 261 Final Project - Double Pendulum
 *
 * Author: Vincent Marias
 *
 *  "Simulation" of a simple double pendulum (NOT a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 */

#include <SFML/Graphics.hpp>
using namespace sf;

#include <fstream>
#include <iostream>
using namespace std;

const int WIDTH = 1920;
const int HEIGHT = 1080;

int main() {
    // anti-aliasing to smooth out jagged edges
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    // create a RenderWindow object
    // specify the size to be WIDTHxHEIGHT
    // set the title to be "Double Pendulum Simulation"
    // pass the settings object for antialiasing option
    RenderWindow window( VideoMode( WIDTH, HEIGHT ),
                         "Double Pendulum Simulation", Style::Default,
                         settings );


    // while window is open, keep it open
    // this is the draw loop
    while ( window.isOpen() ) {
        window.clear( Color::Black );             // clear contents of old frame

        window.display();

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