function sfunction_compiler_call(model_string, open_model)
% SFUNCTION_COMPILER_CALL Given a model compile all S-Function in 
% s-Function Builder Blocks.
% Prints in console build results.
    close_system(model_string,0);
    if open_model == 1
       open_system(model_string); 
    else 
        load_system(model_string);
    end
    cd './bin'
    if strcmp(bdroot,model_string)
        fprintf(1,'In system :: %s :: found blocks: \n',model_string);
        blkNames = find_system(bdroot,'BlockType','S-Function');
        for i = 1:numel(blkNames)
           fprintf(1,'%i :: %s :: Compiled? ',i,blkNames{i});
           blkHandle = get_param(blkNames{i}, 'Handle');
           appdata = sfunctionwizard(blkHandle,'GetApplicationData');
           appdata = sfunctionwizard(blkHandle,'Build',appdata);
           if appdata.compileSuccess == 1
              fprintf(1,'COMPILED!\n'); 
           else
              fprintf(1,'NOT Compiled?!?\n'); 
           end
        end
    else
        fprintf(1,'ERROR OPENING SYSTEM! \n');
    end
    
    cd './..'

end

