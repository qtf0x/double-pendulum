/* CSCI 261 Final Project - Double Pendulum
 *
 *  Simulation of a simple double pendulum (not a Harmonograph / Blackburn
 *  pendulum) written in C++ using the SFML multimedia library.
 *
 *  MIT License
 *  Copyright (c) 2021 Vincent Marias
 */

#include "Pendulums.h"

#include <fstream>                                     // for ifstream
#include <iostream>                                    // for cerr
#include <string>                                      // for string library
using namespace std;

#include <cmath>                                       // for M_PI_2
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

    unsigned int antiAliasing( 16 ), pointCount( 100 );
    bool vSync = true;
    unsigned int framerateLimit = 60;
    double G = 1;
    unsigned int width( 1920 ), height( 1080 );
    double startPosX( 960.0 ), startPosY( 540.0 );
    double startAng1( M_PI_2 ), armLen1( 250 ), bobMass1( 20 );
    double startAng2( M_PI_2 ), armLen2( 250 ), bobMass2( 20 );
    bool lineTracing = false;
    double traceRadius = 4.0;
    int red( 255 ), green( 0 ), blue( 255 ), alpha( 255 );
    string nextValue;

    while( getline( configFileIn, nextValue ) ) {

        if ( nextValue.rfind( ';', 0 ) == 0 || nextValue.rfind( '[', 0 ) == 0 )
        {
            continue;                                  // skip comments/headers
        }

        // Anti-aliasing
        // if current line starts with "AntiAliasing, get value after '='
        if ( ( nextValue.rfind( "AntiAliasing", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            antiAliasing = stoi( nextValue.substr( nextValue.find( '=' ) + 1,
                                                   string::npos ) );

            if ( antiAliasing > 16 ) {
                antiAliasing = 16;                     // >16 breaks everything
            }

            continue;
        }

        // Circle Point Count
        // if current line starts with "CirclePointCount", get value after '='
        if ( ( nextValue.rfind( "CirclePointCount", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            pointCount = stoi( nextValue.substr( nextValue.find( '=' ) + 1,
                                                 string::npos ) );

            if ( pointCount < 3 ) {
                pointCount = 3;                        // <3 breaks everything
            }

            continue;
        }

        // VSync
        // if current line starts with "VSync", get value after '='
        if ( ( nextValue.rfind( "VSync", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos )) {
            vSync = ( nextValue.substr( nextValue.find( '=' ) + 1,
                                        string::npos ) == "true" );

            continue;
        }

        // Framerate Limit
        // if current line starts with "FramerateLimit", get value after '='
        if ( ( nextValue.rfind( "FramerateLimit", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            framerateLimit = stoi( nextValue.substr( nextValue.find( '=' ) + 1,
                                                     string::npos ) );

            continue;
        }

        // Gravity
        // current line starts with "GravitationalConstant", get value after '='
        if ( ( nextValue.rfind( "GravitationalConstant", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            G = stod( nextValue.substr( nextValue.find( '=' ) + 1,
                                        string::npos ) );

            continue;
        }

        // Window Size
        // if current line starts with "WindowWidth", get value after '='
        if ( ( nextValue.rfind( "WindowWidth", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            width = stoi( nextValue.substr( nextValue.find( '=' ) + 1,
                                            string::npos ) );

            if ( width < 1 ) {
                width = 1920;
            }

            continue;
        }
        // if current line starts with "WindowHeight", get value after '='
        if ( ( nextValue.rfind( "WindowHeight", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            height = stoi( nextValue.substr( nextValue.find( '=' ) + 1,
                                             string::npos ) );

            if ( height < 1 ) {
                height = 1080;
            }

            continue;
        }

        // Start Position
        // if current line starts with "StartPosX", get value after '='
        if ( ( nextValue.rfind( "StartPosX", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            startPosX = stod( nextValue.substr( nextValue.find( '=' ) + 1,
                                                string::npos ) );

            continue;
        }
        // if current line starts with "StartPosY", get value after '='
        if ( ( nextValue.rfind( "StartPosY", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            startPosY = stod( nextValue.substr( nextValue.find( '=' ) + 1,
                                                string::npos ) );

            continue;
        }

        // Initial Conditions 1
        // if current line starts with "StartAngle1", get value after '='
        if ( ( nextValue.rfind( "StartAngle1", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            startAng1 = stod( nextValue.substr( nextValue.find( '=' ) + 1,
                                                string::npos ) );

            continue;
        }
        // if current line starts with "ArmLength1", get value after '='
        if ( ( nextValue.rfind( "ArmLength1", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            armLen1 = stod( nextValue.substr( nextValue.find( '=' ) + 1,
                                              string::npos ) );

            if ( armLen1 < 0 ) {
                armLen1 *= -1.0;
            }

            continue;
        }
        // if current line starts with "BobMass1", get value after '='
        if ( ( nextValue.rfind( "BobMass1", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            bobMass1 = stod( nextValue.substr( nextValue.find( '=' ) + 1,
                                               string::npos ) );

            if ( bobMass1 < 0 ) {
                bobMass1 *= -1.0;
            }

            continue;
        }

        // Initial Conditions 2
        // if current line starts with "StartAngle2", get value after '='
        if ( ( nextValue.rfind( "StartAngle2", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            startAng2 = stod( nextValue.substr( nextValue.find( '=' ) + 1,
                                                string::npos ) );

            continue;
        }
        // if current line starts with "ArmLength2", get value after '='
        if ( ( nextValue.rfind( "ArmLength2", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            armLen2 = stod( nextValue.substr( nextValue.find( '=' ) + 1,
                                              string::npos ) );

            if ( armLen2 < 0 ) {
                armLen2 *= -1.0;
            }

            continue;
        }
        // if current line starts with "BobMass2", get value after '='
        if ( ( nextValue.rfind( "BobMass2", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            bobMass2 = stod( nextValue.substr( nextValue.find( '=' ) + 1,
                                               string::npos ) );

            if ( bobMass2 < 0 ) {
                bobMass2 *= -1.0;
            }

            continue;
        }

        // Tracing Type
        // if current line starts with "LineTracing", get value after '='
        if ( ( nextValue.rfind( "LineTracing", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            lineTracing = nextValue.substr( nextValue.find( '=' ) + 1,
                                            string::npos ) == "true";

            continue;
        }

        // Tracing Circle Radius
        // if current line starts with "TraceCircleRadius", get value after '='
        if ( ( nextValue.rfind( "TraceCircleRadius", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            traceRadius = stod( nextValue.substr( nextValue.find( '=' ) + 1,
                                                  string::npos ) );

            continue;
        }

        // Tracing Color
        // if current line starts with "TraceColorRed", get value after '='
        if ( ( nextValue.rfind( "TraceColorRed", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            red = stoi( nextValue.substr( nextValue.find( '=' ) + 1,
                                          string::npos ) );

            continue;
        }
        // if current line starts with "TraceColorGreen", get value after '='
        if ( ( nextValue.rfind( "TraceColorGreen", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            green = stoi( nextValue.substr( nextValue.find( '=' ) + 1,
                                            string::npos ) );

            continue;
        }
        // if current line starts with "TraceColorBlue", get value after '='
        if ( ( nextValue.rfind( "TraceColorBlue", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            blue = stoi( nextValue.substr( nextValue.find( '=' ) + 1,
                                           string::npos ) );

            continue;
        }
        // if current line starts with "TraceColorAlpha", get value after '='
        if ( ( nextValue.rfind( "TraceColorAlpha", 0 ) == 0 )
             && ( nextValue.find( '=' ) != string::npos ) ) {
            alpha = stoi( nextValue.substr( nextValue.find( '=' ) + 1,
                                            string::npos ) );

            continue;
        }

    }

    Color traceColor( red, green, blue, alpha );       // create trace color

    configFileIn.close();                              // close config file

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