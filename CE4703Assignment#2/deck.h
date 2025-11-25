/**
 * @file deck.h
 * @brief //Card type: Suit enum, Rank enum, Card struct and basic operations.
 *
 * This file defines the data type for a single playing card.
 * A card has a suit (Club, Spade, Heart, Diamond)
 * and a rank (Two through Ace). It also declares helper
 * functions to print and compare cards.
 * This type will be used in the card game program.
 *
 * @author Shrestha Dey
 * @date 25 November 2025
 */

#pragma once
#ifndef DECK_H
#define DECK_H

#include "card.h"

/**
* @brief  Structure representing a deck of playing cards
*/
typedef struct {
    Card* cards;     ///< Dynamic array of cards
    int size;        ///< Current number of cards in the deck
    int capacity;   ///< Total allocated space for cards
} CardDeck;

/**
 * @brief Initializes a new deck with the specified number of card packs
 *
 * Creates a deck containing num_packs complete packs of 52 cards each.
 * Each pack contains all 4 suits with cards from Two to Ace.
 * The deck is allocated dynamically and must be freed with freeDeck().
 *
 * @param num_packs Number of complete card packs to include (>= 0)
 * @return Pointer to newly created CardDeck or NULL on failure
 */
CardDeck* initDeck(int num_packs);

/**
 * @brief Frees all memory associated with a deck
 *
 * Deallocates the cards array and the deck structure itself.
 * After calling this, the deck pointer becomes invalid.
 *
 * @param deck Pointer to the deck to be freed, can be NULL
 */
void freeDeck(CardDeck* deck);

/**
 * @brief Shuffles the deck randomly
 *
 * Uses the Fisher-Yates shuffle algorithm to randomize the order
 * of all cards in the deck.
 *
 * @param deck Pointer to the deck to shuffle, cannot be NULL
 */
void shuffleDeck(CardDeck* deck);

/**
 * @brief Adds a card to the top of the deck
 *
 * The deck will automatically grow if needed to accommodate the new card.
 *
 * @param deck Pointer to the deck, cannot be NULL
 * @param card The card to add (copied into the deck)
 * @return true if card was added successfully, false on memory allocation failure
 */
bool addCard(CardDeck* deck, Card card);

/**
 * @brief Removes and returns the top card from the deck
 *
 * The top card is the last card in the array (highest index).
 * The deck size is reduced by one.
 *
 * @param deck Pointer to the deck, cannot be NULL
 * @param out_card Pointer to store the removed card, cannot be NULL
 * @return true if a card was removed successfully, false if deck was empty
 */
bool removeTopCard(CardDeck* deck, Card* out_card);

/**
 * @brief Removes a card at a specific position in the deck
 *
 * Position 0 is the bottom of the deck.
 * Cards after the removed position are shifted down to fill the gap.
 *
 * @param deck Pointer to the deck, cannot be NULL
 * @param position Index of the card to remove (0 to size-1).
 * @param out_card Pointer to store the removed card, cannot be NULL
 * @return true if card was removed successfully, false if position is invalid
 */
bool removeCardAt(CardDeck* deck, int position, Card* out_card);

#endif