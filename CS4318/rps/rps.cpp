// CS 4318, spring 2021
// Agent Challenge 1: Rock, paper, scissors
//
// Here are the functions available to each agent.

#include "rps.h"

int outcome(handsign focal, handsign opponent)
{
   // Return the focal player's outcome given the two handsigns.
   if (focal == opponent)
   {
      return 0;
   }
   if (focal == rock)
   {
      if (opponent == paper)
      {
         return -payoffForSmallWin;
      }
      return payoffForBigWin;
   }
   if (focal == paper)
   {
      if (opponent == scissors)
      {
         return -payoffForMediumWin;
      }
      return payoffForSmallWin;
   }
   if (focal == scissors)
   {
      if (opponent == rock)
      {
         return -payoffForBigWin;
      }
      return payoffForMediumWin;
   }
   if (opponent == rock)
   {
      return -payoffForBigWin;
   }
   if (opponent == paper)
   {
      return -payoffForSmallWin;
   }
   if (opponent == scissors)
   {
      return -payoffForMediumWin;
   }
   return 0;
}

int randomInt(int n)
{
   // Return a random nonnegative integer less than n.
   int r;
   if (n <= 0)
   {
      return 0;
   }
   do
   {
      r = random();
   }
   while (r >= INT_MAX / n * n);
   return r / (INT_MAX / n);
}
