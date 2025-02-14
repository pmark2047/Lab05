/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"
 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
   angle = 0;
   status = PLAYING;
   fuel = 5000.0;
   velocity.setDX(random(-10, -4));
   velocity.setDY(random(-2, 2));
   pos.setX(posUpperRight.getX() - 1);
   pos.setY(random(375.0, 395.0));
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
   gout.drawLander(pos, angle.getRadians());
   gout.drawLanderFlames(pos, angle.getRadians(), thrust.isMain(), thrust.isClock(), thrust.isCounter());
   
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   Acceleration acceleration;
   acceleration.setDDY(gravity);
   
   if (fuel > 0)
   {
      if (thrust.isMain())
      {
         double thrustMagnitude = thrust.mainEngineThrust();
         double angleRadians = angle.getRadians();
         
         double thrustX = -sin(angleRadians) * thrustMagnitude;
         double thrustY = cos(angleRadians) * thrustMagnitude;
         
         acceleration.addDDX(thrustX);
         acceleration.addDDY(thrustY);
         
         fuel -= 10;
      }
      
      if (thrust.isClock())
      {
         angle.add(0.1);
         fuel -= 1;
      }
      if (thrust.isCounter())
      {
         angle.add(-0.1); 
         fuel -= 1;
      }
   }
   
   return acceleration;
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   if (!isFlying())
   {return;}
   double newDX = velocity.getDX() + acceleration.getDDX() * time;
   double newDY = velocity.getDY() + acceleration.getDDY() * time;
   
   double newX = pos.getX() + velocity.getDX() * time + 0.5 * acceleration.getDDX() * time * time;
   double newY = pos.getY() + velocity.getDY() * time + 0.5 * acceleration.getDDY() * time * time;
   
   velocity.setDX(newDX);
   velocity.setDY(newDY);
   
   pos.setX(newX);
   pos.setY(newY);
}
