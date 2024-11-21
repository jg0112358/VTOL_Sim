/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CProperty.cpp                                                   *
 * Purpose:         To define a property template class                             *
 * Description:     This defines a template class to be used as properties with     *
 *                  .get() and .set() methods. Must be able to evaluate with "<"    *
 *                  and ">" operators for max/min values.                           *
 ***********************************************************************************/
 
/*********************************** INCLUDES **************************************/
//Libraries
#include <iostream>
#include <format>
#include <string>
#include <stdexcept>

//Internal Headers
#include "../header/CProperty.hpp"

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
CProperty<T>::CProperty(const T& value, const T& minValue, const T& maxValue):Value(value), MaxValue(maxValue), MinValue(minValue) {};

/*===========================================================================
 * Function:        CProperty<T>::get()
 * Arguments:       none
 * Returns:         T Value - the value stored in property
 * Description:     getter
 */
template <typename T>
const T& CProperty<T>::get() const{
    return this->Value;
}

/*===========================================================================
 * Function:        CProperty<T>::set()
 * Arguments:       const T& newValue - new value to set in CProperty
 * Returns:         int - 0 on success, 1 on fail
 * Description:     setter with min/max limits
 */
template <typename T>
void CProperty<T>::set(const T& newValue) {
    if((newValue > this->MaxValue) || (newValue < this->MinValue)) {
        std::string message = std::format("Set a value within the bounds of {} and {}", 
                                                    this->MinValue , this->MaxValue);
        throw std::out_of_range(message);
    } else {
        this->Value = newValue;
        return;
    }
}

//Add support for all types desired:
template class CProperty<double>;