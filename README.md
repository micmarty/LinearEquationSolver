# LinearEquationSolver

First thing first: http://screenshot.sh/m7zG1OBxZYdFG

**Project inspired by curiosity, just to check how reliable probability theories are.**

What if you could simulate the whole play and anticipate who'll win? 

Project was invented by Faculty of Algorithms ...bla bla.

##What is it all about?
You have one dimensional gameboard, where are 2 players.

Each of the players is rolling a dice (1-6 points), then he jumps to the field, he (pseudo)randomly rolled. 

The look of our board is hardcoded in GameState.cpp in setPenalties() function.

By default each field has a value of 1, but some fields have some penalties. 

If you hit the penalty, you need to go <value on that field> fields back.

We are calculating what is the probability(chance) of 1st player winning.

##How this works?
The algorithm is generating a linear equation for each gamestate, 
then every equation is put into matrix(squared).

for example:
- a - position of the first player
- b - posiiton of the second player
- g - which player is currently rolling a dice

x(g,a,b);

TODO describe each one in details

NEED TO FINISH THIS README

..............................................

