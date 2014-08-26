function extimates = optimizer2(rr, H_meas, guess)
    DEBUG = 0;
    if DEBUG
       fprintf(1,'DEBUG :: Optimizer2\n');
       fprintf(1,'rr dimensions: %d x %d\n', size(rr,1), size(rr,2));
       fprintf(1,'H_mean dimensions: %d x %d\n', size(H_meas,1), size(H_meas,2));
       fprintf(1,'guess dimensions: %d x %d\n\n', size(guess,1), size(guess,2));
    end
    fsolve_options = optimoptions('fsolve', ...
                                  'Display','off', ... % must be off
                                  'Algorithm','levenberg-marquardt', ...
                                  'ScaleProblem','Jacobian', ...
                                   'TolFun',1e-18, ...
                                   'TolX', 1e-9);
    extimates = fsolve(@(x)(optimizer_residuals_c2(x, rr, H_meas)), guess, fsolve_options);
end