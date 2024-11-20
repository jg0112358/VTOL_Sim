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
// #include ""

/************************************ GLOBALS **************************************/


/***************************** FUNCTIONS DEFINITIONS********************************/
/*===========================================================================
 * Function:        main
 * Arguments:       int argc - Number of command line arguments 
                    char *argv[] - Array of command line arguments 
 * Returns:         int - 0 on success, 1 on fail
 * Description:     main function
 */
template <typename T>
class CProperty{
    private:
        T Value;
        T MaxValue;
        T MinValue;
    public:
        CProperty(const T& value, const T& maxValue, const T& maxValue) : 
                                            Value(value), MaxValue(maxValue), MinValue(minValue) {};
        T get() const{
            return Value;
        }
        void set(const T& newValue) {
            if((newValue > this->MaxValue) || (newValue < this->MinValue)) {
                throw std::out_of_range;
            } else {
                this->Value = newValue;
                return;
            }
        }

};



int main(int argc, char *argv[]){

  
  return 0;
}


