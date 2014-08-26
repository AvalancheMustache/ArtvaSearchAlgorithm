function [mut, Sigmat, Ht, Gt, Kt] = ekf( mut_hat, Sigmat_1, Ht, Gt, zt, zt_mut_hat, Rt, Qt )
%EKF Extende Kalman Filter
%
% [mut, Sigmat, Ht, Gt, Kt] = ekf( mut_hat, Sigmat_1, Ht, Gt, zt, zt_mut_hat, Rt, Qt )
%
% Implement extended Kalman Filter algorithm, using persistent memory. This
% function DO NOT perform linearization steps. Already linearized matrix
% required, input not required. Measurement from estimated stade must be
% performed outside and passed to the function
%
% Input
% -> mut_hat : state evaluated from non linear function, obtained from
%              previous estimation
% -> Sigmat_1 : previous covariance estimation
% -> Ht : measurement function linearized matrix
% -> Gt : model function linearized matrix
% -> zt : actual measurement
% -> zt_mut_hat : measurement from estimated state
% -> Rt : state noise covariance matrix
% -> Qt : measurement noise covariance matrix
%
% Output
% <- mut : new state stimation
% <- Sigmat : new covariance estimation
% <- Ht : measurement function linearized matrix
% <- Gt : model function linearized matrix
% <- Kt : Kalman Gain

    Sigmat_hat = Gt * Sigmat_1 * (Gt') + Rt;
    Kt = Sigmat_hat * Ht' * pinv(Ht * Sigmat_hat * Ht' + Qt);
    
    mut = mut_hat + Kt * (zt - zt_mut_hat);
    Sigmat = (eye(size(Sigmat_1)) - Kt * Ht) * Sigmat_hat;

end

