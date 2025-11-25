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


#endif