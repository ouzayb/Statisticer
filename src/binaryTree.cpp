//--------------------------//
//---Name & Surname: Oğuzhan Aybar
//---Student Number: 150200077
//--------------------------//

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cmath>

#include "binaryTree.h"

using namespace std;

Node::Node(double _value){
value = _value;
nodeOverlapCount = 1;
leftChildCount = 0;
rightChildCount = 0;
parent = NULL;
leftChild = NULL;
rightChild = NULL;
}

BinaryTree::BinaryTree(){
   root = NULL;
   Q1Low = NULL;
   Q2Low = NULL;
   Q3Low = NULL;
   min =  100000000;
   max = -100000000;
   nodeCount = 0;
   sum = 0;
   minTime = "NULL";
   maxTime = "NULL";
}

BinaryTree::BinaryTree(double _value,string _time){
   root = new Node(_value);
   Q1 = Q2 = Q3 = _value;
   Q1Low = Q2Low = Q3Low = root;
   Q1Overlap = Q2Overlap = Q3Overlap = 1;
   nodeCount = 1;
   //Q1Index = Q2Index = Q3Index = 0;

   min = _value;
   max = _value;


   sum = _value;
   minTime = _time;
   maxTime = _time;
}

void BinaryTree::Add(double _value,string _time,bool CheckQ){
   //minTime = (_time < minTime)? _time : minTime;  
   maxTime = _time;//used ternary as much as possible as they are more efficient

   //addTime++;

   nodeCount++; 

   sum += _value;

   min =(_value < min)? _value : min;
   max =(_value > max)? _value : max;
 

   Node* tempParent;
   Node* temp = root;
   while(temp != NULL)
   {
      tempParent = temp;

      if(_value < temp->GetValue())
      {
         temp->IncrementLeftChildCount();
         temp = temp->GetLeftChild();
         continue;
      }

      else if(_value > temp->GetValue())
      {
         temp->IncrementRightChildCount();
         temp = temp->GetRightChild();
         continue;
      }
      
      //if value equal
      temp->IncrementOverlapCount();
      if(CheckQ)
         UpdateQ(_value);
      return;
   }

   Node* newNode = new Node(_value);

   Connect(tempParent, newNode);
   if(CheckQ)
      UpdateQ(_value);
}

//Updates the Q Nodes accordingly
void BinaryTree::UpdateQ(double _value){ 
   double Q1Perc = (((nodeCount-1)*25) % 100)/(float)100;
   double Q2Perc = (((nodeCount-1)*50) % 100)/(float)100;
   double Q3Perc = (((nodeCount-1)*75) % 100)/(float)100;
   //by calculating the after the dot part of Q indexes, we can understand which one went up an index
   
   //UpdateQTime++;

   if(_value < Q1Low->GetValue()){ //if value is smaller than the Q
      if(Q1Perc != 0) // and Q index hasn't risen
         BacwardMove(&Q1Low,&Q1Overlap); //move backwards
   }

   else if(Q1Perc == 0){ //if Q index has risen move forward
     ForwardMove(&Q1Low,&Q1Overlap);
   }


   if(_value < Q2Low->GetValue()){
      if(Q2Perc != 0)
         BacwardMove(&Q2Low,&Q2Overlap);
   }

   else if(Q2Perc == 0){
     ForwardMove(&Q2Low,&Q2Overlap);
   }


   if(_value < Q3Low->GetValue()){
      if(Q3Perc >= 0.75)
         BacwardMove(&Q3Low,&Q3Overlap);
   }

   else if(Q3Perc < 0.75){
     ForwardMove(&Q3Low,&Q3Overlap);
   }


//linear estimation of the values with Q nodes and nodes after that
   Q1 = Q1Low->GetValue()*(1-Q1Perc) + (GetForwardNode(Q1Low,&Q1Overlap)->GetValue())*(Q1Perc);
   Q2 = Q2Low->GetValue()*(1-Q2Perc) + (GetForwardNode(Q2Low,&Q2Overlap)->GetValue())*(Q2Perc);
   Q3 = Q3Low->GetValue()*(1-Q3Perc) + (GetForwardNode(Q3Low,&Q3Overlap)->GetValue())*(Q3Perc);
}

//moves nodes forward
void BinaryTree::ForwardMove(Node** _Q, int* overlap ){
   Node* temp = (*_Q);
   //GoForwardNodeTime++;
   *_Q = GetForwardNode(temp,overlap); 
   if(temp == *_Q){
      (*overlap)++;
      return;  
   }
   (*overlap) = 1;
}

//moves nodes backwards
void BinaryTree::BacwardMove(Node** _Q, int* overlap ){
   Node* temp = (*_Q);

   //GoBackwardsNodeTime++;
   *_Q = GetBacwardNode(temp,overlap); 
   if(temp == *_Q){
      (*overlap)--;
      return;  
   }
   (*overlap) = (*_Q)->GetOverlapCount();

}

//gets the node one after the given in in order traversal
Node* BinaryTree::GetForwardNode(Node* _node, int* overlap ){
   Node* temp = _node;
   //GetForwardNodeTime++;
   if(temp->GetOverlapCount() > *overlap){
      return _node;
   }

   if(temp->GetRightChild() != NULL)
   {
      return (temp->GetRightChild());
   }

   if(temp->GetParent() == NULL)
      return _node;

   while(temp->GetParent()->GetRightChild() == temp)
   {
      temp = temp->GetParent();
      if(temp->GetParent() == NULL){
         return _node;
      }
   }

   return temp->GetParent();
}

//gets the node one before the given in in order traversal
Node* BinaryTree::GetBacwardNode(Node* _node, int* overlap){
   Node* temp = _node;
   //GetBackwardsNodeTime++;
   if(*overlap > 1){
      return _node;
   }


   if(temp->GetLeftChild() != NULL)
   {
      return (temp->GetLeftChild());
   }

    if(temp->GetParent() == NULL)
      return _node;

   while(temp->GetParent()->GetLeftChild() == temp)
   {
      temp = temp->GetParent();
      if(temp->GetParent() == NULL){
         return _node;
      }
   }
   return (temp->GetParent());
}

void BinaryTree::Connect(Node* _parent, Node* _child, bool _left){
   _child->SetParent(_parent);
   if(left){
      _parent->SetLeftChild(_child);
      return;
   }
      _parent->SetRightChild(_child);
}

void BinaryTree::Connect(Node* _parent, Node* _child){
   _child->SetParent(_parent);
   if(_child->GetValue() < _parent->GetValue()){
      _parent->SetLeftChild(_child);
      return;
   }
      _parent->SetRightChild(_child);
}

double BinaryTree::getStD(){
   double mean = sum/(float)nodeCount;

   double valueDifferenceSum = 0;

   InorderRecursiveDifferenceSum(root,mean,&valueDifferenceSum);

   return sqrt(valueDifferenceSum / (float)(nodeCount - 1));
}

void BinaryTree::InorderRecursiveDifferenceSum(Node* _node,double mean, double* valueDifferenceSum){
   //InorderRecursiveDifferenceSumTime++;
   if(_node->GetLeftChildCount() > 0)
      InorderRecursiveDifferenceSum(_node->GetLeftChild(),mean,valueDifferenceSum);
   *valueDifferenceSum += ((_node->GetValue() - mean ) * (_node->GetValue() - mean ) * _node->GetOverlapCount());
   if(_node->GetRightChildCount() > 0)
      InorderRecursiveDifferenceSum(_node->GetRightChild(),mean,valueDifferenceSum);
}

string BinaryTree::Print(bool parameters[],int arrayLenght){

   string out = ""; 
   
   out += minTime + "," + maxTime;

   out += (parameters[0] ?  ("," +  to_string(sum/(float)nodeCount)) : "");
   out += (parameters[1] ?  ("," +  to_string(getStD())) : "");
   out += (parameters[2] ?  ("," +  to_string(min)) : "");
   out += (parameters[3] ?  ("," +  to_string(Q1)) : "");
   out += (parameters[4] ?  ("," +  to_string(Q2)) : "");
   out += (parameters[5] ?  ("," +  to_string(Q3)) : "");
   out += (parameters[6] ?  ("," +  to_string(max)) : "");

   out += "\n";

   return out;
}