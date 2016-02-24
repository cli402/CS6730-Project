#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <random>
#include <iostream>
using namespace std;

static const int numberOfV = 30;

static const int numberOfE = 120;

//Generate the seed for random number generation functions
mt19937 gen(time(NULL));

//Uniform integer random number generator
int uniIntRand(int n) {
    uniform_int_distribution<int> distribution(1, n);
    return distribution(gen);
}

//Uniform real number generator
double uniRealRand() {
    uniform_real_distribution<double> distribution(0.0,1.0);
    return distribution(gen);
}

//Output the generated adjacent matrix to screen to check results validity
void outputToText( string networkName, int AMatrix[][numberOfV], int Node_num){
    ofstream myfile;
    const string fileName = "Network Topology/" + networkName + ".txt";
    myfile.open (fileName);
    for (int i=0; i < Node_num; i++){
        for (int j=0; j < Node_num; j++){
            if (j==49) {
              myfile<< AMatrix[i][j];
            }
            else{
                myfile<< AMatrix[i][j]<< ",";
            }
        }
    myfile<<"\n";
    }
    myfile.close();
}


//Ring Network
void Ring_Topology(int n){
   int array[numberOfV][numberOfV] = {};
	for(int i = 0; i < n; i++){
	  int N1=(i+1+n)%n;
	  int N2=(i+2+n)%n;
	  int N3=(i-1+n)%n;
	  int N4=(i-2+n)%n;
      array[i][N1]=1;
      array[i][N2]=1;
      array[i][N3]=1;
      array[i][N4]=1;
    }
    outputToText("Ring_numberOfV_numberOfE", array, n);
}


//StarLike Network
void StarLike_Topology(int N){
    int StarLike[numberOfV][numberOfV] = {0};
	for(int nRow = 0; nRow<2; nRow++)
		for (int nCol = 0; nCol<N; nCol++)
			StarLike[nRow][nCol] = 1;

	for(int nRow = 0; nRow<N; nRow++)
		for (int nCol = 0; nCol<2; nCol++)
			StarLike[nRow][nCol] = 1;

	StarLike[0][0] = 0;
	StarLike[1][1] = 0;

    outputToText("StarLike_numberOfV_97", StarLike, N);
}


//Random Network
void generate_Node(int * Node,int range){
	Node[0]=uniIntRand(range)-1;
	Node[1]=uniIntRand(range)-1;
}

void Rand_Topology(int Node_num,int Link_num){
    //generate the desired matrix
   int array[numberOfV][numberOfV]={};
   int Node[2]={};

   //generate the random topology of the matrix
   for (int i=0;i<Link_num;i++){

       while (1){
            generate_Node(Node,Node_num);
            int N1 = Node[0];
            int N2 = Node[1];
        if (array[N1][N2]==0&&array[N2][N1]==0&& N1!=N2){
              array[N1][N2]=1;
              array[N2][N1]=1;
              break;
        }
        else
            {continue;}
        }
    }

    outputToText("Random_30_120", array, Node_num);
}


//Scale Free Network
int PickNode(int D[numberOfV], int N, int DTotal){
	int i;
	double Prob_Pick = uniRealRand();
    double Degree_Pick= Prob_Pick * double(DTotal);
    double Add_Degree = 0.0;

	for (i = 0; i < N; ++i) {
        Add_Degree = Add_Degree + double(D[i]);
	    if (Degree_Pick <= Add_Degree) {
            return i;
            break;
	    }
	}
}

void Scalefree_Topology(int Node_num, int existing_node_num){
    int D_Total = 0;  //sum of the node degrees over the entire network
    int D_Matrix[numberOfV] = {};
    int array[numberOfV][numberOfV]={};

//Generate a fully connected network with desired number of nodes
    for (int i = 0; i < existing_node_num; ++i) {
        D_Matrix[i] = existing_node_num - 1;
        for (int j = 0; j < existing_node_num; ++j) {
            if (i!=j){
            array[i][j]=1;
            D_Total += 1;
            }
        }
	}

//Preferential node selection
	for (int i = existing_node_num ; i < Node_num; ++i) {
		int Picked_Node1;
		int Picked_Node2;

		while(1){
			Picked_Node1 = PickNode(D_Matrix, i, D_Total);
			if (Picked_Node1!=i)break;
			else continue;
		}

		while(1){
            Picked_Node2=PickNode(D_Matrix,i,D_Total);
			if (Picked_Node2==Picked_Node1||Picked_Node2==i)
				continue;
			else break;
		}

		D_Matrix[Picked_Node1]++;
		D_Matrix[Picked_Node2]++;
		D_Matrix[i] = 2;
		D_Total += 4;
        array[i][Picked_Node1]=1;
        array[i][Picked_Node2]=1;
        array[Picked_Node1][i]=1;
        array[Picked_Node2][i]=1;
	}

    outputToText("SF_30_120", array, Node_num);

}


int main (){
	Rand_Topology(numberOfV,numberOfE/2);
	//Ring_Topology(numberOfV);
    //StarLike_Topology(numberOfV);
    Scalefree_Topology(numberOfV,5);
	return 0;
}

