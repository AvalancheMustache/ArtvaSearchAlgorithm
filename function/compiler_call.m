function compiler_call( x, y )
%COMPILE compilation handle for main
    if or(strcmp(y,'release'),strcmp(y,'r'))
        fprintf(1,'Compilazione funzione di RELEASE: %s ... ',x);
        cd ./function
        system(sprintf('mex %s -outdir ../bin',x));
        cd ./..
        fprintf(1, 'Fatto! \n');
    elseif or(strcmp(y,'debug'),strcmp(y,'r'))
        fprintf(1,'Compilazione funzione di DEBUG: %s ... ',x);
        cd ./function
        system(sprintf('mex -g -D__DEBUG %s -outdir ../bin',x));
        cd ./..
        fprintf(1, 'Fatto! \n');
    end
end

