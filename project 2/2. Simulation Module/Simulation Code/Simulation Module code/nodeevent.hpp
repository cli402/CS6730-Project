#ifndef _NODEEVENT_HPP_
#define _NODEEVENT_HPP_

#include "Queue.hpp"
#include <cstdio>
#include <iostream>
#include <queue>
#include "Path.h"
#include <random>

int rand(int a,int Range);
void send_to_Next(Node_Info_Passing&node,Node_queue&node_queue,int i,int simu,float size, bool Normal_distribution,int TOPO_INDEX);
void prepare_node_to_send(Node_queue&node_queue,float Bandwidth,int Num_node,int simu,float size, bool Normal_distribution,int TOPO_INDEX);
void Send_Node(Node_queue & node_queue,float Bandwidth,int simu,float size, bool Normal_distribution,int TOPO_INDEX);
void Generate_node(Node_queue& node_queue,bool a,int n,float info_size_max,int simu,Dij&G,bool Normal_distribution,int TOPO_INDEX);
void Compute_path( Node_Info_Passing&node,Dij &G);
void simulation(Node_queue&node_queue,Dij &G,bool Normal_distribution,float size,int TOPO_INDEX);
void Printtofile(Node_queue&node_queue,float size, bool Normal_distribution,int TOPO_INDEX);
void Printtofile_node(Node_Info_Passing&node,int time_step,float size, bool Normal_distribution,int TOPO_INDEX);
int uniIntRand(int n) ;


#endif 