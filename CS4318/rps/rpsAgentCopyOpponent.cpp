// CS 4318, spring 2021
// Agent Challenge 1: Rock, paper, scissors
//
// Here's an example agent function.  You can do much better than this.

#include "rps.h"

handsign rpsAgentCopyOpponent(const vector<handsign> focal, const vector<handsign> opponent)
{
   if (opponent.size() <= 0)
   {
      // Play rock in the first round.
      return rock;
   }
   // In subsequent rounds, play whatever the opponent just played in the previous round.
   return opponent.back();
}
