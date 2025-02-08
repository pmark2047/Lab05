/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;
class TestLander;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
public:
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestLander;
   
   // Constructors
   Angle()                 : radians(0.0)  {}
   Angle(const Angle& rhs) : radians(rhs.radians)  {}
   Angle(double degrees)   : radians((degrees/360) * 2 * M_PI)  {}

   // Getters
   double getDegrees() const { return ((radians / (2 * M_PI)) * 360); }
   double getRadians() const { return radians; }

   // Setters
   void setDegrees(double degrees) {this->radians = normalize((degrees/360) * 2 * M_PI);}
   void setRadians(double radians) {this->radians = normalize(radians);}
   void setUp()                    {radians = 0.0;}
   void setDown()                  {radians = M_PI;}
   void setRight()                 {radians = M_PI/2;}
   void setLeft()                  {radians = M_PI * 1.5;}
   void reverse()                  {radians += M_PI;}
   Angle& add(double delta) { radians = normalize(radians + delta); return *this; }

private:
   double normalize(double radians) const;

   double radians;   // 360 degrees equals 2 PI radians
};

