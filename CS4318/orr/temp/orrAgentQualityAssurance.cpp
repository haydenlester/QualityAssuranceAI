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
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>
using namespace std;

namespace
{
   // If you need to define any new types or functions, put them here in
   // this unnamed namespace.  But no variables allowed!
   
}

vector<drivingDirection> orrAgentQualityAssurance(TerrainMap &map)
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
   
   vector<vector<drivingDirection>> routes; //2d vector of all routes, and all directions in those routes
   vector<int> visited; //sorted vector of all visited hexes
   vector<int> routesCost; //parallel to routes vector, holds total route cost
   vector<int> curHex; //parallel to routes vector, holds current hex
   
   routes.push_back(vector<drivingDirection>());
   routesCost.push_back(0);
   curHex.push_back(map.getStartHex());
   
   bool optimalPathFound = false;
   
   int bestRouteI;
   int nextHex;
   drivingDirection moveToTry;
   vector<drivingDirection> tempRoute;
   
   while(!optimalPathFound){
      
      //pick the smallest route
      bestRouteI = 0;
      for(uint i = 0; i < routes.size(); i++){
         
         if(routesCost[bestRouteI] > routesCost[i]){
            
            bestRouteI = i;
            
         }
         
      }
      
      //bestRouteI now holds the smallest route.
      
      //test for end condition
      if(curHex[bestRouteI] == map.getFinishHex()){
         
         optimalPathFound = true;
         cout << "\nBefore return size is: " << routes.size() << '\n';
         cout << "\nSize of returned route: " << routes[bestRouteI].size() << '\n';
         cout << "\nReturned route: " << bestRouteI << '\n';
         return routes[bestRouteI];
         
      }
      
      //explore all routes
      for(moveToTry = driveW; moveToTry <= driveE; moveToTry = static_cast<drivingDirection>(moveToTry + 1)){
         
         nextHex = map.getNeighborHex(curHex[bestRouteI], moveToTry);
         
         //ensure move is valid
         if(nextHex != curHex[bestRouteI]){
            
            //ensure hex was not previously explored
            if(!binary_search(visited.cbegin(), visited.cend(), nextHex)){
               
               //clear temproute
               tempRoute.clear();
               //push route
               tempRoute.assign(routes[bestRouteI].begin(), routes[bestRouteI].end());
               tempRoute.push_back(moveToTry);
               routes.push_back(tempRoute);
               //push routecost
               routesCost.push_back(routesCost[bestRouteI] + map.getMoveTime(curHex[bestRouteI], moveToTry));
               //push curhex
               curHex.push_back(nextHex);
               
            }
            
         }
         
      }
      
      //add curHex[bestRouteI] to visited.
      visited.insert(upper_bound(visited.begin(), visited.end(), curHex[bestRouteI]), curHex[bestRouteI]);
      //remove route
      routes.erase(routes.begin()+bestRouteI);
      //remove route cost
      routesCost.erase(routesCost.begin()+bestRouteI);
      //remove curHex
      curHex.erase(curHex.begin()+bestRouteI);
      
   }
   
   return vector<drivingDirection>();
   
   //Uniform Cost Search!
   
   // 1) Explore all paths from root
   //    Visited = { }
   //    Routes = { S }
   //    RoutesCost = { 0 }
   // 2) Add root to visited list
   //    Visited = { S }
   //    Routes = {SA, SB, SC}
   //    RoutesCost = {2, 5, 8}
   // 3) Pick the smallest route cost-wise (does this satisfy G?)
   //    Visited = { S }
   //    Routes = {>SA<, SB, SC}
   //    RoutesCost = {2, 5, 8}
   // 4) Explore all paths from root
   
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
 
 

*/
