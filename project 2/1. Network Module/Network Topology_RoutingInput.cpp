#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

//This function is to read in the adjacent matrix of each network and then output it to the desried form for finidng all the shortest paths beteen two nodes within a network
int main(){

//The read in part
    int networkIndex = 0;
    int numberOfNodes = 50;

    string networkName = "StarLike_50_97";

    ifstream file1(networkName + ".txt");
    int count = 0;

    int col_read = numberOfNodes;
    int row_read = numberOfNodes;

    #define row_read row_read
    #define col_read col_read

    int array[row_read][col_read];

    for(int row = 0; row < row_read; ++row){
        string line;
        getline(file1, line,';');
        stringstream iss(line);

        for (int col = 0; col <col_read; ++col)
        {
            string val;
            getline(iss, val, ',');

            int number = 0;
            number = atoi(val.c_str());
            array[row][col] = number;
            if (number == 1){
                count = count + 1;
            }
        }
    }


//The output part
    ofstream file2;
    file2.open("RouteInput_"+ networkName + ".txt");
    file2<<"{";

    int checkCount = 0;
    for(int row = 0; row < row_read; ++row){
        for (int col = 0; col <col_read; ++col)
        {

            if (array[row][col] ==1){
                checkCount = checkCount + 1;
                if (checkCount != count){
                    file2<<"Link<int>("<<row<<","<<col<<"),\n";
                }else{
                    file2<<"Link<int>("<<row<<","<<col<<")};";

                }
            }
        }
    }

    file2.close();

    return 0;
}



