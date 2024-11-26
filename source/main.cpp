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
#include "../header/CDynamicsUpdater.hpp"

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

  CState state = CState();
  CInputVector inputs = CInputVector(CControlSurfaces(), CMotorList(CMotor(9.81,0.35,1,0,90), CMotor(9.81,0.35,-1,0,90), CMotor(9.81,-0.7,0,0,90)));

  std::cout << "THE STATE IS: \n";
  std::cout << "Time: " << state.time.get() << std::endl;
  std::cout << "X: " << state.LinearPositions.X.get() << " | Y: " 
                    << state.LinearPositions.Y.get() << " | Z: " << state.LinearPositions.Z.get() << std::endl;
  std::cout << "Xdot: " << state.LinearVelocities.X.get() << " | Ydot: " 
                    << state.LinearVelocities.Y.get() << " | Zdot: " << state.LinearVelocities.Z.get() << std::endl;
  std::cout << "Pitch: " << state.AngularPositions.Pitch.get() << " | Roll: " 
                    << state.AngularPositions.Roll.get() << " | Yaw: " << state.AngularPositions.Yaw.get() << std::endl;
  std::cout << "PitchDot: " << state.AngularVelocities.Pitch.get() << " | RollDot: " 
                    << state.AngularVelocities.Roll.get() << " | YawDot: " << state.AngularVelocities.Yaw.get() << std::endl;
  std::cout << "THE INPUT IS: \n";
  std::cout << "Left: " << inputs.ControlSurfaces.LeftAileronAngle.get() 
                    << " | Right: " << inputs.ControlSurfaces.RightAileronAngle.get() << std::endl;
  std::cout << "Elev: " << inputs.ControlSurfaces.ElevatorAngle.get() 
                    << " | Rudd: " << inputs.ControlSurfaces.RudderAngle.get() << std::endl;
  std::cout << "FLMotor: " << inputs.Motors.FrontLeft.Thrust.get() 
                    << " | FRMotor: " << inputs.Motors.FrontRight.Thrust.get() 
                    << " | RearMotor: " << inputs.Motors.Rear.Thrust.get() << std::endl;
  std::cout << "FLMotor(deg): " << inputs.Motors.FrontLeft.RelativeAngularPosition.Pitch.get() 
                    << " | FRMotor(deg): " << inputs.Motors.FrontRight.RelativeAngularPosition.Pitch.get() << std::endl;

  for (int i = 0; i < 500; i++){
    std::cout << "\n Updating States... \n\n";
    CDynamicsUpdater::UpdateStates(inputs, state);

    std::cout << "THE STATE IS: \n";
    std::cout << "Time: " << state.time.get() << std::endl;
    std::cout << "X: " << state.LinearPositions.X.get() << " | Y: " 
                      << state.LinearPositions.Y.get() << " | Z: " << state.LinearPositions.Z.get() << std::endl;
    std::cout << "Xdot: " << state.LinearVelocities.X.get() << " | Ydot: " 
                      << state.LinearVelocities.Y.get() << " | Zdot: " << state.LinearVelocities.Z.get() << std::endl;
    std::cout << "Pitch: " << state.AngularPositions.Pitch.get() << " | Roll: " 
                      << state.AngularPositions.Roll.get() << " | Yaw: " << state.AngularPositions.Yaw.get() << std::endl;
    std::cout << "PitchDot: " << state.AngularVelocities.Pitch.get() << " | RollDot: " 
                      << state.AngularVelocities.Roll.get() << " | YawDot: " << state.AngularVelocities.Yaw.get() << std::endl;
    std::cout << "THE INPUT IS: \n";
    std::cout << "Left: " << inputs.ControlSurfaces.LeftAileronAngle.get() 
                      << " | Right: " << inputs.ControlSurfaces.RightAileronAngle.get() << std::endl;
    std::cout << "Elev: " << inputs.ControlSurfaces.ElevatorAngle.get() 
                      << " | Rudd: " << inputs.ControlSurfaces.RudderAngle.get() << std::endl;
    std::cout << "FLMotor: " << inputs.Motors.FrontLeft.Thrust.get() 
                      << " | FRMotor: " << inputs.Motors.FrontRight.Thrust.get() 
                      << " | RearMotor: " << inputs.Motors.Rear.Thrust.get() << std::endl;
    std::cout << "FLMotor(deg): " << inputs.Motors.FrontLeft.RelativeAngularPosition.Pitch.get() 
                      << " | FRMotor(deg): " << inputs.Motors.FrontRight.RelativeAngularPosition.Pitch.get() << std::endl;
  }
 
  return 0;
}


