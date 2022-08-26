#include "rps.h"
#include <iostream>

handsign rpsAgentA312Weight(const vector<handsign> focal, const vector<handsign> opponent){
	
	uint rWeight = 3, pWeight = 1, sWeight = 2;
	
	int t = randomInt(rWeight+pWeight+sWeight);
	
	if(t >= 3){
		return rock;
	}else if(t >= 1){
		return scissors;
	}else{
		return paper;
	}
	
}

//test agent with a 321 rps weight