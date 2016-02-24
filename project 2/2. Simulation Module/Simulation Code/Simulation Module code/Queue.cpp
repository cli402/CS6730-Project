#include <string>
#include "Queue.hpp"

int Node_queue::success_pass_counter=0;
int Node_queue::success_deliver_counter=0;
int Node_queue::aborted_counter=0;

std::vector<unsigned> Node_queue::Queue_Conjested(static_cast<size_t>(50));

Node_queue::Node_queue():Info_Queue(static_cast<size_t>(50)),
                        Queue_Size(static_cast<size_t>(50)){};


 void Node_queue::addToQueue(const Node_Info_Passing& node){

 Info_Queue[node.position].push(node);

 };

  unsigned Node_queue::queueSize(const Node_Info_Passing& node ) const{
  	return Info_Queue[node.position].size();
  };


  const Node_Info_Passing& Node_queue::viewFrontNodeInfo(const Node_Info_Passing& node) const
  {
     return Info_Queue[node.position].front();
  };

  Node_Info_Passing Node_queue::getFrontNode(const Node_Info_Passing& node)
  {
       Node_Info_Passing front_node(Info_Queue[node.position].front());
       Info_Queue[node.position].pop();
       return front_node;
  };


 void Node_queue::increaseGroupSize(const Node_Info_Passing& node){
     Queue_Size[node.position]+=1;
 };

 void Node_queue::decreaseGroupSize(const Node_Info_Passing& node)
 {
    Queue_Size[node.position]-=1;
  };

unsigned Node_queue::groupSize(const Node_Info_Passing& node) const
{
 return Queue_Size[node.position];
};

void Node_queue::Set_Conjested(const Node_Info_Passing& node)
{
   Queue_Conjested[node.position]=false;
};

void Node_queue::Clear_Conjested_state(const Node_Info_Passing&node)
{
  Queue_Conjested[node.position]=true;
};

bool Node_queue::isConjested(const Node_Info_Passing& node)
{
	return Queue_Conjested[node.position];
};

