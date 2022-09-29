
#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathPlanner {
public:


   // Initialise with a given Env of size (rows,cols)
   PathPlanner(Env env, int rows, int cols);

   // Clean-up
   ~PathPlanner();

   // Set The initial position
   void initialPosition(int row, int col);

   NodeList* getReachableNodes();

   NodeList* getPath();

   //bool PathPlanner::checkAdjacent(Env env, NodePtr P, int direction, char target);

private:
   Env env;
   int row;
   int col;
   NodeList* openList;
   NodeList* closedList;
   NodeList* visitedList;
   NodeList* finalList;

};



#endif // COSC_ASS_ONE_PATH_PLANNING
