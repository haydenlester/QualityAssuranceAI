// Hayden Lester
//
// CS 4318, spring 2021
// Agent Challenge 1: Rock, paper, scissors
//
// Rename this file and the function below.  For example, if your agent name
// is Jones, rename this rpsAgentSmith.cpp file to rpsAgentJones.cpp and the
// rpsAgentSmith function below to rpsAgentJones.  Complete your agent
// function and turn it in on Blackboard.  Feel free to create other
// agents--each in a separate .cpp file--for yours to compete against, but
// turn in only one.  Test your agent(s) with
//
//    nice bash rpsBuild.bash
//
// and then
//
//    nice ./rpsRunSim
//
// Each submitted agent will play each other in contests of some number of
// rounds each (at least 100) to determine the standings, which will be
// posted soon after the agents are due.

#include "rps.h"
#include <iostream>

// QualityAssurance Iteration Two, codename 'BAD'
handsign rpsAgentQualityAssurance(const vector<handsign> focal, const vector<handsign> opponent){
	
	//(r/p/s)co - rock/paper/scissors count opposing
	// counters to count how many times the opponent has played certain handsigns
	uint rco = 0, pco = 0, sco = 0;
   // counters to count how many times we have played certain handsigns
   uint rcf = 0, pcf = 0, scf = 0;
   
   int score = 0;
	
	// uint sSize represents how many games backwards the agent will look at to tally the counters above
	const uint sSize = 10;
	
	//loop through the vector
	// if the vectors size is less than the sample size, we'll just loop through the whole vector
	// For our first run, our counters will all be 0, so the if-else on line 64 will always choose rock first
	for(uint i = (focal.size() > sSize ? focal.size()-sSize : 0) ; i < focal.size(); ++i){
		
      //tally score
      if(focal[i] == rock){
         
         if(opponent[i] == scissors){
            score+=3;
         }else if(opponent[i] == paper){
            score-=1;
         }
         
      }else if(focal[i] == scissors){
         
         if(opponent[i] == paper){
            score+=2;
         }else if(opponent[i] == rock){
            score-=3;
         }
         
      }else if(focal[i] == paper){
         
         if(opponent[i] == rock){
            score+=1;
         }else if(opponent[i] == scissors){
            score-=2;
         }
         
      }
		
		//tally opponent play data
		switch(opponent[i]){
			
			case rock: rco++;
			break;
			case scissors: sco++;
			break;
			default: pco++;
			
		}
      
      //tally our play data
		switch(opponent[i]){
			
			case rock: rcf++;
			break;
			case scissors: scf++;
			break;
			default: pcf++;
			
		}
		
		
	}
   
   //this is the failsafe strategy. if we're losing this badly, we need to preserve our points as best we can
   if(score < -100){
      
      int rInt = randomInt(11);
      
      if(rInt < 2){
         return scissors;
      }else if(rInt < 6){
         return paper;
      }else{
         return rock;
      }
      
   }
	
	//add weights to the rps counts
	//important to note, i am weighting by multiplying whatever occurences of rock, paper, or scissors show
	// if they play scissors too much, that is important because i can use rock. hence the 3x weight
	rco*=randomInt(6);
	pco*=randomInt(4);
	sco*=randomInt(2);
	
	//determine which sign to play after weighting the counts of opposing signs played
	if(sco >= rco){
		if(sco >= pco)
			return rock; //they played scissors most, counter w/ rock
		else
			return scissors; //they played paper most, counter w/ scissors
	}else{
		if(rco >= pco)
			return paper; //they played rock most, counter w/ paper
		else
			return scissors; //they played paper most, counter w/ scissors
	}
	
}

/*

--------NOTES ON APPROACH--------

 - 	With this function, I decided to try and tally up recent plays by the opposing
	side and figure out which signs were played more often.
 -	During testing with spreadsheets, I found that a sample size of 10
	and rps weights of x1, x2, and x3 respectively work pretty well.
 -	I still play rock plenty enough to beat pseudorandom agents, but I do not lose the ability to change signs
 -  if someone plays paper 2/3rds of the time, for example.
 -	That means I can both capitalize on unpredictability, but also hopefully won't get caught
 -	with my agent stuck on Scissors because of how someone weighted their choices
 -	With more deterministic agents, mine will be able to switch what it's playing if it's getting beat a lot
 -	I can do this without needing to measure if I'm getting beat, by simply playing
 -	the opposite of what my opponent is playing most.
 
 -	To weight my outcome, I just multiplied the recorded plays of the opposite sign.
 -	Ex: to weight rock, I multiplied recorded plays of scissors by 3.

 -	This approach works great with my current test agents.
 -  It beats all of them, every time, by a lot.
 -	Probably because my test agents aren't very good.
 -  Interested to see who will beat me and try to figure out how.
 
 -	In class, it was explained that we probably want at least some randomness
 -	This uses none of that, because I sort of "borrow" any of my opponents randomness
 -	Because it's deterministic solely based off what the opponent plays,
 -	If the opponent plays in an unpredictable way, I will as well.
 -  Vs a deterministic agent, mine often sticks to one handsign. Which is FINE in this case.
 -	Vs random agents, mine switches around a lot but tends towards rock enough to rack up massive gains.
 
 -	I don't think anyone is going to try to determine my determinism of themselves.
 -	That's sort of weird to think of, but I guess it would be possible.
 
 -	In the second iteration, I want to include code that tallys scores, so if it's ran too high,
 -   my agent will switch to being purely defensive to minimize score loss.
 
 - 	The only thing I am really afraid of is if someone found the ideal defensive strategy.
 -	In which case, it could REALLY beat this agent, I feel.
 
 - _________ POST 1st ITERATION ___________
 
 - Which is probably what happened. That, or, I just wasn't random enough.
 - Because of this, I made some key changes.
 - 1) Weights are now randomized somewhat. ROCK IS STILL GIVEN priority though.
 -     - I did this by just making it where rock can roll between 0 and 6 for a multiplier, and scissors can only roll between 0 and 2, etc.
 - 2) I adjusted the weights according to the ideal defensive strategy, so they'll center around that.
 - 3) I added a failsafe to take on the ideal defensive strategy if we're losing badly enough.
 
 - I believe this will make a difference against the type of agents I'll be up against. But we'll just have to see!

*/