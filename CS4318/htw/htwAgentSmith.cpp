// YOUR NAME: 
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
#include <utility>

namespace
{
   // If you need to define any new types or functions, put them here in
   // this unnamed namespace.  But no variables allowed!
   
   //the danger value of a stench in an adjacent tile
   
   /* unfinished code
   const stenchDanger = 100;
   const pitDanger = 20;
   const exploreDanger = 10;
   */

   struct KnowledgeBase
   {
      //agent knowledge
      int whereX = 0;
      int whereY = 0;
      
      /* unfinished code
      action previousActions[160];
      int currentAction = 0;
      */
      
      int haveGold = false;
      
      /* unfinished code
      int foundWumpus = false;
      int wumpusDead = false;
      */
      
      /* unfinished code
      
      //functionality :
      // adjacent cells to a stench cell will be incremented
      // the same function will see if any cells equal 2 after the incremented
      // if so, wumpusFound == true, and we rely on wumpusLocation instead
      int wumpusLocationX = 0;
      int wumpusLocationY = 0;
      int wumpusMap[4][4] =
      {
         
         {0, 0, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0},
         
      };
      
      //functionality :
      // pits need to be handled differently from wumpuses
      // this is because there can be up to 15 pits! (extremely unlikely, but still)
      // each cell adjacent to a breeze will be incremented
      // we will want to avoid areas with a high chance of pits
      int pitMap[4][4] =
      {
         
         {0, 0, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0},
         
      };
      
      bool exploredMap[4][4] =
      {
         
         {true, false, false, false},
         {false, false, false, false},
         {false, false, false, false},
         {false, false, false, false}
         
      };
      
      */
      
   };
   
   /* unfinished code
   
   //TODO
   void updatePitMap(KnowledgeBase& kb)
   {
      for(int i = -1; i <= 1; i++)
      {
         for(int j = -1; j <= 1; j++)
         {
            
            if(kb.locationX == 0)
            {
               
               
               
            }
            
            if(kb.locationY == 0)
            {
               
               
               
            }
            
         }
      }
      
   }
   
   //TODO
   void updateWumpusMap(KnowledgeBase& kb)
   {
      
      
      
   }
   
   //Function takeAction logs the action and returns it
   //TODO
   action takeAction(KnowledgeBase& kb, action myAction)
   {
      
      kb.previousActions[kb.currentAction] = myAction;
      
      //if action moves, change position
      //if action kills wumpus, change wumpusDead
      //clear wumpusMap and pitMap for move location
      
      return myAction;
   }
   
   //done untested
   Pair<int, int> calculateTile(KnowledgeBase& kb, action myAction)
   {
      //x, y
      Pair<int, int> tile;
      
      switch(myAction)
      {
         
         moveW: tile.first -= 1;
         break;
         moveN: tile.second += 1;
         break;
         moveS: tile.second -= 1;
         break;
         moveE: tile.first += 1;
         break;
         default: tile.first = -1;
         
      }
      
      return tile;
      
   }
   
   //done untested
   int calculateWumpusDanger(KnowledgeBase& kb, int x, int y)
   {
      
      if(!kb.wumpusDead)
      {
         
         if(!kb.wumpusFound)
         {
            
            if(kb.wumpusMap[x][y])
            {
               
               return stenchDanger;
               
            }else{
               return 0;
            }
            
         }
         
         if(kb.wumpusLocationX == x && kb.wumpusLocationY == y){
            
            return 99999;
            
         }
         
      }
      
      return 0;
      
   }
   
   //done untested
   int calculatePitDanger(KnowledgeBase& kb, int x, int y)
   {
      
      if(pitMap[x][y])
      {
         
         return pitMap[x][y] * pitDanger;
         
      }
      
      return 0;
      
   }
   
   //done untested
   bool isValidMove(KnowledgeBase& kb, action myAction)
   {
      
      Pair<int, int> tile = calculateTile(kb, myAction);
      
      if(tile.first >= 0 && tile.first < 4)
      {
         
         if(tile.second >= 0 && tile.second < 4)
         {
            
            return true;
            
         }
         
      }
      
      return false;
      
   }
   
   //done untested
   action inverseMove(action myAction)
   {
      
      switch(myAction)
      {
         
         moveW: return moveE;
         break;
         moveN: return moveS;
         break;
         moveS: return moveN;
         break;
         moveE: return moveW;
         break;
         default: return doNothing;
         
      }
      
   }
   
   // done untested
   bool isExplored(KnowledgeBase& kb, action myAction)
   {
      
      Pair<int, int> tile = calculateTile(kb, myAction);
      
      if(exploredMap[tile.first][tile.second])
      {
         
         return true;
         
      }
      
      return false;
      
   }
   
   //done untested
   action selectLeastDangerousTile(KnowledgeBase& kb, action myAction)
   {
      action bestAction = doNothing;
      int bestActionDanger = 99999;
      
      for(action m = moveW; m <= moveE; m = static_cast<action>(m + 1)
      {
         
         if(isValidMove(kb, myAction)){
            
            danger = 0;
            danger += calculateWumpusDanger(kb, calculateTile(kb, myAction));
            danger += calculatePitDanger(kb, calculateTile(kb, myAction));
            danger += isExplored(kb, myAction) ? exploreDanger : 0;
            
            if(danger < bestActionDanger)
            {
               
               bestAction = m;
               bestActionDanger = danger;
               
            }
            
         }
         
      }
      
      return bestAction;
      
   }
   
   //done untested
   action backtrack(KnowledgeBase& kb)
   {
      
      //we make a move, we remove one action
      kb.movesRemaining--;
      
      while(isValidMove(kb.previousActions[kb.currentAction]).first == -1)
      {
         
         kb.currentAction--;
         
         if(kb.currentAction == 0)
         {
            return climbOut;
         }
         
      }
      
      if(kb.currentAction == 0)
      {            
         return climbOut;
      }
      
      return inverseMove(kb.previousActions[kb.currentAction]);
      
   }
   
   */
   
}

// Rename and complete this agent function.
action htwAgentSmith(WumpusWorldSensor currentSensor, bool shouldReset)
{
   // Declare one static variable of type KnowledgeBase.
   static KnowledgeBase kb;
   // Only one static variable is allowed!

   // Your function must end up returning a valid action.
   // No random-number generation allowed!

   if (shouldReset)
   {
      // Create a fresh knowledge base for the new wumpus world.
      kb = KnowledgeBase();
      // Just return without taking an action.
      return doNothing;
   }
   
   //make a variable, bestAction, which is nothing right now
   action bestAction = doNothing;
   
   /*
   
   //If there's gold, grab it (should not be subject to judgement!)
   if(!kb.haveGold && currentSensor.perceiveGlitter())
   {
      return TakeAction(kb, grab);
   }
   
   //Actions to take if we have gold
   // -----------------------------
   if(kb.haveGold)
   {
      
      //If we have the gold and we're at the exit, let's get out! (should not be subject to judgement)
      if(kb.locationX == 0 && kb.locationY == 0){
         //no need to log this
         return climbOut;
      }
      
      //decide move here ------------------------------------------<<<
      //we'll just backtrack! guaranteed to get there.
      
   }else{
   
      //Actions to take if we don't have gold
      // -----------------------------
      if(kb.perceiveStench() && !kb.wumpusDead && !kb.wumpusFound)
      {
         //update stench map
      }
      
      if(kb.perceiveBreeze())
      {
         //update breeze map
      }
      
      //decide move here ------------------------------------------<<<
      if(kb.movesRemaining < 85)
      {
         return backtrack(kb);
      }
      
      bestAction 
      
   }
   
   //failsafe
   return takeAction(kb, bestAction);
   
   */
   
    if (!kb.haveGold && currentSensor.perceiveGlitter())
   {
      bestAction = grab;
   }
   else if (kb.whereX > 0)
   {
      bestAction = moveW;
   }
   else if (kb.whereY > 0)
   {
      bestAction = moveS;
   }
   else
   {
      bestAction = climbOut;
   }

   switch (bestAction)
   {
   case climbOut:
      break;
   case grab:
      kb.haveGold = true;
      break;
   case moveW:
      kb.whereX -= 1;
      break;
   case moveS:
      kb.whereY -= 1;
      break;
   case moveN:
      kb.whereY += 1;
      break;
   case moveE:
      kb.whereX += 1;
      break;
   case shootW:
      break;
   case shootS:
      break;
   case shootN:
      break;
   case shootE:
      break;
   case doNothing:
      break;
   }

   return bestAction;
   
}

/*

 - First, carefully comment your code above to clarify how it works.
 - Here, describe your approach and analyze it.  How exactly did you develop
   and test it?  What are its strengths and weaknesses?  Why do you expect
   it to do well against the other submitted agents?
 - Also make a note here if you talked about the assignment with anyone or
   gave or received any kind of help.
   
 - IMPORTANT TO NOTE: I am trying to use ISOCPP standards for formatting since they're most widely used.
 - I apologize if some of the formatting is inconsistent because of this, I'm still learning and getting used to it.
   
 - First and foremost, I wanted to map out all of the obviously best actions that should never be subjected to judgement.
 - This includes : Grabbing gold, exiting when we have gold, finding an exit when we have gold (while avoiding danger!)
 -                 One strategy for the last one would be to retrace all of my steps. I'll do that.
                   It's relatively safe, not assured to be the best but considering other factors, that's okay here.
  
 - I want to separate my program's actions into 3 main categories
 - Actions to take when we have gold (mapped completely)
 - Actions to take when we don't have gold (decisions!)
   - I think I'll use a modified a* kind of algorithm.
   - Essentially, I will "explore" all nodes around me.
   - I will select an unexplored tile with the least danger
   - wumpuses tiles and wumpuses will be the most danger at 100
 - Best actions always (only grabbing gold)
 
 - I didn't finish -- Yet!
 - I am working on this tomorrow. if the iteration hasn't been ran by then, I will try to submit the final agent.
 - I think I'm deep in function overload right now. It'll be a challenge to keep track of which functions work and which do not.
 - I've left comments i can use ctrl+f to find, in order to finish unfinished functions
 - Also left comments on untested functions
 
 - I may just restart and completely streamline this. We will see.
 

*/
