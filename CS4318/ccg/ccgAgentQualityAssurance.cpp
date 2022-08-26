// YOUR NAME: Hayden Lester
//
// CS 4318, spring 2021
// Agent Challenge 4: Cricket card game
//
// Rename this file and the function below.  For example, if your agent name
// is Jones, rename this ccgAgentSmith.cpp file to ccgAgentJones.cpp and the
// ccgAgentSmith function below to ccgAgentJones.  Complete your agent
// function and turn it in on Blackboard.  Random-number generation is not
// allowed; your agent must be entirely deterministic.  Feel free to create
// other agents--each in a separate .cpp file--for yours to play against,
// but turn in only one.  Test your agent(s) with
//
//    nice bash ccgBuild.bash
//
// and then
//
//    nice ./ccgRunSim
//
// Each submitted agent will play each other, batting first and batting
// second an equal number of times, to determine the standings, which will
// be posted soon after the agents are due.

#include "ccg.h"
#include <cmath>

namespace
{
   //#############################################################################################################################
   
   //------------------------------
   //VARIABLES
   //------------------------------
   
   //Constants
   const int handSize = 6;
   const int meanCardNumber = 5;
   
   //Multipliers to fiddle with and search for optimal strategies
   
   //Batting multipliers
   const double dFMultiplier = 1.0; // for dF
   const double tFMultiplier = 1.2; // for tF
   const double faFMultiplier = .48; // for faF
   
   //Bowling multipliers
   const double hcFFlatMultiplier = .97; // for hcF
   const double pbFMultiplier = 1.54;
   
   //------------------------------
   //UTILITY FUNCTIONS
   //------------------------------
   
   //returns average value of cards in the deck, normalized
   double deckAvg(Hand hand){
      
      double accum = 0.0;
      
      for(uint i = 0; i < 6; i++)
         accum += hand.getCard(i).getNumber();
      
      return (accum/handSize)/11;
      
   }
   
   //------------------------------
   //CRITERIA CALCULATION FUNCTIONS
   //------------------------------
   // See notes for more info.
   
   //Calculate dF
   //Output range: [0, 5]
   //Outputs how many cards (excluding our card) that we have with matching suits.
   double calculateDF(Hand hand, int i){
      
      double dF = -1.0; // diversity factor, offset by one since one card will always match itself
      Card curCard = hand.getCard(i);
      
      for(int i = 0; i < handSize; ++i){
         
         if(hand.getCard(i).getSuit() == curCard.getSuit())
            dF += 1.0;
         
      }
      
      return dF*dFMultiplier;
      
   }
   
   //Calculate tF
   //Output range: [-5]u[0, 6]
   //Outputs the number of runs scored by playing this card, or -5 for a fallen wicket.
   double calculateTF(Card curCard, Card lastBowledCard){
      
      double tF; // turnout factor
      
      //if our suits match
      if(curCard.getSuit() == lastBowledCard.getSuit()){
         
         //calculate runs scored
         tF = numRuns(curCard.getNumber()-lastBowledCard.getNumber());
         //multiply it by the multiplier and return it
         return tF*tFMultiplier;
         
      }
      
      if(curCard.getNumber() < lastBowledCard.getNumber())
         return -5.0*tFMultiplier;
      
      return 0;
      
   }
   
   //Calculate faF
   //Output range: [0, 5]
   //Outputs how many below the average card our selected card is.
   double calculateFAF(Card curCard){
      
      double faF; // futureadv factor
      
      //our expression returns positive values for cards below the meanCardNumber, negative values otherwise.
      //this means that cards below meanCardNumber will be positively weighted
      faF = (meanCardNumber - curCard.getNumber())*faFMultiplier;
      
      return faF;
      
   }
   
   //Calculate hcF
   //Output range: [1, 10]
   double calculateHCF(Card card, Hand hand){
      
      return card.getNumber() * deckAvg(hand) * hcFFlatMultiplier;
      
   };
   
   //Calculate pbF
   //Output range: [0, 1]
   //Returns 1 if the card matches the previous card bowled, 0 otherwise
   // (multiplied by the multiplier of course)
   double calculatePBF(Card curCard, Card lastBowledCard){
      
      if(curCard.getSuit() == lastBowledCard.getSuit())
         return 1.0;
      
      return 0.0;
      
   }
   
   //#############################################################################################################################
}

int ccgAgentQualityAssurance(Hand hand, Card lastBowledCard, bool isBatting, const MatchState &match)
{
   
   //Variables
   double value[6]; // Holds value of our hand on a card-by-card basis
   int bestCardIndex = 0; // Holds index of best card
   Card curCard; // Holds the current card for iterative processes (ex: within for loops)

   if(isBatting){
      
      //iterate through our hand
      for(int i = 0; i < 6; ++i){
         
         //grab our current card
         curCard = hand.getCard(i);
         
         //sets value to 0 before performing arithmetic operations later on
         value[i] = 0;
         
         //totals all criteria values into the value
         value[i] += calculateDF(hand, i); // apply dF
         value[i] += calculateTF(curCard, lastBowledCard); // apply tF
         value[i] += calculateFAF(curCard); // apply faF
         
         //sets it as the new best card if it beat previous cards
         if(value[i] > value[bestCardIndex]){
            bestCardIndex = i;
         }
         
      }
      
      //return bestCardIndex as our chosen card
      return bestCardIndex;
      
   }else{
      
      //iterate through our hand
      for(int i = 0; i < 6; ++i){
         
         //grab our current card
         curCard = hand.getCard(i);
         
         //sets value to 0 before performing arithmetic operations later on
         value[i] = 0;
         
         //totals all criteria values into the value
         value[i] += calculateHCF(curCard, hand); // apply hcF
         value[i] += calculatePBF(curCard, lastBowledCard); // apply pbF
         
         //sets it as the new best card if it beat previous cards
         if(value[i] > value[bestCardIndex]){
            bestCardIndex = i;
         }
         
      }
      
      //return bestCardIndex as our chosen card
      return bestCardIndex;
      
   }
   
}

/*
 ---GENERAL APPROACH---
 Generally, this program will...
 1) Iterate through our hand
 2) Assign a value to each card based off criteria
 3) Pick the card with the best value
 
 I wanted to do a criteria-based approach for my second iteration and spend a lot more time
 investigating approaches and searching criteria genetically.
 I've written the calculations for all criteria as separate functions in the namespace, so it is easy to read and see.
 Much of my code lies in these calculation functions, generally the description will give you a good idea of what they do.
 
 Multipliers are on line 37-48
 Criteria format is "xxF", so "High Card Factor" becomes hcF. Descriptions of the criteria are below.

 ---CRITERIA---
   1) Batter
      a) dF - Diversity Factor - Prioritizes playing cards that we have multiple suits of
                               - This serves to "Diversify" the deck and eliminate the loss of wickets as much as possible
      b) tF - Turnout Factor - Prioritizes playing cards that have a favorable turnout for us
                             - This ensures that we play cards that don't lose us wickets, or score us more runs!
      c) faF - Future Advantage Factor - Prioritizes playing cards less than the mean card, 5.5.
                                       - This makes it such that our deck's average value will be most likely to go up after a move.
   2) Bowler
      a) hcF - High Card Factor - Prioritizes playing higher cards
                                - Self explanatory, but relies on deck average to determine multiplier
      b) pbF - Previous Bowl Factor - Prioritizes playing the previously bowled card's suit
                                    - Playing many of the same card is good because the batter will run out of the suit most likely.
*/
