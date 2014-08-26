function simulink2svg(model,filename)

    % Get handle of current model
    h = get_param(model,'Handle');
    print(h,'-dsvg',filename);

end
                                 