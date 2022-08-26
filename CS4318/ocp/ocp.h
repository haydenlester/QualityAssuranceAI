// ASU AI Competition
// Agent Challenge A: One-card poker
// Rob LeGrand <rlegrand@angelo.edu>
//
// Here are the #includes and definitions available to each agent.

#ifndef OCP_H
#define OCP_H

#include <climits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// Are an opponent's bets and cards from previous hands always visible?
const bool allInfoVisible = true;

// Returns a random nonnegative integer less than n.
int randomInt(int n);

// The history of one matchup between two poker-playing agents from the
// point of view of one of them.
class MatchupHistory
{
private:
   int limit;
   int totalAmountWon;
   vector<int> opponentBets;
   vector<int> opponentCards;
   vector<int> ownAmountsWon;
   vector<int> ownBets;
   vector<int> ownCards;
public:
   MatchupHistory();
   MatchupHistory(int limit);
   void dealHand(int ownCard, int opponentCard);
   int getAmountWon(int whichHand) const;
   int getTotalAmountWon() const;
   int getLimit() const {return limit;}
   int getNumCompletedHands() const {return ownBets.size();}
   int getOpponentPastBet(int whichHand) const;
   int getOpponentPastCard(int whichHand) const;
   int getOwnCurrentCard() const;
   int getOwnPastBet(int whichHand) const;
   int getOwnPastCard(int whichHand) const;
   void placeBets(int ownBet, int opponentBet);
   bool wasHandAShowdown(int whichHand) const;
};

#endif // #ifndef OCP_H
