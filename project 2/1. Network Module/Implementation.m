networkNames = {'StarLike_50_97', 'SF_50_100', 'Random_50_100', 'Ring_50_100'};

for networkIndex = 1:4;
    
    DijFileName = char(strcat('ShortestDistance/Dij_', networkNames(networkIndex),{'.txt'}));
    NTFileName = char(strcat('Network Topology/', networkNames(networkIndex),{'.txt'}));
    
    data = dlmread(DijFileName,',');
    matrix = dlmread(NTFileName,',');

    dimensions = size(matrix);

    for i = 1 : dimensions(1);
        for j = 1 : dimensions(1); 
            if matrix(i,j) == 0;
                matrix(i,j) = inf;
            end
        end
    end
    
    paths = cell(dimensions(1),dimensions(1)) ;
    for i = 1 : (dimensions(1)-1)*dimensions(1)/2;
            source = data(i,1)+1;
            destination = data(i,2)+1;
            k = data(i,3);
            [shortestPaths, totalCosts] = kShortestPath(matrix, source, destination, k);
            numberOrPaths = size(shortestPaths);
            paths{source,destination} = {numberOrPaths(2),shortestPaths};

    end
    
    eval(['paths' num2str(networkIndex) '= paths ;'])
end