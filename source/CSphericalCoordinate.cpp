/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CSphericalCoordinate.cpp                                        *
 * Purpose:         To define a spherical coordinates class                         *
 * Description:     This defines a class of three angular coordinate values.        *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries
#include <iostream>
#include <cfloat>

//Internal Headers
#include "../header/CSphericalCoordinate.hpp"


/************************************ GLOBALS **************************************/


/***************************** FUNCTIONS DEFINITIONS********************************/

/*===========================================================================
 * Function:        CLinearCoordinate::CLinearCoordinate()
 * Arguments:       double pitch - Theta value
 *                  double roll   - Phi value
 *                  double yaw   - Psi value
 * Returns:         none      
 * Description:     Linear Coordinate class constructor
 */
CSphericalCoordinate::CSphericalCoordinate(double pitch, double roll, double yaw){
    //Setting with DBL_MIN and DBL_MAX since we are not imposing setter restrictions on this one
    this->Pitch = CProperty(pitch, ANGULAR_MIN, ANGULAR_MAX);
    this->Roll   = CProperty(roll, ANGULAR_MIN, ANGULAR_MAX);
    this->Yaw   = CProperty(yaw, ANGULAR_MIN, ANGULAR_MAX);

}

/*===========================================================================
 * Function:        CLinearCoordinate::CLinearCoordinate()
 * Arguments:       CProperty<double> pitch - Theta value
 *                  CProperty<double> roll   - Phi value
 *                  CProperty<double> yaw   - Psi value
 * Returns:         none      
 * Description:     Linear Coordinate class constructor
 */
CSphericalCoordinate::CSphericalCoordinate(const CProperty<double>& pitch, 
                                            const CProperty<double>& roll, 
                                            const CProperty<double>& yaw){
    this->Pitch = pitch;
    this->Roll   = roll;
    this->Yaw   = yaw;
}