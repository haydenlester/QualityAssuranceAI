// ASU AI Competition
// Agent Challenge A: One-card poker
// Rob LeGrand <rlegrand@angelo.edu>
//
// Here's an example agent function.  You can do better than this.

#include "ocp.h"

int ocpAgentUniformRandom(const MatchupHistory &mh)
{
   // Bet a random amount, all possible bets equally likely.
   return randomInt(mh.getLimit()) + 1;
}
