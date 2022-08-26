// YOUR NAME: 
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
#include <utility>

namespace
{
   
}

int ccgAgentSmith(Hand hand, Card lastBowledCard, bool isBatting, const MatchState &match)
{
   return 0;
}

/*

 - I made some observations here.
 Bowler observations - Suits are not held in higher regard than others, while numbers can be!
                     - This makes suits fluff for bowlers, that can be ignored!
                     - This means that when a high card is played, we can estimate the deck's value as being lower!
                     - As a bowler, if our deck is estimated to be worth more, we can play high cards!
                     - Otherwise, we want to stick to lower cards.
                     
 Batter observations - Suits do matter here, since we can see the bowler's card before playing.
                     - If our high card estimate is higher than the bowlers, we can probably score more runs.
                     - If our high card estimate is lower than the bowlers, we should just minimize wicket losses.
                     - Thus, we want to use our low cards while their high card estimate is higher
                     - We also want to use our high cards when their high card esimate is lower, but ONLY IF we can score on it.
                     
 - I (slowly) realized this approach would not work, as I am not passed a matchup history with previous cards, there's no way for me to "count cards"
 - Usually my strategy is to play off of the other agent's playstyle, so I will need to do more thinking on this.
 - Also having trouble with genetic algorithms in class, so i will do more research on my own time
 
 - The code above is from ccgAgentDefensive.cpp and ccgAgentAggressive.cpp
 - The only stipulation I added, is I added a rudimentary "confidence" variable based off my deck's value.
 

*/
