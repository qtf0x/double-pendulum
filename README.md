# Double Pendulum Simulation
Simulation of a simple double pendulum (not a Harmonograph / Blackburn 
pendulum) written in C++ using the SFML multimedia library.
## Features
* Configurable via `config.ini` file
  * Rendering / Performance (anti-aliasing, framerate, etc.)
  * Simulation behavior (speed, gravity)
  * Initial conditions of each pendulum
  * Tracing of pendulum trajectory (lines/circles, color, etc.)
## Example
```c++
    Pendulums doublePendulum;

    // while window is open, keep it open
    // this is the draw loop
    while ( window.isOpen() ) {
        window.clear( Color::Black );                  // clear old frame

        doublePendulum.drawEverything( window );       // draw double pendulum

        window.display();                              // present window

        doublePendulum.updateEverything();             // update pendulums
    }
```
