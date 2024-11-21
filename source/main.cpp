/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            main.cpp                                                        *
 * Purpose:         To create a simulated model of my VTOL aircraft for data-gen    *
 * Description:     This script is intended to take the flow5 simulation op-points, *
 *                  and combine them with basic vector mechanics and simulation of  *
 *                  the motor and propellers, and the battery to create a discrete- *
 *                  time state-space model of the VTOL aircraft. It is expected that*
 *                  this will not be a perfect representation of the aircraft, but  *
 *                  will be sufficient.                                             *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries
#include <iostream>

//Internal Headers
#include "../header/CState.hpp"
#include "../header/CInputVector.hpp"

/************************************ GLOBALS **************************************/


/***************************** FUNCTIONS DEFINITIONS********************************/
/*===========================================================================
 * Function:        main
 * Arguments:       int argc - Number of command line arguments 
                    char *argv[] - Array of command line arguments 
 * Returns:         int - 0 on success, 1 on fail
 * Description:     main function
 */
int main(int argc, char *argv[]){
  CLinearCoordinate Lin = CLinearCoordinate(1,2,3);
  
  double a = Lin.X.get();
  a=5;
  Lin.Y.set(a);

  CState state = CState();

  double b=state.LinearPositions.X.get();

  CInputVector inputs = CInputVector(CControlSurfaces(), CMotorList());

  double c = inputs.ControlSurfaces.ElevatorAngle.get();
  
  return (int)(b+c);
}


