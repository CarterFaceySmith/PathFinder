
#ifndef COSC_ASS_ONE_NODE
#define COSC_ASS_ONE_NODE

#include "Types.h"

class Node {
public:

   // get row-co-ordinate
   int getRow();

   // get Column-co-ordinate
   int getCol();

   // getters and setters for distance to source
   int getDistanceToS();
   void setDistanceToS(int distanceToS);

   //Set col and row vals of a node
   void setRow(int rowVal);
   void setCol(int colVal);
   
   // Constructor/Destructor
   Node(int row, int col, int distanceToS);
   ~Node();
    
    
private:
    int row;
    int col;
    int distanceToS;
    

};

// Pointer to a Position-Distance
typedef Node* NodePtr;

#endif // COSC_ASS_ONE_NODE
