/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            state.cpp                                                       *
 * Purpose:         To define a state class                                         *
 * Description:     This defines a state class, with getters and setters, and a     *
 *                  property template to implement the getters/setters              *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries
#include <iostream>

//Internal Headers
#include "CProperty.hpp"

/************************************ GLOBALS **************************************/


/***************************** FUNCTIONS DEFINITIONS********************************/

/*===========================================================================
 * Function:        CProperty<T>::CProperty
 * Arguments:       const T& value - initialization value to set in CProperty 
                    const T& maxValue - max value for setter
                    const T& minValue - min value for setter
 * Returns:         none
 * Description:     Property class constructor
 */
template <typename T>
CProperty<T>::CProperty(const T& value, const T& maxValue, const T& minValue):Value(value), MaxValue(maxValue), MinValue(minValue) {};

/*===========================================================================
 * Function:        CProperty<T>::get()
 * Arguments:       none
 * Returns:         T Value - the value stored in property
 * Description:     main function
 */
template <typename T>
const T& CProperty<T>::get() const{
    return this->Value;
}

/*===========================================================================
 * Function:        main
 * Arguments:       int argc - Number of command line arguments 
                    char *argv[] - Array of command line arguments 
 * Returns:         int - 0 on success, 1 on fail
 * Description:     main function
 */
template <typename T>
void CProperty<T>::set(const T& newValue) {
    if((newValue > this->MaxValue) || (newValue < this->MinValue)) {
        throw std::out_of_range;
    } else {
        this->Value = newValue;
        return;
    }
}
