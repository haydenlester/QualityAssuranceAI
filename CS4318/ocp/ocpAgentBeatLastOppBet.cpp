// ASU AI Competition
// Agent Challenge A: One-card poker
// Rob LeGrand <rlegrand@angelo.edu>
//
// Here's an example agent function.  You can do better than this.

#include "ocp.h"

int ocpAgentBeatLastOppBet(const MatchupHistory &mh)
{
   // Bet honestly in the first hand; after that, bet whatever would just
   // barely beat your opponent's last bet; if their last bet was
   // unbeatable, bet the minimum.
   int opponentLastBet;
   if (mh.getNumCompletedHands() <= 0)
   {
      return mh.getOwnCurrentCard();
   }
   opponentLastBet = mh.getOpponentPastBet(mh.getNumCompletedHands() - 1);
   return opponentLastBet < mh.getLimit() ? opponentLastBet + 1 : 1;
}
