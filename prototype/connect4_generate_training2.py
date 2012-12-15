#!/usr/bin/python
from random import uniform
import os
import csv
import neuralnet as nn


f = open('weights.csv', 'rb')
f_reader = csv.reader(f)
weights = []
for row in f_reader:
    weights.append([float(r) for r in row])
f.close()

class ConnectFourBoard(object):
    def __init__(self, rows=6, cols=7, placeholder=" "):
        self.rows=rows
        self.cols=cols
        self.placeholder=placeholder
        self.reset()
        self.last_move = [0,0]
        
    def __str__(self):
        return "\n".join([" ".join(x) for x in self.board])
    
    def reset(self):
        self.board = [[self.placeholder for col in xrange(self.cols)] for row in xrange(self.rows)]
        self.column_status = [0 for x in xrange(self.cols)]

    def __updateColumnStatus(self):
        for col in xrange(self.cols):
            if self.board[0][col] != self.placeholder:
                self.column_status[col] = 1
                
    def makeMove(self, column, player):
        r = 0
        for row in self.board[::-1]:            
            if row[column] == self.placeholder:
                row[column] = player
                break
            r += 1
            
        self.last_move =[(self.rows-1)-r,column]

        self.__updateColumnStatus()

    
class ConnectFourAI(object):
    def __init__(self, marker):
        self.marker = marker
        self.in_layer = nn.InputNeuronLayer(126)
        self.hidden_layer = nn.FullyConnectedNeuronLayer(256, self.in_layer, False, weights[0])
        self.out_layer = nn.FullyConnectedNeuronLayer(7, self.hidden_layer, False, weights[1])
        self.network = [self.in_layer, self.hidden_layer, self.out_layer]
#        print self.network[1].neurons[0].in_weights
        
    def makeMove(self, board):
        is_good = 0

        blank = []
        red = []
        blue = []
        for row in board.board:
            for cell in row:
                if cell == 'r':
                    red.append(1)                            
                else:
                    red.append(0)
                if cell == 'b':
                    blue.append(1)                            
                else:
                    blue.append(0)
                            
                if cell == '*':
                    blank.append(1)                            
                else:
                    blank.append(0)                            

        a = blank + red + blue
        self.in_layer.setInputs(a)

        for layer in self.network:
            layer.fireAll()
            res = self.network[2].getOutputs()

        elim = 0;
        temp_res = 0
        while not is_good:
            temp_res = [ r*uniform(0,2) for i,r in enumerate(res)]
            move = temp_res.index(max(temp_res))
            
            if board.column_status[move]:
                is_good = 0
                res[temp_res.index(max(temp_res))] = 0
            else:
                is_good = 1
                
        return (move, self.marker)

class ConnectFourPlayer(object):
    def __init__(self, marker):
        self.marker = marker

    def makeMove(self, board):
        move = -1
        while ((move < 0) or (move >= board.cols)):
            try:
                move = int(raw_input("Which Column? "))
            except ValueError:
                move = -1
                
            if (move < board.cols) and (move >= 0):
                if board.column_status[move]:
                    print "Row Full Try Again"
                    move = -1
                
        return (move, self.marker)

class ConnectFour(object):
    def __init__(self, markers=('r','b'), ai=False, placeholder=" "):
        self.board = ConnectFourBoard(placeholder=placeholder)
        self.turn = 0
        self.players = ['','']
        self.players[0] = ConnectFourAI(markers[0])
        if ai == True:
            self.players[1] = ConnectFourAI(markers[1])
        else:
            self.players[1] = ConnectFourPlayer(markers[1])

        self.history = []
        self.winning_condition = False
        self.winner = 0

    def reset(self):
        self.winning_condition = False
        self.winner = 0
        self.turn = 0
        self.board.reset()
        self.history = []
        
    def stepGame(self):
        move = (0, " ")
        move = self.players[self.turn].makeMove(self.board)
        self.history.append( [move, self.board.board]) 
        self.board.makeMove(move[0], move[1])            
        self.__checkCondition(self.players[self.turn])
        self.turn ^= 1

    def __checkCondition(self, player):
        # Not sure how I want to check for winning conditions
        board = self.board
        pt = board.last_move
        # Search Horizontal
        horiz_counter = 0
        for i in range(3):
            if ((pt[1]+i+1) <= (board.cols-1)):
                if board.board[pt[0]][pt[1]+1+i] == player.marker:
                    horiz_counter += 1
                else:
                    break

        for i in range(3):
            if ((pt[1]-i-1) >= 0):
                if board.board[pt[0]][pt[1]-1-i] == player.marker:
                    horiz_counter += 1
                else:
                    break            

        vert_counter = 0
        for i in range(3):
            if ((pt[0]+i+1) <= (board.rows-1)):
                if board.board[pt[0]+i+1][pt[1]] == player.marker:
                    vert_counter += 1
                else:
                    break

        for i in range(3):
            if ((pt[0]-i-1) >= 0):
                if board.board[pt[0]-i-1][pt[1]] == player.marker:
                    vert_counter += 1
                else:
                    break

        diag_r_counter = 0
        for i in range(3):
            if ((pt[0]+i+1) <= (board.rows-1)) and ((pt[1]+1+i) <= (board.cols-1)):
                if board.board[pt[0]+i+1][pt[1]+i+1] == player.marker:
                    diag_r_counter += 1
                else:
                    break

        for i in range(3):
            if ((pt[0]-i-1) >=  0) and ((pt[1]-1-i) >= 0):
                if board.board[pt[0]-i-1][pt[1]-i-1] == player.marker:
                    diag_r_counter += 1
                else:
                    break

        diag_l_counter = 0
        for i in range(3):
            if ((pt[0]-i-1) >= 0) and ((pt[1]+1+i) <= board.cols-1):
                if board.board[pt[0]-i-1][pt[1]+i+1] == player.marker:
                    diag_l_counter += 1
                else:
                    break

        for i in range(3):
            if ((pt[0]+i+1) <= (board.rows-1)) and ((pt[1]-1-i) >= 0):
                if board.board[pt[0]+i+1][pt[1]-i-1] == player.marker:
                    diag_l_counter += 1
                else:
                    break
                
        if (horiz_counter == 3) or (vert_counter == 3) or (diag_l_counter == 3) or (diag_r_counter == 3):
            self.winning_condition = True
            self.winner = player
        elif (sum(board.column_status) == 6):
            self.winning_condition = True
            self.winner = player
            
    def __str__(self):
        a = " ".join([str(x) for x in range(self.board.cols)])
        return a+"\n"+str(self.board)
    
if __name__ == "__main__":
    training_f = open('trainingdata2.csv', 'wb')
    writer = csv.writer(training_f)
    game = ConnectFour(ai=True, placeholder="*")
#    print game
    end_game = 0
    games_played = 0
    while not end_game:
     #   os.system( [ 'clear', 'cls' ][ os.name == 'nt' ] )
    #    print game
   #     print game.winning_condition
        while not game.winning_condition:
            game.stepGame()
  #          os.system( [ 'clear', 'cls' ][ os.name == 'nt' ] )
 #           print game
        print "Game Over! Winner is %s" % game.winner.marker
        if game.winner.marker == 'r':
            hist = game.history[::2]
        else:
            hist = game.history[1::2]
        for mov in hist:
#            print mov[1]
            blank = []
            red = []
            blue = []
            for row in mov[1]:
                for cell in row:
                    if cell == 'r':
                        red.append(1)                            
                    else:
                        red.append(0)
                    if cell == 'b':
                        blue.append(1)                            
                    else:
                        blue.append(0)
                            
                    if cell == '*':
                        blank.append(1)                            
                    else:
                        blank.append(0)                            

            output = [0 for a in range(7)]
            output[mov[0][0]] = 1
            a = blank + red + blue + output
            #print a
            writer.writerow(a)
                
            games_played += 1
        if games_played < 3000:
            game.reset()
        else:
            break


