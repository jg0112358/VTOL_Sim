/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            state.cpp                                                       *
 * Purpose:         To define a state class                                         *
 * Description:     This defines a state class, with getters and setters, and a     *
 *                  property template to implement the getters/setters              *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries
#include <iostream>

//Internal Headers
#include "../header/CState.hpp"

/************************************ GLOBALS **************************************/


/***************************** FUNCTIONS DEFINITIONS********************************/

/*===========================================================================
 * Function:        CState::CState()
 * Arguments:       none 
 * Returns:         none
 * Description:     Default constructor
 */
CState::CState(): LinearPositions(CLinearCoordinate(0, 0, 0)), 
                    LinearVelocities(CLinearCoordinate(0, 0, 0)),
                    AngularPositions(CSphericalCoordinate(0, 0, 0)), 
                    AngularVelocities(CSphericalCoordinate(0, 0, 0)) {}

/*===========================================================================
 * Function:        CState::CState()
 * Arguments:       x    - initial X value
 *                  y    - initial Y value
 *                  z    - initial Z value
 *                  xDot - initial XDot value
 *                  yDot - initial YDot value
 *                  zDot - initial ZDot value 
 * Returns:         none
 * Description:     Default constructor
 */
CState::CState(double x, double y, double z, double xDot, double yDot, double zDot):
                    LinearPositions(CLinearCoordinate(x, y, z)), 
                    LinearVelocities(CLinearCoordinate(xDot, yDot, zDot)),
                    AngularPositions(CSphericalCoordinate(0, 0, 0)), 
                    AngularVelocities(CSphericalCoordinate(0, 0, 0)) {}

/*===========================================================================
 * Function:        CState::CState()
 * Arguments:       x - initial X value
 *                  y - initial Y value
 *                  z - initial Z value
 *                  xDot - initial XDot value
 *                  yDot - initial YDot value
 *                  zDot - initial ZDot value 
 *                  theta - inital Theta value
 *                  phi - initial Phi value
 *                  psi - initial Psi value
 *                  thetaDot - initial ThetaDot value
 *                  phiDot - initial PhiDot value
 *                  psiDot - initial PsiDot value
 * Returns:         none
 * Description:     Default constructor
 */
CState::CState(double x, double y, double z, double xDot, double yDot, double zDot,
                    double theta, double phi, double psi, double thetaDot, double phiDot, double psiDot):
                    LinearPositions(CLinearCoordinate(x, y, z)), 
                    LinearVelocities(CLinearCoordinate(xDot, yDot, zDot)),
                    AngularPositions(CSphericalCoordinate(theta, phi, psi)), 
                    AngularVelocities(CSphericalCoordinate(thetaDot, phiDot, psiDot)) {}