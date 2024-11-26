/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CInputParser.hpp                                                *
 * Purpose:         To define a class to store interpolated coefficients            *
 * Description:     This defines a class for aerodynamic coefficients               *
 ***********************************************************************************/

#ifndef C_INPUT_PARSER_H
#define C_INPUT_PARSER_H

#include <vector>
#include <array>
#include <string>
#include "CInputVector.hpp"

class CInputParser{
    public://Values

    public://Methods
        bool static ParseInputs(std::string filePath, std::vector<CInputVector>& inputs);
};


#endif // C_INPUT_PARSER_H
