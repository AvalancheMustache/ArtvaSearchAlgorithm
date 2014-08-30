%% RESULTS PLOTTING

close all

%% Plot State variable position and attitude

figure('color','white','position',[50,50,700,310]);
    subplot(1,2,1);
       plot(sim_time,sim_position(:,1),'b'); hold on;
       plot(sim_time,sim_position(:,2),'g'); hold on;
       plot(sim_time,sim_position(:,3),'r');
       legend({'x','y','z'});
       xlabel('t [s]');
       ylabel('Position [m]');
       title('Position'); grid on;
    subplot(1,2,2);
       plot(sim_time,sim_attitude(:,1),'b'); hold on;
       plot(sim_time,sim_attitude(:,2),'g'); hold on;
       plot(sim_time,sim_attitude(:,3),'r');
       legend({'\phi','\theta','\psi'});
       xlabel('t [s]');
       ylabel('Orientation [rad]');
       title('Orientation'); grid on;
       
%figure('color','white');
%   plot3(sim_position(:,1),sim_position(:,2),sim_position(:,3),'k');
%   xlabel('x [m]'); ylabel('y [m]'); zlabel('z [m]'); title('Position');

%% Plot position and attitude

j = 0;
step = 1;
scale = 1;
figure('color','white');
plot3(sim_position(:,1), sim_position(:,2), sim_position(:,3), 'k'); hold on;
for i = 1:size(sim_time,1)
    if sim_time(i,1) > j*step
        if j < 4
            j = (j+0.35)^2;
        else
            j = 1.6*j;
        end        
        rot = scale .* Rot_B2G_mex(sim_attitude(i,:));
        %rot = scale .* rotation_matrix(sim_attitude(i,:));
        pos = sim_position(i,:);
        plot3([pos(1,1),pos(1,1) + rot(1,1)],[pos(1,2),pos(1,2) + rot(2,1)],[pos(1,3), pos(1,3) + rot(3,1)],'b'); hold on;
        plot3([pos(1,1),pos(1,1) + rot(1,2)],[pos(1,2),pos(1,2) + rot(2,2)],[pos(1,3), pos(1,3) + rot(3,2)],'g'); hold on;
        plot3([pos(1,1),pos(1,1) + rot(1,3)],[pos(1,2),pos(1,2) + rot(2,3)],[pos(1,3), pos(1,3) + rot(3,3)],'r'); hold on;
    end
end
plot3(TP(1),TP(2),TP(3),'ro');
for i = 1:size(obstacle,2)
    plot3(obstacle(1,i),obstacle(2,i),obstacle(3,i),'x');
end
title('Trajectory'); grid on;
xlabel('x [m]'); ylabel('y [m]'); zlabel('z [m]');

%% 2D plotting

Posizione = squeeze(Posizione);
pos_opt = squeeze(pos_opt);

    
figure('color','white')
    subplot(2,1,1)
        plot(sim_time,cos_theta,'k'); hold on; plot(sim_time,cos_theta_real,'k--'); hold on;
        plot(sim_time,sin_theta,'k'); hold on; plot(sim_time,sin_theta_real,'k--'); grid on;
        title('Learned orientation follower');
    subplot(2,1,2)
        plot(sim_time,Habs,'k'); hold on; plot(sim_time,Habs_real,'r'); grid on;
        title('Learned |H| follower');
    
%% Position ParzenWindow LEARNED

sigma = 1;
X = -100:0.1:100;
extX = @(x)(ParzenWindowEstimator(x,pos_opt(1,:)',sigma));
for i = 1:size(X,2)
    extX_data(i) = extX(X(i));
end

sigma = 1;
Y = -100:0.1:100;
extY = @(y)(ParzenWindowEstimator(y,pos_opt(2,:)',sigma));
for i = 1:size(Y,2)
    extY_data(i) = extY(Y(i));
end

figure('color','white')
    title('Learned Optimization Problem');
    subplot(4,4,[2,3,4,6,7,8,10,11,12]);
        plot(TP(1,1),TP(1,2),'ro'); hold on;
        plot(Posizione(:,1),Posizione(:,2),'k'); hold on;
        plot(pos_opt(1,:),pos_opt(2,:),'x','Color',[.7 .7 .7]);
        xlim([-50;50]);ylim([-50;50]);
        xlabel('x [m]'); ylabel('y [m]'); grid on;
    subplot(4,4,[14,15,16])
        hextX = plot(X,extX_data); hold on; grid on;
        camroll(180);
        set(gca(),'xtick',[]);
    subplot(4,4,[1,5,9])
        plot(Y,extY_data,'r'); grid on;
        camroll(90);
        set(gca(),'xtick',[]);

%% Range finder receiver

figure('color','white')
    subplot(4,4,[2,3]);
        plot(time,RangeResults(:,1));
        title({'Range Finder Receiver'});
        legend({'0'});
    subplot(4,4,[5,6]);
        plot(time,RangeResults(:,2));
        legend({'\pi/3'});
    subplot(4,4,[7,8]);
        plot(time,RangeResults(:,3));
        legend({'5 \pi/3'});
    subplot(4,4,[9,10]);
        plot(time,RangeResults(:,4));
        legend({'2 \pi/3'});
    subplot(4,4,[11,12]);
        plot(time,RangeResults(:,5));
        legend({'4 \pi/3'});
    subplot(4,4,[14,15]);
        plot(time,RangeResults(:,6));
        legend({'3 \pi/3'});
        
%% Position ParzenWindow UNLEARNED
% 
% sigma = 1;
% X = -100:0.1:100;
% extX = @(x)(ParzenWindowEstimator(x,pos_opt_rt(1,:)',sigma));
% for i = 1:size(X,2)
%     extX_data(i) = extX(X(i));
% end
% 
% sigma = 1;
% Y = -100:0.1:100;
% extY = @(y)(ParzenWindowEstimator(y,pos_opt_rt(2,:)',sigma));
% for i = 1:size(Y,2)
%     extY_data(i) = extY(Y(i));
% end