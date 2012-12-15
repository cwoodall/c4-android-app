# Simple Connect 4

Here I present a simple connect 4 game. Currently it only has a terminal client.
However, I may take it as an exercise to implement it in some other manner.

This connect four player, while written in python was written as an exercise
for a C++ version which will be used as a back-end using the NDK for an 
Android implementation for a class project.

# How to use

Just run connect4.py using:

> $ python connect4.py

This game will play in the terminal and has an AI player to play against you.

# AI Development

## Nov 21, 2012

The current AI is pretty stupid. It just makes random guesses. In fact, it
can't even be considered competent. However, I am working on improving this.
I would barely call it an AI, its more like a bad stochastic machine.

## Nov 28, 2012

Worked on a NeuralNetwork class library that include Neuron, NeuronLayers and 
can train Neurons using backpropagation. This currently not well implemented, 
but is currently generalizeable to N inputs and M outputs where N and M are 
greater than 0, with some effort.

I have effectively trained 3 input XOR and an arbitrary 3 input function at 
the same time (2 outputs). I was rather impressed with this result.

## Dec 14, 2012

Production halted temporarially. EC327 project finished with simple AI. Fiture
versions of the C4 app will contain a better AI preferably with different 
levels.
