#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include <queue>
#include <vector>
#include <iostream>


struct Node_Info_Passing{
  int Origin;
  int Destination;
  int position;
  std::queue<int> Path;
  float info_size;
  int Simul_step;
  int Initial_Sim_Step;
};


class Node_queue {
public:
  enum queue_static {Normal,Conjested,Empty};

  Node_queue();

  static int success_pass_counter;
  static int success_deliver_counter;
  static int aborted_counter;

public:
  void addToQueue(const Node_Info_Passing&);

  unsigned queueSize(const Node_Info_Passing&) const;

  const Node_Info_Passing& viewFrontNodeInfo(const Node_Info_Passing&) const;

  Node_Info_Passing getFrontNode(const Node_Info_Passing&);

  void increaseGroupSize(const Node_Info_Passing&);

  void decreaseGroupSize(const Node_Info_Passing&);

  unsigned groupSize(const Node_Info_Passing&) const;


public:
  static void Set_Conjested(const Node_Info_Passing&);

  static void Clear_Conjested_state(const Node_Info_Passing&);

  static bool isConjested(const Node_Info_Passing&);

//private:
  std::vector<std::queue<Node_Info_Passing> > Info_Queue;
  std::vector<float> Queue_Size;

//private:
  static std::vector<unsigned> Queue_Conjested;
}; // class QueueState

#endif // QUEUE_HPP_

