#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <numeric>
#include <windows.h>
class Deck
{
	int k = { 0 };				
	int j = { 0 };				
	std::vector<int> usedcards; //Tracks all cards that have previously been played, checked by cardgen to prevent 'redraws'


public:
//Assigns each of the 52 cards in a standard deck a number value. The 4 suits each contain 13 unique cards, and are grouped
//here so that an Ace of Spades has the same value as an Ace of Clubs. Aces are high.
	int value(int card) {

		switch (card) {
		case 0: case 13: case 26: case 39:
			return 11;
			break;
		case 1: case 14: case 27: case 40:
			return 2;
			break;
		case 2: case 15: case 28: case 41:
			return 3;
			break;
		case 3: case 16: case 29: case 42:
			return 4;
			break;
		case 4: case 17: case 30: case 43:
			return 5;
			break;
		case 5: case 18: case 31: case 44:
			return 6;
			break;
		case 6: case 19: case 32: case 45:
			return 7;
			break;
		case 7: case 20: case 33: case 46:
			return 8;
			break;
		case 8: case 21: case 34: case 47:
			return 9;
			break;
		case 9: case 22: case 35: case 48:
		case 10: case 23: case 36: case 49:
		case 11: case 24: case 37: case 50:
		case 12: case 25: case 38: case 51:
			return 10;
			break;
		default:
			std::cout << "Error";
			break;

		}
		return 0;
	}
//calculates the value of a given hand. 
//
	int handvalue(std::vector<int>& h4nd) {
	
		int handval{ 0 };
		std::vector<int> hand = h4nd;
		handval = std::accumulate(hand.begin(), hand.end(), 0);
		return handval;
}
//Generates a random integer between 0 and 51 using the Mersenne Twister algorithm. 

	int gencard() {

		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<>	distr(0, 51);
		int deal = distr(eng);
		return deal;
	}
//Takes an int from gencard and checks usedcards to make sure it is not already on the table. generates a new card
//if a duplicate is found.
	int deal() {
		int d3al = gencard();
		int& deal = d3al;
		for (int i = 0; i < usedcards.size(); i++) {
			if (deal == usedcards.at(i)) {
				deal = gencard();
				i = -1;
			}
		}
		usedcards.push_back(deal);
		return deal;
	}
//Assigns four groups of 13 integers a suit, one for every rank in that suit. These values
//coincide with value and face to ensure consistency, sourced from a simple matrix I drew when I was barely awake.
	char suit(int card) {

		switch (card) {
		case 0: case 1: case 2: case 3:
		case 4: case 5: case 6: case 7:
		case 8: case 9: case 10: case 11:
		case 12:
			return 'S';
			break;
		case 13: case 14: case 15: case 16:
		case 17: case 18: case 19: case 20:
		case 21: case 22: case 23: case 24:
		case 25:
			return 'H';
			break;
		case 26: case 27: case 28: case 29:
		case 30: case 31: case 32: case 33:
		case 34: case 35: case 36: case 37:
		case 38:
			return 'C';
			break;
		case 39: case 40: case 41: case 42:
		case 43: case 44: case 45: case 46:
		case 47: case 48: case 49: case 50:
		case 51:
			return 'D';
			break;
		default:
			std::cout << "Error";
			return '0';
			break;
		}
	}
//Much like value, assigns a face to every four cards. Returns this value as a string as opposed to a char to ensure 
//consistent printing on the 'card' itself
	std::string face(int card) {

		switch (card) {
		case 0: case 13: case 26: case 39:
			return " A";
			break;
		case 1: case 14: case 27: case 40:
			return " 2";
			break;
		case 2: case 15: case 28: case 41:
			return " 3";
			break;
		case 3: case 16: case 29: case 42:
			return " 4";
			break;
		case 4: case 17: case 30: case 43:
			return " 5";
			break;
		case 5: case 18: case 31: case 44:
			return " 6";
			break;
		case 6: case 19: case 32: case 45:
			return " 7";
			break;
		case 7: case 20: case 33: case 46:
			return " 8";
			break;
		case 8: case 21: case 34: case 47:
			return " 9";
			break;
		case 9: case 22: case 35: case 48:
			return "10";
			break;
		case 10: case 23: case 36: case 49:
			return " J";
			break;
		case 11: case 24: case 37: case 50:
			return " Q";
			break;
		case 12: case 25: case 38: case 51:
			return " K";
			break;
		default:
			std::cout << "Error";
			return "X";
			break;

		}

	}
//creates a COORD struct, allowing direct manipulation of the cursor in the console. This is critical for the below
//printcard function
	void gotoxy(int x, int y)
	{
		COORD c = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	}

//Uses the previous function to print cards side by side in a consistent manner, while allowing these cards to
//be unique. Every new card in the same hand adds to k, which moves the cursor along the horizontal axis and prints 
//the next card by its side. Every new hand increases j, which resets k and moves the cursor and prints 
//the next hand below the previous.

	void printcard(int card, char side) {



		std::string fac3 = face(card);
		char su1t = suit(card);
		gotoxy(8 * k, (8 * j + 0));
		std::cout << "#######";
		gotoxy(8 * k, (8 * j + 1));
		std::cout << "#" << fac3 << su1t << "  #";
		gotoxy(8 * k, (8 * j + 2));
		std::cout << "#     #";
		gotoxy(8 * k, (8 * j + 3));
		std::cout << "#     #";
		gotoxy(8 * k, (8 * j + 4));
		std::cout << "#     #";
		gotoxy(8 * k, (8 * j + 5));
		std::cout << "#  " << fac3 << su1t << "#";
		gotoxy(8 * k, (8 * j + 6));
		std::cout << "#######";
		
		gotoxy(0, (8 * j + 7));
		if (side == 'd') {
			std::cout << "House";
		}
		else std::cout << "Your Hand";
		gotoxy(0, (8 * j + 14));
		k++;
		return;
	}
//Uses the gotoxy function to make sure the text prompts are legible and dont conflict with card printing. Prints	
//either the game state or the prompt for Player input.
	void printprompt(int choice) {
		switch (choice) {
		case 1:
			gotoxy(0, (8 * j + 8));
			std::cout << "Hit or stay? Enter 1 to hit, or 2 to stay: ";
			break;
		case 2:
			gotoxy(0, (8 * j + 9));;
			std::cout << "You've gone and busted my good man";
			break;
		case 3:
			gotoxy(0, (8 * j + 9));
			std::cout << "You've won!";
			break;
		case 4:
			gotoxy(0, (8 * j + 9));
			std::cout << "The House has won";
			break;
		case 5:
			gotoxy(0, (8 * j + 9));
			std::cout << "Play Again? 1 for yes, anything else for no:";
		}
		
		return;
	}
//Clears the usedcards vector, allowing cards in previous hands to be dealt again.
//
	void shuffle() {
		usedcards.clear();
		return;
	}
//Effectively moves the cursor to change the hand. When the Dealer's turn is over, newhand is called and the cursor
//is moved over and down so that the next hand, the Players, doesnt visually clash.
	void newhand() {
		k = 0;
		j++;
		j++;
	}
//Clears the screen and resets the cursor.
//
	void resetscreen() {
		gotoxy(0, 0);
		for (int i = 0; i < 101; i++) {
			for (int j = 0; j < 101; j++) {
				std::cout << " ";
			}
		}
		k = 0;
		j = 0;

	}
};



