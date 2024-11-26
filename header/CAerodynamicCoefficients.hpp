/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CAerodynamicCoefficients.hpp                                    *
 * Purpose:         To define a class to store interpolated coefficients            *
 * Description:     This defines a class for aerodynamic coefficients               *
 ***********************************************************************************/

#ifndef C_AERODYNAMIC_COEFFICIENTS_H
#define C_AERODYNAMIC_COEFFICIENTS_H

#include "CProperty.hpp"
#include "CLinearCoordinate.hpp"
#include "CSphericalCoordinate.hpp"

class CAerodynamicCoefficients{
    public:
        // Lift Coefficient
        CProperty<double> CLift;
        // Drag Coefficient
        CProperty<double> CDrag;
        // SideForce Coefficient
        CProperty<double> CSideForce;
        // Pitch Moment Coefficient
        CProperty<double> CPitchMom;
        // Roll Moment Coefficient
        CProperty<double> CRollMom;
        // Yaw Moment Coefficient
        CProperty<double> CYawMom;
    public:
        //Default Motor Constructor
        CAerodynamicCoefficients(){}
        // Motor Constructor (value based)
        CAerodynamicCoefficients(double cLift, double cDrag, double cSideForce, double cPitchMom, double cRollMom, double cYawMom):
                            CLift(CProperty<double>(cLift, 0, 10)),CDrag(CProperty<double>(cDrag, 0, 10)),CSideForce(CProperty<double>(cSideForce, 0, 10)),
                            CPitchMom(CProperty<double>(cPitchMom, 0, 10)),CRollMom(CProperty<double>(cRollMom, 0, 10)),CYawMom(CProperty<double>(cYawMom, 0, 10)) {}
        // Motor Constructor (property based)
        CAerodynamicCoefficients(CProperty<double> cLift, CProperty<double> cDrag, CProperty<double> cSideForce,
                                 CProperty<double> cPitchMom, CProperty<double> cRollMom, CProperty<double> cYawMom):
                                 CLift(cLift), CDrag(cDrag), CSideForce(cSideForce),
                                 CPitchMom(cPitchMom), CRollMom(cRollMom),
                                 CYawMom(cYawMom) {}
};


#endif // C_AERODYNAMIC_COEFFICIENTS_H
