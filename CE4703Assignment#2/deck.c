/**
 * @file deck.c
 * @brief Implementation of CardDeck operations
 *
 * This file implements all the CardDeck functions declared in deck.h.
 * The deck uses a dynamic array that grows as needed when cards are added.
 *
 * @author Shrestha Dey
 * @date 25 November 2025
 */
#include "deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARDS_PER_PACK 52
#define INITIAL_CAPACITY 52

 /**
  * @brief Helper function to grow the deck's capacity
  *
  * Doubles the current capacity and reallocates the cards array.
  *
  * @param deck Pointer to the deck to grow
  * @return true on success, false on memory allocation failure
  */
static bool growDeck(CardDeck* deck)
{
    int new_capacity = deck->capacity * 2;
    Card* new_cards = realloc(deck->cards, new_capacity * sizeof(Card));
    if (!new_cards) {
        return false;
    }
    deck->cards = new_cards;
    deck->capacity = new_capacity;
    return true;
}

/**
 * @brief Initializes a new deck with the specified number of card packs
 */
CardDeck* initDeck(int num_packs)
{
    if (num_packs < 0) {
        return NULL;
    }

    /// Allocate the deck structure
    CardDeck* deck = malloc(sizeof(CardDeck));
    if (!deck) {
        return NULL;
    }

    /// Calculate total cards needed
    int total_cards = num_packs * CARDS_PER_PACK;
    int capacity = (total_cards > 0) ? total_cards : INITIAL_CAPACITY;

    /// Allocate the cards array
    deck->cards = malloc(capacity * sizeof(Card));
    if (!deck->cards) {
        free(deck);
        return NULL;
    }

    deck->size = 0;
    deck->capacity = capacity;

    /// Fill the deck with complete packs
    for (int pack = 0; pack < num_packs; pack++) {
        for (Suit s = CLUB; s <= DIAMOND; s++) {
            for (Rank r = TWO; r <= ACE; r++) {
                Card c = { s, r };
                deck->cards[deck->size++] = c;
            }
        }
    }

    return deck;
}

/**
 * @brief Frees all memory associated with a deck
 */
void freeDeck(CardDeck* deck)
{
    if (deck) {
        free(deck->cards);
        free(deck);
    }
}