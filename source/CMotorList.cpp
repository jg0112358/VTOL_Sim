/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CMotorList.cpp                                                  *
 * Purpose:         To define the methods for CMotorList                            *
 * Description:     This defines methods for a class CMotorList                     *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries

//Internal Headers
#include "../header/CMotorList.hpp"


/************************************ GLOBALS **************************************/

/***************************** FUNCTIONS DEFINITIONS********************************/

/*===========================================================================
 * Function:        CMotorList::CMotorList()
 * Arguments:       CMotor frontLeft - front left motor
 *                  CMotor frontRight - front right motor
 *                  CMotor rear - rear motor
 * Returns:         none      
 * Description:     Motor Constructor (value based)
 */
CMotorList::CMotorList(CMotor frontLeft, CMotor frontRight, CMotor rear): 
    FrontLeft(frontLeft),
    FrontRight(frontRight),
    Rear(rear) 
{}
