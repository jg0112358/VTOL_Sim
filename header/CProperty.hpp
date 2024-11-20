/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CProperty.hpp                                                   *
 * Purpose:         To define a property template class                             *
 * Description:     This defines a template class to be used as properties with     *
 *                  .get() and .set() methods. Must be able to evaluate with "<"    *
 *                  and ">" operators for max/min values.                           *
 ***********************************************************************************/

#ifndef C_PROPERTY_H
#define C_PROPERTY_H

template <typename T>
class CProperty{
    private:
        // Value to be stored in the property
        T Value;
        // Max value when using set()
        T MaxValue;
        // Min value when using set()
        T MinValue;
    public:
        //Default constructor 
        CProperty(){}
        // Class constructor
        CProperty(const T& value, const T& minValue, const T& maxValue);
        // Getter
        const T& get() const{};
        // Setter
        void set(const T& newValue) {};
};

#endif // C_PROPERTY_H
