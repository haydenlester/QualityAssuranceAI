
#include "ocp.h"

// Rename and complete this agent function.
int ocpAgentAlphaChad(const MatchupHistory &mh)
{
   int card = mh.getOwnCurrentCard();
   return ( card < 4 ) ? 1 : 4;
}
