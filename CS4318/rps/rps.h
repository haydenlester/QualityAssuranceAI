// CS 4318, spring 2021
// Agent Challenge 1: Rock, paper, scissors
//
// Here are the #includes and definitions available to each agent.

#ifndef RPS_H
#define RPS_H

#include <climits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const int payoffForBigWin = 3;
const int payoffForMediumWin = 2;
const int payoffForSmallWin = 1;

// The handsigns available for the agents to play.
enum handsign {rock, paper, scissors};

// Returns the focal player's outcome given the two handsigns.
int outcome(handsign focal, handsign opponent);

// Returns a random nonnegative integer less than n.
int randomInt(int n);

#endif // #ifndef RPS_H
