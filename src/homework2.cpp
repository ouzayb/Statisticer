//--------------------------//
//---Name & Surname: Oğuzhan Aybar
//---Student Number: 150200077
//--------------------------//

#include <iostream> 
#include <stdio.h>
#include <string.h>
#include <chrono>

#include <fstream>

#include "binaryTree.h"

using namespace std;

void GetInfo(string);
void save(BinaryTree*);

#define PARAMETER_COUNT 7
#define INPUT_COUNT 4
#define OUT_FILE_NAME "output.txt"

string ParameterValues[PARAMETER_COUNT] = {"mean", "std", "min", "firstq", "median", "thirdq", "max"};
string InputValues[INPUT_COUNT] = {"gap", "grp", "v", "gi"};

// {mean, std, min, Q1, Q2, Q3, max}
bool parameters[7] = {false,false,false,false,false,false,false};

ofstream fileOutput (OUT_FILE_NAME);

int main(int argc, char* argv[])
{
    auto start = chrono::high_resolution_clock::now();
    GetInfo(argv[1]);
    auto end = chrono::high_resolution_clock::now();
    auto durationGet = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "time spent is :" << durationGet.count() << endl;
    return 0;
}

//gets the information from an input file given and processes
void GetInfo(string fileName)
{
    string current_info;
    string comparisonCase;
    string infoDivided[INPUT_COUNT + 2];
    int comparisonIndex;
    int outputCount;
    int inputLenght;


    ifstream file ( fileName.c_str() );



    if( file.is_open() )
    {
        
        //first line: count of output parameters
        getline(file, current_info);
        outputCount = stoi(current_info);

        //parameter set
        for(int j = 0;j < outputCount;j++)
        {
            getline(file, current_info);
            for(int k = 0; k < PARAMETER_COUNT; k++)
                if(ParameterValues[k] == current_info){
                    parameters[k] = true;
                    break;
                }
        }

        //gap line
        getline(file, current_info);

        //comparison values
        getline(file, current_info);
        int commaPlace = current_info.find(",");
        inputLenght = stoi(current_info.substr(0,commaPlace));
        comparisonCase = current_info.substr(commaPlace + 1);
        for (int i = 0; i < INPUT_COUNT; i++)
        {
            if(InputValues[i] == comparisonCase){
             comparisonIndex = i;
             break;
             }
                
        }
        

        /* first input line (this is a little weird considering this is done 
        automatically in the next for loop but for optimized initialization, 
        /binary tree must be constructed with a first value) */
        getline(file, current_info);
        getline(file, current_info);
        for(int j = 0;j < INPUT_COUNT+2;j++)
        {
            int commaPlace = current_info.find(",");
            if(j == 0 || j == 1 || j == comparisonIndex+2) //? check if better without "if"
                infoDivided[j] = current_info.substr(0,commaPlace);
            current_info = current_info.substr(commaPlace + 1);
        }
        BinaryTree* tree = new BinaryTree(stof(infoDivided[comparisonIndex + 2]), infoDivided[0] + "," + infoDivided[1] );



        for(int i=0; getline(file, current_info); i++ ) 
        {
            if(current_info == "add"){
                getline(file, current_info);
                for(int j = 0;j < INPUT_COUNT+2;j++)
                {
                    int commaPlace = current_info.find(",");
                    if(j == 0 || j == 1 || j == comparisonIndex+2){
                        infoDivided[j] = current_info.substr(0,commaPlace);
                    }
                    current_info = current_info.substr(commaPlace + 1);
                }
                tree->Add(stod(infoDivided[comparisonIndex + 2]), infoDivided[0] + "," + infoDivided[1] , parameters[3] || parameters[4] || parameters[5]);
                continue;
            }
            //else (current_info = "print")
            save(tree);

        }
        // cout << "add : " << tree->addTime << endl;
        // cout << "InorderRecursiveDifferenceSum : " << tree->InorderRecursiveDifferenceSumTime << endl;
        // cout << "GetForwardNode : " << tree->GetForwardNodeTime << endl;
        // cout << "GetBackwardsNode : " << tree->GetBackwardsNodeTime << endl;
        // cout << "GoForward : " << tree->GoForwardNodeTime << endl;
        // cout << "GoBackward : " << tree->GoBackwardsNodeTime << endl;
        // cout << "UpdateQ : " << tree->UpdateQTime << endl;
        // cout << "===================================" << endl;
        file.close();
    }
}

void save(BinaryTree* _tree)
{

    if( fileOutput.is_open() )
    {
        fileOutput << _tree->Print(parameters, PARAMETER_COUNT);
    }

    
}