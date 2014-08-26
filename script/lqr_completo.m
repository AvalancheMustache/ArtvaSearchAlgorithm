% Definisce il controllo esterno di assetto del sistema stabilizzato

%
% Impostare questa variabile a 1 per salvare il risultato di K
save_k = 1;
psi = 1.5;

load(fullfile(pwd,'../data','data.mat'));

A = [0 0 0 0.1e1 * cos(psi) 0.1e1 * sin(psi) 0 0 0 0 0 0 0; 
     0 0 0 -0.1e1 * sin(psi) 0.1e1 * cos(psi) 0 0 0 0 0 0 0; 
     0 0 0 0 0 0.1e1 0 0 0 0 0 0; 
     0 0 0 0 0 0 0 0.1e1 * g 0 0 0 0; 
     0 0 0 0 0 0 -0.1e1 * g 0 0 0 0 0; 
     0 0 0 0 0 0 0 0 0 0 0 0; 
     0 0 0 0 0 0 0 0 0 0.1e1 0 0; 
     0 0 0 0 0 0 0 0 0 0 0.1e1 0; 
     0 0 0 0 0 0 0 0 0 0 0 0.1e1; 
     0 0 0 0 0 0 0 0 0 0 0 0; 
     0 0 0 0 0 0 0 0 0 0 0 0; 
     0 0 0 0 0 0 0 0 0 0 0 0;];
B = [0 0 0 0 0 0; 
     0 0 0 0 0 0; 
     0 0 0 0 0 0; 
     0 0 0 0 0 0; 
     0 0 0 0 0 0; 
     -0.1e1 / m -0.1e1 / m -0.1e1 / m -0.1e1 / m -0.1e1 / m -0.1e1 / m; 
     0 0 0 0 0 0; 
     0 0 0 0 0 0; 
     0 0 0 0 0 0; 
     0 -sqrt(0.3e1) / Ix * L / 0.2e1 -sqrt(0.3e1) / Ix * L / 0.2e1 0 sqrt(0.3e1) / Ix * L / 0.2e1 sqrt(0.3e1) / Ix * L / 0.2e1; 
     0.1e1 / Iy * L 0.1e1 / Iy * L / 0.2e1 -0.1e1 / Iy * L / 0.2e1 -0.1e1 / Iy * L -0.1e1 / Iy * L / 0.2e1 0.1e1 / Iy * L / 0.2e1; 
     0.1e1 / Iz * beta -0.1e1 / Iz * beta 0.1e1 / Iz * beta -0.1e1 / Iz * beta 0.1e1 / Iz * beta -0.1e1 / Iz * beta;];

r = 1;
R = r * eye(6,6);
Q = zeros(12,12);

Q(1,1)   = 10;
Q(2,2)   = 10;
Q(3,3)   = 1.5;
Q(4,4)   = 0.01;
Q(5,5)   = 0.01;
Q(6,6)   = 0.01;
Q(7,7)   = 20;
Q(8,8)   = 20;
Q(9,9)   = 10;
Q(10,10) = 15;
Q(11,11) = 15;
Q(12,12) = 5;

N = zeros(12,6);

[K, P, e] = lqr(A,B,Q,R,N);

format short;
fprintf(1,'\n Matrice A e B: \n');
A
B
fprintf(1,'\n Risultato del controllo: \n');
K
fprintf(1,'\n Soluzione equazione Riccati: \n');
P
fprintf(1,'\n Autovalori del risultato: \n');
e
format long;

if save_k
   save(fullfile(pwd,'../data','lqr_controllo_completo.mat'),'K');
end