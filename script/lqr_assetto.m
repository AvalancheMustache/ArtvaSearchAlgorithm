% Identifica il controllo LQR per l'assetto

%
% Impostare questa variabile a 1 per salvare il risultato di K
save_k = 1;


q1 = 150;
q2 = 150;
q3 = 1;
q4 = 100;
q5 = 100;
q6 = 50;
r1 = 1;

load(fullfile(pwd,'../data','data.mat'));

A = [ 0 0 0 1 0 0; 
      0 0 0 0 1 0;
      0 0 0 0 0 1;
      0 0 0 0 0 0;
      0 0 0 0 0 0;
      0 0 0 0 0 0 ];
B = [ 0        0                0                0         0               0; 
      0        0                0                0         0               0;
      0        0                0                0         0               0;
      0        -sqrt(3)/2*L/Ix  -sqrt(3)/2*L/Ix  0         sqrt(3)/2*L/Ix  sqrt(3)/2*L/Ix;
      L/Iy     L/(2*Iy)         -L/(2*Iy)        -L/Iy     -L/(2*Iy)       L/(2*Iy);
      beta/Iz -beta/Iz          beta/Iz          -beta/Iz  beta/Iz         -beta/Iz];
      
Q = [ q1 0  0  0  0  0;
      0  q2 0  0  0  0;
      0  0  q3 0  0  0;
      0  0  0  q4 0  0;
      0  0  0  0  q5 0;
      0  0  0  0  0  q6 ];
  
R = r1 * eye(6);
N = zeros(6);

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
   save(fullfile(pwd,'../data','lqr_controllo_assetto.mat'),'K');
end