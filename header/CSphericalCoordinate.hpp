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
        static constexpr double ANGULAR_MIN = -180.0;
        static constexpr double ANGULAR_MAX = 180.0;
        // Theta-value
        CProperty<double> Pitch;
        // Phi-value
        CProperty<double> Roll;
        // Psi-value
        CProperty<double> Yaw;
        // Default constructor
        CSphericalCoordinate(){}
        // Constructor
        CSphericalCoordinate(double pitch, double roll, double yaw);
        // Constructor with CProperty types
        CSphericalCoordinate(const CProperty<double>& pitch, 
                                const CProperty<double>& roll, 
                                const CProperty<double>& yaw);
};


#endif // C_SPHERICAL_COORDINATE_H
