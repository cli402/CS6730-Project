    #include <iostream>
    #include <vector>
    #include "nodeevent.hpp"
    #include "Path.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <cstdlib>
    #include <sstream>
#include <stdexcept>

    using namespace std;
     float sigma,mu;


void print_usage()
{
    
    std::cout << " USAGE:      ./TOPOLO -s n [ or arguement -d <mu> <sigma>]" << std::endl;
    std::cout << "             define the info size of each node generates "<<std::endl;
    std::cout << "             (-s <n>  std::string(argv[1])size range from 0.05 to 1 )"<< std::endl;
    std::cout << "             Or else if input distribution mode   <-d> is on" << std::endl;
    std::cout << "             Generate the info with the size following the normal distribution " << std::endl;
    std::cout << "             set the mu and sigma to define the shape of the distribution " << std::endl;

}

    int main(int argc, char *argv[])
   {
     bool Normal_distribution=false;

        //parse the argument into the system
    if (argc >4||argc<2)
     {
      print_usage();
      exit(EXIT_FAILURE);
    }

       float lambda; 
     
         
      if (argc==3&&!std::string(argv[1]).compare("-s")){
          lambda=stof(argv[2]);
        
        if (lambda<0||lambda>=1){
          print_usage();
          exit(EXIT_FAILURE);
        }

      }
       
       if (argc ==4)
        {    sigma=stof(argv[3]);
             mu=stof(argv[2]);

          if (!string(argv[1]).compare("-d")&& mu <=1 && mu >0)
          {   
              Normal_distribution=true;           
        }
        else{
               print_usage();
            exit(EXIT_FAILURE);
    }
    }


      //parse the parameter into the 
        Dij G[4];
        Init_Graph(&G[0]);
         //run the simulation
        for (int i=0;i<4;i++){
        Node_queue node_queue;
        simulation(node_queue,G[i],Normal_distribution,lambda,i);
        node_queue.success_pass_counter=0;
        node_queue.success_deliver_counter=0;
        node_queue.aborted_counter=0;
       }

       return 0;
    }
