/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CMotor.hpp                                                      *
 * Purpose:         To define a Motor class                                         *
 * Description:     This defines a class for Motors                                 *
 ***********************************************************************************/

#ifndef C_MOTOR_H
#define C_MOTOR_H

#include "CProperty.hpp"
#include "CLinearCoordinate.hpp"
#include "CSphericalCoordinate.hpp"

class CMotor{
    public:
        // Motor Thrust value (N)
        CProperty<double> Thrust;
        // Position of motor relative to C.O.G. (m)
        const CLinearCoordinate RelativeLinearPosition;
        // Angle of motor thrust vector relative to inertial reference frame (deg)
        CSphericalCoordinate RelativeAngularPosition;
    public:
        //Default Motor Constructor
        CMotor(){}
        // Motor Constructor (value based)
        CMotor(double initialThrust, double x, double y, double z, double initialAngle, bool fixed=false);
        // Motor Constructor (property based)
        CMotor(const CProperty<double>& thrust, const CLinearCoordinate& relativeLinearPosition,
                                            const CProperty<double>& angularPosition);
};


#endif // C_MOTOR_H
