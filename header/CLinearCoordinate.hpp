/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CLinearCoordinate.hpp                                           *
 * Purpose:         To define a coordinates class                                   *
 * Description:     This defines a class of three coordinate values.                *
 ***********************************************************************************/

#ifndef C_LINEAR_COORDINATE_H
#define C_LINEAR_COORDINATE_H

#include "CProperty.hpp"

class CLinearCoordinate{
    public:
        // X-value
        CProperty<double> X;
        // X-value
        CProperty<double> Y;
        // X-value
        CProperty<double> Z;
        //Constructor
        CLinearCoordinate(double x, double y, double z);
};


#endif // C_LINEAR_COORDINATE_H
