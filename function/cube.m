function obstacle = cube( Size,Origin,Orientation,Resolution )
%CUBE define cube in the speace
    obstacle = zeros(3,int32((floor(Size(1)/Resolution(1)) + 1)*(floor(Size(2)/Resolution(2)) + 1)*(floor(Size(3)/Resolution(3)) + 1)));
    z = 0;
    RR = Rot_B2G_mex(Orientation);
    for i=0:Resolution(1):Size(1)
        for j=0:Resolution(2):Size(2)
            for k=0:Resolution(3):Size(3)
                z = z +1;
                obstacle(:,z) = RR*[ i + Origin(1), j + Origin(2), k + Origin(3)]';
            end
        end
    end
end

