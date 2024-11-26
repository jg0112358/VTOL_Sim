/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            state.cpp                                                       *
 * Purpose:         To define a state class, and declare its methods                *
 * Description:     This defines a state class, with getters and setters, and a     *
 *                  property template to implement the getters/setters              *
 ***********************************************************************************/

#ifndef C_STATE_H
#define C_STATE_H

#include <cfloat>
#include "CLinearCoordinate.hpp"
#include "CSphericalCoordinate.hpp"

class CState {
public:
  CProperty<double> time = CProperty<double>(0,0,DBL_MAX);
  // Values of X, Y, Z
  CLinearCoordinate LinearPositions;
  // Values of XDot, YDot, ZDot (Absolute Reference Frame)
  CLinearCoordinate LinearVelocities;
  // Values of Pitch, Roll, Yaw (Pitch and Roll relative to traveling reference frame, Yaw relative to absolute)
  CSphericalCoordinate AngularPositions;
  // Values of PitchDot, RollDot, YawDot
  CSphericalCoordinate AngularVelocities;
  //Default Constructor
  CState();
  //Linear Constructor (3-axis/6-var)
  CState(double x, double y, double z, double xDot, double yDot, double zDot);
  //Full Constructor (6-axis/12-var)
  CState(double x, double y, double z, double xDot, double yDot, double zDot,
         double theta, double phi, double psi, double thetaDot, double phiDot, double psiDot);

};


#endif // C_STATE_H
