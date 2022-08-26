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

int ocpAgentEqualPlay(const MatchupHistory &mh)
{
   int myCard = mh.getOwnCurrentCard();
   
   if(myCard <= 2){
      return 1;
   }else{
      return 4;
   }
   
}