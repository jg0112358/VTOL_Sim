/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            state.cpp                                                       *
 * Purpose:         To define a state class, and declare its methods                *
 * Description:     This defines a state class, with getters and setters, and a     *
 *                  property template to implement the getters/setters              *
 ***********************************************************************************/

#ifndef C_STATE_H
#define C_STATE_H


#include <vector>
#include <tuple>

class CComplexMatrix {
private:
  std::vector<std::vector<CComplexNumber>> Matrix;
  int numRows;
  int numCols;
public:
  //Default Constructor
  CComplexMatrix();
  //Constructor for specific size
  CComplexMatrix(int row, int col);
  //Constructor
  CComplexMatrix(std::vector<std::vector<CComplexNumber>> matrix);
  //Method to write any one element with a new complex number
  bool WriteElement(int row, int column, CComplexNumber value);
  //Method to read an element of the matrix
  CComplexNumber ReadElement(int row, int column) const;
  //Method to overload the * operator for matrix multiplication
  CComplexMatrix operator*(const CComplexMatrix& argument);
  //Method to get the size of the matrix
  std::tuple<int,int> GetSize();
  //Method to display the matrix
  bool Display();
  //Destructor
  ~CComplexMatrix();
};


#endif // C_STATE_H
