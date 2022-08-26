// YOUR NAME: Hayden Lester
//
// ASU AI Competition
// Agent Challenge A: One-card poker
//
// Rename this file and the function below.  For example, if your agent name
// is Jones, rename this ocpAgentSmith.cpp file to ocpAgentJones.cpp and the
// ocpAgentSmith function below to ocpAgentJones.  Complete your agent
// function and turn it in on Blackboard.  Feel free to create other
// agents--each in a separate .cpp file--for yours to compete against, but
// turn in only one.  Test your agent(s) with
//
//    nice bash ocpBuild.bash
//
// and then
//
//    nice ./ocpRunSim
//
// Each submitted agent will play each other in matchups of some number of
// hands each (at least 100) to determine the standings, which will be
// posted soon after the agents are due.

#include "ocp.h"
using namespace std;

int ocpAgentQualityAssurance3(const MatchupHistory &mh)
{
   int myCard = mh.getOwnCurrentCard();
   int cardsBluffed[4] = {0, 0, 0, 0}; // keep track of which cards they're bluffing, fold if lower than mean bluff card
   int cardsFolded[4] = {0, 0, 0, 0}; // keep track of which cards they're folding, honesty if higher than mean fold card
   int totalBluffs = 0, totalFolds = 0; // total bluffs and folds
   int meanBluffCard, meanFoldCard; // keeps track of mean bluff and fold cards
   int avgBluffBy = 0, avgFoldBy = 0; // keeps track of how much they bluff by
   int bluffAdditive = 2, foldAdditive = -1;
   
   
   // if we're a 4, there is no reason to not be honest
   if(myCard == 4){
      return 4;
   }
   
   //checks if this is the first round, always plays 1
   if(mh.getNumCompletedHands() == 0){
      return 1;
   }
   
   //for loop counts past folds and bluffs
   // This step is only essential for calculating meanBluff and meanFold on line XX.
   // For this reason, I won't explain the code too much, as the result is simple and immediately evident.
   for(int i = 0; i < mh.getNumCompletedHands(); i++){
      
      int pastCard = mh.getOpponentPastCard(i);
      int pastBet = mh.getOpponentPastBet(i);
      
      if(pastBet > pastCard){
         cardsBluffed[pastCard] += 1;
         avgBluffBy += pastBet - pastCard;
         totalBluffs++;
      }else if(pastBet < pastCard){
         cardsFolded[pastCard] += 1;
         avgFoldBy += pastCard - pastBet - foldAdditive;
         totalFolds++;
      }
      
   }
   
   //calculate avgBluffBy
   avgBluffBy /= mh.getNumCompletedHands();
   
   //calculate meanBluffCard and meanFoldCard
   meanBluffCard = (cardsBluffed[0] * 1 + cardsBluffed[1] * 2 + cardsBluffed[2] * 3 + cardsBluffed[3] * 4)/(totalBluffs == 0 ? 1 : totalBluffs);
   meanFoldCard = (cardsFolded[0] * 1 + cardsFolded[1] * 2 + cardsFolded[2] * 3 + cardsFolded[3] * 4)/(totalFolds == 0 ? 1 : totalFolds);
   
   
   //select our card to play
   if(myCard >= meanBluffCard){
      //bluff, bluff risk is on average going to pay out
      return myCard+avgBluffBy+bluffAdditive <= 4 ? myCard+avgBluffBy+bluffAdditive : 4;
   }else if(myCard > meanFoldCard){
      //honesty, cant risk bluff
      return myCard;
   }else if(myCard <= meanFoldCard){
      //fold, they will bluff or honesty most likely
      return myCard-avgFoldBy+foldAdditive >= 1 ? myCard-avgFoldBy+foldAdditive : 1;
   }
   
   return 1;
   
   
   
}

/*
Notes on approach

TABLE. X = Their bet, Y = My bet
--------------
   1  2  3  4
   
1  C  -1 -1 -1

2  1  C  -2 -2

3  1  2  C  -3

4  1  2  3  C
--------------

Approach :
 I wanted to create an approach that would tell me what their average card must be to bluff and fold.
 I use this information in order to select my next move. Whether to bluff or fold, depends on if my card is higher or lower than these cards.
 This way, I can use previous information in a helpful way, and play around the opposing agent's playstyle.
 
 Essentially, meanBluffCard represents the average card they bluff on
 This means that, if they bluff with a 2, I should be bluffing with a higher card than that (to match, and hopefully beat their playstyle)
 Admittedly, this approach is conservative. It plays honestly when we're in uncertain territory (equal to their mean bluff card rounded kind of)
 It folds when our card is below what they would fold.
 By only bluffing higher cards than them, and only folding lower cards, the plan is to minimize our losses and eventually come out on top.
 I think maximizing our gains is a very poor way to play this challenge. (See note)
 
 Note:
 After the previous iteration, I noticed an agent that only played 1 and 4, roughly 50% of the time each to any statistical significance
 This can only mean one thing, to me: This agent plays 1 if they're a 1 or 2, and 4 if they're a 3 or 4.
 In interest of having more interesting code and a more thoughtful approach, I still want to submit this one.
 This approach takes WAY more advantage of people with lesser agents and less advantage of mine.
 Mine simply takes less advantage of lesser agents.
 
 Note 2:
 Final submission. I did some testing with some minor changes and this is the best agent I was able to make.
 It beat all my other agents by a considerable amount--that's not saying much, though.
 It also beat them only sometimes. But I'm counting on being more aggressive to take advantage of lesser agents.
 I noticed that when folding, if I simply fold to 1 instead of doing something weird with my additives, it scores higher.
 It's possible that is the case because this agent is slightly more aggressive.
 The idea is the same though:
  1) Find out the range of cards where the opponent bluffs, folds, or is more honest
  2) React by only bluffing cards above that bluff range (less risky than their agent)
     -> This has the added benefit of us winning most bet-draws. That is, my card is likely to be higher when they bet the same.
  3) Fold cards lower than that mostly, to avoid losing points when not taking advantage.

*/
