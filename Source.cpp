#include <stdio.h>
#include <time.h>
#include <stdlib.h>


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

	switch (card.face)
	{
	case 1:
	{

		printf("l'As de  %c\n", card.suit);

		break;
	}
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	{

		printf("le %2d de %c   \n", card.face, card.suit);
		break;
	}
	case 11:
	{
		printf("le Valet de  %c\n", card.suit);
		break;
	}
	case 12:
	{
		printf("la Reine de  %c\n", card.suit);
		break;
	}
	case 13:
	{
		printf("le Roi de  %c\n", card.suit);
		break;
	}

	}
}

int card_value(cards pcards[], int i) {
	char d;
	if (pcards[i].face == 1) {

		printf("Choisissez une valeur pour  l'As, entrez 'y' pour 11 ou 'n' pour 1 :\n");
		do { d = getchar(); } while (d != 'y' && d != 'n');

		if (d == 'y') {
			printf("Vous avez choisis 11 comme valeur de l'As.\n");
			return 11;
		}
		else if (d == 'n') {
			printf("Vous avez choisis 1 comme valeur de l'As.\n");
			return 1;
		}
	}
	//printf("%d face\n", pcards[i].face);
	// King, Queen, and Jester = 10pts
	if (pcards[i].face > 10) {
		return 10;
	}

	else return pcards[i].face;



}


int b_init(cards bcards[]) {
	//init computer deck & sum

	int temp_sum = 0;
	for (int i = 0; i < 2; i++) {

		if (bcards[i].face == 1) {

			if (temp_sum <= 10) {
				temp_sum += 11;
			}
			else {
				temp_sum += 1;
			}
		}

		else if (bcards[i].face > 10) {
			temp_sum += 10;
		}

		else {
			temp_sum += bcards[i].face;
		}
	}
	printf("La sommes des cartes de l'ordinareur est maintenant de:%d\n\n", temp_sum);
	return temp_sum;
}



int play(void)
{
	int i;
	int psum = 0;
	int bsum = 0;
	cards pcards[5] = { 0 };
	cards bcards[5] = { 0 };
	cards deck[52];
	char go_on;
	char d;


	//Melange cartes
	shuff(deck);

	//attribuer les carte
	pcards[0] = deck[0];
	pcards[1] = deck[1];
	bcards[0] = deck[2];
	bcards[1] = deck[3];

	//les 2 cartes du joueur
	printf("La première carte de l'ordinateur est ");
	pick(bcards[0]);
	printf("\n");
	printf("\n");
	printf("Vous avez tiré ");
	pick(pcards[0]);
	printf("et ");
	pick(pcards[1]);

	for (i = 0; i < 2; i++) {
		//printf("%d psum\n", psum);
		psum += card_value(pcards, i);

		if (psum > 21) {

			printf("La sommes de vos cartes est maintenant de:%d\n\n", psum);
			printf("L'ordinateur a gagné !\n");
			return 0;
		}
		else if (psum == 21) {

			printf("La sommes de vos cartes est maintenant de:%d\n\n", psum);
			printf("Félicitation vous avez gagné!\n");
			return 0;
		}
	}
	printf("La sommes de vos cartes est maintenant de:%d\n\n", psum);

	//si le joueur veut une autre carte

	for (i = 0; i < 3; i++) {
		char j = ' ';
		//printf_s("01 le j c'est le %c", &j);

		printf("Voulez vous une carte de plus ? Entrez y ou n:\n");

		while (j != 'y' && j != 'n') {
			scanf_s("%c", &j);
			//printf_s("02 le j c'est le %c", &j);
		}

		if (j == 'y')
		{
			pcards[i + 2] = deck[i + 4];
			printf("Vous avez tiré ");
			pick(pcards[i + 2]);

			psum += card_value(pcards, i + 2);
			if (psum > 21)
			{
				printf("La sommes de vos cartes est maintenant de:%d\n\n", psum);
				printf("l'ordinateur a gagné !\n");
				return 0;
			}
			else if (psum == 21)
			{
				printf("La sommes de vos cartes est maintenant de:%d\n\n", psum);
				printf("Félicitation vous avez gagné!\n");
				return 0;
			}
			else printf("La sommes de vos cartes est maintenant de:%d\n\n", psum);
		}
		else
		{
			printf("Vous n'avez pas tiré de carte, la somme de vos cartes est de:%d\n\n", psum);
			break;
		}

	}


	// 2 cartes de l'ordi
	printf("Carte de l'ordinateur:\n");
	pick(bcards[0]);
	pick(bcards[1]);

	//init first 2 cards of computer deck
	bsum += b_init(bcards);

	//l'ordi tire tant que bsum n'est pas plus grand que 16
	//i=0;
	for (i = 0; i < 3 && bsum < 17; i++) {

		bcards[i + 2] = deck[i + 7];
		printf("La %deme carte de l'ordinateur est:\n", i + 3);
		pick(bcards[i + 2]);

		if (bcards[i + 2].face == 1)
		{
			if (bsum + 11 <= 21)
			{
				printf("l'ordinateur a choisi l'As valant 11\n");
				bsum = bsum + 11;
				printf("La sommes des cartes de l'ordinareur est maintenant de:%d\n\n", bsum);
			}
			else
			{
				printf("l'ordinateur a choisi l'AS valant 1\n");
				bsum = bsum + 1;
				printf("La sommes des cartes de l'ordinareur est maintenant de:%d\n\n", bsum);
			}
		}
		else
		{
			bsum = bsum + bcards[i + 2].face;
			printf("La sommes des cartes de l'ordinareur est maintenant de:%d\n\n", bsum);
		}
	}





	if (bsum > 21 || psum > bsum)
	{
		printf("Vous gagnez!\n");
		return 0;
	}
	else if (psum == bsum)
	{
		printf("Vous avez le meme score que l'ordinateur!\n");
		return 0;
	}
	else if (psum < bsum)
	{
		printf("l'ordinateur gagne!\n");
		return 0;
	}

	return 0;
}






void main() {

	int menu_val = 0;
	int nbr;

	while (menu_val == 0) {
		printf("Bienvenue dans notre jeu BlackJack!\n"
			"1\ Consulter les règles du jeux\n"
			"2\ Jouer au BlackJack \n"
			"3\ A propos de nous \n"
			"4\ Quitter le menu \n");

		scanf_s("%d", &nbr);

		switch (nbr) {

		case 1:
			system("CLS");
			printf("Les règles du jeu sont blebblebleblelble\n"
				"Le but est d'obtenir un score supérieur à celui du croupier sans dépasser le score de 21\n"
				"L’as vaut entre 1 et 11 points selon ce que vous avez décidé au départ. La valeur ne peut changer en cours de partie.\n"
				"Le roi, la reine et le valet valent 10 points.\n"
				"Les autres cartes entre 2 et 10, la valeur correspondant à ce qui est affiché sur la carte.\n\n"
				"Au début de chaque tour le joueur selectionne sa mise.\n"
				"Le croupier distribue ensuite 2 cartes à chaque joueur.\n\n"
				"Le joueur à le choix de demander plus de cartes, \n"
				"de doubler sa mise et de recevoir une carte supplémentaire,\n"
				"d'effectuer un split: si le joueur possède une paire il peut séparer son jeu\n"
				"en deux mains indépendantes,\n"
				"ne rien faire,\n"
				"ou encore abandonner\n\n");
			break;

		case 2: {
			system("CLS");
			play();

			int loop = 0;
			char again;
			printf_s("\nVoulez vous jouer à nouveau? Entrez 'y' ou 'n':\n");

			do {
				scanf_s("%c", &again);
			} while (again != 'y' && again != 'n');


			while (again == 'y') {

				system("CLS");
				printf("\nEt c'est reparti!\n\n");
				play();

				printf_s("\nVoulez vous jouer à nouveau? Entrez 'y' ou 'n':\n");
				do { again = getchar(); } while (again != 'y' && again != 'n');
			}
			system("CLS");
			break;
		}




		case 3:
			system("CLS");
			printf("nous sommes une ékip de développeurs compétents, et même hors normes\n"
				"notre team compte parmis ses membres l'éminent programmeur venu tout droit des\n"
				"plus grandes institutions du Portugal,\n"
				"après une enfance dorée dans les hautes sphères du 91 il s'est lancé dans le code dès ses 4 ans et demi,\n"
				"j'ai nommé le grand Brian Catarina-Graca.\n"
				"Nous comptons également parmis nous Maxime Lorang, un autre développeur de talent,\n"
				"un vraie génie dans son domaine, d'origine judéo-espagno-portugo-italiano-turco-marocaine, \n"
				"ce jeune homme a grandit dans les banlieues chaudes de neuilly-sur-Seine, il est prêt à tout pour quitter le quartier\n");
			break;

		case 4:
			menu_val = 1;
			break;

		}
	}
}


//enum suit{hearts = 3, diamonds = 4, clubs = 5, spades = 6};
//enum face{ace = 1, 
