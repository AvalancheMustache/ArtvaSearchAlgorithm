clear all;
close all;
clc;

%% Adding path 

addpath('script');
addpath('simulink');
addpath('function');
addpath('bin');

%% Simulation configurations

% Generates data for simulation
config.run.data = 1;
% Elaborates control for attitude only
config.run.lqr_assetto = 0;
% Elaborates complete control
config.run.lqr_completo = 1;
% Enable Obstacle avoidance definition
config.obstacleAvoid = 1;

% Compile options: 
% * 0 = do not compile
% * 'release' or 'r' release version
% * 'debug' or 'd' debug version with debug symbols
config.compile.clean = 1;

config.compile.H_receiver = 'release';
config.compile.optimizer = 'release'; 
config.compile.ParzenWin = 'release';
config.compile.rotmat = 'release';
config.compile.Rot_G2B = 'release';
config.compile.Rot_B2G = 'release';
config.compile.RangeReceiver = 'release';

% Simulink
config.simulink.model = 'hexacopter';
config.simulink.SFuncComp = 1;
config.simulink.Open = 1; % if 0 model will be only loaded in memory
config.simulink.run_model = 1;

% Notification configurations
config.notification.enable = 0;
config.notification.mail_settings = 'D:\email_matlab.mat';
config.notification.sendto = 'nirvana1289@gmail.com';
if config.notification.enable == 1
   run('./script/notification_settings.m');
end

%% Cleaning previous compiled function
if config.compile.clean == 1
    delete ./bin/*
end 

%% MEX-FUNCTION Compilation
compiler_call('H_receiver.c', config.compile.H_receiver);
compiler_call('rotation_matrix.c',config.compile.rotmat);
compiler_call('Rot_G2B_mex.c',config.compile.Rot_G2B);
compiler_call('Rot_B2G_mex.c',config.compile.Rot_B2G);
compiler_call('ParzenWindowEstimator.c',config.compile.ParzenWin);
compiler_call('optimizer_residuals_c2.c',config.compile.optimizer);
compiler_call('rangeReceiver_mex.c',config.compile.RangeReceiver);

%% S-FUNCTION Compilation
if config.simulink.SFuncComp == 1
    sfunction_compiler_call(config.simulink.model, config.simulink.Open)
end

%% Adding path, again
% This passage is needed because of simulink compilation

addpath('script');
addpath('simulink');
addpath('function');
addpath('bin');

%% Adding data to workspace

if config.run.data
    fprintf(1, 'Salvataggio dati... ');
    run('./script/data_creation.m');
    fprintf(1, 'Fatto! \n');
end

if config.run.lqr_assetto
    fprintf(1, 'Elaborazione controllo di assetto... ');
    run('./script/lqr_assetto.m');
    fprintf(1, 'Fatto! \n');
end

if config.run.lqr_completo
    fprintf(1, 'Elaborazione controllo completo... ');
    run('./script/lqr_completo.m');
    fprintf(1, 'Fatto! \n');
end

if config.obstacleAvoid == 1
    % Parametri ricevitore: ultrasonic range finder
    RangeFinderParam = [ 6, 1, 0.1 ];
    RangeFinderMeanError = 0;
    RangeFinderVarianceError = 1;
    RangeFinderErrorGain = 0.1;
    RangeFinderFilterN = [ 1 ];
    RangeFinderFilterD = [ 10, 1 ];
    % Definizione di un ostacolo
    obstacle = cube([5,5,5], [10,-20,0], [0,0,0], [0.5,0.5,0.5]);
end 

%% Run SIMULINK Model

if config.simulink.run_model == 1
    if config.simulink.Open == 1
        open_system(config.simulink.model)
    else 
        load_system(config.simulink.model)
    end
    tic;
    sim(config.simulink.model);
    toc;
end

if config.notification.enable == 1
    sendmail(config.notification.sendto,'Simulation Notification','Simulation has finished. Please check your results');
end