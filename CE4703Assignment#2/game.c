#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

/* --- game init and cleanup --- */
GameState* initGame(int numPacks)
{
	if (numPacks <= 0) {
		return NULL;
	}

	GameState* game = malloc(sizeof(GameState));
	if (!game) {
		return NULL;
	}

	// init hidden deck
	game -> hiddenDeck = initDeck(numPacks);
	if (!game -> hiddenDeck) {
		free(game);
		return NULL;
	}
	shuffleDeck(game -> hiddenDeck);

	// init palyed deck 
	game -> playedDeck = initDeck(0);	// empty deck
	if (!game -> playedDeck) {
		freeDeck(game -> hiddenDeck);
		free(game);
		return NULL;
	}

	// init players
	for (int i = 0; i < NUM_PLAYERS; i++) {
		game -> players[i].hand = initDeck(0);	// empty hand
		if (!game -> players[i].hand) {
			//if fail, then clean.
			for (int j = 0; j < i; j++) {
				freeDeck(game -> players[j].hand);
			}
			freeDeck(game -> hiddenDeck);
			freeDeck(game -> playedDeck);
			free(game);

			return NULL;
		}
		printf(game -> players[i].name, "Player %d", i + 1);
	}

	game -> currentPlayer = 0;
	game -> gameOver = 0;

	return game;
}
void freeGame(GameState* game);

/* --- game op ---*/
void dealInitialCards(GameState* game);
int findMatchingCard(const GameState* game, int playerIndex);
int playCard(GameState* game, int playerIndex, int cardIndex);
void drawCardForPlayer(GameState* game, int playerIndex);
void reshuffleHiddenDeck(GameState* game);

/* --- display fns ---*/
void printPlayerHand(int playerIndex, const CardDeck* hand);
void printGameState(const GameState* game);

/* --- game flow ---*/
void nextTurn(GameState* game);
int checkGameOver(const GameState* game);