#pragma once
#ifndef _deck_H_
#define _deck_H_
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>
#include <SFML/Graphics.hpp>


using  namespace std;


int getRandomNumber(int low, int high);
int CardValue(int card);
int getTopCard(int deck[]);
int getHandValue(const int hand[]);
bool playAnotherHand(char&);
bool userWantsToDraw(char&);
void initializeDeck(int deck[]);
void dumpDeck(int deck[], int size);
void shuffle(int deck[], int size);
void ShowCard(int card);
void showCards(const int cards[], int numCards, bool hideFirstCard);
void whoWins(const int pHand[], const int dHand[]);
void checkBust(const int pHand[], const int dHand[], char Play);
void blackJack(const int pHand[], const int dHand[], char Play);
void naturalBlackJack(const int pHand[], const int dHand[], char Play);
void playOneHand();
void scoreBoard(const int pHand[], const int dHand[]);
void backdoorKenny(const int hand[]);
void checkSoftOrHard(int pHand[]);
void softOrHardAI(int dHand[], int pHand[]);
void addToHand(int hand[], int cardToAdd);
void hitUntilStand(int dHand[], int deck[], int pHand[]);

int screen_width = 1024;
int screen_height = 512;
int card_width = 85;
int card_height = 128;
int hhh = 1024 / screen_width;


sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "BlackJack");

//game
void lol() {
	window.setFramerateLimit(60);
	sf::Event event;
	while (window.isOpen())
	{
		
		while (window.pollEvent(event))
		{
			cout <<"1";
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
		}
		


		sf::Event::MouseButtonPressed;
		playOneHand();
	}
}

void ttt(string h, int x, int y)
{
	sf::Texture texture;
	texture.loadFromFile(h);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	//sprite.setTextureRect(sf::IntRect(0, 0, card_width, card_height));
	sprite.setPosition(sf::Vector2f(x, y));
	window.draw(sprite);
	window.display();
}

int topCard = 0;
float win = 1.00;
int level;
int xxx = 343;
int yyy = 453;

int* u = &xxx;
int* i = &yyy;

//Основное действо игры
void playOneHand()
{
	char Play = 'N';
	do
	{
		sf::Vector2f size(screen_width, screen_height);
		window.clear(sf::Color(255, 255, 255));
		sf::Texture texture;
		texture.loadFromFile("table1.png");
		sf::Sprite sprite1;
		sprite1.setTexture(texture);
		sprite1.setPosition(sf::Vector2f(0, 0));
		window.draw(sprite1);
		//Declare local variable
		char Draw = 'H';
		int deck[52];
		initializeDeck(deck);
		shuffle(deck, 51);
		int pHand[10] = { 0 };
		int dHand[10] = { 0 };
		//Первый ход
		addToHand(pHand, getTopCard(deck));
		addToHand(dHand, getTopCard(deck));
		addToHand(pHand, getTopCard(deck));
		addToHand(dHand, getTopCard(deck));
		/*cout << "//////////////////////////////////////////////////////////" << endl;
		cout << "\n" << endl;
		cout << "The Dealer shuffled and dealt you each your cards. ";
		cout << "\n" << endl;*/
		naturalBlackJack(pHand, dHand, 'y');
		blackJack(pHand, dHand, 'Y');
		//cout << "Your hand:" << endl;
		xxx = 453;
		yyy = 343;
		showCards(pHand, 10, false);
		xxx = 386;
		yyy = 118;
		//cout << "\n\nDealer's hand:" << endl;
		showCards(dHand, 10, true);
		sf::Texture bu1;
		bu1.loadFromFile("cards\\hit.png");
		sf::Sprite hit;
		hit.setTexture(bu1);
		hit.setTextureRect(sf::IntRect(0, 0, 100, 150));
		hit.setPosition(sf::Vector2f(280, 220));
		window.draw(hit);
		window.display();
		sf::Texture bu2;
		bu2.loadFromFile("cards\\stand.png");
		sf::Sprite stand;
		stand.setTexture(bu2);
		stand.setTextureRect(sf::IntRect(0, 0, 100, 150));
		stand.setPosition(sf::Vector2f(280, 220));
		window.draw(stand);
		window.display();
		int zxc1, zxc2;
		zxc1 = sf::Mouse::getPosition(window).y;
		zxc2 = sf::Mouse::getPosition(window).x;
		/*do
			if ((880 <= zxc2 <= 980) && (220 <= zxc1 <= 370) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				cout << "\nButton pressed\n" << sf::Mouse::getPosition(window).y <<"\n" << sf::Mouse::getPosition(window).x << endl;
			}
		
		while ((window.isOpen()) == true && (880 < sf::Mouse::getPosition(window).x < 980) && (220 < sf::Mouse::getPosition(window).y < 370));*/

		checkSoftOrHard(pHand);
		while (userWantsToDraw(Draw))
		{
			addToHand(pHand, getTopCard(deck));
			cout << "The Dealer dealt you another card.\n" << endl;
			cout << "Your hand:" << endl;
			showCards(pHand, 10, false);
			checkSoftOrHard(pHand);
			checkBust(pHand, dHand, 'y');
			blackJack(pHand, dHand, 'Y');
		}
		hitUntilStand(dHand, deck, pHand);
		cout << endl;
		checkBust(pHand, dHand, 'Y');
		blackJack(pHand, dHand, 'Y');
		whoWins(pHand, dHand);
		cout << endl;
		cout << "Winnings multiplier: " << win << endl;

	} while (playAnotherHand(Play));
}

//Создание колоды
void initializeDeck(int deck[])
{
	int Rank = 101;
	int i = 0;
	//Hearts
	for (i = 0; i <= 13; i++)
	{
		deck[i] = Rank++;
	}
	//Diamonds
	for (i = 13; i <= 26; i++)
	{
		deck[i] = Rank++ + 100 - 14;
	}
	//Clubs
	for (i = 26; i <= 39; i++)
	{
		deck[i] = Rank++ + 200 - 28;
	}
	//Spades
	for (i = 39; i <= 51; i++)
	{
		deck[i] = Rank++ + 300 - 42;
	}
}

//Раскидывает карты по колоде
void shuffle(int deck[], int size)
{

	for (int i = 0; i < 500; i++)
	{
		int T1 = 0;
		int R1 = getRandomNumber(0, size);
		int R2 = getRandomNumber(0, size);

		T1 = deck[R1];
		deck[R1] = deck[R2];
		deck[R2] = T1;
	}
}

//Показывает карту и её масть
void ShowCard(int card)
{
	string a = "cards\\";
	if (card == 0) {}
	//Define Suits.
	else
	{
		//Hearts
		if ((card >= 101) && (card <= 114))
		{
			a = a + "Herth\\";
		}

		//Diamonds
		else if ((card >= 201) && (card <= 214))
		{
			a = a + "Diam\\";
		}

		//Clubs
		else if ((card >= 301) && (card <= 314))
		{
			a = a + "Club\\";
		}

		//Spades
		else if ((card >= 401) && (card <= 414))
		{
			a = a + "Spade\\";
		}
	}

	//Show nothing for non cards (ie.0)
	if (card == 0)
	{
		cout << "";
	}
	//Define Ranks.
	else
	{
		switch (card % 100)
		{
		case 1:
			a = a + "14.png";
			break;
		case 11:
			a = a + "11.png";
			break;
		case 12:
			a = a + "12.png";
			break;
		case 13:
			a = a + "13.png";
			break;
		case 14:
			a = a + "14.png";
			break;
			//For non-face cards, just use their 10s value as rank.
		default:
			a += to_string(card % 100);
			a += ".png";
		}
	} 
	ttt(a, xxx, yyy);
	xxx += 43;
	cout << a << endl;
}

//Вывод карт игроков на стол
void showCards(const int deck[], int numCards, bool hideFirstCard)
{
	if (hideFirstCard)
	{
		sf::Texture texture;
		texture.loadFromFile("cards\\card-back.png");
		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, card_width, card_height));
		sprite.setPosition(sf::Vector2f(453, 343));
		window.draw(sprite);
		window.display();

	}
	else
	{
		ShowCard(deck[0]);
		//cout << " ";
	}
	for (int i = 1; i < numCards; i++)
	{
		if (deck[i] != 0)
		{
			ShowCard(deck[i]);
			//cout << " ";
		}
		else
		{
			//cout << "";
		}
	}
}

//Проверка доски и кол-ва очков карт
void dumpDeck(int deck[], int size)
{

	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << ".) " << deck[i] << endl;
	}
}

//Выбор рандомной карты из колоды
int getRandomNumber(int low, int high) {
	static bool firstTime = true;
	int randNum;


	if (firstTime) {
		srand(static_cast<unsigned int>(time(NULL)));
		firstTime = false;
	}


	randNum = rand() % (high - low + 1) + low;

	return randNum;
}

//Проверка на кол-во очков карты
int CardValue(int card)
{

	int cardVal;

	switch (card % 100)
	{
	case 1:
		cardVal = 11;
		break;
	case 11:
	case 12:
	case 13:
		cardVal = 10;
		break;
	case 14:
		cardVal = 1;
		break;

	default:
		cardVal = (card % 100);
	}
	return cardVal;
}

//Получить первую карту на столе
int getTopCard(int deck[])
{

	for (int i = 0; i < 51; i++)
	{

		if (deck[i] != 0)
		{

			topCard = deck[i];
			deck[i] = 0;
			return topCard;
		}
	}
}

//Берем карту в руки
void addToHand(int hand[], int cardToAdd)
{

	for (int i = 0; i < 9; i++)
	{

		if (hand[i] == 0)
		{

			hand[i] = cardToAdd;
			break;
		}
	}
}

//Лоогика бота
void hitUntilStand(int dHand[], int deck[], int pHand[])
{

	for (int i = 0; i < 9; i++)
	{


		if (level == 2)
		{

			for (int i = 0; i < 9; i++)
			{

				if (CardValue(dHand[i]) == 11)
				{

					dHand[i] = dHand[i] + 13;
				}
			}
		}
		else;
		if (getHandValue(dHand) < 17)
		{
			if (level == 1)
			{
				addToHand(dHand, getTopCard(deck));
			}


			else if (level == 2)
			{
				addToHand(dHand, getTopCard(deck));
				softOrHardAI(dHand, pHand);
			}
		}
		else
		{
			if (i == 0)
			{
				cout << "The Dealer stands." << endl;
				break;
			}
			else if (i == 1)
			{
				cout << "The Dealer hit a card and stands." << endl;
				break;
			}
			else
			{
				cout << "The Dealer hit " << i << " cards and stands." << endl;
				break;
			}
		}
		if (level == 1);
		else if (level == 2)
		{
			softOrHardAI(dHand, pHand);
		}
	}
}

//Получени счета одной из рук
int getHandValue(const int hand[])
{
	int addCardValues = 0;
	for (int i = 0; i < 9; i++)
	{
		addCardValues = addCardValues + CardValue(hand[i]);
	}
	return addCardValues;
}

//Смена карт игрока
bool playAnotherHand(char& Play)
{
	cout << endl << "\nWould you like to play another hand? (Y/N) ";
	cin >> Play;
	cout << "\n" << endl;
	if (Play == 'y' || Play == 'Y')
	{
		lol();
		*u = 900;
		*i = 370;
		return (true);
	}
	else
	{
		exit(0);
		return (false);
	}
}

//Берем карту игроку при его желании
bool userWantsToDraw(char& Draw)
{
	cout << endl << "\nWould you like to hit or stand? (H/S) ";
	cin >> Draw;
	cout << "\n";
	if (Draw == 'h' || Draw == 'H')
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

//Проверка кто победил из двух игроков
void whoWins(const int pHand[], const int dHand[])
{
	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);
	//Вывод счета игроков
	scoreBoard(pHand, dHand);
	if ((playerScore < 22)
		&& (playerScore > dealerScore)
		|| ((dealerScore > 21)
			&& (playerScore < 22)))
	{
		cout << "\n";
		cout << "You win!" << endl;
		win++;
	}
	else
	{
		if (playerScore == dealerScore)
		{
			cout << "\n";
			cout << "Push in the Dealer's favor. 0:1 payout." << endl;
		}
		else
		{
			cout << "\n";
			cout << "You lose." << endl;
			win--;
		}
	}
}

//Проверка на то, больше ли 21 очка у одного из игроков или нет
void checkBust(const int pHand[], const int dHand[], char Play)
{
	//Описываем локальный счет
	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);
	//Проверка на проигрыш игрока
	//Вывод сообщения в случае проигрыша, предложение сыграть ещё раз
	if (playerScore > 21)
	{
		cout << "You bust with " << getHandValue(pHand) << " points." << endl;
		cout << "\n" << endl;
		win--;
		cout << "Winnings multiplier: " << win << endl;
		playAnotherHand(Play);
	}
	//Проврка на проигрыш бота
	//Вывод сообщения в случае победы, предложение сыграть ещё раз
	else if (dealerScore > 21)
	{
		scoreBoard(pHand, dHand);
		cout << "\n" << endl;
		cout << "The Dealer went bust. You Win!" << endl;
		cout << "\n" << endl;
		win++;
		cout << "Winnings multiplier: " << win << endl;
		playAnotherHand(Play);
	}
}

//Проверка на Кенни
void backdoorKenny(const int hand[])
{
	if ((CardValue(hand[0]) % 100 == 10) && (CardValue(hand[1]) % 100 == 11))
	{
		cout << "\n\n";
		cout << "You pulled a Backdoor Kenny!\n" << endl;
		cout << "Win an additional 1:4 payout\n" << endl;
		win = win + .25;
		cout << "Winnings multiplier: " << win << endl;
	}
}

//Проверка на ничью
void blackJack(const int pHand[], const int dHand[], char Play)
{

	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);

	if ((playerScore == 21) && (dealerScore != 21))
	{

		cout << "\n\n";
		scoreBoard(pHand, dHand);
		cout << "\n";
		cout << "Blackjack! You win a 3:2 payout." << endl;
		win = win + 1.5;
		cout << "\n";
		cout << "Winnings multiplier: " << win << endl;
		backdoorKenny(pHand);
		playAnotherHand(Play);
	}

	else if ((playerScore == 21) && (dealerScore == 21))
	{

		scoreBoard(pHand, dHand);
		cout << "\n";
		cout << "The Dealer and you both got Blackjack. Push in your favor at 1:1 payout!" << endl;
		win++;
		cout << "\n";
		cout << "Winnings multiplier: " << win << endl;
		playAnotherHand(Play);
	}
}

//Проверка на победу одного из игроков по 21 очков
void naturalBlackJack(const int pHand[], const int dHand[], char Play)
{
	int playerScore = getHandValue(pHand);
	int dealerScore = getHandValue(dHand);
	if ((playerScore == 21) && (dealerScore != 21))
	{
		scoreBoard(pHand, dHand);
		cout << "\n";
		cout << "Natural Blackjack! You win a 3:2 payout.";
		win = win + 1.5;
		backdoorKenny(pHand);
		playAnotherHand(Play);
	}
}

//Вывод информации о счете и картах
void scoreBoard(const int pHand[], const int dHand[])
{
	cout << "Player hand: ";
	//	showCards(pHand, 10, false);
	cout << " (" << getHandValue(pHand) << "pts)." << endl;
	cout << "V.S." << endl;
	cout << "Dealer hand: ";
	//	showCards(dHand, 10, false);
	cout << " (" << getHandValue(dHand) << "pts)." << endl;
}

//Проверка на наличие туза и выбор кол-ва очков туза
void checkSoftOrHard(int pHand[])
{

	for (int i = 0; i < 9; i++)
	{

		int checkAce = CardValue(pHand[i]);
		int softOrHard;

		if (checkAce == 1 || checkAce == 11)
		{
			cout << "\n";
			cout << "\nWould you like your Ace to count as 1 or 11 points? (1/11): ";
			cin >> softOrHard;
			if (softOrHard == 1)
			{
				if (checkAce == 11)
					pHand[i] = pHand[i] + 13;
			}
			else if (softOrHard == 11)
			{
				if (checkAce == 1)
				{
					pHand[i] = pHand[i] - 13;
				}
			}
			else if (softOrHard != 1 && softOrHard != 11)
			{

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nPlease enter the number 1 or 11." << endl;
				checkSoftOrHard(pHand);
			}
		}
	}
}

//Настройка сложности Бота
void softOrHardAI(int dHand[], int pHand[])
{
	for (int i = 0; i < 9; i++)
	{
		if (CardValue(dHand[i]) == 1 || CardValue(dHand[i]) == 11)
		{
			if (CardValue(dHand[i]) == 11)
			{
				if (getHandValue(dHand) - CardValue(dHand[i]) + 1 > getHandValue(pHand))
				{
					if (getHandValue(dHand) - CardValue(dHand[i]) + 1 < 22)
					{
						dHand[i] = dHand[i] + 13;
					}
				}
				else if (getHandValue(dHand) > 21)
				{
					dHand[i] = dHand[i] + 13;
				}
			}
			else
			{
				if (getHandValue(dHand) - CardValue(dHand[i]) + 11 > getHandValue(pHand))
				{
					if (getHandValue(dHand) - CardValue(dHand[i]) + 11 < 22)
					{
						dHand[i] = dHand[i] - 13;
					}
				}
			}
		}
	}
}


#endif // !_deck_H_
