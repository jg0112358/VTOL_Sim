/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CControlSurfaces.hpp                                            *
 * Purpose:         To define a Control Surfaces class                              *
 * Description:     This defines a class for Control Surfaces                       *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries
#include <iostream>


//Internal Headers
#include "../header/CControlSurfaces.hpp"


/************************************ GLOBALS **************************************/


/***************************** FUNCTIONS DEFINITIONS********************************/

/*===========================================================================
 * Function:        CControlSurfaces::CControlSurfaces()
 * Arguments:       CProperty<double> elevator - initial elevator angle with min/max
 *                  CProperty<double> rudder - initial rudder angle with min/max
 *                  CProperty<double> leftAileron 
 *                              - initial left aileron angle with min/max
 *                  CProperty<double> rightAileron 
 *                              - initial right aileron angle with min/max
 * Returns:         none      
 * Description:     Motor Constructor (value based)
 */
CControlSurfaces::CControlSurfaces(CProperty<double> elevator, CProperty<double> rudder, 
                            CProperty<double> leftAileron, CProperty<double> rightAileron): 
    ElevatorAngle(elevator),
    RudderAngle(rudder),
    LeftAileronAngle(leftAileron),
    RightAileronAngle(rightAileron)
{}

