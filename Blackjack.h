#pragma once
#include "CardEngine.h"
Deck cards;
namespace blackjack {

std::vector<int> DealerHand; //stores the value of the Dealer's hand for a given round.
std::vector<int> PlayerHand; //stores the value of the Player's hand for a given round.
std::vector<int> DealerDeal;

//Handles the logic of the Dealer's hand, generating a random card, adding it to the Dealer's hand, storing its value into
//DealerHand, and storing the card number itself into DealerDeal so it can be reprinted after Player's turn.
//
	void Dealer() {
		int dealt = cards.deal();
		cards.printcard(dealt, 'd');
		DealerHand.push_back(cards.value(dealt));
		DealerDeal.push_back(dealt);
		return;

	}
//Like the above function, this handles the logic of the players hand. 
//Seeing as the players hand does not need to be displayed
//multiple times in different rows in a given round, there is no player equivalent of DealerDeal. 
//
	void Player() {
		int dealt = cards.deal();
		cards.printcard(dealt, 'p');
		PlayerHand.push_back(cards.value(dealt));
		return;
	}
//Clears the vectors holding the values of previous turn. Effectively a discard, as well as bringing the cursor down
//to the next position.
//
	void FreshHand() {
		PlayerHand.clear();
		DealerHand.clear();
		DealerDeal.clear();
		cards.newhand();
		return;
	}
//Checks the value of the Player's hand. Effectively a neutered version of the already nauseating DealerWinCheck.
//
//
	int PlayerWinCheck() {
		int PlayerCheck = cards.handvalue(PlayerHand);
		if (PlayerCheck == 21) { return 1; }
		if (PlayerCheck > 21) { return 2; }
		if (PlayerCheck < 21) { return 3; }
		else return 0;
	}
//This is implemented rather poorly, but it does do the job. It compares both compares the value of the Dealer's current
//hand to not only the cardinal value (21) but also to the Player's own hand. If the difference in value to 21 from the 
//Dealer's own hand is less than that of the value of the Player's without exceeding that cardinal value (or busting)
//then the Dealer is considered the winner. This does not force the Dealer to hit or stand on certain values, which along
//with forcing the Ace to only be 11 eliminates much of the strategy of the game.
	int DealerWinCheck() {
		int DealerCheck = cards.handvalue(DealerHand);
		if (DealerCheck == 21) { return 1; }
		if (DealerCheck > 21) { return 2; }
		if (DealerCheck < 21 && ((21-DealerCheck) < (21 - cards.handvalue(PlayerHand)))) {return 4;}
		if (DealerCheck < 21) { return 3; }
		else return 0;
	}
//Deals two cards to both sides at the beginning of the game
//
//
	void SetTable() {
		Dealer();
		Dealer();
		cards.newhand();
		Player();
		Player();
		return;
	}
//Calculates the value of Player's hand after every card is dealt, and prompts the Player to hit or stay until 
//they stay, bust or hit 21. 
//
	int PlayerTurn() {
		int choice = 0;
		cards.printprompt(1);
		std::cin >> choice;
		while (choice == 1) {
			Player();
			int check = PlayerWinCheck();
			if (check == 1) {
				return 1;
			}
			else if (check == 2) {
				cards.printprompt(2);
				return 2;
			}
			else if (check == 3) {
				cards.printprompt(1);
				std::cin >> choice;
			}

		}
	}
//Reprints the first two cards in the Dealer's hand and checks the value of the Dealer's hand. 
//Should the value of the hand
//checked in DealerWinCheck indicate a winning state, it will exit. 
//Otherwise it will loop through and the Dealer hit until 
//it meets a win condition or busts.
	int DealerTurn() {
		cards.printcard(DealerDeal.at(0),'d');
		cards.printcard(DealerDeal.at(1), 'd');
		int check = DealerWinCheck();
		int choice = check;
		while (choice == 3) {
			check = DealerWinCheck();
			if (check == 2) {
				cards.printprompt(3);
				return 2;
			}
			else if (check == 1) {
				cards.printprompt(4);

				return 1;
			}
			else if (check == 4) {
				cards.printprompt(4);
				return 1;
			}
			else if (check == 3) { 
				Dealer();
				choice = 3;
			}
		}
		cards.printprompt(4);

		return 0;
	}
//Both sides are dealt, the Player is dealt until he busts or stays. 
//If the player busts the round ends, while if they hits 21 or stays
//they will have to wait for the Dealer's turn. 
//All ties go to the dealer, and after the Dealer ends the round is over.
//
	int Blackjack() {
		SetTable();
		if (PlayerTurn() == 2) {
			FreshHand();
			return 0; }

		cards.newhand();
		DealerTurn();
		FreshHand();
		return 0;
	}
}






