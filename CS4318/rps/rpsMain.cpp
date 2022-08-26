// CS 4318, spring 2021
// Agent Challenge 1: Rock, paper, scissors
//
// Here's the main function that plays all agents against each other and
// summarizes the results.

#include "rps.h"

extern const int numAgents;
extern handsign (*agentFunc[])(const vector<handsign>, const vector<handsign>);
extern string agentStr[];

void printHistory(const vector<handsign>);

int main()
{
   const int numRounds = 1000;   // Change if you like.
   handsign stratI, stratJ;
   int best[numAgents], countPR[numAgents], countPS[numAgents],
       countRP[numAgents], countRS[numAgents], countSP[numAgents],
       countSR[numAgents], i, j, losses[numAgents], matchupScoreI,
       matchupScoreJ, order[numAgents], round, ties[numAgents],
       totalScore[numAgents], wins[numAgents], worst[numAgents];
   vector<handsign> histI, histJ;

   srandom(time(0));

   cout << "Agent Challenge 1: Rock, paper, scissors\n"
        << "Iteration results\n\n"
        << "One-on-one contests:\n\n";
   for (i = 0; i < numAgents; i += 1)
   {
      totalScore[i] = 0;
      wins[i] = 0;
      ties[i] = 0;
      losses[i] = 0;
      best[i] = INT_MIN;
      worst[i] = INT_MAX;
      countRS[i] = 0;
      countSP[i] = 0;
      countPR[i] = 0;
      countRP[i] = 0;
      countPS[i] = 0;
      countSR[i] = 0;
   }
   for (i = 0; i < numAgents - 1; i += 1)
   {
      for (j = i + 1; j < numAgents; j += 1)
      {
         histI.clear();
         histJ.clear();
         matchupScoreI = 0;
         matchupScoreJ = 0;
         for (round = 0; round < numRounds; round += 1)
         {
            stratI = (*agentFunc[i])(histI, histJ);
            if (stratI != rock && stratI != paper)
            {
               stratI = scissors;
            }
            stratJ = (*agentFunc[j])(histJ, histI);
            if (stratJ != rock && stratJ != paper)
            {
               stratJ = scissors;
            }
            histI.push_back(stratI);
            histJ.push_back(stratJ);
            matchupScoreI += outcome(stratI, stratJ);
            matchupScoreJ += outcome(stratJ, stratI);
            if (stratI == rock)
            {
               if (stratJ == paper)
               {
                  countRP[i] += 1;
                  countPR[j] += 1;
               }
               else if (stratJ == scissors)
               {
                  countRS[i] += 1;
                  countSR[j] += 1;
               }
            }
            else if (stratI == paper)
            {
               if (stratJ == rock)
               {
                  countPR[i] += 1;
                  countRP[j] += 1;
               }
               else if (stratJ == scissors)
               {
                  countPS[i] += 1;
                  countSP[j] += 1;
               }
            }
            else
            {
               if (stratJ == rock)
               {
                  countSR[i] += 1;
                  countRS[j] += 1;
               }
               else if (stratJ == paper)
               {
                  countSP[i] += 1;
                  countPS[j] += 1;
               }
            }
         }
         if (matchupScoreI > matchupScoreJ)
         {
            wins[i] += 1;
            losses[j] += 1;
         }
         else if (matchupScoreI < matchupScoreJ)
         {
            losses[i] += 1;
            wins[j] += 1;
         }
         else
         {
            ties[i] += 1;
            ties[j] += 1;
         }
         totalScore[i] += matchupScoreI;
         totalScore[j] += matchupScoreJ;
         if (matchupScoreI > best[i])
         {
            best[i] = matchupScoreI;
         }
         if (matchupScoreI < worst[i])
         {
            worst[i] = matchupScoreI;
         }
         if (matchupScoreJ > best[j])
         {
            best[j] = matchupScoreJ;
         }
         if (matchupScoreJ < worst[j])
         {
            worst[j] = matchupScoreJ;
         }
         cout << setw(20) << left << agentStr[i] << " " << setw(5) << right
              << matchupScoreI << " ";
         printHistory(histI);
         cout << "\n";
         cout << setw(20) << left << agentStr[j] << " " << setw(5) << right
              << matchupScoreJ << " ";
         printHistory(histJ);
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
         if (totalScore[order[i]] < totalScore[order[j]])
         {
            round = order[i];
            order[i] = order[j];
            order[j] = round;
         }
      }
   }
   cout << "\n"
        << "Overall standings:\n"
        << "                        total  W  T  L  best worst    RS    SP    PR    RP    PS    SR\n";
   for (i = 0; i < numAgents; i += 1)
   {
      cout << setw(20) << left << agentStr[order[i]]
           << " " << setw(8) << right << totalScore[order[i]]
           << " " << setw(2) << right << wins[order[i]]
           << " " << setw(2) << right << ties[order[i]]
           << " " << setw(2) << right << losses[order[i]]
           << " " << setw(5) << right << best[order[i]]
           << " " << setw(5) << right << worst[order[i]]
           << " " << setw(5) << right << countRS[order[i]]
           << " " << setw(5) << right << countSP[order[i]]
           << " " << setw(5) << right << countPR[order[i]]
           << " " << setw(5) << right << countRP[order[i]]
           << " " << setw(5) << right << countPS[order[i]]
           << " " << setw(5) << right << countSR[order[i]]
           << "\n";
   }

   return 0;
}

void printHistory(const vector<handsign> hist)
{
   unsigned i;
   for (i = 0; i < hist.size(); i += 1)
   {
      switch (hist.at(i))
      {
      case rock:
         cout << 'R';
         break;
      case paper:
         cout << 'P';
         break;
      case scissors:
         cout << 'S';
         break;
      default:
         cout << '*';
         break;
      }
   }
}
