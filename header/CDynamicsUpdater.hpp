/************************************************************************************
 * Project:         Interpolation-Based Simulator                                   *
 *                                                                                  *
 * Author:          James Guest                                                     *
 * File:            CDynamicsUpdater.cpp                                            *
 * Purpose:         To update the dynamics for each time-step                       *
 * Description:     This defines a dynamics updater class which contains methods    *
 *                  for updating the CState of the aircraft for each time step      *
 ***********************************************************************************/

#ifndef C_DYNAMICS_UPDATER_H
#define C_DYNAMICS_UPDATER_H

#include <vector>
#include "CInputVector.hpp"
#include "CState.hpp"
#include "CAerodynamicCoefficients.hpp"

struct Sflow5DataPoint {
    double Left, Right, Elevator, Rudder, Alpha, CLift, CDrag, CSide, CPitch, CRoll, CYaw;
};
struct S6DegResultant {
    // absolute reference frame:
    double forceX, forceY, forceZ;
    // relative reference frame:
    double momentX, momentY, momentZ;
};

class CDynamicsUpdater {
private:
    static constexpr double fuselageDragCoeff = 0.4, fuselageArea = 3.14*0.35*0.35;
    static constexpr double airDensity = 1.225; // kg/m^3
    static constexpr double Ixx = 1.1135, Iyy = 0.91147, Izz = 2.01400; //kg*m^2
    static constexpr double Ixz = 0.03478, Ixy = 0, Iyz = 0; //kg*m^2 
    static constexpr double wingArea = 0.675; //m^2
    static constexpr double mass = 2; //kg
    static constexpr double timeDelta = 0.01; //seconds
    static constexpr double fuselageEquivalentDragCoeff = fuselageDragCoeff * fuselageArea / wingArea;

public:
    // Function to query flow5Data.db to obtain the aerodynamic reactions
    CAerodynamicCoefficients static InterpolateFlow5(const CInputVector& inputs, const CState& currentState);

    // Function to update the state vector based on the motor outputs and flow5 data
    bool static UpdateStates(const CInputVector& inputs, CState& currentState);

    // Function to calculate the low and high bounds for a given control surface angle to pass to SQL
    void static NearestControlSurfacePoints(double value, double& low, double& high);

    // single dimensional linear interpolation
    double static linearInterpolate(double x, double x1, double x2, double F1, double F2) {
        return (((x2 - x) / (x2 - x1) * F1) + ((x - x1) / (x2 - x1) * F2));  
    }

    // 5-dimensional linear interpolation
    double static pentalinearInterpolate(double x, double xLow, double xHigh,
                                            double y, double yLow, double yHigh,
                                            double z, double zLow, double zHigh,
                                            double t, double tLow, double tHigh,
                                            double q, double qLow, double qHigh,
                                            const std::vector<double>& points,
                                            int (&locatedPoints)[2][2][2][2][2]);
                                        
    //Function to calculate force/moment values from aerodynamic coefficients
    double static valueFromCoeff(double coefficient, double velocity){
        return 0.5 * airDensity * velocity * velocity * coefficient * wingArea;
    }

    //Function to calculate the net forces and moments about the C.O.G from the motors
    S6DegResultant static getMotorResultant(const CInputVector& inputs);

    //Normalize the angular position within bounds
    double static setAngleInNominalRange(double angle){
        while (angle > CSphericalCoordinate::ANGULAR_MAX) {
        angle -= 360;
        }
        while (angle < CSphericalCoordinate::ANGULAR_MIN) {
            angle += 360;
        }
        return angle;
    }

};


#endif // C_DYNAMICS_UPDATER_H
