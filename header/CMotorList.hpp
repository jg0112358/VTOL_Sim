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
        CMotor FrontLeft = CMotor(0,0.35,1,0,90);
        // Front Right
        CMotor FrontRight = CMotor(0,0.35,-1,0,90);
        //Rear
        CMotor Rear = CMotor(0,-0.7,0,0,90, true);
    public:
        // Default Motor List Constructor
        CMotorList(){}
        // Motor List Constructor
        CMotorList(CMotor frontLeft, CMotor frontRight, CMotor rear);
};


#endif // C_MOTOR_LIST_H
