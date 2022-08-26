// ASU AI Competition
// Agent Challenge A: One-card poker
// Rob LeGrand <rlegrand@angelo.edu>
//
// Here are the functions available to each agent.

#include "ocp.h"

int randomInt(int n)
{
   // Return a random nonnegative integer less than n.
   int r;
   if (n <= 0)
   {
      return 0;
   }
   do
   {
      r = random();
   }
   while (r >= INT_MAX / n * n);
   return r / (INT_MAX / n);
}

MatchupHistory::MatchupHistory()
{
   limit = 0;
   totalAmountWon = 0;
}

MatchupHistory::MatchupHistory(int limit)
{
   this->limit = limit;
   totalAmountWon = 0;
}

void MatchupHistory::dealHand(int ownCard, int opponentCard)
{
   if (ownBets.size() == opponentBets.size() &&
       ownCards.size() == opponentCards.size() &&
       ownBets.size() == ownCards.size())
   {
      ownCards.push_back(ownCard);
      opponentCards.push_back(opponentCard);
   }
}

int MatchupHistory::getAmountWon(int whichHand) const
{
   if (whichHand >= 0 && whichHand < static_cast<int>(ownAmountsWon.size()))
   {
      return ownAmountsWon.at(whichHand);
   }
   return 0;
}

int MatchupHistory::getOpponentPastBet(int whichHand) const
{
   if (whichHand >= 0 && whichHand < static_cast<int>(opponentBets.size()))
   {
      return opponentBets.at(whichHand);
   }
   return 0;
}

int MatchupHistory::getOpponentPastCard(int whichHand) const
{
   if (whichHand >= 0 && whichHand < static_cast<int>(opponentCards.size()) &&
       whichHand < static_cast<int>(opponentBets.size()))
   {
      return opponentCards.at(whichHand);
   }
   return 0;
}

int MatchupHistory::getOwnCurrentCard() const
{
   if (ownCards.size() > ownBets.size())
   {
      return ownCards.back();
   }
   return 0;
}

int MatchupHistory::getOwnPastBet(int whichHand) const
{
   if (whichHand >= 0 && whichHand < static_cast<int>(ownBets.size()))
   {
      return ownBets.at(whichHand);
   }
   return 0;
}

int MatchupHistory::getOwnPastCard(int whichHand) const
{
   if (whichHand >= 0 && whichHand < static_cast<int>(ownCards.size()))
   {
      return ownCards.at(whichHand);
   }
   return 0;
}

int MatchupHistory::getTotalAmountWon() const
{
   return totalAmountWon;
}

void MatchupHistory::placeBets(int ownBet, int opponentBet)
{
   int whichHand;
   if (ownBets.size() == opponentBets.size() &&
       ownCards.size() == opponentCards.size() &&
       ownBets.size() + 1 == ownCards.size() &&
       ownBets.size() == ownAmountsWon.size())
   {
      ownBet = min(max(ownBet, 1), limit);
      opponentBet = min(max(opponentBet, 1), limit);
      whichHand = ownBets.size();
      ownBets.push_back(ownBet);
      opponentBets.push_back(allInfoVisible || opponentBet <= ownBet ? opponentBet : ownBet + 1);
      if (ownBets.at(whichHand) > opponentBets.at(whichHand))
      {
         ownAmountsWon.push_back(opponentBets.at(whichHand));
         totalAmountWon += opponentBets.at(whichHand);
         if (!allInfoVisible)
         {
            opponentCards.at(whichHand) = 0;
         }
      }
      else if (ownBets.at(whichHand) < opponentBets.at(whichHand))
      {
         ownAmountsWon.push_back(-ownBets.at(whichHand));
         totalAmountWon -= ownBets.at(whichHand);
         if (!allInfoVisible)
         {
            opponentCards.at(whichHand) = 0;
         }
      }
      else if (ownCards.at(whichHand) > opponentCards.at(whichHand))
      {
         ownAmountsWon.push_back(opponentBets.at(whichHand));
         totalAmountWon += opponentBets.at(whichHand);
      }
      else if (ownCards.at(whichHand) < opponentCards.at(whichHand))
      {
         ownAmountsWon.push_back(-ownBets.at(whichHand));
         totalAmountWon -= ownBets.at(whichHand);
      }
      else
      {
         ownAmountsWon.push_back(0);
      }
   }
}

bool MatchupHistory::wasHandAShowdown(int whichHand) const
{
   if (whichHand >= 0 && whichHand < static_cast<int>(ownBets.size()) &&
       whichHand < static_cast<int>(opponentBets.size()))
   {
      return ownBets.at(whichHand) == opponentBets.at(whichHand);
   }
   return false;
}
