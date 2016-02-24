#include "nodeevent.hpp"
#include <cmath>
#include "Queue.hpp"
#include "Path.h"
#include <iostream>
#include <fstream>
#include <random>
using namespace std;
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//define the queue capacity
#define Queue_Capacity 10
extern float sigma,mu;

string networkNames[4] = {"StarLike", "SF", "Random", "Ring"};


//prepare the info to be send to its destination according to the capacity of the node
//after the info has been send from its previous node
void send_to_Next(Node_Info_Passing&info, Node_queue&node_queue,
                  int i,int simu,float size,bool Normal_distribution,
                  int TOPO_INDEX)
{
    info.position = info.Path.front();

    if(info.position != info.Destination){
        if ((node_queue.Queue_Size[info.position] + info.info_size) <= Queue_Capacity){
            info.Path.pop();
            info.Simul_step = simu;
            node_queue.addToQueue(info);
            node_queue.Queue_Size[info.position] += info.info_size;
            node_queue.success_pass_counter += 1;
        }else{
            node_queue.aborted_counter += 1;
        }
    }else{
        Printtofile_node(info, simu,size,Normal_distribution,TOPO_INDEX);
        node_queue.success_deliver_counter += 1;
    }
    //decrease the total info-size of the current Queue_size
    node_queue.Queue_Size[i] -= info.info_size;
};

//pop out the node and send it to the next destination.
//set the bandwidth of the node to limit the number of info that could be sent
void prepare_node_to_send(Node_queue&node_queue, float Bandwidth, int Num_node,
                           int simu,float size, bool Normal_distribution,int TOPO_INDEX){
    float Band_width = Bandwidth;

    while(Band_width>0){
        if (node_queue.Info_Queue[Num_node].size()&&node_queue.Info_Queue[Num_node].front().Simul_step < simu){

            if(node_queue.Info_Queue[Num_node].front().info_size <= Band_width){
                send_to_Next(node_queue.Info_Queue[Num_node].front(),
                             node_queue, Num_node, simu,size,Normal_distribution,TOPO_INDEX);
                Band_width -= node_queue.Info_Queue[Num_node].front().info_size;
                node_queue.Info_Queue[Num_node].pop();
            }else{
                break;
            }

        }else{
            break;
        }

    }
};


//wrapper function for the Send_Node function
void Send_Node(Node_queue & node_queue,float Bandwidth,
               int simu,float size, bool Normal_distribution,
               int TOPO_INDEX){
    for(int i=0; i<50; i++){
	//message sending protocol, limited to the bandwidth of the node
        prepare_node_to_send(node_queue,Bandwidth,i,simu,size,Normal_distribution,TOPO_INDEX);
    }
};


mt19937 gen(time(NULL));
int uniIntRand(int n) {
    uniform_int_distribution<int> distribution(1, n);
    return distribution(gen)-1;
};

std::default_random_engine generator;
float ND(float mu,float sigma){
    normal_distribution<float> distribution(mu,sigma);
    return distribution(generator);
};

//for the generate of the node, at each simulation step, each
//node would generate one piece of infomation according the 
// size principle we choose at the begining. 
void Generate_node(Node_queue& node_queue, bool a, int n,
                   float info_size_max, int simu, Dij &G,
                   bool Normal_distribution,int TOPO_INDEX){
    //set the origin, destination, path, step ect. info into the info
    for (int i=0;i<n;i++){
        Node_Info_Passing info;
        info.Origin = i;
        info.Simul_step = simu;
        info.Initial_Sim_Step = simu;
        info.position = i;

        //follow the uniform distribution pattern to control the size
        //of the info
        if (Normal_distribution==false){
        info.info_size = info_size_max; }
       //follow the normal distribution mode to generate the info
        else {
       while(1){
       info.info_size=ND(mu,sigma);
       if (info.info_size>0&&info.info_size<1){
        break;
       }
       }
    }
        int dest;
        while(1){
            dest = uniIntRand(50);
            if(dest != info.Origin){
                break;
            }
        }

        info.Destination = dest;

        Compute_path(info, G);

        node_queue.addToQueue(info);

        node_queue.Queue_Size[info.position] += info.info_size;
    }
};

//getting the shortest path for the info that has been generated
void Compute_path( Node_Info_Passing&info, Dij &G){
    info.Path = Shortest_Path(info.Origin, info.Destination, G);
    Clear_Path(&G.shortestPath);
    //Print_Path(info.Path); //Origin is not included.
};


//wrapper function to get the simulation running
void simulation(Node_queue&node_queue,Dij &G,bool Normal_distribution,
                float size,int TOPO_INDEX){
    float Bandwidth = 1.0;

    for (int i=1; i < 101; i++){
        Generate_node(node_queue, 0, 50, size, i, G,Normal_distribution,TOPO_INDEX);
        Send_Node(node_queue, Bandwidth, i,size,Normal_distribution,TOPO_INDEX);
        Printtofile(node_queue,size,Normal_distribution,TOPO_INDEX);
    }
};

//get the different results put into the file for analysis
void Printtofile(Node_queue&node_queue,float size, bool Normal_distribution,int TOPO_INDEX){
    ofstream queue_size_file;

    if (Normal_distribution==false){
        const string fileName = networkNames[TOPO_INDEX] + "/SIZE/"+"Queue_Size"+"_size_"+std::to_string(size)+".csv";
        queue_size_file.open (fileName,ios::app);
    }else {
        const string fileName = networkNames[TOPO_INDEX] + "/SIZE/"+"Queue_Size_Normal_distribution--mu-"+std::to_string(mu)+"-sig-"+std::to_string(sigma)+".csv";
        queue_size_file.open (fileName,ios::app);
    }
    //node_queue.Queue_Size.size() = 50 for now
    for(int i=0; i<node_queue.Queue_Size.size(); i++){
        queue_size_file << node_queue.Queue_Size[i]<<",";
    }

    queue_size_file<<"\n";
    queue_size_file.close();

    //success_send_counter print out
    ofstream counter;
    if (Normal_distribution==false){

    const string fileName = networkNames[TOPO_INDEX] + "/CONT/"+"Counter_Pa_De_Ab"+"_size_"+std::to_string(size)+".csv";
    counter.open (fileName,ios::app);
    }
    else {
    const string fileName = networkNames[TOPO_INDEX] + "/CONT/"+"Counter_Pa_De_Ab_Normal_distribution--mu-"+std::to_string(mu)+"-sig-"+std::to_string(sigma)+".csv";
    counter.open (fileName,ios::app);
}
    counter << node_queue.success_pass_counter + node_queue.success_deliver_counter<<","<<node_queue.success_deliver_counter<<","<<node_queue.aborted_counter<<"\n";
    counter.close();
};


//get the infomation printed out for the node that has been successfully sent
void Printtofile_node(Node_Info_Passing&info, int time_step,
                      float size, bool Normal_distribution,int TOPO_INDEX){
    //Node passing
    ofstream info_delivery_time;
     if (Normal_distribution==false){

    const string fileName = networkNames[TOPO_INDEX] + "/DEL/"+"Info_Deliver_Time"+"_size_"+std::to_string(size)+".csv";
    info_delivery_time.open (fileName,ios::app);
    }
    else {
    const string fileName = networkNames[TOPO_INDEX] + "/DEL/"+"Info_Deliver_Time_Normal_distribution-mu-"+std::to_string(mu)+"-sig-"+std::to_string(sigma)+".csv";
    info_delivery_time.open (fileName,ios::app);
}
    info_delivery_time <<time_step<<","<<time_step-info.Initial_Sim_Step;
    info_delivery_time<<"\n";
    info_delivery_time.close();
};

// const string fileName = "Network Topology/" + networkName + ".txt";
// string networkNames[4] = {"StarLike", "SF", "Random", "Ring"};
// string networkName = networkNames[networkIndex];
