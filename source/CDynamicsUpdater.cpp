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
#include <sqlite3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <format>

//Internal Headers
#include "../header/CDynamicsUpdater.hpp"

/************************************ GLOBALS **************************************/


/***************************** FUNCTIONS DEFINITIONS********************************/


/*===========================================================================
 * Function:        CDynamicsUpdater::InterpolateFlow5()
 * Arguments:       CInputVector& inputs - inputs at current time 
 *                  CState& currentState - state at current time
 *                  double deltaTime - timestep size in seconds
 * Returns:         CAerodynamicCoefficients& - coefficients interpolated from SQLite
 * Description:     Default constructor
 */
CAerodynamicCoefficients CDynamicsUpdater::InterpolateFlow5(const CInputVector& inputs, const CState& currentState){
    
    // Create a datapoint based on query data
    Sflow5DataPoint queryPoint;
    queryPoint.Left = inputs.ControlSurfaces.LeftAileronAngle.get();
    queryPoint.Right = inputs.ControlSurfaces.RightAileronAngle.get();
    queryPoint.Elevator = inputs.ControlSurfaces.ElevatorAngle.get();
    queryPoint.Rudder = inputs.ControlSurfaces.RudderAngle.get();
    queryPoint.Alpha = currentState.AngularPositions.Pitch.get();

    // Manually compute the nearest control surface datapoints
    double LeftLow, LeftHigh;
    NearestControlSurfacePoints(queryPoint.Left, LeftLow, LeftHigh);
    double RightLow, RightHigh;
    NearestControlSurfacePoints(queryPoint.Right, RightLow, RightHigh);
    double ElevLow, ElevHigh;
    NearestControlSurfacePoints(queryPoint.Elevator, ElevLow, ElevHigh);
    double RuddLow, RuddHigh;
    NearestControlSurfacePoints(queryPoint.Rudder, RuddLow, RuddHigh);
    double AlphaLow, AlphaHigh;
    if (std::floor(queryPoint.Alpha) == std::ceil(queryPoint.Alpha)){
        AlphaLow = queryPoint.Alpha;
        AlphaHigh = queryPoint.Alpha + 1;
    } else {
        AlphaLow = std::floor(queryPoint.Alpha);
        AlphaHigh = std::ceil(queryPoint.Alpha);
    }


    //open the SQL database
    sqlite3* db;
    sqlite3_open("flow5Data.db", &db);
    // Step 1: Prepare the query to fetch the 32 closest points
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, 
        "SELECT LEFT, RIGHT, ELEVATOR, RUDDER, ALPHA, CLIFT, CDRAG, CSIDEFORCE, CPITCH, CROLL, CYAW "
        "FROM FLOW5DATA "
        "WHERE "
            "LEFT  BETWEEN ? AND ? AND "
            "RIGHT  BETWEEN ? AND ? AND "
            "ELEVATOR BETWEEN ? AND ? AND "
            "RUDDER BETWEEN ? AND ? AND "
            "ALPHA BETWEEN ? AND ? "
        "LIMIT 32;", -1, &stmt, nullptr);

    double tolerance = 0.2;

    sqlite3_bind_double(stmt, 1, LeftLow-tolerance);
    sqlite3_bind_double(stmt, 2, LeftHigh+tolerance);
    sqlite3_bind_double(stmt, 3, RightLow-tolerance);
    sqlite3_bind_double(stmt, 4, RightHigh+tolerance);
    sqlite3_bind_double(stmt, 5, ElevLow-tolerance);
    sqlite3_bind_double(stmt, 6, ElevHigh+tolerance);
    sqlite3_bind_double(stmt, 7, RuddLow-tolerance);
    sqlite3_bind_double(stmt, 8, RuddHigh+tolerance);
    sqlite3_bind_double(stmt, 9, AlphaLow-tolerance);
    sqlite3_bind_double(stmt, 10, AlphaHigh+tolerance);

    // Step 2: Fetch the points
    std::vector<Sflow5DataPoint> points;
    std::vector<double> CLIFT, CDRAG, CSIDE, CPITCH, CROLL, CYAW;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Sflow5DataPoint p;
        p.Left = sqlite3_column_double(stmt, 0);
        p.Right = sqlite3_column_double(stmt, 1);
        p.Elevator = sqlite3_column_double(stmt, 2);
        p.Rudder = sqlite3_column_double(stmt, 3);
        p.Alpha = sqlite3_column_double(stmt, 4);
        p.CLift = sqlite3_column_double(stmt, 5);
        p.CDrag = sqlite3_column_double(stmt, 6);
        p.CSide = sqlite3_column_double(stmt, 7);
        p.CPitch = sqlite3_column_double(stmt, 8);
        p.CRoll= sqlite3_column_double(stmt, 9);
        p.CYaw = sqlite3_column_double(stmt, 10);
        points.push_back(p);
        CLIFT.push_back(p.CLift);
        CDRAG.push_back(p.CDrag);
        CSIDE.push_back(p.CSide);
        CPITCH.push_back(p.CPitch);
        CROLL.push_back(p.CRoll);
        CYAW.push_back(p.CYaw);
    }
    if (points.size() > 32) {
        std::cout << "too many SQL points selected, " << points.size() <<" points selected\n";
        throw std::out_of_range("");
    } else if (points.size() < 32) {
        std::cout << "not enough SQL points selected, " << points.size() <<" points selected\n";
        std::cout << "LeftLow" << " | " << "LeftHigh" << " | " << "RightLow" << " | " << "RightHigh" << " | " << "ElevLow" << " | " << "ElevHigh" << " | " << "RuddLow"  << " | " << "RuddHigh"  << " | " << "AlphaLow"  << " | " << "AlphaHigh" << std::endl;
        std::cout << LeftLow << " | " << LeftHigh << " | " << RightLow << " | " << RightHigh << " | " << ElevLow << " | " << ElevHigh << " | " << RuddLow  << " | " << RuddHigh  << " | " << AlphaLow  << " | " << AlphaHigh << std::endl;
        throw std::out_of_range("");
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);


    // Step 3: Check alpha bounds
    double maxAlpha = 0;
    double minAlpha = 0;
    for (const auto& point : points) {
        if (point.Alpha > maxAlpha){
            maxAlpha = point.Alpha;
        }
        if (point.Alpha < minAlpha){
            minAlpha = point.Alpha;
        }
    }
    if (queryPoint.Alpha > maxAlpha || queryPoint.Alpha < minAlpha){
        throw std::out_of_range("alpha out of range for interpolation");
    }


    // Step 4: Seek the relative locations of each point
    int locatedPointIndices[2][2][2][2][2] = {};
    int leftIndex, rightIndex, elevIndex, ruddIndex, alphaIndex;
    int index = 0;
    for (const auto& point : points) {
        if (point.Left == LeftLow) {
            leftIndex = 0;
        } else if (point.Left == LeftHigh) {
            leftIndex = 1;
        } else {
            throw std::out_of_range("SQL point \"Left\" not as expected");
        }
        if (point.Right == RightLow) {
            rightIndex = 0;
        } else if (point.Right == RightHigh) {
            rightIndex = 1;
        } else {
            throw std::out_of_range("SQL point \"Right\" not as expected");
        }
        if (point.Elevator == ElevLow) {
            elevIndex = 0;
        } else if (point.Elevator == ElevHigh) {
            elevIndex = 1;
        } else {
            throw std::out_of_range("SQL point \"Elevator\" not as expected");
        }
        if (point.Rudder == RuddLow) {
            ruddIndex = 0;
        } else if (point.Rudder == RuddHigh) {
            ruddIndex = 1;
        } else {
            throw std::out_of_range("SQL point \"Rudder\" not as expected");
        }
        if (point.Alpha == AlphaLow) {
            alphaIndex = 0;
        } else if (point.Alpha == AlphaHigh) {
            alphaIndex = 1;
        } else {
            throw std::out_of_range("SQL point \"Alpha\" not as expected");
        }
        if (!locatedPointIndices[leftIndex][rightIndex][elevIndex][ruddIndex][alphaIndex]){
            locatedPointIndices[leftIndex][rightIndex][elevIndex][ruddIndex][alphaIndex] = index;
        } else {
            throw std::out_of_range("two points have gerated the same interpolation index");
        }   
    }

    // Step 5: Pentalinear interpolation
    double InterpCLift = pentalinearInterpolate(queryPoint.Left, LeftLow, LeftHigh,
                                            queryPoint.Right, RightLow, RightHigh,
                                            queryPoint.Elevator, ElevLow, ElevHigh,
                                            queryPoint.Rudder, RuddLow, RuddHigh,
                                            queryPoint.Alpha, AlphaLow, AlphaHigh,
                                            CLIFT, locatedPointIndices);
    double InterpCDrag = pentalinearInterpolate(queryPoint.Left, LeftLow, LeftHigh,
                                            queryPoint.Right, RightLow, RightHigh,
                                            queryPoint.Elevator, ElevLow, ElevHigh,
                                            queryPoint.Rudder, RuddLow, RuddHigh,
                                            queryPoint.Alpha, AlphaLow, AlphaHigh,
                                            CDRAG, locatedPointIndices);
    double InterpCSide = pentalinearInterpolate(queryPoint.Left, LeftLow, LeftHigh,
                                            queryPoint.Right, RightLow, RightHigh,
                                            queryPoint.Elevator, ElevLow, ElevHigh,
                                            queryPoint.Rudder, RuddLow, RuddHigh,
                                            queryPoint.Alpha, AlphaLow, AlphaHigh,
                                            CSIDE, locatedPointIndices);
    double InterpCPitch = pentalinearInterpolate(queryPoint.Left, LeftLow, LeftHigh,
                                            queryPoint.Right, RightLow, RightHigh,
                                            queryPoint.Elevator, ElevLow, ElevHigh,
                                            queryPoint.Rudder, RuddLow, RuddHigh,
                                            queryPoint.Alpha, AlphaLow, AlphaHigh,
                                            CPITCH, locatedPointIndices);
    double InterpCRoll = pentalinearInterpolate(queryPoint.Left, LeftLow, LeftHigh,
                                            queryPoint.Right, RightLow, RightHigh,
                                            queryPoint.Elevator, ElevLow, ElevHigh,
                                            queryPoint.Rudder, RuddLow, RuddHigh,
                                            queryPoint.Alpha, AlphaLow, AlphaHigh,
                                            CROLL, locatedPointIndices);
    double InterpCYaw = pentalinearInterpolate(queryPoint.Left, LeftLow, LeftHigh,
                                            queryPoint.Right, RightLow, RightHigh,
                                            queryPoint.Elevator, ElevLow, ElevHigh,
                                            queryPoint.Rudder, RuddLow, RuddHigh,
                                            queryPoint.Alpha, AlphaLow, AlphaHigh,
                                            CYAW, locatedPointIndices);

    CAerodynamicCoefficients outputs = CAerodynamicCoefficients(InterpCLift, InterpCDrag, InterpCSide, 
                                                                InterpCPitch, InterpCRoll, InterpCYaw);

    return outputs;
}

/*===========================================================================
 * Function:        CDynamicsUpdater::pentalinearInterpolate()
 * Arguments:       double x, double xLow, double xHigh
 *                                  - first dimensional to interpolate
 *                  double y, double yLow, double yHigh
 *                                  - second dimensional to interpolate
 *                  double z, double zLow, double zHigh
 *                                  - third dimensional to interpolate
 *                  double t, double tLow, double tHigh
 *                                  - fourth dimensional to interpolate
 *                  double q, double qLow, double qHigh
 *                                  - fifth dimensional to interpolate
 *                  const std::vector<double>& points
 *                                  - a reference to a vector of points to interpolate between
 *                  int (&locatedPoints)[2][2][2][2][2]
 *                                  - a reference to a 5 dimensional array providing the indices
 *                                    of which points belong where dimensionally
 * Returns:         none
 * Description:     Function to calculate the low and high bounds for a given control surface angle to pass to SQL
 */
double CDynamicsUpdater::pentalinearInterpolate(double x, double xLow, double xHigh,
                                                double y, double yLow, double yHigh,
                                                double z, double zLow, double zHigh,
                                                double t, double tLow, double tHigh,
                                                double q, double qLow, double qHigh,
                                                const std::vector<double>& points,
                                                int (&locatedPoints)[2][2][2][2][2]){
    double fx[2][2][2][2] = {};
    for(int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                for (int l = 0; l < 2; l++){
                    fx[i][j][k][l] =  linearInterpolate(x, xLow, xHigh, 
                                                points[locatedPoints[0][i][j][k][l]], 
                                                points[locatedPoints[1][i][j][k][l]]);
                }
            }
        }
    }
    double fxy[2][2][2] = {};
    for (int j = 0; j < 2; j++){
        for (int k = 0; k < 2; k++){
            for (int l = 0; l < 2; l++){
                fxy[j][k][l] =  linearInterpolate(y, yLow, yHigh, 
                                            fx[0][j][k][l], 
                                            fx[1][j][k][l]);
            }
        }
    }
    double fxyz[2][2] = {};
    for (int k = 0; k < 2; k++){
        for (int l = 0; l < 2; l++){
            fxyz[k][l] =  linearInterpolate(z, zLow, zHigh, 
                                        fxy[0][k][l], 
                                        fxy[1][k][l]);
        }
    }
    double fxyzt[2] = {};
    for (int l = 0; l < 2; l++){
        fxyzt[l] =  linearInterpolate(t, tLow, tHigh, 
                                    fxyz[0][l], 
                                    fxyz[1][l]);
    }
    double fxyztq = linearInterpolate(q, qLow, qHigh, 
                                    fxyzt[0], 
                                    fxyzt[1]);

    return fxyztq;
}

/*===========================================================================
 * Function:        CDynamicsUpdater::NearestControlSurfacePoints()
 * Arguments:       double value - value for lookup
 *                  double& low  - reference to a double in which to store low
 *                  double& high  - reference to a double in which to store high
 * Returns:         none
 * Description:     Function to calculate the low and high bounds for a given control surface angle to pass to SQL
 */
void CDynamicsUpdater::NearestControlSurfacePoints(double value, double& low, double& high){

    switch ((int)std::ceil(value)) {
    case -18 ... -5:
        low = -18;
        high = -5;
        break;
    case -4 ... 0:
        low = -5;
        high = 0;
        break;
    case 1 ... 5:
        low = 0;
        high = 5;
        break;
    case 6 ... 18:
        low = 5;
        high = 18;
        break;
    default:
        throw std::out_of_range("Control Surface Out of Range for interpolation");
    }
}

/*===========================================================================
 * Function:        CState::CState()
 * Arguments:       CInputVector& inputs    - a reference to the input vector
 *                  CState& currentState    - a reference to the state vector
 *                  CAerodynamicCoefficients& interpolatedCoeffs
 *                                          - a reference to the aerodynamic coefficients from flow5
 * Returns:         none
 * Description:     Default constructor
 */
bool CDynamicsUpdater::UpdateStates(const CInputVector& inputs, CState& currentState){
    //Calculate Aerodynamic Coefficients
    CAerodynamicCoefficients coeffs = InterpolateFlow5(inputs, currentState);

    //Calculate Moments and Body Forces from coefficients
    double airspeed  = currentState.LinearVelocities.X.get()    /* airspeed in x-y plane */
                        * cos(currentState.AngularPositions.Yaw.get() * M_PI/180)
                        + currentState.LinearVelocities.Y.get() 
                        * sin(currentState.AngularPositions.Yaw.get() * M_PI/180);
    double LiftForce = valueFromCoeff(coeffs.CLift.get(), airspeed);
    double DragForce = valueFromCoeff(coeffs.CDrag.get() + fuselageDragCoeff, airspeed);
    double SideForce = -1 * valueFromCoeff(coeffs.CSideForce.get(), airspeed);
    double PitchMoment = valueFromCoeff(coeffs.CPitchMom.get(), airspeed);
    double RollMoment = valueFromCoeff(coeffs.CRollMom.get(), airspeed);
    double YawMoment = valueFromCoeff(coeffs.CYawMom.get(), airspeed);

    // Propogate forces and moments to absolute coord sys
    S6DegResultant absoluteAeroResult;
    absoluteAeroResult.forceZ = LiftForce * cos(currentState.AngularPositions.Roll.get() * M_PI/180)
                               + SideForce * sin(currentState.AngularPositions.Roll.get() * M_PI/180);
    absoluteAeroResult.forceX = cos(M_PI - currentState.AngularPositions.Yaw.get() * M_PI/180) * DragForce
                                - cos(currentState.AngularPositions.Yaw.get() * M_PI/180 - M_PI / 2) 
                                * (LiftForce * sin(currentState.AngularPositions.Roll.get() * M_PI/180)
                               + SideForce * cos(currentState.AngularPositions.Roll.get() * M_PI/180));
    absoluteAeroResult.forceY = -1 * sin(M_PI - currentState.AngularPositions.Yaw.get() * M_PI/180) * DragForce
                                - sin(currentState.AngularPositions.Yaw.get() * M_PI/180 - M_PI / 2) 
                                * (LiftForce * sin(currentState.AngularPositions.Roll.get() * M_PI/180)
                               + SideForce * cos(currentState.AngularPositions.Roll.get() * M_PI/180));
    absoluteAeroResult.momentX = -1 * RollMoment;
    absoluteAeroResult.momentY = -1 * PitchMoment;
    absoluteAeroResult.momentZ = YawMoment;


    //Calculate Motor Moments and Body Forces
    S6DegResultant motorResultant = getMotorResultant(inputs);

    // Propogate forces and moments to absolute coord sys
    S6DegResultant absoluteMotorResult;
    absoluteMotorResult.forceX = motorResultant.forceX 
                                        * cos(currentState.AngularPositions.Pitch.get() * M_PI/180)
                                        * cos(currentState.AngularPositions.Yaw.get() * M_PI/180)
                                - motorResultant.forceY
                                        * cos(currentState.AngularPositions.Roll.get() * M_PI/180)
                                        * sin(currentState.AngularPositions.Yaw.get() * M_PI/180)
                                - motorResultant.forceZ 
                                        * cos(currentState.AngularPositions.Roll.get() * M_PI/180)
                                        * sin(currentState.AngularPositions.Pitch.get() * M_PI/180)
                                        * cos(currentState.AngularPositions.Yaw.get() * M_PI/180);
    absoluteMotorResult.forceY = motorResultant.forceX 
                                        * cos(currentState.AngularPositions.Pitch.get() * M_PI/180)
                                        * sin(currentState.AngularPositions.Yaw.get() * M_PI/180)
                                + motorResultant.forceY
                                        * cos(currentState.AngularPositions.Roll.get() * M_PI/180)
                                        * cos(currentState.AngularPositions.Yaw.get() * M_PI/180)
                                - motorResultant.forceZ 
                                        * cos(currentState.AngularPositions.Roll.get() * M_PI/180)
                                        * sin(currentState.AngularPositions.Pitch.get() * M_PI/180)
                                        * sin(currentState.AngularPositions.Yaw.get() * M_PI/180);
    absoluteMotorResult.forceZ = motorResultant.forceX 
                                        * sin(currentState.AngularPositions.Pitch.get() * M_PI/180)
                                + motorResultant.forceY
                                        * sin(currentState.AngularPositions.Roll.get() * M_PI/180)
                                + motorResultant.forceZ 
                                        * cos(currentState.AngularPositions.Roll.get() * M_PI/180)
                                        * cos(currentState.AngularPositions.Pitch.get() * M_PI/180);

    absoluteMotorResult.momentX = motorResultant.momentX;
    absoluteMotorResult.momentY = motorResultant.momentY;
    absoluteMotorResult.momentZ = motorResultant.momentZ;


    //Calculate Net Forces and Moments
    S6DegResultant netResult;
    netResult.forceX = absoluteAeroResult.forceX + absoluteMotorResult.forceX;
    netResult.forceY = absoluteAeroResult.forceY + absoluteMotorResult.forceY;
    netResult.forceZ = absoluteAeroResult.forceZ + absoluteMotorResult.forceZ - 9.81 * mass;
    if (netResult.forceZ < 0 && currentState.LinearPositions.Z.get() <= 0){
        netResult.forceZ = 0;
    } 
    netResult.momentX = absoluteAeroResult.momentX + absoluteMotorResult.momentX;
    netResult.momentY = absoluteAeroResult.momentY + absoluteMotorResult.momentY;
    netResult.momentZ = absoluteAeroResult.momentZ + absoluteMotorResult.momentZ;
    
    
    // Update Positions with current velocities
    CState nextState;
    nextState.time.set(currentState.time.get() + timeDelta);

    double newX = currentState.LinearPositions.X.get() + timeDelta * currentState.LinearVelocities.X.get();
    nextState.LinearPositions.X.set(newX);
    double newY = currentState.LinearPositions.Y.get() + timeDelta * currentState.LinearVelocities.Y.get();
    nextState.LinearPositions.Y.set(newY);
    double newZ = currentState.LinearPositions.Z.get() + timeDelta * currentState.LinearVelocities.Z.get();
    nextState.LinearPositions.Z.set(newZ);
    double newPitch = currentState.AngularPositions.Pitch.get() + timeDelta * currentState.AngularVelocities.Pitch.get();
    nextState.AngularPositions.Pitch.set(setAngleInNominalRange(newPitch));
    double newRoll = currentState.AngularPositions.Roll.get() + timeDelta * currentState.AngularVelocities.Roll.get();
    nextState.AngularPositions.Roll.set(setAngleInNominalRange(newRoll));
    double newYaw = currentState.AngularPositions.Yaw.get() + timeDelta * currentState.AngularVelocities.Yaw.get();
    nextState.AngularPositions.Yaw.set(setAngleInNominalRange(newYaw));

    // Update Velocities with net forces/moments
    double newXdot = currentState.LinearVelocities.X.get() + netResult.forceX / mass * timeDelta;
    nextState.LinearVelocities.X.set(newXdot);
    double newYdot = currentState.LinearVelocities.Y.get() + netResult.forceY / mass * timeDelta;
    nextState.LinearVelocities.Y.set(newYdot);
    double newZdot = currentState.LinearVelocities.Z.get() + netResult.forceZ / mass * timeDelta;
    nextState.LinearVelocities.Z.set(newZdot);
    double newPitchDot = currentState.AngularVelocities.Pitch.get() - netResult.momentY / Iyy * timeDelta;
    nextState.AngularVelocities.Pitch.set(newPitchDot);
    double newRollDot = currentState.AngularVelocities.Roll.get() - netResult.momentX / Ixx * timeDelta;
    nextState.AngularVelocities.Roll.set(newRollDot);
    double newYawDot = currentState.AngularVelocities.Yaw.get() - netResult.momentZ / Izz * timeDelta;
    nextState.AngularVelocities.Yaw.set(newYawDot);

    // assign the updated state to the currentState reference
    currentState = nextState;

    return true;
}

/*===========================================================================
 * Function:        CState::CState()
 * Arguments:       CInputVector& inputs    - a reference to the input vector
 *                  CState& currentState    - a reference to the state vector
 *                  CAerodynamicCoefficients& interpolatedCoeffs
 *                                          - a reference to the aerodynamic coefficients from flow5
 * Returns:         none
 * Description:     Default constructor
 */
S6DegResultant CDynamicsUpdater::getMotorResultant(const CInputVector& inputs){
    S6DegResultant result;


    //Calculate forces and moments of front left motor
    double forceX = inputs.Motors.FrontLeft.Thrust.get() 
                    * cos(inputs.Motors.FrontLeft.RelativeAngularPosition.Pitch.get()* M_PI/180);
    double forceY = 0;
    double forceZ = inputs.Motors.FrontLeft.Thrust.get()
                    * sin(inputs.Motors.FrontLeft.RelativeAngularPosition.Pitch.get()* M_PI/180);
    double momentX = forceZ * inputs.Motors.FrontLeft.RelativeLinearPosition.Y.get();
    double momentY = -1 * forceZ * inputs.Motors.FrontLeft.RelativeLinearPosition.X.get();
    double momentZ = -1 * forceX * inputs.Motors.FrontLeft.RelativeLinearPosition.Y.get();
    //add forces and moments to resultant
    result.forceX = forceX; result.forceY = forceY; result.forceZ = forceZ;
    result.momentX = momentX; result.momentY = momentY; result.momentZ = momentZ;


    //Calculate forces and moments of front right motor
    forceX = inputs.Motors.FrontRight.Thrust.get() 
                    * cos(inputs.Motors.FrontRight.RelativeAngularPosition.Pitch.get()* M_PI/180);
    forceY = 0;
    forceZ = inputs.Motors.FrontRight.Thrust.get()
                    * sin(inputs.Motors.FrontRight.RelativeAngularPosition.Pitch.get()* M_PI/180);
    momentX = forceZ * inputs.Motors.FrontRight.RelativeLinearPosition.Y.get();
    momentY = -1 * forceZ * inputs.Motors.FrontRight.RelativeLinearPosition.X.get();
    momentZ = -1 * forceX * inputs.Motors.FrontRight.RelativeLinearPosition.Y.get();
    //add forces and moments to resultant
    result.forceX += forceX; result.forceY += forceY; result.forceZ += forceZ;
    result.momentX += momentX; result.momentY += momentY; result.momentZ += momentZ;


    //Calculate forces and moments of front left motor
    forceX = inputs.Motors.Rear.Thrust.get() 
                    * cos(inputs.Motors.Rear.RelativeAngularPosition.Pitch.get()* M_PI/180);
    forceY = 0;
    forceZ = inputs.Motors.Rear.Thrust.get()
                    * sin(inputs.Motors.Rear.RelativeAngularPosition.Pitch.get()* M_PI/180);
    momentX = forceZ * inputs.Motors.Rear.RelativeLinearPosition.Y.get();
    momentY = -1 * forceZ * inputs.Motors.Rear.RelativeLinearPosition.X.get();
    momentZ = -1 * forceX * inputs.Motors.Rear.RelativeLinearPosition.Y.get();
    //add forces and moments to resultant
    result.forceX += forceX; result.forceY += forceY; result.forceZ += forceZ;
    result.momentX += momentX; result.momentY += momentY; result.momentZ += momentZ;

    return result;
}
