// YOUR NAME: Hayden Lester
//
// CS 4318, spring 2021
// Agent Challenge 6: Hunt the wumpus
//
// Rename this file and the function below.  For example, if your agent name
// is Jones, rename this htwAgentSmith.cpp file to htwAgentJones.cpp and the
// htwAgentSmith function below to htwAgentJones.  Complete your agent
// function and turn it in on Blackboard.  Random-number generation is not
// allowed; your agent must be entirely deterministic.  Feel free to create
// other agents--each in a separate .cpp file--for comparison purposes, but
// turn in only one.  Test your agent(s) with
//
//    nice bash htwBuild.bash
//
// and then
//
//    nice ./htwRunSim
//
// Each submitted agent will explore each of many random 4x4 wumpus worlds
// to determine the standings, which will be posted soon after the agents
// are due.

#include "htw.h"
#include <string>

namespace
{
   // If you need to define any new types or functions, put them here in
   // this unnamed namespace.  But no variables allowed!

   struct KnowledgeBase
   {
      //agent knowledge
      int whereX = 0;
      int whereY = 0;
      
      action previousMoves[160]; // Not dynamic memory allocation :D
      int moveIndex = 1;
      
      bool haveGold = false; // Whether we have gold
      bool wumpusDead = false; // Weather the wumpus is dead. Largely unused.
      bool wumpusLocated = false; // Whether we've pinned down the Wumpuses location
      
      string dangerMap[4][4] = {
         
         {"n", "n", "n", "n"},
         {"n", "n", "n", "n"},
         {"n", "n", "n", "n"},
         {"n", "n", "n", "n"},
         
      };
      // DANGER MAP
      // d = death! wumpus is here.
      // w = wumpus possible, v = not wumpus
      // p = pit poss, b = not pit
      // c = nothing, n = unknown
      
      //True if tile is potentially dangerous
      //False otherwise
      bool notDangerous(int x, int y){
         
         
         if(wumpusLocated){
            if(dangerMap[y][x].find_first_of("pd") == string::npos)
               return true;
            return false;
         }
         
         
         if(dangerMap[y][x].find_first_of("wp") == string::npos)
            return true;
         return false;
         
      }
      
      
      //chooses a move based on an x, y.
      //there's definitely an easier way to do this.
      // it also tracks what move index i'm on, and where i'm at.
      action chooseMove(int x, int y){
         
         if(x == 0){
            
            if(y == 1){ // move up
               previousMoves[moveIndex] = moveN;
               moveIndex++;
               whereY++;
               return moveN;
            }else{ // move down
               previousMoves[moveIndex] = moveS;
               moveIndex++;
               whereY--;
               return moveS;
            }
            
         }else{
            
            if(x == -1){ // move left
               previousMoves[moveIndex] = moveW;
               moveIndex++;
               whereX--;
               return moveW;
            }else{ // move right
               previousMoves[moveIndex] = moveE;
               moveIndex++;
               whereX++;
               return moveE;
            }
            
         }
         
      }
      
      //backtracks once.
      action backtrack(){
         
         action move = previousMoves[moveIndex-1];
         
         switch(move){
            
            case moveN: move = moveS;
                        whereY--;
            break;
            case moveS: move = moveN;
                        whereY++;
            break;
            case moveW: move = moveE;
                        whereX++;
            break;
            case moveE: move = moveW;
                        whereX--;
            break;
            default: move = doNothing;
            
         }
         
         moveIndex--;
         
         if(moveIndex == 0)
            return climbOut;
         
         return move;
         
      }
      
   };
   
   
   //Removes any instances of any character in rm from str
   //Useful for update function
   void rmChars(string& str, string rm){
      
      string::size_type v;
      
      for(uint i = 0; i < rm.size(); i++){
         
         v = str.find(rm[i]);
         
         while(v != string::npos){
            
            str.erase(v);
            
            v = str.find(rm[i]);
            
         }
         
      }
      
      return;
      
   }
   
   //Determines if a tile is valid in searching
   //Checks in range, and that it's orthagonal
   bool isValidTile(int x, int y, int i, int j){
      
      return (x+i >= 0 && y+j >= 0 &&
             ((i == 0) != (j == 0)) &&
             (x+i <= 3 && y+j <= 3));
      
   }
   
   //function updateMap is called every time we begin a move. it updates the map of danger.
   // Could have made this a member function of KnowledgeBase. Would've been cleaner. But hindsight is always 20/20.
   // It's already really late, so as long as it isn't painfully slow, I'll stick with it.
   void updateMap(KnowledgeBase& kb, string danger = ""){
      
      int x = kb.whereX;
      int y = kb.whereY;
      string::size_type npos = string::npos;
      string dangerTile;
      
      // If we're not on an already explored tile
      if(kb.dangerMap[y][x].find('c') == npos){
         
         //if we get a wumpus stench on this tile, and wumpus isn't located
         if(danger.find('w') != npos && kb.wumpusLocated == false){
            
            //iterate through all tiles adjacent
            for(int i = -1; i <= 1; i++){
               for(int j = -1; j <= 1; j++){
                  
                  //only orthogonal, valid tiles
                  if(isValidTile(x, y, i, j)){
                     
                     dangerTile = kb.dangerMap[y+j][x+i];
                     
                     //if there are exclusion states on the tile
                     if(dangerTile.find('c') == npos && dangerTile.find('v') == npos){
                        
                        //check to see if we found the wumpus
                        if(dangerTile.find('w') != npos){
                           dangerTile = 'd';
                           kb.wumpusLocated = true;
                        }else{
                           dangerTile += 'w';
                        }
                        
                     }
                     
                     kb.dangerMap[y+j][x+i] = dangerTile;
                     
                  }
               }
            }
         //otherwise, if we don't have a stench
         }else if(danger.find('w') == npos){
            
            //iterate through all tiles adjacent
            for(int i = -1, j = -1; i < 1 && j < 1; i++ && j++){
               
               //only orthogonal, valid tiles
               if(isValidTile(x, y, i, j)){
                  
                  dangerTile = kb.dangerMap[y+j][x+i];
                  
                  //if there are exclusion states already on the tile
                  if(dangerTile.find('v') == npos){
                     
                     rmChars(dangerTile, "w");
                     dangerTile += 'v';
                     
                  }
                  
                  kb.dangerMap[y+j][x+i] = dangerTile;
                  
               }
               
            }
            
         }
         
         if(danger.find('p') != npos){
            
            //iterate through all tiles adjacent
            for(int i = -1; i <= 1; i++){
               for(int j = -1; j <= 1; j++){
                  
                  //only orthogonal, valid tiles
                  if(isValidTile(x, y, i, j)){
                     
                     dangerTile = kb.dangerMap[y+j][x+i];
                     
                     //if there are exclusion states on the tile
                     if(dangerTile.find('c') == npos && dangerTile.find('b') == npos){
                        
                        // slap a pit warning on
                        if(dangerTile.find('p') == npos)
                           dangerTile += 'p';
                     }
                     
                     kb.dangerMap[y+j][x+i] = dangerTile;
                     
                  }
               }
            }
            
         //otherwise, if we don't have a breeze
         }else{
            
            //iterate through all tiles adjacent
            for(int i = -1; i <= 1; i++){
               for(int j = -1; j <= 1; j++){
                  
                  //only orthogonal, valid tiles
                  if(isValidTile(x, y, i, j)){
                     
                     dangerTile = kb.dangerMap[y+j][x+i];
                     
                     //make sure there's not already a b
                     if(dangerTile.find('b') == npos){
                        
                        rmChars(dangerTile, "p");
                        dangerTile += 'b';
                        
                     }
                     
                     kb.dangerMap[y+j][x+i] = dangerTile;
                     
                  }
                  
               }
            }
            
         }
         
      }
      
      //This area as clear. Mark it so.
      kb.dangerMap[y][x] = 'c';
      
   }
   
}

// Rename and complete this agent function.
action htwAgentQualityAssurance(WumpusWorldSensor currentSensor, bool shouldReset){
   static KnowledgeBase kb;

   if (shouldReset){
      // Create a fresh knowledge base for the new wumpus world.
      kb = KnowledgeBase();
      // Just return without taking an action.
      return doNothing;
      
   }
   
   //Collects percepts and modifies map
   string danger = "";
   
   if(currentSensor.perceiveStench()){
      danger += 'w';
   }
   if(currentSensor.perceiveBreeze()){
      danger += 'p';
   }
   
   //Our updateMap function just updates our model of our surrounding (and danger)
   // Most of the program's logic resides in that function.
   updateMap(kb, danger);
   
   // Always grab gold, if we can.
   if(currentSensor.perceiveGlitter() && !kb.haveGold){
      kb.haveGold = true;
      return grab;
   }
   
   if(kb.haveGold){
      //--------------------------------------
      //ACTIONS TO TAKE WHEN WE HAVE GOLD HERE
      //--------------------------------------
      
      if(kb.whereX == 0 && kb.whereY == 0){
         return climbOut;
      }
      
      //backtrack to exit and leave
      return kb.backtrack();
      
   }else{
      //--------------------------------------
      //ACTIONS TO TAKE WHEN WE DONT HAVE GOLD
      //--------------------------------------
      
      //Find the nearest unexplored tile, go there.
      for(int i = -1; i <= 1; i++){
         
         for(int j = -1; j <= 1; j++){
            
            //If it's valid (orthogonal and not out of bounds)
            if(isValidTile(kb.whereX, kb.whereY, i, j)){
               
               //If it's not dangerous
               if(kb.notDangerous(kb.whereX+i, kb.whereY+j)){
                  
                  //If it's not explored
                  if(kb.dangerMap[kb.whereY+j][kb.whereX+i].find('c') == string::npos){
                     return kb.chooseMove(i, j); // Choose that move.
                  }
                  
               }
               
            }
            
         }
         
      }
      
      //If no unexplored tiles exist from start, climb out
      if(kb.whereX == 0 && kb.whereY == 0){
         return climbOut;
      }
      
      //otherwise, we'll keep backtracking
      return kb.backtrack();
      //note: not entirely sure why my agent doesn't explore other paths, but perpetually backtracks.
      
   }
   
   
   
}

/*

 - First, carefully comment your code above to clarify how it works.
 - Here, describe your approach and analyze it.  How exactly did you develop
   and test it?  What are its strengths and weaknesses?  Why do you expect
   it to do well against the other submitted agents?
 - Also make a note here if you talked about the assignment with anyone or
   gave or received any kind of help.
   
 - Iteration Two Notes: I DID IT!
 
 - Based off my last iteration, I knew I had to streamline this if I wanted to get it done.
 - I made a few choices about designing the agent towards this goal.
 - 1) I would not try to use a* (for now). This would make my avg go up for sure, but I need sleep.
      -> Not even sure I could without dynamic memory allocation.
 - 2) I would write one function that will update everything in our model (and therefore contain most of the logic, instead of having function overload!)
 - 3) I would not attempt anything fancy, such as shooting the wumpus.
 
 - Based off this, I came up with a pretty simple algorithm.
 - First, update the map with percepts
 - Second, determine if you have gold.
 -         -> If not, just move to a nearby unexplored nondangerous tile.
              > If you have no options from (0, 0), climb out.
              > If there are no options from where you are other than (0, 0), backtrack.
 -         -> If so, climb out if at (0, 0)
              > If not, backtrack.
 - For a while, my function would backtrack completely and climb out at the slighted hint of danger.
 - But, I figured out my backtrack member function of kb didn't update the location! So I changed that, and got +200 more on avg.
 
 - This performs really, really well for not shooting the Wumpus or having better pathfinding at all.
 - I am very happy with it. It's a little rough around the edges, but it was far worse hours ago.

*/
