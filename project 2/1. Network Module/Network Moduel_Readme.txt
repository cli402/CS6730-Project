Step1: Run Network Topology.cpp to generate adjacency matrices for all four network models.

Step2: Run Distance.cpp to calculate <D> for each network and generate inputs for calcualte pi.

Step3: Run Network Topology_RoutingInput.cpp to get the adjancency matrices into desired fomat so that they can be used fo pi calculation.

Step4: Run Implementation.m to generate paths.mat and then import that paths.mat into Polarization.m to calcualte pi values for all the four networks.

Step5. Run Visual.m in the Network Visual folder to visualize all the four networks.


*The kShortestPath.m and dijkstra.m are not written by us, and they are downloaded from Matlab File Exchange.