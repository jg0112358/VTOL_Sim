/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CCoord.hpp                                                      *
 * Purpose:         To define a coordinates class                                   *
 * Description:     This defines a class of three coordinate values.                *
 ***********************************************************************************/

#ifndef C_COORD_H
#define C_COORD_H

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


#endif // C_COORD_H
