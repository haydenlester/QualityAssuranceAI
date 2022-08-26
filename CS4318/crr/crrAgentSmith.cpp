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

namespace
{
   // If you need to define any new types or functions, put them here in
   // this unnamed namespace.  But no variables allowed!
}

ChocolateSquareLocation crrAgentSmith(const ChocolateBar &bar)
{
   // Find the entire rightmost available column of squares.
   ChocolateSquareLocation bite;
   int biteColumn;

   // Consider each possible bite, starting with the right column.
   for (biteColumn = bar.getWidth() - 1; biteColumn > 0; biteColumn -= 1)
   {
      // If a valid bite is found, return it.
      bite = ChocolateSquareLocation(biteColumn, 0);
      if (bar.isSquareThere(bite))
      {
         return bite;
      }
   }

   // If only the left column remains, try to bite all but the poison square.
   bite = ChocolateSquareLocation(0, 1);
   if (bar.isSquareThere(bite))
   {
      return bite;
   }

   // If nothing's left, bite the poison square.
   return ChocolateSquareLocation(0, 0);
}

/*

 - First, carefully comment your code above to clarify how it works.
 - Here, describe your approach and analyze it.  How exactly did you develop
   and test it?  What are its strengths and weaknesses?  Why do you expect
   it to do well against the other submitted agents?
 - Also make a note here if you talked about the assignment with anyone or
   gave or received any kind of help.
   
   // This is crrAgentBiteRight. I am turning something in while I work on the agent more this weekend.
   // If I can get a good agent in before submissions close for this iteration, I will, otherwise I'll just make it better for iteration 2

*/
