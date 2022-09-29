
#include "NodeList.h"
#include <iostream>

// Remember nodelist is a node pointer array, the nodes themselves are stored in free memory disjointed, this is an array of pointers to those nodes.

NodeList::NodeList(){
   this->length = 0;
}


NodeList::~NodeList(){
   
}

NodeList::NodeList(NodeList& other){

      //Simply iterate to the length of the nodelist and add each position i to the new nodelist as a deep copy using the addBack method.
      for(int i = 0; i < this->length; i++){
         other.addBack(this->nodes[i]);
      }
   }

void NodeList::reverseNodeList(){
   int size = this->length;
   int firstElem = 0;
   int lastElem = size - 1;

   //Iterate through the nodeList from both ends, swapping their positions as we go until there are none left to swap.
   while(firstElem < lastElem){
      NodePtr temp;
      temp = this->nodes[firstElem];
      this->nodes[firstElem] = this->nodes[lastElem];
      this->nodes[lastElem] = temp;

      firstElem++;
      lastElem--;
   }

}

NodePtr NodeList::locateNode(int row, int col){
   Node* locatedNodePtr = nullptr;

   //Compare the column and row of the input node to each node at position i until it is located, or return a nullptr if it isn't.
   for(int i = 0; i < this->getLength(); i++){
      if (this->get(i)->getCol() == col && this->get(i)->getRow() == row){
         locatedNodePtr = this->get(i);
      }
   }
   return locatedNodePtr;
}

int NodeList::getLength(){
   return this->length;
}


NodePtr NodeList::get(int i){
   return this->nodes[i];
}

void NodeList::addBack(NodePtr theNodeToCopy){
   this->length += 1;

   //Initialise an entirely new node with the nodeToCopy's variables.
   Node* node = new Node (theNodeToCopy->getRow(), theNodeToCopy->getCol(), theNodeToCopy->getDistanceToS());
   nodes[this->length-1] = node;
}

bool NodeList::containsNode(NodePtr node){
   bool nodeFlag = false;
   
   for (int i = 0; i < this->length; i++){
      if (nodes[i]->getCol() == node->getCol() && nodes[i]->getRow() == node->getRow()){
         nodeFlag = true;
      }
   }
   return nodeFlag;
}

void NodeList::clear(){
   for (int i = 0; i < this->length; i++){
      if (nodes[i] != nullptr){
         delete &nodes[i];
         nodes[i] = nullptr;
      }
   }
}

// void NodeList::deleteNode(int position){
//    std::cout << "delete f1" << std::endl;
//    if (this->nodes[position] != nullptr && position < this->getLength())
//    {
//       std::cout << "delete f1-2" << std::endl;
//       std::cout << this->nodes[position] << std::endl;
//       delete this->nodes[position];
//       std::cout << "delete f2" << std::endl;
//       this->nodes[position] = nullptr;
//       std::cout << "delete f3" << std::endl;
//       std::cout << "delete f4" << std::endl;
//       for (int i = position; i < this->getLength()-1; i++){
//          std::cout << "delete f5" << std::endl;
//          this->nodes[position] = this->nodes[position+1];
//          std::cout << "delete f6" << std::endl;
//       }  
//       this->nodes[this->getLength()-1] = nullptr;
//       std::cout << "delete f7" << std::endl;
//       this->length -= 1;
//    }  
// }

void printList(NodeList* nodes){
   for(int i = 0; i < nodes->getLength(); ++i) {
      std::cout << "[";
      std::cout << nodes->get(i)->getCol() << ", ";
      std::cout << nodes->get(i)->getRow() << ", ";
      std::cout << nodes->get(i)->getDistanceToS() << "]" << std::endl;
      std::cout << std::endl;
   }


}