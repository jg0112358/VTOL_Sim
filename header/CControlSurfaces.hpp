/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CControlSurfaces.hpp                                            *
 * Purpose:         To define a Control Surfaces class                              *
 * Description:     This defines a class for Control Surfaces                       *
 ***********************************************************************************/

#ifndef C_CONTROL_SURFACES_H
#define C_CONTROL_SURFACES_H

#include "CProperty.hpp"
#include "CLinearCoordinate.hpp"
#include "CSphericalCoordinate.hpp"

class CControlSurfaces{
    public:
        //Default max deflection (deg)
        static const inline double DEFAULT_MIN_DEFLECTION = -18;
        //Default min deflection (deg)
        static const inline double DEFAULT_MAX_DEFLECTION = 18;
        // Elevator (deg)
        CProperty<double> ElevatorAngle = CProperty<double>(0, DEFAULT_MIN_DEFLECTION, DEFAULT_MAX_DEFLECTION);
        // Rudder (deg)
        CProperty<double> RudderAngle = CProperty<double>(0, DEFAULT_MIN_DEFLECTION, DEFAULT_MAX_DEFLECTION);
        // Left Aileron (deg)
        CProperty<double> LeftAileronAngle = CProperty<double>(0, DEFAULT_MIN_DEFLECTION, DEFAULT_MAX_DEFLECTION);
        // Right Aileron (deg)
        CProperty<double> RightAileronAngle = CProperty<double>(0, DEFAULT_MIN_DEFLECTION, DEFAULT_MAX_DEFLECTION);
    public:
        // Default Control Surfaces Constructor
        CControlSurfaces(){}
        // Control Surfaces Constructor
        CControlSurfaces(CProperty<double> elevator, CProperty<double> rudder, 
                            CProperty<double> leftAileron, CProperty<double> rightAileron);
};


#endif // C_CONTROL_SURFACES_H
