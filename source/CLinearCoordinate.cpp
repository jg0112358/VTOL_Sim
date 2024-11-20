/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CProperty.cpp                                                   *
 * Purpose:         To define a property template class                             *
 * Description:     This defines a template class to be used as properties with     *
 *                  .get() and .set() methods. Must be able to evaluate with "<"    *
 *                  and ">" operators for max/min values.                           *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries
#include <iostream>
#include <cfloat>

//Internal Headers
#include "CLinearCoordinate.hpp"


/************************************ GLOBALS **************************************/


/***************************** FUNCTIONS DEFINITIONS********************************/

/*===========================================================================
 * Function:        CLinearCoordinate::CLinearCoordinate()
 * Arguments:       double x - X value
 *                  double y - Y value
 *                  double z - Z value
 * Returns:         none      
 * Description:     Linear Coordinate class constructor
 */
CLinearCoordinate::CLinearCoordinate(double x, double y, double z){
    //Setting with DBL_MIN and DBL_MAX since we are not imposing setter restrictions on this one
    this->X = CProperty(x, DBL_MIN, DBL_MAX);
    this->Y = CProperty(y, DBL_MIN, DBL_MAX);
    this->Z = CProperty(z, DBL_MIN, DBL_MAX);

}

