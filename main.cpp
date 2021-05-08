/* CSCI 261 Final Project - Double Pendulum
 *
 *  Simulation of a simple double pendulum (not a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 *
 *  MIT License
 *  Copyright (c) 2021 Vincent Marias
 */

// TODO: Install Boost and switch to that for config file processing
// TODO: Make line tracing color dynamic w/ user input
// TODO: Graphs!
// TODO: Add an option for air resistance
// TODO: Make pendulums interactive w/ mouse (drag masses, pin around)
// TODO: Add sliders for various values (mass, length, etc.)

#include "Pendulums.h"
#include "inipp-develop/inipp/inipp.h"                 // include inipp library
using namespace inipp;

#include <fstream>                                     // for ifstream
#include <iostream>                                    // for cerr
#include <string>                                      // for string library
using namespace std;

#include <ctime>                                       // for time()

int main() {

    //**********************************
    // CONFIG FILE PROCESSING BELOW HERE
    //**********************************

    string configInFilename = "config.ini";
    ifstream configFileIn( configInFilename );         // open config file
    if ( configFileIn.fail() ) {                       // check for file errors
        cerr << "Could not open config file \"" << configInFilename << "\""
             << endl << "Shutting down";
        return EXIT_FAILURE;
    }


    Ini<char> config;                                  // inipp .ini parser
    config.parse( configFileIn );                      // parse config file
    // parse default section
    config.default_section( config.sections["DEFAULT"] );
    // I don't know what this does, but it makes inipp work
    config.interpolate();

    // Anti-aliasing
    unsigned int antiAliasing = 0;
    // get value from appropriate section in config.ini
    get_value( config.sections["Rendering"], "AntiAliasing", antiAliasing );
    if ( antiAliasing > 16 ) {
        antiAliasing = 16;                             // >16 breaks everything
    }

    // Circle point count
    unsigned int pointCount = 0;
    // get value from appropriate section in config.ini
    get_value( config.sections["Rendering"], "CirclePointCount", pointCount );
    if ( pointCount < 3 ) {
        pointCount = 3;                                // <3 breaks everything
    }

    // VSync
    bool vSync = 0;
    // get value from appropriate section in config.ini
    get_value( config.sections["Rendering"], "VSync", vSync );

    // Framerate Limit
    unsigned int framerateLimit = 0;
    // get value from appropriate section in config.ini
    get_value( config.sections["Rendering"], "FramerateLimit", framerateLimit );

    // Gravity
    double G;
    // get value from appropriate section in config.ini
    get_value( config.sections["Simulation"], "GravitationalConstant", G );

    // Window size
    // get values from appropriate section in config.ini
    unsigned int width(1920), height(1080);            // window dim. default
    get_value( config.sections["Size and Position"], "WindowWidth", width );
    get_value( config.sections["Size and Position"], "WindowHeight", height );

    // Start position
    double startPosX, startPosY;
    // get values from appropriate section in config.ini
    get_value( config.sections["Size and Position"], "StartPosX", startPosX );
    get_value( config.sections["Size and Position"], "StartPosY", startPosY );

    // Initial conditions 1
    double startAng1, armLen1( -1 ), bobMass1( -1 );
    // get values from appropriate section in config.ini
    get_value( config.sections["Initial Conditions Pendulum 1"], "StartAngle",
               startAng1 );
    get_value( config.sections["Initial Conditions Pendulum 1"], "ArmLength",
               armLen1 );
    get_value( config.sections["Initial Conditions Pendulum 1"], "BobMass",
               bobMass1 );

    // Initial conditions 2
    double startAng2, armLen2( -1 ), bobMass2( -1 );
    // get values from appropriate section in config.ini
    get_value( config.sections["Initial Conditions Pendulum 2"], "StartAngle",
               startAng2 );
    get_value( config.sections["Initial Conditions Pendulum 2"], "ArmLength",
               armLen2 );
    get_value( config.sections["Initial Conditions Pendulum 2"], "BobMass",
               bobMass2 );

    // Tracing type
    bool lineTracing;
    // get value from appropriate section in config.ini
    get_value( config.sections["Path Tracing"], "LineTracing", lineTracing );

    // Tracing circle radius
    double traceRadius = -1;
    // get value from appropriate section in config.ini
    get_value( config.sections["Path Tracing"], "TraceCircleRadius",
               traceRadius );

    // Tracing color
    int red( -1 ), green( -1 ), blue( -1 ), alpha( -1 );
    // get value from appropriate section in config.ini
    get_value( config.sections["Path Tracing"], "TraceColorRed", red );
    get_value( config.sections["Path Tracing"], "TraceColorGreen", green );
    get_value( config.sections["Path Tracing"], "TraceColorBlue", blue );
    get_value( config.sections["Path Tracing"], "TraceColorAlpha", alpha );
    Color traceColor( red, green, blue, alpha );       // create color

    configFileIn.close();                              // close config file

    // when critical values are left default -1, indicates misuse of config file
    // in reality, this is a limitation of the inipp library
    if ( armLen1 < 0 || bobMass1 < 0 || armLen2 < 0 || bobMass2 < 0
         || traceRadius < 0 ) {
        cerr << "Oops, there was a configuration error!" << endl
             << "You probably left an entire section blank in the config file."
             << endl << "Please don't do that." << endl
             << "Goodbye!";
    }

    //**********************************
    // CONFIG FILE PROCESSING ABOVE HERE
    //**********************************

    ContextSettings settings;
    settings.antialiasingLevel = antiAliasing;         // smooth jagged edges

    // create a RenderWindow object
    // specify the size to be width x height
    // set the title to be "Double Pendulum Simulation"
    // pass the settings object for antialiasing option
    RenderWindow window( VideoMode( width, height ),
                         "Double Pendulum Simulation", Style::Default,
                         settings );

    window.setVerticalSyncEnabled( vSync );            // set VSync
    window.setFramerateLimit( framerateLimit );        // set FPS limit

    // call Pendulums constructor with the ridiculous mass of configuration
    // arguments we've collected (could also use default constructor)
    Pendulums doublePendulum( width, height, lineTracing, traceColor,
                              traceRadius, startPosX, startPosY, startAng1,
                              armLen1, bobMass1, startAng2, armLen2, bobMass2,
                              G, antiAliasing, pointCount );

    unsigned int frameCount = 0;                       // frame counter

    // while window is open, keep it open
    // this is the draw loop
    while ( window.isOpen() ) {
        window.clear( Color::Black );                  // clear old frame

        doublePendulum.drawEverything( window );       // draw double pendulum

        window.display();                              // present window

        doublePendulum.updateEverything();             // update pendulums

        // Event Handling
        Event event;
        while ( window.pollEvent( event ) ) {          // ask if event occurred
            switch ( event.type ) {
                case Event::Closed:                    // event type Closed,
                    window.close();                    // then close window
                    break;
                case Event::KeyReleased:               // event type KeyReleased
                    // space bar pressed
                    if ( event.key.code == Keyboard::Space ) {
                        // name output file "frame_framecount_time.png"
                        string imgOutFilename = "output/frame_"
                                                + to_string( frameCount ) + '_'
                                                + to_string( time( nullptr ) )
                                                + ".png";
                        // export drawing canvas texture as image file
                        doublePendulum.getcanvas().getTexture().copyToImage()
                                .saveToFile( imgOutFilename );
                    }
                    break;
                case Event::Resized:                   // event type Resized
                    View newView( window.getView() );  // retrieve view object
                    // get new window size
                    const Vector2f newSize( window.getSize().x,
                                            window.getSize().y );
                    newView.setSize( newSize );        // resize view to window
                    window.setView( newView );         // give window new view
                    break;
            }
        }

        ++frameCount;                                  // increment frame count
    }

    return EXIT_SUCCESS;
}