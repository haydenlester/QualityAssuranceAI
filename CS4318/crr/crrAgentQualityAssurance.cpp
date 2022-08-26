// YOUR NAME: Hayden Lester
//
// CS 4318, spring 2021
// Agent Challenge 5: Chocolate Russian roulette
//
// Rename this file and the function below.  For example, if your agent name
// is Jones, rename this crrAgentSmith.cpp file to crrAgentJones.cpp and the
// crrAgentSmith function below to crrAgentJones.  Complete your agent
// function and turn it in on Blackboard.  Random-number generation is not
// allowed; your agent must be entirely deterministic.  Feel free to create
// other agents--each in a separate .cpp file--for yours to play against,
// but turn in only one.  Test your agent(s) with
//
//    nice bash crrBuild.bash
//
// and then
//
//    nice ./crrRunSim
//
// Each submitted agent will play each other using chocolate bar sizes
// varying from 3x4 to 6x9, once moving first and once moving second, to
// determine the standings, which will be posted soon after the agents are
// due.

#include "crr.h"
#include <algorithm>

namespace
{
   // If you need to define any new types or functions, put them here in
   // this unnamed namespace.  But no variables allowed!
   
   //takes a vector and pushes all valid moves onto the vector
   uint getSquareCount(const ChocolateBar &bar){
      uint sqrcnt = 0;
      
      for (int biteRow = bar.getHeight() - 1; biteRow >= 0; biteRow -= 1){
      
         for (int biteColumn = bar.getWidth() - 1; biteColumn >= 0; biteColumn -= 1){
         
            if (bar.isSquareThere(ChocolateSquareLocation(biteColumn, biteRow))){
               sqrcnt++;
            }
         
         }
      }
      
      return sqrcnt;
   }
   
}

ChocolateSquareLocation crrAgentQualityAssurance(const ChocolateBar &bar){
   
   uint sqrcnt = getSquareCount(bar);
   ChocolateSquareLocation bite;
   
   //key positions
   ChocolateSquareLocation key1 = ChocolateSquareLocation(1, 0);
   ChocolateSquareLocation key2 = ChocolateSquareLocation(0, 1);
   
   //dummy copy bar
   ChocolateBar gamebar;
   
   //if there's only bad chocolate left, bite it
   if(!bar.isSquareThere(key1) && !bar.isSquareThere(key2)){
      return ChocolateSquareLocation(0, 0);
   }
   
   //return assured victory conditions
   if(bar.isSquareThere(key1) != bar.isSquareThere(key2)){
      return (bar.isSquareThere(key1) ? key1 : key2);
   }
   
   if(sqrcnt%2 == 0){
      
      //if it's even, we want to nibble two squares off and keep it even on our turn
      for (int biteRow = bar.getHeight() - 1; biteRow >= 0; biteRow -= 1){
      
         for (int biteColumn = bar.getWidth() - 1; biteColumn >= 0; biteColumn -= 1){
            cout << "Nibble\n";
            if (bar.isSquareThere(ChocolateSquareLocation(biteColumn, biteRow))){
               return ChocolateSquareLocation(biteColumn, biteRow);
            }
            
         }
      
      }
      
   }else{
      
      //if it's odd, take as many squares off as possible
      for (int biteColumn = bar.getWidth() - 1; biteColumn > 0; biteColumn -= 1)
      {
         // If a valid bite is found, return it.
         bite = ChocolateSquareLocation(biteColumn, 0);
         if (bar.isSquareThere(bite))
         {
            return bite;
         }
      }
      
   }
   
   //failsafe return
   return ChocolateSquareLocation(0, 0);
   
}

/*

 - First, carefully comment your code above to clarify how it works.
 - Here, describe your approach and analyze it.  How exactly did you develop
   and test it?  What are its strengths and weaknesses?  Why do you expect
   it to do well against the other submitted agents?
 - Also make a note here if you talked about the assignment with anyone or
   gave or received any kind of help.
   
   This is something I cooked up since it's clear I won't be able to finish the minimax approach in time for iteration one.
   I'm mostly stuck on Alpha-Beta pruning, I'm still trying though.
   
   The idea behind this one is that having an even amount of squares (if victory conditions aren't met) seems to be a power position.
   This is from my anecdotal evidence playing the game. I haven't solved for it. However, this approach seems to do well against my test agents I have had time to write.
   
   Basically, the idea is that apart from assured victory or defeat, we want to give the opposing agent an ODD number of tiles
   If we receive this odd number, we want to simply bite off lots of tiles (excluding 0) and hopefully keep it even
   It seems to perform better if I don't bite off the maximum amount--hence it causes the condition of a split playing field
   In addition, this makes it where the agent will often cause a "splitted tileset" (that is, there is no way for them to simply win with one move)
   By giving them bad options, they're forced to continually make bad bites on uneven tiles to delay, hence leading us to victory.
   

*/
