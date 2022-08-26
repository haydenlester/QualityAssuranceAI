#include "rps.h"

handsign rpsAgentRPSRPS(const vector<handsign> focal, const vector<handsign> opponent){
	
	if(focal.size() > 0){
		if(focal.back() == rock){
			return paper;
		}else if(focal.back() == paper){
			return scissors;
		}else if(focal.back() == scissors){
			return rock;
		}
	}else{
		return rock;
	}
	
}

//test agent plays RPSRPSRPSRPS