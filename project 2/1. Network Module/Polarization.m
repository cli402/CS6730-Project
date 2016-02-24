for indexNum = 1:4
    eval(['paths = paths' num2str(indexNum) ' ;'])
    BoN = zeros(1,50);
    for i = 1:49
        for j = i+1:50
            NoP = paths{i,j}{1,1};
            if NoP == 3 
                indexNum
                i
                j
            end
            for k = 1:NoP
                pathLength = length(paths{i,j}{1,2}{1,k});
                for m = 1:pathLength
                    BoN(paths{i,j}{1,2}{1,k}(m)) = BoN(paths{i,j}{1,2}{1,k}(m)) + 1/NoP;
                end
            end
        end
    end
    polValue = (max(BoN)-mean(BoN))/mean(BoN);
    eval(['polValue' num2str(indexNum) '= polValue ;'])
end
