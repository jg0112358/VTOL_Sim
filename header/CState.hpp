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

#include "CLinearCoordinate.hpp"
#include "CSphericalCoordinate.hpp"

class CState {
public:
  // Values of X, Y, Z
  CLinearCoordinate LinearPositions;
  // Values of XDot, YDot, ZDot
  CLinearCoordinate LinearVelocities;
  // Values of Theta, Phi, Psi
  CSphericalCoordinate AngularPositions;
  // Values of ThetaDot, PhiDot, PsiDot
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
