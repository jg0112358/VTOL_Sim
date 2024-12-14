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
#include <fstream>
#include <sstream>

//Internal Headers
#include "../header/CState.hpp"
#include "../header/CInputVector.hpp"
#include "../header/CDynamicsUpdater.hpp"
#include "../header/CInputParser.hpp"

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
  if (argc != 2){
    std::cout << "please input the inputseries.csv filename\n";
    return 0;
  }

  CState state = CState();
  std::vector<CInputVector> inputArray;
  CInputParser::ParseInputs(argv[1], inputArray);

  std::cout << "\n System Initialized, running execution... \n\n";
  
  std::cout << "THE INPUT, STATE IS: \n";
  std::cout << "Time, " << "Left, " << "Right, " << "Elev, " <<  "Rudd, " << "FLMotor(N), " << "FRMotor(N), " << "RearMotor(N), " 
              << "FLMotor(deg), " << "FRMotor(deg), " << "X, " <<  "Y, " << "Z, " << "Xdot, " << "Ydot, " << "Zdot, " 
              <<  "Pitch, " <<  "Roll, " << "Yaw, " << "PitchDot, " << "RollDot, " << "YawDot" << std::endl;

  int runLength = inputArray.size();
  
  // file pointer
  std::fstream fout;
  std::string outputFileName = "output_file.csv";

  // opens an existing csv file or creates a new file.
  fout.open(outputFileName, std::ios::out);

  fout << "Time, " << "Left, " << "Right, " << "Elev, " <<  "Rudd, " << "FLMotor(N), " << "FRMotor(N), " << "RearMotor(N), " 
            << "FLMotor(deg), " << "FRMotor(deg), " << "X, " <<  "Y, " << "Z, " << "Xdot, " << "Ydot, " << "Zdot, " 
            <<  "Pitch, " <<  "Roll, " << "Yaw, " << "PitchDot, " << "RollDot, " << "YawDot" << std::endl;

  for (int i = 0; i < runLength; i++){

    CDynamicsUpdater::UpdateStates(inputArray[i], state);

    std::cout << state.time.get() << ", " << inputArray[i].ControlSurfaces.LeftAileronAngle.get() << ", "
              << inputArray[i].ControlSurfaces.RightAileronAngle.get() << ", "<< inputArray[i].ControlSurfaces.ElevatorAngle.get()  
              << ", "<<  inputArray[i].ControlSurfaces.RudderAngle.get() << ", " << inputArray[i].Motors.FrontLeft.Thrust.get() << ", "
              << inputArray[i].Motors.FrontRight.Thrust.get() << ", "<< inputArray[i].Motors.Rear.Thrust.get() << ", "
              << inputArray[i].Motors.FrontLeft.RelativeAngularPosition.Pitch.get() << ", "
              << inputArray[i].Motors.FrontRight.RelativeAngularPosition.Pitch.get() << ", "
              << state.LinearPositions.X.get() << ", "<<  state.LinearPositions.Y.get() << ", "
              << state.LinearPositions.Z.get() << ", "<< state.LinearVelocities.X.get() << ", "
              << state.LinearVelocities.Y.get() << ", "<< state.LinearVelocities.Z.get() << ", "
              << state.AngularPositions.Pitch.get() << ", "<<  state.AngularPositions.Roll.get() << ", "
              << state.AngularPositions.Yaw.get() << ", "<< state.AngularVelocities.Pitch.get() << ", "
              << state.AngularVelocities.Roll.get() << ", "<< state.AngularVelocities.Yaw.get() << std::endl;
  
    fout << state.time.get() << ", " << inputArray[i].ControlSurfaces.LeftAileronAngle.get() << ", "
          << inputArray[i].ControlSurfaces.RightAileronAngle.get() << ", "<< inputArray[i].ControlSurfaces.ElevatorAngle.get()  
          << ", "<<  inputArray[i].ControlSurfaces.RudderAngle.get() << ", " << inputArray[i].Motors.FrontLeft.Thrust.get() << ", "
          << inputArray[i].Motors.FrontRight.Thrust.get() << ", "<< inputArray[i].Motors.Rear.Thrust.get() << ", "
          << inputArray[i].Motors.FrontLeft.RelativeAngularPosition.Pitch.get() << ", "
          << inputArray[i].Motors.FrontRight.RelativeAngularPosition.Pitch.get() << ", "
          << state.LinearPositions.X.get() << ", "<<  state.LinearPositions.Y.get() << ", "
          << state.LinearPositions.Z.get() << ", "<< state.LinearVelocities.X.get() << ", "
          << state.LinearVelocities.Y.get() << ", "<< state.LinearVelocities.Z.get() << ", "
          << state.AngularPositions.Pitch.get() << ", "<<  state.AngularPositions.Roll.get() << ", "
          << state.AngularPositions.Yaw.get() << ", "<< state.AngularVelocities.Pitch.get() << ", "
          << state.AngularVelocities.Roll.get() << ", "<< state.AngularVelocities.Yaw.get() << std::endl;
  }
 
  return 0;
}


