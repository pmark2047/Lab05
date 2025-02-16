/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "acceleration.h"// for ACCELERATION
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#define GRAVITY -1.625
using namespace std;


/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) : ground(posUpperRight), lander(posUpperRight) {}
   Ground ground;
   Lander lander;
   Thrust thrust;
   Acceleration acceleration;
   int phaseShifter = 0;
   Star stars[50];
};



/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator * pSimulator = (Simulator *)p;
   Position posUpperRight(400, 400);

   ogstream gout;
   
   // draw a star
   for (Star& star : pSimulator->stars)
   {
      star.phase += 1;
      gout.drawStar(star.position, star.phase);
   }
   
   // draw the ground
   pSimulator->ground.draw(gout);
   
   // draw the lander
   pSimulator->lander.draw(pSimulator->thrust, gout);
   
   // connect thrusters to lander
   pSimulator->thrust.set(pUI);
   
   pSimulator->acceleration = pSimulator->lander.input(pSimulator->thrust, GRAVITY);
   
   pSimulator->lander.coast(pSimulator->acceleration, 0.1);
   
   pSimulator->lander.input(pSimulator->thrust, GRAVITY);
   
   // Add collisions
   
   if (pSimulator->ground.onPlatform(pSimulator->lander.getPosition(), pSimulator->lander.getWidth())){
      pSimulator->lander.land();
   }
   if (pSimulator->ground.hitGround(pSimulator->lander.getPosition(), pSimulator->lander.getWidth())){
      pSimulator->lander.crash();
   }
   
   // Reset Function
   
   if (pUI -> isQ())
   {
      pSimulator->lander.reset(posUpperRight);
      pSimulator->ground.reset();
   }
   
   // Readout values
   double speed = pSimulator->lander.getSpeed();
   double altitude = pSimulator->lander.getPosition().getY();
   int fuel = pSimulator->lander.getFuel();
   
   gout.drawReadout(speed, altitude, fuel);
   
   //crash message
   if (pSimulator->lander.isDead())
   {
      gout.drawCrashMessage();
   }
   
   //landed message
   if (pSimulator->lander.isLanded())
   {
      gout.drawLandedMessage();
   }
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();

   
   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action
   ui.run(callBack, (void *)&simulator);

   return 0;
}
