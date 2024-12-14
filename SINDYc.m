%% Clear all variables, close all figures, and set the format for output
clear all; 
close all; 
clc;
format compact

%% Defaults
set(groot, 'DefaultLineLineWidth', 2); % Set default LineWidth to 2 (or your desired width)
set(groot, 'DefaultAxesFontSize', 18);       % Sets font size for axes labels and ticks
set(groot, 'DefaultTextFontSize', 18);       % Sets font size for all text objects in figures
set(groot, 'DefaultUicontrolFontSize', 18);  % Sets font size for UI controls (if using GUIs

%% Load the dataset
% load the data
data = readtable('output_file.csv', 'VariableNamingRule', 'preserve');
% data = load('dummy_data.mat');

%% Separate the Variables
%time
time = data.Time';
%inputs
left = data.Left';
right = data.Right';
elev = data.Elev';
rudd = data.Rudd';
fl_thrust = data.("FLMotor(N)")';
fr_thrust = data.("FRMotor(N)")';
rear_thrust = data.("RearMotor(N)")';
fl_angle = data.("FLMotor(deg)")';
fr_angle = data.("FRMotor(deg)")';
%outputs/state
x = data.X';
y = data.Y';
z = data.Z';
xdot = data.Xdot';
ydot = data.Ydot';
zdot = data.Zdot';
yaw = data.Yaw';
pitch = data.Pitch';
roll = data.Roll';
yawdot = data.YawDot';
pitchdot = data.PitchDot';
rolldot = data.RollDot';
%% Noiseify the Data

%inputs
% left = noise_ify(left);
% right = noise_ify(right);
% elev = noise_ify(elev);
% rudd = noise_ify(rudd);
% fl_thrust = noise_ify(fl_thrust);
% fr_thrust = noise_ify(fr_thrust);
% rear_thrust = noise_ify(rear_thrust);
% fl_angle = noise_ify(fl_angle);
% fr_angle = noise_ify(fr_angle);
% %outputs/state
% x = noise_ify(x);
% y = noise_ify(y);
% z = noise_ify(z);
% xdot = noise_ify(xdot);
% ydot = noise_ify(ydot);
% zdot = noise_ify(zdot);
% yaw = noise_ify(yaw);
% pitch = noise_ify(pitch);
% roll = noise_ify(roll);
% yawdot = noise_ify(yawdot);
% pitchdot = noise_ify(pitchdot);
% rolldot = noise_ify(rolldot);


%% Normalization of Data

% %inputs
% left = zeroStdScale(left);
% right = zeroStdScale(right);
% elev = zeroStdScale(elev);
% rudd = zeroStdScale(rudd);
% fl_thrust = rescale(fl_thrust, 0,1);
% fr_thrust = rescale(fr_thrust, 0,1);
% rear_thrust = rescale(rear_thrust, 0,1);
% fl_angle = rescale(fl_angle, 0,1);
% fr_angle = rescale(fr_angle, 0,1);
% %outputs/state
% x = rescale(x, 0,1);
% y = rescale(y, 0,1);
% z = rescale(z, 0,1);
% xdot = rescale(xdot, 0,1);
% ydot = rescale(ydot, 0,1);
% zdot = rescale(zdot, 0,1);
% yaw = zeroStdScale(yaw);
% pitch = zeroStdScale(pitch);
% roll = zeroStdScale(roll);
% yawdot = zeroStdScale(yawdot);
% pitchdot = zeroStdScale(pitchdot);
% rolldot = zeroStdScale(rolldot);

%% Numerically Differentiate the State

%Test deriving velocities
% xdot = gradient(x,time);
% ydot = gradient(y,time);
% zdot = gradient(z,time);
% 
% yawdot = gradient(yaw, time);
% pitchdot = gradient(pitch,time);
% rolldot = gradient(roll, time);

% Double Derivatives
xddot = gradient(xdot,time);
yddot = gradient(ydot,time);
zddot = gradient(zdot,time);

yawddot = gradient(yawdot, time);
pitchddot = gradient(pitchdot,time);
rollddot = gradient(rolldot, time);


%% Visualization of Data

figure('Name', "Linear", 'Position', [10,160,1080,640]);
sgtitle("Linear State Response")
subplot(3,2,1);
plot(time, x, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot x over time
hold on;
ylabel("X Position (m)")
val = x;
span = max(val)-min(val);
tol = 0.2;
ylim([min(val)-tol*span max(val)+tol*span])


subplot(3,2,2);
plot(time, xdot, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot xdot over time
hold on;
ylabel("X Velocity (m/s)")
val = xdot;
span = max(val)-min(val);
ylim([min(val)-tol*span max(val)+tol*span])

subplot(3,2,3);
plot(time, y, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot y over time
hold on;
ylabel("Y Position (m)")
val = y;
span = max(val)-min(val);
ylim([min(val)-tol*span max(val)+tol*span])

subplot(3,2,4);
plot(time, ydot, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot ydot over time
hold on;
ylabel("Y Velocity (m/s)")
val = ydot;
span = max(val)-min(val);
ylim([min(val)-tol*span max(val)+tol*span])

subplot(3,2,5);
plot(time, z, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot z over time
hold on;
ylabel("Z Position (m)")
val = z;
span = max(val)-min(val);
ylim([min(val)-tol*span max(val)+tol*span])

subplot(3,2,6);
plot(time, zdot, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot zdot over time
hold on;
ylabel("Z Velocity (m/s)")
val = zdot;
span = max(val)-min(val);
ylim([min(val)-tol*span max(val)+tol*span])



figure('Name', "Angular", 'Position', [30,160,1080,640]);
sgtitle("Angular State Response")
subplot(3,2,1);
plot(time, yaw, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot yaw over time
hold on;
ylabel("Yaw (deg)")
val = yaw;
span = max(val)-min(val);
ylim([min(val)-tol*span max(val)+tol*span])

subplot(3,2,2);
plot(time, yawdot, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot yawdot over time
hold on;
ylabel("Yaw Rate (deg/s)")
val = yawdot;
span = max(val)-min(val);
ylim([min(val)-tol*span max(val)+tol*span])

subplot(3,2,3);
plot(time, pitch, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot pitch over time
hold on;
ylabel("Pitch (deg)")
val = pitch;
span = max(val)-min(val);
ylim([min(val)-tol*span max(val)+tol*span])

subplot(3,2,4);
plot(time, pitchdot, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot pitchdot over time
hold on;
ylabel("Pitch Rate (deg/s)")
val = pitchdot;
span = max(val)-min(val);
ylim([min(val)-tol*span max(val)+tol*span])

subplot(3,2,5);
plot(time, roll, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot roll over time
hold on;
ylabel("Roll (deg)")
val = roll;
span = max(val)-min(val);
ylim([min(val)-tol*span max(val)+tol*span])

subplot(3,2,6);
plot(time, rolldot, 'DisplayName', 'Data','Color','blue', 'LineWidth', 2, 'LineStyle','-');  % Plot rolldot over time
hold on;
ylabel("Roll Rate (deg/s)")
val = rolldot;
span = max(val)-min(val);
ylim([min(val)-tol*span max(val)+tol*span])


%% Create Function Library for Modelling

numdata = length(time);

ThetaMatrix = [ ones(1, numdata);
    %% INPUTS
    left; right; elev; rudd;
    fl_thrust; fr_thrust; rear_thrust;
    fl_angle; fr_angle;
    %% OUTPUTS
    x; xdot; y; ydot; z; zdot;
    yaw; yawdot; pitch; pitchdot; roll; rolldot;
    %% Variable Funcs
    % Control Surface Trig
    sind(left); cosd(left);
    sind(right); cosd(right);
    sind(elev); cosd(elev);
    sind(rudd); cosd(rudd);
    % Motor Tilt Trig
    fl_thrust .* sind(fl_angle);
    fl_thrust .* cosd(fl_angle);
    fr_thrust .* sind(fr_angle);
    fr_thrust .* cosd(fr_angle);
    % Airspeed
    xdot .* cosd(yaw) + ydot .* sind(yaw);
    % Squared Airspeed
    (xdot .* cosd(yaw) + ydot .* sind(yaw)) .^ 2;];
    % % Orientation Trig
    % cosd(roll); sind(roll);
    % cosd(pitch); sind(pitch);
    % cosd(yaw); sind(yaw);];

XdotMatrix = [xdot; xddot;
              ydot; yddot;
              zdot; zddot;
              yawdot; yawddot;
              pitchdot; pitchddot;
              rolldot; rollddot ];

%% Define Sparsification Threshold
lambda = 0.6;

%% Define Activation Matrix (psi)
       %1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42
% psi = [ 0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0;
%         0  0  0  0  0  0  0  0  0  0  0  1  0  1  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1;
%         0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0;
%         0  0  0  0  0  0  0  0  0  0  0  1  0  1  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1;
%         0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0;
%         0  0  0  0  0  0  0  0  0  0  0  1  0  1  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  2;
%         0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0;
%         0  0  0  0  0  0  0  0  0  0  0  1  0  1  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1;
%         0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0;
%         0  0  0  0  0  0  0  0  0  0  0  1  0  1  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1;
%         0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0;
%         0  0  0  0  0  0  0  0  0  0  0  1  0  1  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1  1;
%         ];

%% Compute Initial Model

% Compute the initial parameter estimate using pseudoinverse
XiMatrix0 = XdotMatrix * pinv(ThetaMatrix); % Without Sequential Thresholded Least-Squares (STLS)

if exist('psi', 'var')
    XiMatrix = XiMatrix0 .* psi; % elemental multiplication with deactivation matrix
else
    XiMatrix = XiMatrix0;
end

%% Applied STLS for Sparsification

n = size(XdotMatrix, 1); % Number of data points

bigIndices = ones(size(XiMatrix));
bigIndicesOld = zeros(size(XiMatrix));
count=0;
maxiter = 15; threshold = 0.1; SumSquareChange = 1;

while (any(bigIndicesOld ~= bigIndices, 'all') && any(abs(XiMatrix)<lambda,'all') && SumSquareChange > threshold) && count < maxiter
    bigIndicesOld = bigIndices;
    smallIndices = (abs(XiMatrix)<lambda); % Find small coefficients (less than threshold)
    NewXiMatrix = XiMatrix;
    NewXiMatrix(smallIndices)=0; % set small coefficients to zero
    bigIndices = ~smallIndices; % find nonzero indices
    for state = 1:n % n is state dimension
        % Regress state 'n'  dynamics onto remaining terms to find sparse Xi
        stateXDotMatrix = XdotMatrix(state,:);
        stateThetaMatrix = ThetaMatrix(bigIndices(state,:),:);
        stateXiMatrix = stateXDotMatrix * pinv(stateThetaMatrix);
        NewXiMatrix(state,bigIndices(state,:)) = stateXiMatrix;
    end
    SumSquareChange = sumOfSquaresOfDifferences(XiMatrix, NewXiMatrix)
    XiMatrix = NewXiMatrix;
    count = count+1;
end

display(XiMatrix)

%% Set up Simulation
x0 = [0;0;0;0;0;0;0;0;0;0;0;0];  % Initial conditions for X
tspan = [time(1), time(end)];


callcount=0;
function Xdot = SINDYc_SIM(t, xInternal, leftInput, rightInput, elevInput, ruddInput, fl_thrustInput, fr_thrustInput, ...
                                rear_thrustInput, fl_angleInput, fr_angleInput, tInput, XiMatrix)
fprintf('.\n')


left = interp1(tInput, leftInput, t, 'linear', 'extrap'); % 'extrap' to handle out-of-bounds
right = interp1(tInput, rightInput, t, 'linear', 'extrap'); 
elev = interp1(tInput, elevInput, t, 'linear', 'extrap'); 
rudd = interp1(tInput, ruddInput, t, 'linear', 'extrap'); 
fl_thrust = interp1(tInput, fl_thrustInput, t, 'linear', 'extrap'); 
fr_thrust = interp1(tInput, fr_thrustInput, t, 'linear', 'extrap'); 
fl_angle = interp1(tInput, fl_angleInput, t, 'linear', 'extrap'); 
fr_angle = interp1(tInput, fr_angleInput, t, 'linear', 'extrap'); 
rear_thrust = interp1(tInput, rear_thrustInput, t, 'linear', 'extrap'); 



x = xInternal(1);   xdot = xInternal(2);
y = xInternal(3);   ydot = xInternal(4);
z = xInternal(5);   zdot = xInternal(6);
yaw = xInternal(7);   yawdot = xInternal(8);
pitch = xInternal(9);   pitchdot = xInternal(10);
roll = xInternal(11);   rolldot = xInternal(12);




ThetaMatrix = [ 1;
    %% INPUTS
    left; right; elev; rudd;
    fl_thrust; fr_thrust; rear_thrust;
    fl_angle; fr_angle;
    %% OUTPUTS
    x; xdot; y; ydot; z; zdot;
    yaw; yawdot; pitch; pitchdot; roll; rolldot;
    %% Variable Funcs
    % Control Surface Trig
    sind(left); cosd(left);
    sind(right); cosd(right);
    sind(elev); cosd(elev);
    sind(rudd); cosd(rudd);
    % Motor Tilt Trig
    fl_thrust .* sind(fl_angle);
    fl_thrust .* cosd(fl_angle);
    fr_thrust .* sind(fr_angle);
    fr_thrust .* cosd(fr_angle);
    % Airspeed
    xdot .* cosd(yaw) + ydot .* sind(yaw);
    % Squared Airspeed
    (xdot .* cosd(yaw) + ydot .* sind(yaw)) .^ 2;];
    % % Orientation Trig
    % cosd(roll); sind(roll);
    % cosd(pitch); sind(pitch);
    % cosd(yaw); sind(yaw);];

Xdot = XiMatrix * ThetaMatrix;



end

%% Simulate the response

options = odeset('MaxStep', 0.05);
% Use ode45 to solve the nonlinear state-space model
[t_sim, x_sim] = ode45(@(t, x) SINDYc_SIM(t, x, left, right, elev, rudd, fl_thrust, fr_thrust, ...
                                rear_thrust, fl_angle, fr_angle, time, XiMatrix), tspan, x0, options);

%% Plot results

figure(findobj('Type', 'figure', 'Name', 'Linear'));
subplot(3,2,1);
plot(t_sim, x_sim(:,1), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle', '--');  % Plot x over time
legend('Location','NorthWest')

subplot(3,2,2);
plot(t_sim, x_sim(:,2), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle','--');  % Plot xdot over time


subplot(3,2,3);
plot(t_sim, x_sim(:,3), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle','--');  % Plot y over time


subplot(3,2,4);
plot(t_sim, x_sim(:,4), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle','--');  % Plot ydot over time


subplot(3,2,5);
plot(t_sim, x_sim(:,5), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle','--');  % Plot z over time


subplot(3,2,6);
plot(t_sim, x_sim(:,6), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle','--');  % Plot zdot over time



figure(findobj('Type', 'figure', 'Name', 'Angular'));
subplot(3,2,1);
plot(t_sim, x_sim(:,7), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle', '--');  % Plot yaw over time


subplot(3,2,2);
plot(t_sim, x_sim(:,8), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle','--');  % Plot yawdot over time
legend('Data', 'Model','Location','northeast');

subplot(3,2,3);
plot(t_sim, x_sim(:,9), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle','--');  % Plot pitch over time


subplot(3,2,4);
plot(t_sim, x_sim(:,10), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle','--');  % Plot pitchdot over time


subplot(3,2,5);
plot(t_sim, x_sim(:,11), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle','--');  % Plot roll over time


subplot(3,2,6);
plot(t_sim, x_sim(:,12), 'DisplayName', 'Model','Color','red', 'LineWidth', 1, 'LineStyle','--');  % Plot rolldot over time