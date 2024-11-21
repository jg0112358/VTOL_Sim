/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CInput.hpp                                                      *
 * Purpose:         To define an inputs class                                       *
 * Description:     This defines a class for input vector                           *
 ***********************************************************************************/

#ifndef C_MOTOR_LIST_H
#define C_MOTOR_LIST_H

#include "CMotor.hpp"

class CMotorList{
    public:
        // Front Left
        CMotor FrontLeft;
        // Front Right
        CMotor FrontRight;
        //Rear
        CMotor Rear;
    public:
        // Default Motor List Constructor
        CMotorList(){}
        // Motor List Constructor
        CMotorList(CMotor frontLeft, CMotor frontRight, CMotor rear);
};


#endif // C_MOTOR_LIST_H
