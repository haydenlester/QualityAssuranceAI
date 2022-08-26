#include "rps.h"

// WinLoss test agent
handsign rpsAgentWinLoss(const vector<handsign> focal, const vector<handsign> opponent){
	
	//constant sSize determines our sample size (last sSize rounds are considered)
	const uint sSize = 10;
	//doubles to hold our weighted win/loss ratio for each handsign
	double rockWinLoss, paperWinLoss, scissorsWinLoss;
	//uints to hold the number of wins and losses for each handsign
	uint wR = 0, wP = 0, wS = 0;
	uint lR = 0, lP = 0, lS = 0;
   int score = 0;
	
	//this check only runs the code to record wins and losses if at least 10 rounds have been played
	if(focal.size() > sSize){
		
		//this code block records wins and losses with various handsigns
		for(uint i = focal.size()-sSize; i < focal.size(); i++){
			
			if(focal[i] == rock){
				
				if(opponent[i] == scissors){
					wR++;
				}else if(opponent[i] == paper){
					lR++;
				}
				
			}else if(focal[i] == paper){
				
				if(opponent[i] == rock){
					wP++;
				}else if(opponent[i] == scissors){
					lP++;
				}
				
			}else if(focal[i] == scissors){
				
				if(opponent[i] == paper){
					wS++;
				}else if(opponent[i] == rock){
					lS++;
				}
				
			}
         
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
			
		}
		
		//this fixes divide by zero error if there are no losses.
		//3 w 0 l is considered a w/l ratio of 3/1, or 3.
		if(!lR){
			lR++;
		}
		if(!lP){
			lP++;
		}
		if(!lS){
			lS++;
		}
		if(!wR){
			wR++;
		}
		if(!wP){
			wP++;
		}
		if(!wS){
			wS++;
		}
		
		//this calculates and weights our win/loss
		rockWinLoss = (static_cast<double>(wR)/lR) * 6;
		paperWinLoss = (static_cast<double>(wP)/lP) * 2;
		scissorsWinLoss = (static_cast<double>(wP)/lP) * 1;
		
      //security. if we're losing, stop from losing.
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
		
		//picks completely randomly if all win/losses are the same to get data
		if(rockWinLoss == paperWinLoss && paperWinLoss == scissorsWinLoss){
			
			int t = randomInt(2);
			switch(t){
				case 0: return rock;
				case 1:	return paper;
				default: return scissors;
			}
				
		}
      
		//this plays the sign with the best win/loss after weighting
		if(rockWinLoss >= scissorsWinLoss){
			
			if(rockWinLoss >= paperWinLoss){
				return rock;
			}else{ // paperWinLoss > rockWinloss >= scissorsWinLoss
				return paper;
			}
			
		}else{ // scissorsWinLoss > rockWinLoss
			
			if(scissorsWinLoss >= paperWinLoss){
				return scissors;
			}else{ // paperWinLoss > scissorsWinLoss > rockWinLoss
				return paper;
			}
			
		}
		
	}else{
      
      int rInt = randomInt(11);
      
      if(rInt < 2){
         return scissors;
      }else if(rInt < 6){
         return paper;
      }else{
         return rock;
      }
      
   }
	
	
}

/*
Test agent selects based off win/loss ratio
*/