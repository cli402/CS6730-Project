#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include "Path.h"

#define INFINITY 999

using namespace std;

void Dij::trys(string  fileName){
    ifstream file(fileName);

    int col_read = number;
    int row_read = number;

    for(int row = 0; row < row_read; ++row)
    {
        string line;
        getline(file, line);

        stringstream iss(line);
        for (int col = 0; col <col_read; ++col)
        {
            string val;
          getline(iss, val, ',');

            int number;
            number=atoi(val.c_str());
            adjMatrix[row][col] = number;
        }
    }
}

void Dij::initialize(){
    for(int i = 0; i < numOfV; i++){
        mark[i] = false;
        predecessor[i] = -1;
        distance[i] = INFINITY;
    }
    distance[source] = 0;
}


int Dij::getClosestUnmarkedNode(){
    int minDistance = INFINITY;
    int closestUnmarkedNode;
    for(int i = 0; i < numOfV; i++){
        if((!mark[i]) && (minDistance >= distance[i])){
            minDistance = distance[i];
            closestUnmarkedNode = i;
        }
    }
    return closestUnmarkedNode;
}

void Dij::calculateDistance(){
    initialize();
    int minDistance = INFINITY;
    int closestUnmarkedNode;
    int count = 0;
    while(count < numOfV){
        closestUnmarkedNode = getClosestUnmarkedNode();
        mark[closestUnmarkedNode] = true;
        for(int i = 0; i < numOfV; i++){
            if((!mark[i]) && (adjMatrix[closestUnmarkedNode][i] > 0)){
                if(distance[i] > distance[closestUnmarkedNode] + adjMatrix[closestUnmarkedNode][i]){
                   distance[i] = distance[closestUnmarkedNode] + adjMatrix[closestUnmarkedNode][i];
                   predecessor[i] = closestUnmarkedNode;
                }
            }
        }
        count++;
    }
}

void Dij::printPath(int node){
    if(node == source){
        //cout<<node<<"..";
    }
    else if(predecessor[node] == -1){
        //cout<<"No path from “<<source<<”to "<<node<<endl;
    }
    else {
        printPath(predecessor[node]);
        //cout<<node<<"..";
        shortestPath.push(node);
      //  cout<<shortestPath.back()<<"..";
    }
}

void Dij::output(){
    if(dest == source){
        //cout<<source<<".."<<source;
    }
    else
        printPath(dest);

    //cout<<"->"<<distance[dest]<<endl;
}

void Init_Graph(Dij*G){
    for (int networkIndex = 0; networkIndex < 4; networkIndex++){
            string networkNames[4] = {"StarLike_50_97", "SF_50_100", "Random_50_100", "Ring_50_100"};
            string networkName = networkNames[networkIndex];
            ofstream myfile;
            myfile.open("ShortestDistance/Dij_" + networkName + ".txt");
            G[networkIndex].trys("Network Topology/" + networkName + ".txt");
        }
}


queue<int> Shortest_Path(int source, int dest, Dij &G){

    G.source = source;
    G.dest = dest;
    G.calculateDistance();
    G.output();

    return G.shortestPath;
};

void Print_Path(queue<int> a){
    while (!a.empty()){
    std::cout << ' ' << a.front();
    a.pop();
    }

    std::cout << '\n';
};

void Clear_Path(queue<int> *a){
    while (!a->empty()){
    a->pop();
    }
};
