// ASU AI Competition
// Agent Challenge A: One-card poker
// Rob LeGrand <rlegrand@angelo.edu>
//
// Here's the main function that plays all agents against each other and
// summarizes the results.

#include "ocp.h"

extern const int numAgents;
extern int (*agentFunc[])(const MatchupHistory &);
extern string agentStr[];

void printBetHistory(const MatchupHistory &);
void printCardHistory(const MatchupHistory &);
void printWinHistory(const MatchupHistory &);

int main()
{
   const int limit = 4;   // Change if you like.
   const int numHands = 2000;   // Change if you like.
   int best[numAgents], betI, betJ, cardI, cardJ, i, j, losses[numAgents],
       numBets[numAgents][limit], order[numAgents], ties[numAgents],
       totalWinnings[numAgents], whichHand, wins[numAgents],
       worst[numAgents];
   MatchupHistory historyI, historyJ;

   srandom(time(0));

   cout << "Agent Challenge A: One-card poker\n"
        << "Iteration results\n\n"
        << "One-on-one matchups:\n\n";
   for (i = 0; i < numAgents; i += 1)
   {
      totalWinnings[i] = 0;
      wins[i] = 0;
      ties[i] = 0;
      losses[i] = 0;
      best[i] = INT_MIN;
      worst[i] = INT_MAX;
      for (j = 0; j < limit; j += 1)
      {
         numBets[i][j] = 0;
      }
   }
   for (i = 0; i < numAgents - 1; i += 1)
   {
      for (j = i + 1; j < numAgents; j += 1)
      {
         historyI = MatchupHistory(limit);
         historyJ = MatchupHistory(limit);
         for (whichHand = 0; whichHand < numHands; whichHand += 1)
         {
            cardI = randomInt(limit) + 1;
            cardJ = randomInt(limit) + 1;
            historyI.dealHand(cardI, cardJ);
            historyJ.dealHand(cardJ, cardI);
            betI = (*agentFunc[i])(historyI);
            betJ = (*agentFunc[j])(historyJ);
            historyI.placeBets(betI, betJ);
            historyJ.placeBets(betJ, betI);
            numBets[i][betI - 1] += 1;
            numBets[j][betJ - 1] += 1;
         }
         totalWinnings[i] += historyI.getTotalAmountWon();
         totalWinnings[j] += historyJ.getTotalAmountWon();
         if (historyI.getTotalAmountWon() > historyJ.getTotalAmountWon())
         {
            wins[i] += 1;
            losses[j] += 1;
         }
         else if (historyI.getTotalAmountWon() < historyJ.getTotalAmountWon())
         {
            losses[i] += 1;
            wins[j] += 1;
         }
         else
         {
            ties[i] += 1;
            ties[j] += 1;
         }
         if (historyI.getTotalAmountWon() > best[i])
         {
            best[i] = historyI.getTotalAmountWon();
         }
         if (historyI.getTotalAmountWon() < worst[i])
         {
            worst[i] = historyI.getTotalAmountWon();
         }
         if (historyJ.getTotalAmountWon() > best[j])
         {
            best[j] = historyJ.getTotalAmountWon();
         }
         if (historyJ.getTotalAmountWon() < worst[j])
         {
            worst[j] = historyJ.getTotalAmountWon();
         }
         cout << setw(27) << right << "cards: ";
         printCardHistory(historyI);
         cout << "\n"
              << setw(17) << right << historyI.getTotalAmountWon()
              << setw(10) << right << "bets: ";
         printBetHistory(historyI);
         cout << "\n"
              << setw(20) << left << agentStr[i] << " wins: ";
         printWinHistory(historyI);
         cout << "\n"
              << setw(20) << left << agentStr[j] << " wins: ";
         printWinHistory(historyJ);
         cout << "\n"
              << setw(17) << right << historyJ.getTotalAmountWon()
              << setw(10) << right << "bets: ";
         printBetHistory(historyJ);
         cout << "\n"
              << setw(27) << right << "cards: ";
         printCardHistory(historyJ);
         cout << "\n\n";
      }
   }

   for (i = 0; i < numAgents; i += 1)
   {
      order[i] = i;
   }
   for (i = 0; i < numAgents - 1; i += 1)
   {
      for (j = i + 1; j < numAgents; j += 1)
      {
         if (totalWinnings[order[i]] < totalWinnings[order[j]])
         {
            whichHand = order[i];
            order[i] = order[j];
            order[j] = whichHand;
         }
      }
   }
   cout << "\n"
        << "Overall standings:\n"
        << "                        total  W  T  L  best worst";
   for (j = 0; j < limit; j += 1)
   {
      cout << " " << setw(6) << right << "bet" << j + 1;
   }
   cout << "\n";
   for (i = 0; i < numAgents; i += 1)
   {
      cout << setw(20) << left << agentStr[order[i]]
           << " " << setw(8) << right << totalWinnings[order[i]]
           << " " << setw(2) << right << wins[order[i]]
           << " " << setw(2) << right << ties[order[i]]
           << " " << setw(2) << right << losses[order[i]]
           << " " << setw(5) << right << best[order[i]]
           << " " << setw(5) << right << worst[order[i]];
      for (j = 0; j < limit; j += 1)
      {
         cout << " " << setw(7) << right << numBets[order[i]][j];
      }
      cout << "\n";
   }

   return 0;
}

void printBetHistory(const MatchupHistory &mh)
{
   int whichHand;
   for (whichHand = 0; whichHand < mh.getNumCompletedHands(); whichHand += 1)
   {
      cout << mh.getOwnPastBet(whichHand);
   }
}

void printCardHistory(const MatchupHistory &mh)
{
   int whichHand;
   for (whichHand = 0; whichHand < mh.getNumCompletedHands(); whichHand += 1)
   {
      cout << mh.getOwnPastCard(whichHand);
   }
}

void printWinHistory(const MatchupHistory &mh)
{
   int whichHand;
   for (whichHand = 0; whichHand < mh.getNumCompletedHands(); whichHand += 1)
   {
      if (mh.getAmountWon(whichHand) >= 0)
      {
         cout << mh.getAmountWon(whichHand);
      }
      else
      {
         cout << "-";
      }
   }
}
