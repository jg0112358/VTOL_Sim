/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CMotor.cpp                                                      *
 * Purpose:         To define the methods for CMotor                                *
 * Description:     This defines methods for a class CMotor                         *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries
#include <iostream>
#include <cfloat>

//Internal Headers
#include "../header/CMotor.hpp"


/************************************ GLOBALS **************************************/
const double THETA_MIN = 0.0;
const double THETA_MAX = 90.0;

/***************************** FUNCTIONS DEFINITIONS********************************/

/*===========================================================================
 * Function:        CMotor::CMotor()
 * Arguments:       double thrust - initial Thrust value
 *                  double x   - const X value (RelativeLinearPosition)
 *                  double y   - const Y value (RelativeLinearPosition)
 *                  double z   - const Z value (RelativeLinearPosition)
 *                  double initialAngle   - inital Theta value (RelativeAngularPosition)
 * Returns:         none      
 * Description:     Motor Constructor (value based)
 */
CMotor::CMotor(double initialThrust, double x, double y, double z, double initialAngle, bool fixed): 
    Thrust(CProperty<double>(initialThrust,0,100)),
    RelativeLinearPosition(CLinearCoordinate(CProperty<double>(x,x,x),
                                                CProperty<double>(y,y,y),
                                                CProperty<double>(z,z,z))),
    RelativeAngularPosition(CSphericalCoordinate(fixed ? CProperty<double>(initialAngle,initialAngle,initialAngle) : CProperty<double>(initialAngle,0,90), 
                                                            CProperty<double>(0,0,0), 
                                                            CProperty<double>(0,0,0))) 
{}

/*===========================================================================
 * Function:        CMotor::CMotor()
 * Arguments:       CProperty<double> thrust - initial Thrust value with min/max
 *                  CLinearCoordinate relativeLinearPosition - relative position
 *                  double initialAngle   - inital Theta value (RelativeAngularPosition)
 * Returns:         none      
 * Description:     Motor Constructor (value based)
 */
CMotor::CMotor(const CProperty<double>& thrust, const CLinearCoordinate& relativeLinearPosition,
                                            const CProperty<double>& angularPosition):
    Thrust(thrust),
    RelativeLinearPosition(relativeLinearPosition),
    RelativeAngularPosition(CSphericalCoordinate(angularPosition, 
                                                    CProperty<double>(0,0,0), 
                                                    CProperty<double>(0,0,0)))
{}