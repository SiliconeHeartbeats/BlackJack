#include "Blackjack.h"


int main() {
	int choice = 1;
	int& pchoice = choice;
	while (choice) {
		Cards.shuffle();
		Cards.resetscreen();
		blackjack::Blackjack();
		Cards.printprompt(5);
		int spork;
		std::cin >> spork;
		
		if (spork == 1) {
			pchoice = 1;
			}
		else { pchoice = 0; }
		
	}
	return 0;
}
