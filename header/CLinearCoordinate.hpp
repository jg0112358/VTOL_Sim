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
        // Y-value
        CProperty<double> Y;
        // Z-value
        CProperty<double> Z;
        //Default Constructor
        CLinearCoordinate(){}
        //Constructor
        CLinearCoordinate(double x, double y, double z);
        //Constructor with custom min/max
        CLinearCoordinate(const CProperty<double>& x,
                            const CProperty<double>& y,
                            const CProperty<double>& z);
};


#endif // C_LINEAR_COORDINATE_H
