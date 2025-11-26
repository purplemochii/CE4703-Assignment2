#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "sort.h"

#define NUM_PLAYERS 2
#define INITIAL_HAND_SIZE 8
#define MAX_HAND_SIZE 20

/* --- player --- */
typedef struct {
	CardDeck* hand; // player's hand
	char name[20]; // player
} Player;

/* --- game state --- */
typedef struct {
	Player players[NUM_PLAYERS]; // players
	CardDeck* hiddenDeck;	// draw pile (the ones that are face down)
	CardDeck* playedDeck;	// discarded pile (faced up)
	Card currentCard;	// current card that is being matched
	int currentPlayer;	// player number (either 0 or 1 bc theres only 2 players)
	int gameOver;	 // flag that signifies game over
} GameState;

/* --- game init and cleanup --- */
GameState* initGame(int numPacks);
void freeGame(GameState* game);

/* --- game op ---*/
void dealInitialCards(GameState* game);
int findMatchingCard(const GameState* game, int playerIndex);
int isValidMove(const Card* card, const Card* currentCard);
int playCard(GameState* game, int playerIndex, int cardIndex);
void drawCardForPlayer(GameState* game, int playerIndex);
void reshuffleHiddenDeck(GameState* game);

/* --- display fns ---*/
void printPlayerHand(int playerIndex, const CardDeck* hand);
void printGameState(const GameState* game);

/* --- game flow ---*/
void nextTurn(GameState* game);
int checkGameOver(const GameState* game);

#endif !GAME_H
