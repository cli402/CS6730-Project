The program is compiled using C++11 version stad. And compiled using VS2010 in windows platform and Linux based Ubuntu platform using Scons.Tested under windows and Linux system.

-----------------------
Compilation Instruction
-----------------------

To compile:
1) in Mac and Linux: install Scons , it is a software construction    tool written in python. Then simply run scons in command line within the folder where the sconscript and sconstruct script is located

2) in Windows's visual studio, compile all the file in the folder as the source file.


---------------------
Running Instruction
---------------------
to run the program, following the instruction below in the command line:
    
USAGE:      ./TOPOLO -s n [ or arguement -d <mu> <sigma>]
           the -s and -d command is used to define the info size of each node generates 
            (-s <n>  n size range from 0.05 to 1 )
            Or else if input distribution mode   <-d> is on" << std::endl;
            Generate the info with the size following the normal distribution 
          set the mu and sigma to define the shape of the distribution

To run the comprehensive simulation to test the size of the info on the network, as well as for the data distribution pattern's
effect on the whole network, 
run 
      ./test.sh 

in the commandline and all the result is out in the desinated folder.

------------------
For the data
------------------
The result data is stored in the CONT,DEL,SIZE folder under different topology's name:

1) CONT 
The data is composed of number of information that each simulation step has successfully Passed to the next destination, number of information that has successfully delivered to its final destination, and the number of information that has been aborted due to the capacity of the node.

2) DEL
The data is composed of the time that each information taken to get to its final destination.

3) Size
The data is composed of the capacity information of the nodes at each simulation step .




