// YOUR NAME: Hayden Lester
//
// CS 4318, spring 2021
// Agent Challenge 3: Off-road rally
//
// Rename this file and the function below.  For example, if your agent name
// is Jones, rename this orrAgentSmith.cpp file to orrAgentJones.cpp and the
// orrAgentSmith function below to orrAgentJones.  Complete your agent
// function and turn it in on Blackboard.  Random-number generation is not
// allowed; your agent must be entirely deterministic.  Feel free to create
// other agents--each in a separate .cpp file--for yours to race against,
// but turn in only one.  Test your agent(s) with
//
//    nice bash orrBuild.bash
//
// and then
//
//    nice ./orrRunSim
//
// Each submitted agent will race on each of at least 100 terrains, with
// sizes ranging from 3x3 to 30x30, to determine the standings, which will
// be posted soon after the agents are due.

#include "orr.h"
#include <algorithm>
using namespace std;

namespace
{
   // If you need to define any new types or functions, put them here in
   // this unnamed namespace.  But no variables allowed!
   
   struct node{
      int location;
      vector<drivingDirection> path;
      uint pathCost;
      
   };
   
   class greaterNode{
      public:
      bool operator() (node lhs, node rhs){
         if(lhs.pathCost > rhs.pathCost){
            return true;
         }
         return false;
      }
   };
   
}

vector<drivingDirection> orrAgentQualityAssuranceTwo(TerrainMap &map)
{
   // Your function must end up returning a vector of moves.
   // No random-number generation allowed!
   // map.getSize() gives the size of the terrain: 6 for a 6x6 map, etc.
   // map.getStartHex() gives the number of the start hex.
   // -- Note : Wasn't sure how this was structured. Returns a single int
   //         : Wrote a test function, deduced that it is (n/mapsize, n%mapsize) = (x, y) visually
   // map.getFinishHex() gives the number of the finish hex.
   // map.getMoveTime(fromHex, move) gives the driving time of one move.
   // map.getNeighborHex(fromHex, move) gives the hex got to by one move.
   // -->returns fromHex if invalid
   //drivingDirection bestMove, moveToTry;
   
   priority_queue<node, vector<node>, greaterNode> frontier; //priority queue to look at unexpanded nodes
   frontier.push(node{map.getStartHex(), vector<drivingDirection>(), 0}); // pushing first node to the pq
   vector<int> explored; // sorted vector to hold explored nodes (sorted for binary search functionality)
   
   //miscellaneous variables
   node curNode;
   node next;
   drivingDirection moveToTry;
   
   while(!frontier.empty()){
      
      //pop off the first node
      curNode = frontier.top();
      frontier.pop();
      
      //is the shortest pathCost node the finish?
      if(curNode.location == map.getFinishHex()){
         
         return curNode.path;
         
      }
      
      //otherwise, insert it into explored nodes
      explored.insert(upper_bound(explored.begin(), explored.end(), curNode.location), curNode.location);
      
      //expand the node
      for(moveToTry = driveW; moveToTry <= driveE; moveToTry = static_cast<drivingDirection>(moveToTry + 1)){
         
         next.location = map.getNeighborHex(curNode.location, moveToTry);
         
         if(!binary_search(explored.begin(), explored.end(), next.location)){
            
            next.pathCost = curNode.pathCost + map.getMoveTime(curNode.location, moveToTry);
            next.path.assign(curNode.path.begin(), curNode.path.end());
            next.path.push_back(moveToTry);
            frontier.push(next);
            
         }
         
      }
      
   }
   
   return curNode.path; // this statement would never trigger, it's just here as an absolute failsafe
   
}

/*

 - First, carefully comment your code above to clarify how it works.
 - NOTES:
 
 - For iteration 2, I am currently starting at 6:00PM on the night it is due.
 - I am rewriting everything from scratch.
 - The search I am trying to implement is the uniform cost search
 .
 - My first attempt to do this was poor. It is uncompleted, but I will leave the code in a previous attempt on BB
 - Just so that it is clear I made an effort, if nothing else/
 - This is because I failed to take into account certain aspects of UCS, such as keeping track of visited hexes
 - And removing routes which had all hexes tried
 - All in all, it would've taken me a lot of crappy hardcoding to remove these flaws
 - And I got really frustrated at the idea of that. So I started over.
 
 - My second attempt went far better.
 - This attempt, I read the textbook again (more thoroughly) and determined I need to use a priority queue.
 - This is because, in part, priority queues are stored as heaps, which makes lookups much quicker.
 - Something that my unofficial second attempt lacked was speed. It was horribly slow. So slow, I was sure it would not be graded.
 - In addition, I decided to store explored nodes in a sorted vector so I could benefit from the o(ln(n)) search time
 - In the end, I found that step unnecessary due to how my code was written.
 
 - Solving for all node values is definitely possible if it weren't for those two nodes with odd degrees in the northwest and southeast corners of the map
 - I have a feeling that was intentional, though! 
 

*/
