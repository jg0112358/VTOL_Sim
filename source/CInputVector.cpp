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
#include "../header/CInputVector.hpp"


/************************************ GLOBALS **************************************/

/***************************** FUNCTIONS DEFINITIONS********************************/

/*===========================================================================
 * Function:        CInputVector::CInputVector()
 * Arguments:       CControlSurfaces controlSurfaces - control surfaces initial state
 *                  CMotorList motors - motors initial state
 * Returns:         none      
 * Description:     Motor Constructor (value based)
 */
CInputVector::CInputVector(CControlSurfaces controlSurfaces,CMotorList motors): 
    ControlSurfaces(controlSurfaces),
    Motors(motors)
{}
