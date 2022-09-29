#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList* solution);
void printList(Env environ, NodeList* theNodes);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // std::cout << "BEGINNING NODE CREATION TEST..." << std::endl << std::endl;
    // testNode();
    // std::cout << "NODE CREATION TEST SUCCESSFUL." << std::endl << std::endl;
    // std::cout << "BEGINNING NODELIST CREATION TEST..." << std::endl << std::endl;
    // testNodeList();
    // std::cout << "NODELIST CREATION SUCCESSFUL." << std::endl << std::endl;

    // Load Environment 
    Env env;
    readEnvStdin(env);
    
    // Solve using forwardSearch
    PathPlanner* pathplanner = new PathPlanner(env, ENV_DIM, ENV_DIM);
    NodeList* reachablePositions = nullptr;
    reachablePositions = pathplanner->getReachableNodes();

    // Get the path
    NodeList* solution = pathplanner->getPath();

    // Print the path
    printPath(env, solution);
    delete pathplanner;
    delete reachablePositions;
    delete solution;
}

void readEnvStdin(Env env){
    char val;
    // Read in environment from std input, store.
    for(int row = 0; row < 20; row++) {
        for(int col = 0; col < 20; col++){
            std::cin >> val;
            env[row][col] = val;
        }
    }
}

void printPath(Env env, NodeList* solution) {
    char up = '^';
    char right = '>';
    char down = 'v';
    char left = '<';

    for(int i = 1; i < solution->getLength()-1; i++){

            //Get first node in solution, retrieve its row and col position, then assign to vars
            int currRow = solution->get(i)->getRow();
            int currCol = solution->get(i)->getCol();

            //Get next node in solution, retrieve its row and col position, then assign to vars
            int nextRow = solution->get(i+1)->getRow();
            int nextCol = solution->get(i+1)->getCol();
            
            //UP
            // Note: A potential future issue with the way this project has been undertaken is the assumption that the maze is bounded on all four sides, if this was not allowed to be assumed then necessary position checks would need to be further implemented to ensure the program doesn't try to check a non-maze position if it is currently at an edge.
            if(nextRow < currRow || env[currRow-1][currCol] == SYMBOL_GOAL){
                env[currRow][currCol] = up;
            }

            //RIGHT
            else if(nextCol > currCol || env[currRow][currCol+1] == SYMBOL_GOAL){
                env[currRow][currCol] = right;
            }

            //DOWN
            else if(nextRow > currRow || env[currRow+1][currCol] == SYMBOL_GOAL){
                env[currRow][currCol] = down;
            }

            //LEFT
            else if(nextCol < currCol || env[currRow][currCol+1] == SYMBOL_GOAL){
                env[currRow][currCol] = left;
            }
        }        

    //Output to std output with path now implemented.
    for(int row = 0; row < 20; row++) {
        for(int col = 0; col < 20; col++){
            std::cout << env[row][col];
        }
        if(row < 19){
            std::cout << std::endl;
        }
    }
}

// void printReachablePositions(Env env, NodeList* reachablePositions){
// }

// void testNode() {
//     std::cout << "TESTING Node" << std::endl;

//     // Make a Node and print out the contents
//     Node* node = new Node(1, 1, 2);
//     std::cout << node->getRow() << ",";
//     std::cout << node->getCol() << ",";
//     std::cout << node->getDistanceToS() << std::endl;
//     delete node;

//     // Change Node and print again
//     node = new Node(4, 2, 3);
//     std::cout << node->getRow() << ",";
//     std::cout << node->getCol() << ",";
//     std::cout << node->getDistanceToS() << std::endl;
//     delete node;
// }

// void testNodeList() {
//     std::cout << "TESTING NodeList" << std::endl;

//     // Make a simple NodeList, should be empty size
//     NodeList* nodeList = new NodeList();
//     std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

//     // Add a Node to the NodeList, print size
//     Node* b1 = new Node(1, 1, 1);
//     nodeList->addBack(b1);
//     std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

//     // Add second Nodetest
//     Node* b2 = new Node(0, 0, 1);
//     nodeList->addBack(b2);
//     std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

//     // Test Get-ith - should be 0,0,1
//     Node* getB = nodeList->get(1);
//     std::cout << getB->getRow() << ",";
//     std::cout << getB->getCol() << ",";
//     std::cout << getB->getDistanceToS() << std::endl;
// }

    
