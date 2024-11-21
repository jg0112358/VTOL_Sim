/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CInputVector.hpp                                                *
 * Purpose:         To define an inputs class                                       *
 * Description:     This defines a class for input vector                           *
 ***********************************************************************************/

#ifndef C_INPUT_VECTOR_H
#define C_INPUT_VECTOR_H

#include "CControlSurfaces.hpp"
#include "CMotorList.hpp"

class CInputVector{
    public:
        // Control Surfaces
        CControlSurfaces ControlSurfaces;
        // Motors
        CMotorList Motors;
    public:
        // Default Input Vector Constructor
        CInputVector(){}
        // Input Vector Constructor
        CInputVector(CControlSurfaces controlSurfaces,CMotorList motors);
};


#endif // C_INPUT_VECTOR_H
