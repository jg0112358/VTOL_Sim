/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CSphericalCoordinate.hpp                                        *
 * Purpose:         To define a spherical coordinates class                         *
 * Description:     This defines a class of three angular coordinate values.        *
 ***********************************************************************************/

#ifndef C_SPHERICAL_COORDINATE_H
#define C_SPHERICAL_COORDINATE_H

#include "CProperty.hpp"

class CSphericalCoordinate{
    public:
        // Theta-value
        CProperty<double> Theta;
        // Phi-value
        CProperty<double> Phi;
        // Psi-value
        CProperty<double> Psi;
        //Constructor
        CSphericalCoordinate(double theta, double phi, double psi);
};


#endif // C_SPHERICAL_COORDINATE_H
