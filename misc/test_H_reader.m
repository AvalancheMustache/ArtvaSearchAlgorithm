% Test funzione H_reader

close all

tP = [3, 0, -3];
m = [0,0,1];
angles = [0,pi/4,0];

fprintf(1,' TESTING VECTOR FIELD \n');
fprintf(1,'  - transmitter position: %3.2f %3.2f %3.2f\n', tP(1), tP(2), tP(3));
fprintf(1,'  - transmitter vector: %3.2f %3.2f %3.2f\n', m(1), m(2), m(3));
fprintf(1,'  - receiver orientation: %3.2f %3.2f %3.2f\n', angles(1), angles(2), angles(3));

fprintf(1,'\n\n Eval vector field:          ');
limit = 10;
step = 0.5;
[x,z] = meshgrid(-limit:step:limit,-limit:step:limit);
SS = size(x,1);
Hx = zeros(SS,SS);
Hz = Hx;
Vx = Hx;
Vz = Hx;
H = Hx;

for i = 1:SS
    fprintf('\b\b\b\b\b\b\b\b%06.2f %%',(i)/(SS)*100);
    for j = 1:SS
       rP = [x(i,j),0,z(i,j)];
       
       tmp = H_receiver(tP,m,rP,angles);
       
       Hx(i,j) = tmp(1);
       Hz(i,j) = tmp(3);
       alpha = atan2(tmp(3),tmp(1));
       Vx(i,j) = 0.1*cos(alpha);
       Vz(i,j) = 0.1*sin(alpha);
       H(i,j) = log(sqrt(Hx(i,j)^2 + Hz(i,j)^2));
    end
end
fprintf(1,'\n');

figure('color','white','Position',[50,50,700,310]); 
  subplot(1,2,1), quiver(x,z,Vx,Vz,'k'), xlabel('x [m]'), ylabel('z [m]'), title('H Field Direction'),xlim([-10,10]),ylim([-10,10]);
  subplot(1,2,2), contourf(x,z,H), xlabel('x [m]'), ylabel('z [m]'), title('H Field Strength');

clear tP m angles x z Hx Hz H Vx Vz alpha rP i j tmp limit step SS;