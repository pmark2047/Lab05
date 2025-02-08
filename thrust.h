/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h"  // for Interface

class TestLander;
class TestThrust;

 /*****************************************************
  * THRUST
  * Represents activation of thrusters
  *****************************************************/
class Thrust
{
   friend TestLander;
   friend TestThrust;
   
public:
   // Thrust is initially turned off
   Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

   // Get rotation in radians per second
   double rotation() const
   {
      if (clockwise == true && counterClockwise == false)
      {
         return 0.1;
      }
      else if (counterClockwise == true && clockwise == false)
      {
         return -0.1;
      }
      else
      {
         return 0;
      }
   }

   // get main engine thrust in  m / s ^ 2
   double mainEngineThrust() const
   {
      if (mainEngine == true)
      {
         return 45000.00 / 15103.00;
      }
      else
      {
         return 0;
      }
   }

   // reflect what is firing
   bool isMain()    const { return mainEngine; }
   bool isClock()   const { return clockwise; }
   bool isCounter() const { return counterClockwise; }

   // set the thrusters
   void set(const Interface * pUI)
   {
      mainEngine       = pUI -> isDown();
      clockwise        = pUI -> isLeft();
      counterClockwise = pUI -> isRight();
   }

private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};
