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

/* --- free game memory ---*/
void freeGame(GameState* game) 
{
	if (!game) {
		return;
	}

	for (int i = 0; i < NUM_PLAYERS; i++) {
		freeDeck(game -> players[i].hand);
	}

	freeDeck(game -> hiddenDeck);
	freeDeck(game -> playedDeck);
	free(game);
}

/* --- game op ---*/

/* -- give initial cards to players -- */
void dealInitialCards(GameState* game)
{
	for (int i = 0; i < INITIAL_HAND_SIZE; i++) {
		for (int p = 0; p < NUM_PLAYERS; p++) {
			if (!isEmpty(game -> hiddenDeck)) {
				Card drawnCard;
				if (removeTopCard(game -> hiddenDeck, &drawnCard)) {
					addCardToEnd(game -> players[p].hand, drawnCard);
				}
			}
		}
	}

	// draw initial card for the played deck 
	if (!isEmpty(game -> hiddenDeck)) {
		removeTopCard(game -> hiddenDeck, &game -> currentCard);
		addCard(game -> playedDeck, game -> currentCard);
	}
}

/* -- find the first matching card -- */
int findMatchingCard(const GameState* game, int playerIndex)
{
	const Player* player = &game -> players[playerIndex];
	CardNode* current = player -> hand -> head;
	int index = 0;

	while (current != NULL) {
		if (isValidMove(&current -> card, &game -> currentCard)) {
			return index;
		}
		current = current -> next;
		index++;
	}

	return -1;	// no matching card found 🥀
}

/* -- checks if a card can be played indeed -- */
int isValidMove(const Card* card, const Card* currentCard)
{
	return (card -> suit == currentCard -> suit) || (card -> rank == currentCard -> rank);
}

/* -- play card from a player's hand -- */
int playCard(GameState* game, int playerIndex, int cardIndex)
{
	Player* player = &game -> players[playerIndex];

	if (cardIndex < 0 || cardIndex >= player -> hand -> size) {
		return 0;
	}

	// remove card from player's hand
	Card playedCard;
	if (!removeCardAt(player -> hand, cardIndex, &playedCard)) {
		return 0;
	}

	// update currentcard and add to played deck
	game -> currentCard = playedCard;
	addCard(game -> playedDeck, playedCard);

	printf(" % s played : ", player -> name);
	printCard(&playedCard);
	printf("\n");

	return 1;
}

/* -- draw a card for a player -- */
void drawCardForPlayer(GameState* game, int playerIndex)
{
	Player* player = &game -> players[playerIndex];

	// if hidden deck is empty, then reshuffle the game
	if (isEmpty(game -> hiddenDeck)) {
		reshuffleHiddenDeck(game);
	}

	// now actually draw a card from hidden deck for the player
	if (!isEmpty(game -> hiddenDeck)) {
		Card drawnCard;
		if (removeTopCard(game -> hiddenDeck, &drawnCard)) {
			addCardToEnd(player -> hand, drawnCard);
			printf("%s draws:", player -> name);
			printCard(&drawnCard);
			printf("\n");
		}
	}
}

/* -- reshuffle played deck -- */
void reshuffleHiddenDeck(GameState* game)
{
	printf("Hidden deck empty! Please hol up while it reshuffles. \n");
	pritnf("what u still looking at..\n");

	// keep the current card in played deck
	if (game -> playedDeck -> size <= 1) {
		return; // the cards aret enough to reshuffle
	}

	// move all but the top card from played to hidden
	while (game -> playedDeck -> size > 1) {
		Card card;

		//remove cards from the bottom so you dont reverse their order
		removeCardAt(game -> playedDeck, game -> playedDeck -> size - 1, &card);
		addCardToEnd(game->hiddenDeck, card);
	}

	shuffleDeck(game->hiddenDeck);
	printf("Reshuffled! hidden deck now had %d cards! \n", game->hiddenDeck->size);
}

/* --- display fns ---*/
void printPlayerHand(int playerIndex, const CardDeck* hand);
void printGameState(const GameState* game);

/* --- game flow ---*/
void nextTurn(GameState* game);
int checkGameOver(const GameState* game);