/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CLinearCoordinate.hpp                                           *
 * Purpose:         To define a linear coordinate class                             *
 * Description:     This defines a class to house linear coordinat                  *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries
#include <iostream>
#include <cfloat>

//Internal Headers
#include "../header/CLinearCoordinate.hpp"


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
    
    return;
}

/*===========================================================================
 * Function:        CLinearCoordinate::CLinearCoordinate()
 * Arguments:       CProperty<double> x - X value with min/max
 *                  CProperty<double> y - Y value with min/max
 *                  CProperty<double> z - Z value with min/max
 * Returns:         none      
 * Description:     Linear Coordinate class constructor with custom min/max 
 *                  set values
 */
CLinearCoordinate::CLinearCoordinate(const CProperty<double>& x,
                                const CProperty<double>& y,
                                const CProperty<double>& z){
    this->X = x;
    this->Y = y;
    this->Z = z;
    
    return;
}

