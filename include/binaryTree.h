//--------------------------//
//---Name & Surname: Oğuzhan Aybar
//---Student Number: 150200077
//--------------------------//

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class Node{
    private:
        double value;
        int nodeOverlapCount;

        int leftChildCount;
        int rightChildCount;

        Node* parent;

        Node* leftChild;
        Node* rightChild;
    public:
        //constructor
        Node(double _value);
        //getters
        double GetValue(){return value;}
        int GetOverlapCount(){return nodeOverlapCount;}
        int GetLeftChildCount(){return leftChildCount;}
        int GetRightChildCount(){return rightChildCount;}
        Node* GetParent(){return parent;}
        Node* GetLeftChild(){return leftChild;}
        Node* GetRightChild(){return rightChild;}
        //setter
        void IncrementOverlapCount(){nodeOverlapCount++;}
        void IncrementLeftChildCount(){leftChildCount++;}
        void IncrementRightChildCount(){rightChildCount++;}
        void SetParent(Node* _parent){parent = _parent;}
        void SetLeftChild(Node* _node){leftChild = _node;}
        void SetRightChild(Node* _node){rightChild = _node;}
        //methods
};


class BinaryTree{
    private:
        Node* root;
        double Q1; //TODO: calculate Q's by seeing the change of index number and placement of Q. if value < Q1 go back Q1 % 1 >= 0.75 go forward
        double Q2;
        double Q3;
        Node* Q1Low; //lower part of Q1 which is saved because of movement and overlap reading
        Node* Q2Low;
        Node* Q3Low;
        int Q1Overlap; //overlap is important because if you are overlapped and you try to go back, then you actually stay in the same node
        int Q2Overlap;
        int Q3Overlap; 
        double min;
        double max;
        int nodeCount;
        double sum;
        string minTime;
        string maxTime;

        //methods
        void InorderRecursiveDifferenceSum(Node* _node,double mean, double* valueDifferenceSum);

    public:
        // int addTime;
        // int InorderRecursiveDifferenceSumTime;
        // int GetForwardNodeTime;
        // int GetBackwardsNodeTime;
        // int GoForwardNodeTime;
        // int GoBackwardsNodeTime;
        // int UpdateQTime;
        
        //constructors
        BinaryTree();
        BinaryTree(double,string);
        //getters
        Node* GetForwardNode(Node *,int*);
        Node* GetBacwardNode(Node *,int*);
        //setter
        //methods
        void Add(double _value,string,bool);
        void ForwardMove(Node **,int*);
        void BacwardMove(Node **,int*);
        void Connect(Node* _parent, Node* _child, bool _left); //connects 2 nodes, direction required
        void Connect(Node* _parent, Node* _child);// connects two nodes automatically
        double getStD(); 
        void UpdateQ(double);
        string Print(bool[],int);
};

