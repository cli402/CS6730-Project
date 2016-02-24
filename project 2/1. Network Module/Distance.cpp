#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdlib.h>

#define INFINITY 999

using namespace std;


static const int number = 50;


//Initialize oath calculation class
class Dij{
    public:
        static const int numOfV = number;
        int predecessor[numOfV], distance[numOfV];
        int adjMatrix[number][number];
        void trys(string);
        int tree[numOfV][numOfV];
        bool mark[numOfV];
        int source;
        int dest;
        void initialize();
        void calculateDistance();
        void output();
        void printPath(int);
        int getClosestUnmarkedNode();
};


//Read adjacent matrix in
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


//Initialize the calculation
void Dij::initialize(){
    for(int i = 0; i < numOfV; i++){
        mark[i] = false;
        predecessor[i] = -1;
        distance[i] = INFINITY;
    }
    distance[source] = 0;
}


//Find the next potential node on path
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


//Calculate the distance from origin to the potential next node on path
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


//Print out result to screen and files
void Dij::printPath(int node){
    if(node == source)
        cout<<node<<"..";
    else if(predecessor[node] == -1)
        cout<<"No path from “<<source<<”to "<<node<<endl;
    else {
        printPath(predecessor[node]);
        cout<<node<<"..";
    }
}


//To get output
void Dij::output(){
    if(dest == source)
        cout<<source<<".."<<source;
    else
        printPath(dest);

    cout<<"->"<<distance[dest]<<endl;
}


//Wrap functions up
int main(){

    for (int networkIndex = 0; networkIndex < 4; networkIndex++){
        string networkNames[4] = {"StarLike_50_97", "SF_50_100", "Random_50_100", "Ring_50_100"};
        string networkName = networkNames[networkIndex];
        ofstream myfile;
        myfile.open("ShortestDistance/Dij_" + networkName + ".txt");
        int totalDistance = 0;

        Dij G;
        G.trys("Network Topology/" + networkName + ".txt");

        for(int i = 0; i < number -1; i++){
                G.source = i;
                G.calculateDistance();
                for(int j = i + 1; j < number; j++){
                    G.dest = j;
                    totalDistance = totalDistance + G.distance[G.dest];
                    myfile<<i<<","<<j<<","<<G.distance[G.dest]<<"\n";
                }
        }
        float avgDistance = float(totalDistance) * 2.0 / float(number* (number-1));
        myfile<<avgDistance<<"\n";
        myfile.close();
    }
    return 0;
}

