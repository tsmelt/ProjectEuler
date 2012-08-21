# 84_v2.py
# Tyler_Smelt@hmc.edu
# 8/12/2012
# Python implementation of Problem 84 from projecteuler.net
# Calculates most-probable squares to land on in Monopoly
# v2 (8/13/2012): Better OOP, multiprocessing, command line options

from random import shuffle, randint
from itertools import cycle
from multiprocessing import cpu_count, Pool
from datetime import datetime
import argparse

class Game:
    def __init__(self, faces, turns):
        self.faces = faces
        self.turns = turns

class Board:
    def __init__(self):
        self.squares = 40
        
        self.CC = [2, 17, 33]
        self.CH = [7, 22, 36]
        self.RR = [5, 15, 25, 35]
        self.U = [12, 28]
        self.GO = 0
        self.JAIL = 10
        self.G2J = 30
        self.C1 = 11
        self.E3 = 24
        self.H2 = 39
        self.R1 = self.RR[0]
        
        self.square = self.GO
    
    def advance(self):
        self.square += 1
        if self.square == self.squares:
            self.square = self.GO
    
    def gotoGO(self):
        self.square = self.GO
    
    def gotoJAIL(self):
        self.square = self.JAIL
    
    def gotoC1(self):
        self.square = self.C1
    
    def gotoE3(self):
        self.square = self.E3
    
    def gotoH2(self):
        self.square = self.H2
    
    def gotoR1(self):
        self.square = self.R1
    
    def nextRR(self):
        while self.square not in self.RR:
            self.advance()
    
    def nextU(self):
        while self.square not in self.U:
            self.advance()
    
    def back3(self):
        self.square -= 3

class Dice:
    def __init__(self, faces):
        self.faces = faces
        self.doubles = 0
        
    def roll(self):
        nums = [randint(1, self.faces), randint(1, self.faces)]
        if (nums[0] == nums[1]):
            self.doubles += 1
        else:
            self.doubles = 0
        return sum(nums)

def play(game):
    """Main function to simulate the Monopoly game."""
    
    board = Board()
    dice = Dice(game.faces)
    cc_cards = [board.gotoGO, board.gotoJAIL] + 14*[None]
    ch_cards = [board.gotoGO, board.gotoJAIL, board.gotoC1, board.gotoE3,
                board.gotoH2, board.gotoR1, board.nextRR, board.nextRR,
                board.nextU, board.back3] + 6*[None]
    shuffle(cc_cards)
    shuffle(ch_cards)
    cc_deck = cycle(cc_cards)
    ch_deck = cycle(ch_cards)

    counts = 40*[0]

    for i in range(game.turns):
        # Roll the dice and advance
        roll = dice.roll()
#        print "Rolled {}, total of {} doubles".format(roll, dice.doubles)
            
        if dice.doubles == 3:
            board.gotoJAIL()
            dice.doubles = 0
#            print "3 Doubles! Go to jail!"
        
        else:
            for i in range(roll):
                board.advance()
            
            # Need to evaluate Chance first because there is a possibility of
            # moving from CH3 to CC3 with ch card 10
            if board.square in board.CH:
#                print "Drawing Chance at {}".format(board.square)
                card = ch_deck.next()
                if card != None:
                    card()
            
            if board.square in board.CC:
#                print "Drawing Community Chest at {}".format(board.square)
                card = cc_deck.next()
                if card != None:
                    card()
                    
            elif board.square == board.G2J:
#                print "Go to jail!"
                board.gotoJAIL()
        
        counts[board.square] += 1
#        print "Ended turn at {}".format(board.square)
    
    return counts
        
def add_counts(counts):
    sum_counts = [0]*len(counts[0])
    for i in range(len(counts[0])):
        for l in range(len(counts)):
            sum_counts[i] += counts[l][i]
    return sum_counts

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("d", type=int, help="Die size")
    parser.add_argument("n", type=int, help="Number of turns")
    args = parser.parse_args()
    die_faces = args.d
    total_turns = args.n
    
    time_start = datetime.now()
    num_games = cpu_count()
    game_turns = total_turns/num_games
    actual_turns = game_turns*num_games

    print("Playing a total of {:,} turns in {} games with {}-sided dice..."
          .format(actual_turns, num_games, die_faces))
    
    games = [Game(die_faces, game_turns)]*num_games
    pool = Pool()
    counts = pool.map(play, games)
    pool.close()
    pool.join()
    
    totals = add_counts(counts)
    
    popular = 3*[None]
    percents = 3*[None]
    for i in range(3):
        percents[i] = float(max(totals))/actual_turns
        popular[i] = totals.index(max(totals))
        totals[totals.index(max(totals))] = 0
        
    time_end = datetime.now()
    time_elapsed = (time_end - time_start).total_seconds()
    print("Finished in {} seconds".format(time_elapsed))
        
    print("Most popular squares: {} ({:.2%}), {} ({:.2%}), and {} ({:.2%})"
          .format(popular[0], percents[0], popular[1], percents[1], popular[2],
          percents[2]))
    print("Modal string: {:0>2}{:0>2}{:0>2}".format(popular[0], popular[1],
                                                       popular[2]))