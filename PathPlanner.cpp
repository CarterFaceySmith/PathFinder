
#include "PathPlanner.h"

#include <iostream>


PathPlanner::PathPlanner(Env env, int rows, int cols){
   //Iterate through new env and set rows and cols values
   for(int i = 0; i < ENV_DIM; i++){
      for(int j = 0; j < ENV_DIM; j++){
         this->env[i][j] = env[i][j];
      }
   }
   //Initialise lists
   this->openList = new NodeList();
   this->closedList = new NodeList();
   this->visitedList = new NodeList();
   this->finalList = new NodeList();
}

PathPlanner::~PathPlanner(){
   
}

void PathPlanner::initialPosition(int row, int col){
   this->row = row;
   this->col = col;
}

NodeList* PathPlanner::getReachableNodes(){
   //Begin algorithm
      Node* startNode = new Node(this->col, this->row, 0);
      //Find and add start position node to open list
      for(int i = 0; i < ENV_DIM; i++){
         for(int j = 0; j < ENV_DIM; j++){
            if(env[i][j] == (SYMBOL_START)){
               startNode->setRow(i);
               startNode->setCol(j);
               startNode->setDistanceToS(0);
               this->openList->addBack(startNode);
            }
         }
      }

      //Define loop flag
      bool nextExists = true;
      
      //Begin while loop for directional checks
      while(nextExists){
         nextExists = false;
         //Set current position variables
         int rowPos = startNode->getRow();
         int colPos = startNode->getCol();
      
         //Iterate through reachable pos in above, right, down left order
         //If not wall, set that node dist to +1 and add to open list
         // Note: A potential future issue with the way this project has been undertaken is the assumption that the maze is bounded on all four sides, if this was not allowed to be assumed then necessary position checks would need to be further implemented to ensure the program doesn't try to check a non-maze position if it is currently at an edge.

         //UP
         if(this->env[rowPos-1][colPos] != (SYMBOL_WALL)){
            Node* thisNode = new Node(rowPos-1, colPos, startNode->getDistanceToS()+1);
            if (!this->openList->containsNode(thisNode)){
               this->openList->addBack(thisNode);
            }
         }

         //RIGHT
         if(this->env[rowPos][colPos+1] != (SYMBOL_WALL)){
            Node* thisNode = new Node(rowPos, colPos+1, startNode->getDistanceToS()+1);
            if (!this->openList->containsNode(thisNode)){
               this->openList->addBack(thisNode);
            }
         }

         //DOWN
         if(this->env[rowPos+1][colPos] != (SYMBOL_WALL)){
            Node* thisNode = new Node(rowPos+1, colPos, startNode->getDistanceToS()+1);
            if (!this->openList->containsNode(thisNode)){
               this->openList->addBack(thisNode);
            }
         }

         //LEFT
         if(this->env[rowPos][colPos-1] != (SYMBOL_WALL)){
            Node* thisNode = new Node(rowPos, colPos-1, startNode->getDistanceToS()+1);
            if (!this->openList->containsNode(thisNode)){
               this->openList->addBack(thisNode);
            }
         }

         this->closedList->addBack(startNode);

         for (int i=0; i<this->openList->getLength() && nextExists == false; ++i) {
            if (this->closedList->containsNode(this->openList->get(i)) == false) {
               startNode = this->openList->get(i);
               nextExists = true;
            }  
         }
      }

      for(int i = 0; i < this->closedList->getLength(); i++){
                  this->visitedList->addBack(this->closedList->get(i));
      }

   return this->visitedList;
}

NodeList* PathPlanner::getPath(){
   //Create goal node pointer
   Node* goalLoc = nullptr;
   
   //Begin finding goal node and point the goalPtr to it once found
   bool goalFound = false;
   while(goalFound == false){
      for(int i = 0; i < ENV_DIM; i++){
         for(int j = 0; j < ENV_DIM; j++){
            if(this->env[i][j] == SYMBOL_GOAL){               
               goalLoc = this->visitedList->locateNode(i,j);
               this->finalList->addBack(goalLoc);
               goalFound = true;
            }
         }
      }
   }

   //Set position variables for use
   int colPos = goalLoc->getCol();
   int rowPos = goalLoc->getRow();
   int distPos = goalLoc->getDistanceToS();

   //Beginning pathfinding algorithm
   while (distPos > 0){
      //Iterate through reachable positions in above, right, down left order
      //If not a wall, set that node dist to +1 and add to pathList

      //Define exit flag
      bool flag = false;

      //UP
      //Since we can assume that the env is always bounded on all four sides, there is no need to have a condition check for if we begin on the outer edge of the maze  
      if(env[rowPos-1][colPos] != (SYMBOL_WALL) && flag == false){
            //Use locateNode to get the distVal and check if it's less than the distVal of goalPtr
            Node* nextNodePtr = this->visitedList->locateNode(rowPos-1, colPos);
            int thisDist = nextNodePtr->getDistanceToS();

            //If it's less by one, we add that node to pathList and move the pointer to that node then repeat
            if(thisDist == (distPos - 1)){
               this->finalList->addBack(nextNodePtr);
               distPos = thisDist;
               rowPos = rowPos-1;
               flag = true;
            }
         }

      //RIGHT
      if(env[rowPos][colPos+1] != (SYMBOL_WALL) && flag == false){
            Node* nextNodePtr = this->visitedList->locateNode(rowPos, colPos+1);
            int thisDist = nextNodePtr->getDistanceToS();

            if(thisDist == (distPos - 1)){
               this->finalList->addBack(nextNodePtr);
               distPos = thisDist;
               colPos++;
               flag = true;
            }
         }
      
      //DOWN
      if(env[rowPos+1][colPos] != (SYMBOL_WALL) && flag == false){
            Node* nextNodePtr = this->visitedList->locateNode(rowPos+1, colPos);
            int thisDist = nextNodePtr->getDistanceToS();
            
            if(thisDist == (distPos - 1)){
               this->finalList->addBack(nextNodePtr);
               distPos = thisDist;
               rowPos++;
               flag = true;
            }
         }
         
         //LEFT
         if(env[rowPos][colPos-1] != (SYMBOL_WALL) && flag == false){
               Node* nextNodePtr = this->visitedList->locateNode(rowPos, colPos-1);
               int thisDist = nextNodePtr->getDistanceToS();

               if(thisDist == (distPos - 1)){
                  this->finalList->addBack(nextNodePtr);
                  distPos = thisDist;
                  colPos--;
                  flag = true;
               }
            }
   }
   
   // Deep copy the path, reverse it and return the new nodelist
   NodeList* returnedPath(finalList);
   returnedPath->reverseNodeList();
   return returnedPath;
}
