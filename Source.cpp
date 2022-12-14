#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <conio.h>

void BJ_BM() {
	printf("				 ___________________________________________\n"
		"				|					    |\n	"
		"			|               BlackJack_BM                |\n"
		"				|___________________________________________|\n\n\n");
}


struct cards {
	int suit;
	int face;
};

int shuff(cards deck[]) {
	srand(time(NULL));
	cards deck_0[52];
	int t;
	int s = 0; 
	int f = 0;

	// init deck of cards in deck_0
	for (int suit = 3; suit < 7; suit++) {

		for (int face = 1; face < 14; face++) {

			cards card;
			card.face = face;
			card.suit = suit;

			if (s == 0) {
				deck_0[f] = card;
				//printf("%d %c\n", deck_0[f].face, deck_0[f].suit);
			}

			else {
				deck_0[f + s * 13] = card;
				//printf("%d %c\n", deck_0[f + s * 13].face, deck_0[f + s * 13].suit);
			}
			f++;
		}
		s++;
		f = 0;
	}
	/*for (int i = 0; i < 52; i++) {
		printf("%d %c\n", deck_0[i].face, deck_0[i].suit);
	}*/
	//shuffle deck_0 into deck -- no need to return an array as deck is defined outside of shuff
	for (int i = 0; i < 52; i++) {

		t = rand() % 52;
		while (deck_0[t].face == 0) {
			t = rand() % 52;
		}
		deck[i] = deck_0[t];
		deck_0[t].face = 0;
	}

	/*for (int i = 0; i < 52; i++) {
		printf("%d %c\n", deck[i].face, deck[i].suit);
	}*/
	return 0;
}



void pick(cards card) {

	switch (card.face) {
	case 1: {printf("\n*******\n");
		printf("*     *\n");
		printf("* %c   *\n", card.suit);
		printf("*   A *\n");
		printf("*     *\n");
		printf("*******\n");
		break;}
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	{   printf("\n*******\n");
		printf("*     *\n");
		printf("* %c   *\n", card.suit);
		printf("*  %d  *\n", card.face);
		printf("*     *\n");
		printf("*******\n");
		break;}
	case 11: {printf("\n*******\n");
		printf("*     *\n");
		printf("* %c   *\n", card.suit);
		printf("*   J *\n");
		printf("*     *\n");
		printf("*******\n");
		break;}
	case 12: {printf("\n*******\n");
		printf("*     *\n");
		printf("* %c   *\n", card.suit);
		printf("*   Q *\n");
		printf("*     *\n");
		printf("*******\n");
		break;}
	case 13: {printf("\n*******\n");
		printf("*     *\n");
		printf("* %c   *\n", card.suit);
		printf("*   K *\n");
		printf("*     *\n");
		printf("*******\n");
		break;}

	}
}

int pcard_value(cards pcards[], int i) {
	char d;
	if (pcards[i - 1].face == 1) {

		printf("\nChoose a value for the Ace.\n\n"
			"Enter 'y' for 11 or 'n' for 1 : ");
		do { d = getchar(); } while (d != 'y' && d != 'n');

		if (d == 'y') {
			printf("\nYou chose 11 for the Ace value.\n\n");
			return 11;
		}
		else if (d == 'n') {
			printf("\nYou chose 1 for the Ace value.\n\n");
			return 1;
		}
	}
	//printf("%d face\n", pcards[i].face);
	// King, Queen, and Jester = 10pts
	if (pcards[i - 1].face > 10) {
		return 10;
	}

	else return pcards[i - 1].face;



}

//init computer deck & sum
int b_init(cards bcards[], int i) {

	int card_val = 0;
	if (bcards[i].face == 1) {

		if (card_val <= 10) {
			card_val = 11;
		}
		else {
			card_val = 1;
		}
	}

	else if (bcards[i].face > 10) {
		card_val = 10;
	}

	else {
		card_val = bcards[i].face;
	}

	return card_val;
}



int play(int account) {
	int bet = 0;
	//in case of a BJ:
	int init_bet = 0;
	int src = 1;

	int i;
	int psum = 0;
	int bsum = 0;
	cards pcards[15] = { 0 };
	cards bcards[15] = { 0 };
	cards deck[52];
	char go_on;
	char d;

	//if there is no money left on account
	if (account == 0) {
		printf("You are broke, you have emptied your wallet gambling,\n"
			"you must be proud of yourself haha.\n"
			"You can still play without betting though.\n\n");
		printf("Type anything to continue.\n");

		char cont = '\0';
		while (true) {
			cont = _getch();
			if (cont != '\0') { break; }
		}
		system("cls");
	}
	else {
		printf("The amount of your account is : %d EUR \n\n", account);
		printf("\nType the amount which you want to bet in EUR : ");
		while (src != 0) {
			scanf_s("%d", &bet);
			 
			if (bet <= account) {
				account = account - bet;
				system("cls");
				printf("\n\nYour bet is %d EUR and it is set.		You have %d EUR left in your account\n", bet, account);
				//printf("", account);
				src = 0;
				init_bet = bet;

			}
			else {
				printf("You have %d EUR on your account, please don't bet more than what you own :) \n", account);
			}
		}
	}

	//Melange cartes
	shuff(deck);

	//attribuer les carte
	//for (int i=0; i<52; i +=2){}
	pcards[0] = deck[0];
	pcards[1] = deck[1];
	bcards[0] = deck[2];
	bcards[1] = deck[3];

	//les 2 cartes du joueur
	printf("The Dealer's first card is: ");
	pick(bcards[0]);
	printf("\n\n");
	printf("Your First card is : ");
	pick(pcards[0]);
	printf("Your Second card is : ");
	pick(pcards[1]);
	printf("\n\n");

	//set value of first 2 cards
	psum += pcard_value(pcards, 1);
	psum += pcard_value(pcards, 2);


	// if BJ with first 2 cards
	if (psum == 21) {

		printf("The Sum of your cards is 21, that's a BlackJack\n\n");
		printf("Congratulation you won !\n");
		bet = round(1.5 * bet);
		printf("You earned %d\n\n", (init_bet + bet));

		return bet;
	}

	//choose wether to Double Down or to Draw a card
	int DD = 0;

	//if the player wants to Double Down (== double bet)
	if ((8 < psum) && (psum < 12) && (bet != 0) && (account >= bet)) {
		printf("\n\n"
			"The Sum of your cards is %d, would you like to Double Down ?\n"
			"Enter y or n : ", psum);
		int dub = ' ';
		do { dub = getchar(); } while (dub != 'y' && dub != 'n');

		//if player choses to DD
		if (dub == 'y') {

			DD++;

			account = account - bet;
			bet += bet;
			init_bet += init_bet;
			printf("\nYou Doubled Down, your new bet is %d EUR.\n\n", bet);
			printf("You have %d EUR left in your account\n\n", account);

			pcards[2] = deck[4];
			printf("\nYour 3rd card is :  ");
			pick(pcards[2]);

			psum += pcard_value(pcards, 3);

			// if drawn cards add up to more than 21
			if (psum > 21) {
				printf("\nThe sum of your cards is now : %d\n\n", psum);
				printf("You lost, the sum of your cards is greater than 21 !\n\n");
				//printf("You lost %d EUR\n\n", bet);
				return -bet;
			}

			// if drawn cards add up to a BJ
			else if (psum == 21) {
				printf("\nThe Sum of your cards is 21, that's a BlackJack\n\n");
				printf("Congratulation you won !\n\n");
				bet = round(1.5 * bet);
				printf("You earned %d\n\n", (init_bet + bet));

				return bet;
			}

			else printf("\nThe sum of your cards is now : %d\n\n", psum);
			printf("Type anything to continue.");

			char cont = '\0';
			while (true) {
				cont = _getch();
				if (cont != '\0') { break; }
			}
			printf("\n\n");

		}
		else {
			printf("You chose Not to Double Down. \n\n");
		}
	}

	else {
		printf("The Sum of your cards is : %d\n\n", psum);
	}



	//si le joueur veut une autre carte

	// can Draw a Card only if no Double Down
	if (DD == 0) {
		for (i = 0; i < 13 && psum < 21; i++) {


			char j = ' ';
			printf("Do you want to draw one more card ?\n"
				"Enter y or n : ");

			while (j != 'y' && j != 'n') {
				scanf_s("%c", &j);
			}

			if (j == 'y') {
				pcards[i + 2] = deck[i + 4];
				printf("\nYou drew : ");
				pick(pcards[i + 2]);

				psum += pcard_value(pcards, i + 3);
				// if drawn cards add up to more than 21
				if (psum > 21) {
					printf("\nThe sum of your cards is now : %d\n\n", psum);
					printf("You lost, the sum of your cards is greater than 21 !\n\n");
					//printf("You lost %d EUR\n\n", bet);
					return -bet;
				}

				// if drawn cards add up to a BJ
				else if (psum == 21) {
					printf("\nThe Sum of your cards is 21, that's a BlackJack\n\n");
					printf("Congratulation you won !\n\n");
					//account += 3 * bet;

					bet = round(1.5 * bet);
					printf("You earned %d\n\n", (init_bet + bet));

					return bet;
				}

				else printf("\nThe sum of your cards is now : %d\n\n", psum);
			}
			else {
				printf("\nYou did not draw a card, the sum of your cards is : %d\n\n", psum);
				break;
			}

		}
	}


	// 2 cartes de l'ordi
	printf("Dealer's cards:\n");
	pick(bcards[0]);
	pick(bcards[1]);

	//init first 2 cards of computer deck
	bsum += b_init(bcards, 0);
	bsum += b_init(bcards, 1);
	printf("The sum of the Dealer's cards is now : %d\n", bsum);

	//l'ordi tire tant que bsum n'est pas plus grand que 16
	//i=0;
	for (i = 3; i < 15 && bsum < 17; i++) {

		bcards[i] = deck[i + 17];
		if (i == 3) {
			printf("the Dealer's 3rd card is : \n");
		}

		else {
			printf("the Dealer's %dth card is : \n", i);
		}
		pick(bcards[i]);
		bsum += b_init(bcards, i);

		printf("The sum of the Dealer's cards is now : % d\n\n", bsum);
	}


	//results :
	if (bsum > 21 || psum > bsum)
	{
		printf("\nYou won !\n");
		//account += 2 * bet;
		printf("You earned %d EUR\n\n", (2 * bet));

		return bet;
	}
	else if (psum == bsum)
	{
		printf("\nYou have the same score as the Dealer !\n");
		//account += bet;
		printf("You get your bet back\n\n");

		return 0;
	}
	else if (psum < bsum)
	{
		printf("\nDealer won !\n\n");
		//printf("You lost %d EUR\n\n",bet);

		return -bet;
	}
}




void main() {
	int menu_val = 0;
	int nbr;


	while (menu_val == 0) {

		while (menu_val == 0) {

			printf("				 ___________________________________________\n"
				"				|					    |\n	"
				"			|      Welcome to our  BlackJack_BM         |\n"
				"				|___________________________________________|\n");

			printf("\n                                  Menu : \n"
				"                                1\ Rules\n"
				"                                2\ Play \n"
				"                                3\ About us \n"
				"                                4\ Exit \n\n");

			//scanf_s("%d", &nbr);
			nbr = _getch() - '0';

			switch (nbr) {

			case 1: {
				//rules of BJ
				system("cls");
				BJ_BM();
				printf(
					"The aim of the game is to obtain a higher score than the dealer without passing throught the limit of 21 \n"
					"Ace worth either 1 or 11 points, it depends what you wish.\n"
					"King, Queen and Jack worth 10 points.\n"
					"The others cards worth between 2 and 10, the value correspont to what is attached to the cards drawn.\n\n"
					"At the begining of each game the player select his bet.\n"
					"The Dealer gives 2 cards to each player.\n\n"
					"The player has the choice to demand more cards, to double his bet and receive a new card\n"
					"the player may also do nothing,\n"
					"or leave \n\n");

				char men = '\0';

				printf("Type anything to go back to the main menu.\n");

				while (true) {
					//scanf_s("%c", &men);
					//if (men != '\0') { break; }
					men = _getch();
					if (men != '\0') { break; }
				}

				system("cls");

				break;
			}

			case 2: {
				//play BJ
				system("cls");
				BJ_BM();

				//each session starts with 10 EUR
				int account = 10;
				account += play(account);

				int loop = 0;
				char again;
				printf_s("You have %d EUR left in your account.\n", account);
				printf_s("\n\n\nDo you want to play again ? Enter 'y' or 'n':\n");

				//play again loop
				do {
					scanf_s("%c", &again);
				} while (again != 'y' && again != 'n');

				system("cls");


				while (again == 'y') {

					system("cls");
					BJ_BM();
					printf("\nHere we go again !!\n\n");
					account += play(account);
					printf_s("\nYou have %d EUR left in your account.\n", account);

					printf_s("\nDo you want to play again ? Enter 'y' or 'n':\n");
					do { again = getchar(); } while (again != 'y' && again != 'n');
				}

				system("cls");
				printf("\n\n\n\nYou are cashing out %d EUR\n\n", account);

				char men = '\0';

				printf("Type anything to go back to the main menu.\n");

				while (true) {
					//scanf_s("%c", &men);
					//if (men != '\0') { break; }
					men = _getch();
					if (men != '\0') { break; }
				}

				system("cls");

				break;
			}




			case 3: {
				//about us
				system("cls");
				BJ_BM();

				printf("This game was made are a duo of highly compentent developpers, whose skillset is rarely matched in the field.\n\n"

					"Our team includes among it's members an eminent programmer who came to us \n"
					"from the greatest institutions of Portugal, this respectable man truly is a prodigy, \n"
					"he started coding during a gilded youth in the highest places of the 91' at the early age of barely 4 years old,\n"
					"he is the Great Mr. Brian Catarina-Graca.\n\n"

					"We are also lucky to have teamed up with Mr. Maxime Lorang, another coding mastermind,\n"
					"a virtuoso in his field of judeo-espagno-portugo-italiano-turco-marocaine origin, \n"
					"this young man had a tough upbringing in the difficult red-light suburbs of Neuilly-sur-Seine.\n"
					"He will do anything to get out of the hood.\n\n"

					"These two engineering cracks have joined forces to deliver you an exquisite digital game of blackjack\n"
					"and they hope you shall enjoy it thoroughly.\n\n\n");

				char men = '\0';

				printf("Type anything to go back to the main menu.\n");

				while (true) {
					//scanf_s("%c", &men);
					//if (men != '\0') { break; }
					men = _getch();
					if (men != '\0') { break; }
				}

				system("cls");

				break;
			}

			case 4:
				menu_val = 1;
				break;

			default: {

				//printf("Enter a number between 1 and 4 %c \n", 2);

				system("cls");
			}
			}
		}
	}
}
//enum suit{hearts = 3, diamonds = 4, clubs = 5, spades = 6};
//enum face{ace = 1, y
