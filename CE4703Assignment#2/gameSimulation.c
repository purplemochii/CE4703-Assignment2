#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"

void simulateGame(int numPacks)
{
	printf("=== Game Start! ===\n");
	printf("Using %d pack(s) of cards.\n", numPacks);
		
	GameState* game = initGame(numPacks);

	if (!game) {
		printf("game did not initialise :(\n");
		return;
	}

	// deal initial cards
	dealInitialCards(game);

	// sort and shiw players hands
	for (int i = 0; i < NUM_PLAYERS; i++) {
		sortDeck(game -> players[i].hand);
		printPlayerHand(i, game -> players[i].hand);
	}

	printf("\n=== Let the games begin! ===\n");

	printf("\nInitial card on table: ");
	printCard(&game -> currentCard);
	printf("\n\n");

	// main game loop
	while (!game -> gameOver) {
		Player* currentPlayer = &game -> players[game -> currentPlayer];

		printf("It's %s's turn!\n", currentPlayer -> name);
		printGameState(game);
		printPlayerHand(game -> currentPlayer, currentPlayer -> hand);

		// check for matching card
		int matchingCardIndex = findMatchingCard(game, game -> currentPlayer);

		if (matchingCardIndex != -1) {
			printf("%s plays a card from their hand!\n", currentPlayer -> name);
			//play the matching card
			playCard(game, game -> currentPlayer, matchingCardIndex);
		} else {
			printf("%s has no matching card and must draw!\n", currentPlayer -> name);
			// no mathcing card, boohoo, draw from hidden deck
			drawCardForPlayer(game, game -> currentPlayer);

			// sort hand after drawing
			sortDeck(currentPlayer -> hand);
		}

		// print new hand
		printPlayerHand(game -> currentPlayer, currentPlayer -> hand);

		//check if gam'es over
		if (checkGameOver(game)) {
			game -> gameOver = 1;
			printf("Game Over! %s wins!\n", currentPlayer -> name);
		} else {
			// next turn
			nextTurn(game);
			printf("\n");
		}
	}
	
	freeGame(game);
	printf("=== Game Over! ===\n");
}