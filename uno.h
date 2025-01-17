
#ifndef UNO
#define UNO

/* include libraries */
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

/* define DEBUG running mode */
#define DEBUG

using namespace std;

/* the enum that contains colors that can be attributed to a Card */
enum ColorEnum
{
    red,
    green,
    blue,
    yellow,
    none
};

/* enum that contains values that can be attributed to a Card */
enum ValueEnum
{
    zero,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    skip,
    reverse,
    drawTwo,
    wild,
    wildFour,
    nullable,
    any
};

/* class that represents a Card */
class Card{

public:
    /* a Card will be defined by a value and a color */
    ValueEnum value;
    ColorEnum color;

    /* constructor for Cards */
    Card(ColorEnum c, ValueEnum v);

    /* constructor for nullable card */
    Card();

    /* destructor of Card class */
    ~Card();

    /* display the content of a card */
    void display() const;
};

/* class that represents a Deck */
class Deck {

    /* a Deck contains an array of cards */
    vector<Card> cards;

    /* randomly shuffles the cards */
    void shuffle();

public:

    /* constructor for Deck */
    Deck();

    /* destructor of Deck class */
    ~Deck();

    /* draws the next Card in line */
    Card draw();

    /* check if the deck is empty */
    bool isEmpty();

    /* prints the content of deck */
    void display();

    /* moves the cards from vector to deck's internal vector */
    void refill(const vector<Card>& v);
};

/* class that represents a Player */
class Player{

    /* and 7 cards in his hand */
    vector<Card> hand;

    /* visualize cards */
    void printHandCards();

public:

    /* a player can finish the game */
    bool finishedGame;

    /* a player can be either human or bot */
    bool isBot;

    /* each player will have a name  */
    string nickname;

    /* constructor fot Player */
    explicit Player(Deck& deck);

    /* destructor of Player class */
    ~Player();

    /* method takes a Card from those in hand and plays it */
    Card playCard(ColorEnum color, ValueEnum value, Deck& deck);

    /* announce UNO */
    bool callUno();

    /* method draws a new Card from Deck */
    void drawCard(Deck& d);
};

/* class that represents a Game */
class Game{

    /* a game will have 2 players */
    Player player1, player2;

    /* deck full of 108 cards */
    Deck deck;

    /* vector of the cards used (placed on table) */
    vector<Card> usedCards;

    /* the current card */
    Card currentCard;

    /* card draw and play pattern */
    bool isClockwise;

    /* check for initialized data integrity */
    bool checkIntegrity();

    /* advances the game through the rounds */
    void round();

    /* makes the next move of the player */
    void makeMove(Player& player);

    /* search for any winners */
    bool foundWinner();

public:

    /* constructor of Game class */
    Game(const Deck& d, const Player& p1, const Player& p2);

    /* destructor of Game class */
    ~Game();

    /* initiates a game */
    void start();

};

#endif
