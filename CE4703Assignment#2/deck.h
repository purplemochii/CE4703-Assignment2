/**
 * @file deck.h
 * @brief CardDeck type and operations for managing a deck of playing cards
 *
 * This file defines the CardDeck data structure which can hold multiple
 * packs of cards (52 cards per pack). The deck linked lists with dynamic 
 * memory allocation to support any number of cards. It provides operations 
 * for shuffling, adding/removing cards, and more.
 *
 * @author Shrestha Dey
 * @date 25 November 2025
 */

#pragma once
#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <stdbool.h>

 /**
  * @brief Node structure for the linked list
  */
typedef struct CardNode {
    Card card;              ///< The card stored in this node
    struct CardNode* next;  ///< Pointer to the next node, or NULL if this is the last node
} CardNode;

/**
* @brief  Structure representing a deck of playing cards
*/
typedef struct {
    CardNode* head;  ///< Pointer to the first node in the list (top of deck)
    CardNode* tail;  ///< Pointer to the last node in the list (bottom of deck)
    int size;        ///< Current number of cards in the deck
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
 * Deallocates all nodes in the linked list and the deck structure itself.
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
 * @brief Add card to the bottom of the deck
 * 
 * @param deck Pointer to the deck, must not be NULL
 * @param card Card to add to the bottom
 * @return true if card added successfully, false if memory failure
*/
bool addCardToEnd(CardDeck* deck, Card card);

/**
 * @brief Removes and returns the top card from the deck
 *
 * The top card is the head of linked list (first card).
 * The head pointer is updated to point to the next card.
 *
 * @param deck Pointer to the deck, cannot be NULL
 * @param out_card Pointer to store the removed card, cannot be NULL
 * @return true if a card was removed successfully, false if deck was empty
 */
bool removeTopCard(CardDeck* deck, Card* out_card);

/**
 * @brief Removes a card at a specific position in the deck
 *
 * Position 0 is the top of the deck and (size-1) is bottom.
 *
 * @param deck Pointer to the deck, cannot be NULL
 * @param position Index of the card to remove (0 to size-1).
 * @param out_card Pointer to store the removed card, cannot be NULL
 * @return true if card was removed successfully, false if position is invalid
 */
bool removeCardAt(CardDeck* deck, int position, Card* out_card);

/**
 * @brief Checks if the deck is empty
 *
 * @param deck Pointer to the deck, cannot be NULL
 * @return true if deck has no cards, false otherwise
 */
bool isEmpty(const CardDeck* deck);

/**
 * @brief Prints all cards in the deck
 *
 * Displays each card on a separate line, useful for debugging.
 *
 * @param deck Pointer to the deck to print, cannot be NULL
 */
void printDeck(const CardDeck* deck);

#endif