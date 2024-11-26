/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CInputParser.cpp                                                *
 * Purpose:         To define a Control Surfaces class                              *
 * Description:     This defines a class for Control Surfaces                       *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>


//Internal Headers
#include "../header/CInputParser.hpp"


/************************************ GLOBALS **************************************/


/***************************** FUNCTIONS DEFINITIONS********************************/

/*===========================================================================
 * Function:        CInputParser::ParseInputs()
 * Arguments:       CProperty<double> elevator - initial elevator angle with min/max
 *                  CProperty<double> rudder - initial rudder angle with min/max
 *                  CProperty<double> leftAileron 
 *                              - initial left aileron angle with min/max
 *                  CProperty<double> rightAileron 
 *                              - initial right aileron angle with min/max
 * Returns:         none      
 * Description:     Motor Constructor (value based)
 */
 bool CInputParser::ParseInputs(std::string filePath, std::vector<CInputVector>& inputs){
    // Open the CSV file
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Error opening file!" << std::endl;
        throw std::runtime_error("Unable to load csv file in CInputParser::ParseInputs");
    }


    std::array<double, 9> inputrow;
    CInputVector inputVector;
    std::string line;

    int row = 0;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        int col = 0;
        while (getline(ss, cell, ',')) {
            inputrow[col] = stod(cell);
            col++;
        }
        
        

        inputVector.ControlSurfaces.LeftAileronAngle.set(inputrow[0]);
        inputVector.ControlSurfaces.RightAileronAngle.set(inputrow[1]);
        inputVector.ControlSurfaces.ElevatorAngle.set(inputrow[2]);
        inputVector.ControlSurfaces.RudderAngle.set(inputrow[3]);
        inputVector.Motors.FrontLeft.Thrust.set(inputrow[4]);
        inputVector.Motors.FrontLeft.RelativeAngularPosition.Pitch.set(inputrow[5]);
        inputVector.Motors.FrontRight.Thrust.set(inputrow[6]);
        inputVector.Motors.FrontRight.RelativeAngularPosition.Pitch.set(inputrow[7]);
        inputVector.Motors.Rear.Thrust.set(inputrow[8]);


        inputs.push_back(inputVector);
        row++;
    }

    // close the file after read opeartion is complete
    file.close();

    std::cout << "File parsed successfully!";

    return true;
}


