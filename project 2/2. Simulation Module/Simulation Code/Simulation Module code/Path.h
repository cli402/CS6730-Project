#ifndef DISTANCE_H_INCLUDED
#define DISTANCE_H_INCLUDED
#include <vector>
#include <string>
#include <queue>
using namespace std;
static const int number=50;

class Dij{
    public:
        queue <int> shortestPath;
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
void Init_Graph(Dij*G);
queue<int> Shortest_Path(int, int , Dij&);
void Print_Path(queue<int> a);
void Clear_Path(queue<int> *a);


#endif // DISTANCE_H_INCLUDED
