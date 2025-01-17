#include "uno.h"

/*
 *
 *    Implementation for methods in class CARD:
 *
 */

/* constructor: */
Card::Card(ColorEnum c, ValueEnum v) : value(v), color(c) {}

/* empty card constructor */
Card::Card()
{
    ValueEnum v = nullable;
    ColorEnum c = none;
    value = v;
    color = c;
}

/* destructor: */
Card::~Card() = default;

/* function: colorToString() -> convert ColorEnum to string */
std::string colorToString(ColorEnum color) {
    switch (color) {
        case red: return "red";
        case green: return "green";
        case blue: return "blue";
        case yellow: return "yellow";
        case none: return "none";
        default: return "unknown";
    }
}

/* function: valueToString() -> convert ValueEnum to string */
std::string valueToString(ValueEnum value) {
    switch (value) {
        case ValueEnum::zero: return "zero";
        case ValueEnum::one: return "one";
        case ValueEnum::two: return "two";
        case ValueEnum::three: return "three";
        case ValueEnum::four: return "four";
        case ValueEnum::five: return "five";
        case ValueEnum::six: return "six";
        case ValueEnum::seven: return "seven";
        case ValueEnum::eight: return "eight";
        case ValueEnum::nine: return "nine";
        case ValueEnum::skip: return "skip";
        case ValueEnum::reverse: return "reverse";
        case ValueEnum::drawTwo: return "draw two";
        case ValueEnum::wild: return "wild";
        case ValueEnum::wildFour: return "wild draw four";
        case ValueEnum::nullable: return "nullable";
        default: return "unknown";
    }
}

/* function: display() ->  display the card content */
void Card::display() const
{
    std::cout << "[ " << valueToString(value) << " - " << colorToString(color) << " ] ";
}

/*
 *
 *    Implementation for methods in class DECK:
 *
 */

/* constructor: */
Deck::Deck()
{
    /*  initialize the Deck with the 108 cards
        by iterating through the colors and values */

    for (int color = 0; color <= 3; color++)
    {
        for (int value = 0; value <= 12; value++)
        {
            /* create a new Card and place it in the Deck */
            Card newCard(static_cast<ColorEnum>(color), static_cast<ValueEnum>(value));
            cards.push_back(newCard);

            if(value != 0)
                cards.push_back(newCard);
        }
    }

    /* create the special "wild cards" (4 of each) */

    ValueEnum wildValue = wild;
    ValueEnum wildFourValue = wildFour;
    ColorEnum color = none;

    Card wildCard(static_cast<ColorEnum>(color), static_cast<ValueEnum>(wildValue));
    Card wildFourCard(static_cast<ColorEnum>(color), static_cast<ValueEnum>(wildFourValue));

    for(int i = 1; i <= 4; i++)
    {
        cards.push_back(wildFourCard);
        cards.push_back(wildCard);
    }

#ifdef DEBUG
    this->display();
#endif

    /* shuffle the cards so they are not ordered */
    Deck::shuffle();
}

/* function: display() -> prints the content of the deck */
void Deck::display()
{
    cout << endl << " DECK CONTENT: " << endl << endl;
    for (const auto & card : cards)
    {
        card.display();
        cout<<endl;
    }
    cout << endl << endl;
}

/* destructor: */
Deck::~Deck() = default;

/* function: shuffle() -> randomizes the cards in array */
void Deck::shuffle()
{
    /* Random number generator */
    std::random_device rd;  /* Provides a random seed */
    std::mt19937 g(rd());   /* Mersenne Twister generator initialized with the seed */

    std::shuffle(cards.begin(), cards.end(), g);
}

/* function: draw() -> return the last card from the deck, eliminates the card from the deck */
Card Deck::draw()
{
    if (!cards.empty()) /* if there are any cards left */
    {
        /* return the last card from the deck */
        Card returnCard = cards.back();
        cards.pop_back();
        return returnCard;
    }
    else /* deck is empty */
    {
        Card returnCard;
        return returnCard;
    }
}

/* function: isEmpty() -> return true if the deck has no cards */
bool Deck::isEmpty()
{
    if(cards.empty()) return true;
    else return false;
}

/* function: refill() -> fills the "cards" vector with the cards in the given argument */
void Deck::refill(const vector<Card>& v)
{
    for(const Card& c : v)
    {
        cards.push_back(c);
    }
    shuffle();
}

/*
 *
 *    Implementation for methods in class PLAYER:
 *
 */


/* constructor for player */
Player::Player(Deck& deck)
{
    nickname = "Bot";
    while (hand.size() < 7) /* give initially the player 7 cards */
        hand.push_back(deck.draw());
    isBot = true;
    finishedGame = false;

#ifdef DEBUG
    cout << endl << "A bot has been created. The cards assigned to the bot are: " << endl;
    for(const auto& card: hand)
    {
        card.display();
        cout << endl;
    }
    cout << endl;
#endif

}

/* destructor */
Player::~Player() = default;

/* function: playCard() -> returns the card chosen by player */
Card Player::playCard(ColorEnum color, ValueEnum value, Deck& deck)
{
    /* print available cards */
    printHandCards();

    if (isBot) /* 1st case: the player is a bot -> returns first found card */
    {
        for (auto it = hand.begin(); it != hand.end(); ++it)
        {
            /* looking for the same value or same color */
            if (it->color == color || it->value == value || value == wild || value == wildFour
            || value == any || it->value == wild || it->value == wildFour)
            {
                Card returnCard = *it; // extract value
                hand.erase(it);
                cout << "Chosen card: ";
                returnCard.display();
                cout << endl;
                return returnCard;
            }
        }

        /* no card found return nullable and draw +1 card */
        drawCard(deck);
        Card returnCard;
        return returnCard;
    }
    else /* 2nd case: the player is human -> will choose a card */
    {
        int index;
        Card returnCard;
        bool valid;

        do { /* read a valid index */

            cout << "Card index (-1 to draw card): " << endl;
            cin >> index;

            /* index not in range */
            if (!(index >= 0 && index < hand.size()) && index != -1)
            {
                cout << "Invalid index!" << endl;
                valid = false;
                continue;
            }

            /* option: draw card */
            if(index == -1)
            {
                /* no card found return nullable and draw +1 card */
                drawCard(deck);
                return returnCard;
            }

            /* check for compatibility */
            returnCard =  *(hand.begin() + index);
            if (returnCard.color != color && returnCard.value != value &&
            returnCard.value != wild && returnCard.value != wildFour)
            {
                cout << "The selected card does not match the card on the table! Select other option!" << endl;
                valid = false;
            }
            else
            {
                valid = true;
            }

        }
        while (!valid);

        /* return selected card */
        hand.erase(hand.begin() + index);

        cout << "Chosen card: ";
        returnCard.display();
        cout << endl;

        return returnCard;
    }
}

/* function: drawCard() -> takes a card from the deck and places it in hand */
void Player::drawCard(Deck& deck)
{
    Card receivedCard = deck.draw();
    if (receivedCard.value == nullable)
    {
        cout << "Empty deck! Stand by one round." << endl;
    }
    else
    {
        hand.push_back(receivedCard);
    }
}

/* function: callUno() -> announce that only one card left in hand */
bool Player::callUno()
{
    if (hand.empty())
    {
        finishedGame = true;
        return true;
    }
    if (hand.size() == 1)
        return true;
    return false;
}

/* function: printHandCads(): shows the cards available */
void Player::printHandCards()
{
    cout <<endl << endl << "Player <" << nickname << "> has the following cards: " << endl;
    for(const Card& c:hand)
    {
        c.display();
    }
    cout<< endl;
}

/*
 *
 *    Implementation for methods in class GAME:
 *
 */

/* constructor for Game class */
Game::Game(const Deck& d, const Player& p1, const Player& p2)
        : deck(d), player1(p1), player2(p2), usedCards(), currentCard(),  isClockwise(true)
{
    if (checkIntegrity())
        cout << "Game data was successfully initialized." << endl;
    else
        exit(-1);
}

/* destructor for class Game */
Game::~Game() = default;

/* function: checkIntegrity() -> verify the data */
bool Game::checkIntegrity()
{
    if (deck.isEmpty()) return false;
    if (!usedCards.empty()) return false;
    return true;
}

/* function: start() -> initiate the game mode */
void Game::start()
{
    cout << endl << "~~~~~ GAME STARTED ~~~~~" << endl << endl;

    int gameMode;

    do
    {
        std::cout<< "Select the game mode: " << endl << "1. Player vs Bot" << endl << "2. Bot vs Bot" << endl << "Your option: ";
        std::cin >> gameMode;
    }
    while (gameMode < 1 || gameMode > 2);

    switch(gameMode)
    {
        case 1: /* the scenario Player vs Bot */
        {
            string nickname;
            cout << "Add a nickname: " << endl; /* read player nickname */
            cin >> nickname;

            /* set name */
            player1.nickname = nickname;
            player1.isBot = false;

            /* game logic */
            round();
        }

        case 2:
        {
            round();
        }

        default:
        {
            break;
        }
    }
}

/* function: round() -> iterates through the rounds (game) */
void Game::round()
{
    int number = 1;
    while (!foundWinner())
    {
        /* print round number */
        cout << endl << "ROUND " << number++ << " IN PROGRESS..."<< endl << endl;

        /* check if there are any cards available in deck */
        if (deck.isEmpty())
        {
            deck.refill(usedCards);
        }

        /* check if there is any card on the table */
        if (usedCards.empty())
        {
            usedCards.push_back(deck.draw());
        }

        /* set the current card on the table */
        currentCard = usedCards.back();

        cout << "CARD ON THE TABLE: ";
        currentCard.display();

        /* check whose turn is */
        if(isClockwise)
        {
            /* player1 makes a move */
            makeMove(player1);

            /* set the current card on the table */
            if (currentCard.value != any)
                    currentCard = usedCards.back();
            cout << endl << "CARD ON THE TABLE: ";
            currentCard.display();

            /*player2 makes move */
            makeMove(player2);
        }
        else
        {
            /* player2 makes move */
            makeMove(player2);

            /* set the current card on the table */
            if (currentCard.value != any)
                currentCard = usedCards.back();
            cout << endl << "CARD ON THE TABLE: ";
            currentCard.display();

            /*player1 makes move */
            makeMove(player1);
        }

#ifdef DEBUG
        while (true)
        {
            int i;
            cout << endl << endl << "DEBUG MODE: wait for 0:";
            cin>>i;
            if (i == 0) break;
        }
#endif
    }
}

/* function: makeMove() -> iterates a round for a player */
void Game::makeMove(Player& player)
{
    /* check for +2 or +4 on table */
    if (currentCard.value == drawTwo)
    {
        player.drawCard(deck);
        player.drawCard(deck);
    }
    if (currentCard.value == wildFour)
    {
        player.drawCard(deck);
        player.drawCard(deck);
        player.drawCard(deck);
        player.drawCard(deck);
    }

    /* check for skip card */
    if (currentCard.value == skip)
    {
        currentCard.value = any;
        return;
    }

    /* choose the right card from hand */
    Card card = player.playCard(usedCards.back().color, usedCards.back().value, deck);

    /* if the card is valid add it to the table stack */
    if (card.value != nullable)
    {
        if (card.value == ValueEnum::reverse)
            isClockwise = !isClockwise;
        usedCards.push_back(card);
    }

    /* verify for any uno */
    if (player.callUno() && !player.finishedGame)
    {
        cout << endl << " UNO! Player <" << player.nickname << "> has only one card left!" << endl;
    }
}

/* function: foundWinner() -> search any winner (no cards in hand) */
bool Game::foundWinner()
{
    if (player1.callUno() && player1.finishedGame)
    {
        cout << "Player " << player1.nickname << " won the game.";
        return true;
    }

    if (player2.callUno() && player2.finishedGame)
    {
        cout << "Player " << player2.nickname << " won the game.";
        return true;
    }
    return false;
}