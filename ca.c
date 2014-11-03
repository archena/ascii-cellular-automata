/*
  Usage: ca {SIZE} {GENERATIONS} {RULE NUMBER}
  Where rule number is based on Wolfram numbering
 
  Example: $ ./ca 50 10 126

        ***      *** * **** ** * *** *** *  * ***  **  
       ** **    ** *****  ******** *** ******** ****** 
      *******  *****   ****      *** ***      ***    **
     **     ****   ** **  **    ** *** **    ** **  ***
     ***   **  ** ***********  ***** *****  ********* *
     * ** *********         ****   ***   ****       ***
     ******       **       **  ** ** ** **  **     ** *
     *    **     ****     *********************   *****
     **  ****   **  **   **                   ** **   *
     *****  ** ******** ****                 ******* **

 */

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

typedef char byte;

/**
 * Converts a CA state into a string and outputs the string to stdout
 */
void printstate(byte* state, unsigned short casize)
{
  char statestr[casize + 1];

  for(int i = 0; i < casize; ++i)
    statestr[i] = state[i] == 1 ? '*' : ' ';

  statestr[casize] = '\n';
  write(1, statestr, casize + 1);
}

void generateCA(unsigned short casize, unsigned short latticesize, unsigned short generations, byte rulenum)
{
  byte state[latticesize];
  byte pstate[latticesize];

  srand(time(NULL));
  for(int i = 1; i <= casize; ++i)
    state[i] = rand() % 2;

  state[0] = state[latticesize - 1] = 0; /* boundaries */

  for(int gen = 0; gen < generations; ++gen)
  {
    printstate(state + 1, casize);

    memcpy(pstate, state, latticesize);
    for(int i = 1; i <= casize; ++i)
    {
      // The next state is a function of the current cell, and its left and right neighbours.
      // Rather than building a rule table, the rule number's bits are treated as the table.
      state[i] = !!(rulenum & (0x01 << ((pstate[i-1] << 2) + (pstate[i] << 1) + pstate[i+1])));
    }
  }
}

/**
 * Main program
 */
int main(int argc, char* argv[])
{
  if(argc < 3)
  {
    printf("Usage: ca {SIZE} {GENERATIONS} {RULE NUMBER}\n");
    return 1;
  }
  else
  {
    // n.b. for a CA of size n, n+2 bytes are allocated.
    // The extra two are fixed at 0 and represent the left and right lattice boundaries
    unsigned short casize = atoi(argv[1]);
    unsigned short latticesize = casize + 2;
    unsigned short generations = atoi(argv[2]);
    byte rulenum = atoi(argv[3]);
    generateCA(casize, latticesize, generations, rulenum);
    return 0;
  }
}
