%% Crea un file contente tutti i dati necessari alla simulazione 

% massa del drone
m    = 2.000;

% Inerzia del drone
Ix   = 0.010;
Iy   = 0.008;
Iz   = 0.030;

% Rapporto tra spinta e drag
beta = 0.200;
% Lunghezza del braccio
L    = 0.300;
% Accelerazione gravitazionale
g    = 9.810;

% Rumore misura
%vt = zeros(3,1);
%Qt = eye(3,3);
%Qt = zeros(3,3);

% Rumore Stato
wt = zeros(9,1);
%Rt = eye(9,9);
Rt = zeros(9,9);

vt = zeros(3,1);
Qt = 0.5*ones(3,3);

TP = [20,-25,-3];
RP = [3,3,4];
M = [0,0,1];

%% Salvataggio dei dati
save(fullfile(pwd,'../data','data.mat'),'m','Ix','Iy','Iz','beta','L','g','vt','Rt','wt','Qt');

PARAM = [ m, Ix, Iy, Iz, beta, L, g ];