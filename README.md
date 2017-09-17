# LinearEquationSolver - toy project

[![asciicast](https://asciinema.org/a/lP2rmm3PuoxvpQj6WO6AdCyOQ.png)](https://asciinema.org/a/lP2rmm3PuoxvpQj6WO6AdCyOQ)

## How to run
```bash
cd build
./LinearEquationSolver.out
```

## How to compile manually (Linux)
(Windows still a possibility, e.g. Visual Studio)
```bash
g++ -c src/*.cpp && mv *.o build
g++ build/*.o -o build/LinearEquationSolver.out

```

## Project inspired by curiosity, just to check how reliable probability theories are.**

What if you could simulate the whole play and anticipate who'll win? 

Project was invented by the Faculty of Algorithms ... bla, bla, bla ...

## What is it all about?
You have one dimensional gameboard, where are 2 players.

Each one rolls a dice (1-6 points), then he jumps to the field, he (pseudo)randomly rolled. 

The look of our board is hardcoded in GameState.cpp in setPenalties() function.

By default each field has a value of 1, but some of the fields may contain penalties. 

If you hit the penalty with value **n**, you need to go **n** fields back.

#### We are calculating what is the probability(chance) of 1st player winning the game (reaching the finish line).

## How this works?
The algorithm is generating a linear equation for each gamestate, 
then every equation is put into a squared matrix.

For example:
- a - position of the first player
- b - posiiton of the second player
- g - which player is currently rolling a dice

Then we can write this function as follows:
```
x(g,a,b);
```

## In my program there are 3 methods for anticipating the winner

- Gauss–Seidel method - the method of successive displacement -> iterative method
- Gaussian Elimination method
- Monte Carlo simulation with different number of iterations

## TODO 
- [x] Update README with compilation guide + Linux support
- [ ] Describe each file in details


..............................................

