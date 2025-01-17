
/* include game library */
#include <uno.h>

int main()
{
    Deck deck;
    Player p1(deck);
    Player p2(deck);

    Game game(deck, p1, p2);

    game.start();

    return 0;
}