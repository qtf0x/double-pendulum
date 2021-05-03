/* CSCI 261 Final Project - Double Pendulum
 *
 *  Simulation of a simple double pendulum (NOT a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 *
 *  MIT License
 *  Copyright (c) 2021 Vincent Marias
 */

// TODO: Formatting + Documentation
// TODO: Color cycling

#include "Pendulums.h"
#include "inipp-develop/inipp/inipp.h"
using namespace inipp;

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <ctime>

int main() {
    unsigned int WIDTH = 1920;
    unsigned int HEIGHT = 1080;

    // Config file processing
    Ini<char> config;

    string configInFilename = "config.ini";
    ifstream configFileIn;
    configFileIn.open( configInFilename );
    if ( configFileIn.fail() ) {
        cerr << "Could not open config file \"" << configInFilename << "\"" << endl;
        cerr << "Shutting down";
        return EXIT_FAILURE;
    }

    config.parse( configFileIn );
    config.default_section( config.sections["DEFAULT"]);
    config.interpolate();

    // Anti-aliasing
    unsigned int antiAliasing = 0;
    get_value( config.sections["Rendering"], "AntiAliasing", antiAliasing );
    if ( antiAliasing > 16 ) {
        antiAliasing = 16;
    }

    // Circle point count
    unsigned int pointCount = 0;
    get_value( config.sections["Rendering"], "CirclePointCount", pointCount );
    if ( pointCount < 3 ) {
        pointCount = 3;
    }

    // Gravity
    double G;
    get_value( config.sections["Simulation"], "GravitationalConstant", G );

    // Window size
    get_value( config.sections["Size and Position"], "WindowWidth", WIDTH );
    get_value( config.sections["Size and Position"], "WindowHeight", HEIGHT );

    // Start position
    double startPosX, startPosY;
    get_value( config.sections["Size and Position"], "StartPosX", startPosX );
    get_value( config.sections["Size and Position"], "StartPosY", startPosY );

    // Initial conditions 1
    double startAng1, armLen1( -1 ), bobMass1( -1 );
    get_value( config.sections["Initial Conditions Pendulum 1"], "StartAngle", startAng1 );
    get_value( config.sections["Initial Conditions Pendulum 1"], "ArmLength", armLen1 );
    get_value( config.sections["Initial Conditions Pendulum 1"], "BobMass", bobMass1 );

    // Initial conditions 2
    double startAng2, armLen2( -1 ), bobMass2( -1 );
    get_value( config.sections["Initial Conditions Pendulum 2"], "StartAngle", startAng2 );
    get_value( config.sections["Initial Conditions Pendulum 2"], "ArmLength", armLen2 );
    get_value( config.sections["Initial Conditions Pendulum 2"], "BobMass", bobMass2 );

    // Tracing type
    bool lineTracing;
    get_value( config.sections["Path Tracing"], "LineTracing", lineTracing );

    // Tracing circle radius
    double traceRadius = -1;
    get_value( config.sections["Path Tracing"], "TraceCircleRadius", traceRadius );

    // Tracing color
    int red( -1 ), green( -1 ), blue( -1 ), alpha( -1 );
    get_value( config.sections["Path Tracing"], "TraceColorRed", red );
    get_value( config.sections["Path Tracing"], "TraceColorGreen", green );
    get_value( config.sections["Path Tracing"], "TraceColorBlue", blue );
    get_value( config.sections["Path Tracing"], "TraceColorAlpha", alpha );
    Color traceColor( red, green, blue, alpha );

    configFileIn.close();

    if ( armLen1 < 0 || bobMass1 < 0 || armLen2 < 0 || bobMass2 < 0 || traceRadius < 0 ) {
        cerr << "Oops, there was a configuration error!" << endl
             << "You probably left an entire section blank in the config file . . ." << endl
             << "Please don't do that." << endl
             << "Goodbye!";
    }

    // anti-aliasing to smooth out jagged edges
    ContextSettings settings;
    settings.antialiasingLevel = antiAliasing;

    // create a RenderWindow object
    // specify the size to be WIDTHxHEIGHT
    // set the title to be "Double Pendulum Simulation"
    // pass the settings object for antialiasing option
    RenderWindow window( VideoMode( WIDTH, HEIGHT ),
                         "Double Pendulum Simulation", Style::Default,
                         settings );

    window.setVerticalSyncEnabled( true );
    window.setFramerateLimit( 117 );

    Pendulums doublePendulum( WIDTH, HEIGHT, lineTracing, traceColor, traceRadius, startPosX, startPosY, startAng1, armLen1, bobMass1, startAng2, armLen2, bobMass2, G, antiAliasing, pointCount );

    // Frame counter
    unsigned int frameCount = 0;

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
            switch ( event.type ) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyReleased:
                    if ( event.key.code == Keyboard::Space ) {
                        string imgOutFilename = "output/frame_" + to_string( frameCount ) + '_' + to_string( time( nullptr ) ) + ".png";
                        doublePendulum.getcanvas().getTexture().copyToImage().saveToFile( imgOutFilename );
                    }
                    break;
                case Event::Resized:
                    View newView( window.getView() );
                    const Vector2f newSize( window.getSize().x, window.getSize().y );
                    newView.setSize( newSize );
                    window.setView( newView );
                    break;
            }
        }

        ++frameCount;
    }

    return EXIT_SUCCESS;
}