/**
 * @file game.c
 * @brief Implementation of game logic
 *
 * This file implements the complete card game according to the specified rules.
 * It handles card dealing, matching logic, player turns, and game flow.
 *
 * @author Oluwatunmise Adegbola
 * @date 26 November 2025
*/

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
		sprintf(game -> players[i].name, sizeof(game -> players[i].name), "Player %d", i + 1);
	}

	game -> currentPlayer = 0;
	game -> gameOver = 0;

	return game;
}


/**
 * @brief Frees all memory associated with the game
 *
 * @param game Game state to free
*/

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


/**
 * @brief Deals initial cards to all players
 *
 * Deals INITIAL_HAND_SIZE cards to each player alternately from the hidden deck.
 *
 * @param game Game state
*/

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


/**
 * @brief Finds the first matching card in player's hand
 *
 * @param game Game state
 * @param playerIndex Index of player to check
 * @return Index of matching card, or -1 if no match found
*/

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


/**
 * @brief Checks if a card can be played on the current card
 *
 * A card is valid if it matches the current card's suit OR rank.
 *
 * @param card Card to check
 * @param currentCard Current top card
 * @return 1 if valid move, 0 otherwise
*/

/* -- checks if a card can be played indeed -- */
int isValidMove(const Card* card, const Card* currentCard)
{
	return (card -> suit == currentCard -> suit) || (card -> rank == currentCard -> rank);
}


/**
 * @brief Plays a card from player's hand
 *
 * @param game Game state
 * @param playerIndex Index of player playing the card
 * @param cardIndex Index of card in player's hand to play
 * @return 1 if card was played successfully, 0 otherwise
*/

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

	printf(" %s played : ", player -> name);
	printCard(&playedCard);
	printf("\n");

	return 1;
}


/**
 * @brief Draws a card from hidden deck for player
 *
 * If hidden deck is empty, reshuffles played deck into hidden deck first.
 *
 * @param game Game state
 * @param playerIndex Index of player drawing the card
*/

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


/**
 * @brief Reshuffles played deck into hidden deck
 *
 * Keeps the last played card in the played deck, moves the rest to hidden deck.
*/

/* -- reshuffle played deck -- */
void reshuffleHiddenDeck(GameState* game)
{
	printf("Hidden deck empty! Please hol up while it reshuffles. \n");

	// keep the current card in played deck
	if (game -> playedDeck -> size <= 1) {
		return; // the cards aret enough to reshuffle
	}

	// move all but the top card from played to hidden
	while (game -> playedDeck -> size > 1) {
		Card card;

		//remove cards from the bottom so you dont reverse their order
		removeCardAt(game -> playedDeck, game -> playedDeck -> size - 1, &card);
		addCardToEnd(game -> hiddenDeck, card);
	}

	shuffleDeck(game -> hiddenDeck);
	printf("Reshuffled! hidden deck now has %d cards! \n", game -> hiddenDeck -> size);
}

/* --- display fns ---*/


/**
 * @brief Prints a player's hand
 *
 * @param playerIndex Index of the player
 * @param hand Pointer to player's hand deck
*/

/* -- print players hand -- */
void printPlayerHand(int playerIndex, const CardDeck* hand)
{
	printf("Player %d hand (%d cards): \n", playerIndex + 1, hand -> size);
	CardNode* current = hand -> head;
	int index = 0;
	while (current != NULL) {
		printf(" [%d] ", index++);
		printCard(&current -> card);
		current = current -> next;

	}
	printf("\n");
}


/**
 * @brief Prints current game state
 *
 * @param game Game state
*/

/* -- prints current game state -- */
void printGameState(const GameState* game)
{
	printf("\n=== GAME STATE ===\n");
	printf("Current card: ");
	printCard(&game -> currentCard);
	printf("\n");
	printf("Current player: %s\n", game -> players[game -> currentPlayer].name);
	printf("Hidden deck: %d cards\n", game -> hiddenDeck -> size);
	printf("Played deck: %d cards\n", game->playedDeck->size);
	printf("\n");

}

/* --- game flow ---*/


/**
 * @brief Advances to next player's turn
 *
 * @param game Game state
*/

/* -- goes to player's next turn -- */
void nextTurn(GameState* game)
{
	game -> currentPlayer = (game -> currentPlayer + 1) % NUM_PLAYERS;
}


/**
 * @file deck.c
 * @brief Implementation of CardDeck operations
 *
 * This file implements all the CardDeck functions declared in deck.h.
 * The deck uses a singly linked list with head and tail pointers.
 *
 * @author Shrestha Dey
 * @date 25 November 2025
*/

/* -- check if game is over -- */
int checkGameOver(const GameState* game)
{
	for (int i = 0; i < NUM_PLAYERS; i++) {
		if (game -> players[i].hand -> size == 0) {
			printf("\n*** %s wins the game! ***\n", game -> players[i].name);
			return 1;
		}
	}
	return 0;
}