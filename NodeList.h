#ifndef COSC_ASS_ONE_NODE_LIST
#define COSC_ASS_ONE_NODE_LIST

#include "Node.h"
#include "Types.h"

class NodeList {
public:
   
   // Create a New Empty List
   NodeList();

   // Clean-up the list
   ~NodeList();

   // Copy Constructor
   // Produces a DEEP COPY of the NodeList
   NodeList(NodeList& other);

   // Number of items in the list
   int getLength();

   //Reverse the NodeList
   void reverseNodeList();

   NodePtr locateNode(int row, int col);

   void printList(NodeList* theNodes);

   // Get a pointer to the ith node in the node list
   NodePtr get(int i);

   void addBack(NodePtr newNode);

   // Checks if the list contains a node with the same co-ordinate
   //    as the given node.
   bool containsNode(NodePtr node);

   // void deleteNode(int position);

   void clear();


private:

   // NodeList: list of node objects
   NodePtr    nodes[NODE_LIST_ARRAY_MAX_SIZE];
   // Number of nodes currently in the NodeList
   int      length;
   


};

#endif // COSC_ASS_ONE_NODE_LIST
