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
const double ANGULAR_MIN = 0.0;
const double ANGULAR_MAX = 360.0;

/***************************** FUNCTIONS DEFINITIONS********************************/

/*===========================================================================
 * Function:        CLinearCoordinate::CLinearCoordinate()
 * Arguments:       double theta - Theta value
 *                  double phi   - Phi value
 *                  double psi   - Psi value
 * Returns:         none      
 * Description:     Linear Coordinate class constructor
 */
CSphericalCoordinate::CSphericalCoordinate(double theta, double phi, double psi){
    //Setting with DBL_MIN and DBL_MAX since we are not imposing setter restrictions on this one
    this->Theta = CProperty(theta, ANGULAR_MIN, ANGULAR_MAX);
    this->Phi   = CProperty(phi, ANGULAR_MIN, ANGULAR_MAX);
    this->Psi   = CProperty(psi, ANGULAR_MIN, ANGULAR_MAX);

}

