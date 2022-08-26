// ASU AI Competition
// Agent Challenge A: One-card poker
// Rob LeGrand <rlegrand@angelo.edu>
//
// Here's an example agent function.  You can do better than this.

#include "ocp.h"

int ocpAgentHonest(const MatchupHistory &mh)
{
   // Bet an amount equal to the value of your card.
   return mh.getOwnCurrentCard();
}
