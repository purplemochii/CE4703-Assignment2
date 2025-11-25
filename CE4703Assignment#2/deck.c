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