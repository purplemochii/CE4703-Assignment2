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

/**
 * @brief Shuffles the deck randomly
 */
void shuffleDeck(CardDeck* deck)
{
    if (!deck || deck->size <= 1) {
        return;
    }

    for (int i = deck->size - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        /// Swap cards[i] and cards[j]
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}
/**
 *@brief Adds a card to the top of the deck
 */
bool addCard(CardDeck* deck, Card card)
{
    if (!deck) {
        return false;
    }

    // Grow the deck if needed
    if (deck->size >= deck->capacity) {
        if (!growDeck(deck)) {
            return false;
        }
    }

    // Add card to the top (end of array)
    deck->cards[deck->size++] = card;
    return true;
}

/**
 * @brief Removes and returns the top card from the deck
 */
bool removeTopCard(CardDeck* deck, Card* out_card)
{
    if (!deck || !out_card || deck->size == 0) {
        return false;
    }

    // Remove from the top (end of array)
    *out_card = deck->cards[--deck->size];
    return true;
}

/**
 * @brief Removes a card at a specific position in the deck
 */
bool removeCardAt(CardDeck* deck, int position, Card* out_card)
{
    if (!deck || !out_card || position < 0 || position >= deck->size) {
        return false;
    }

    // Store the card to return
    *out_card = deck->cards[position];

    // Shift all cards after position down by one
    for (int i = position; i < deck->size - 1; i++) {
        deck->cards[i] = deck->cards[i + 1];
    }

    deck->size--;
    return true;
}

/**
 * @brief Checks if the deck is empty
 */
bool isEmpty(const CardDeck* deck)
{
    return deck && (deck->size == 0);
}

/**
 * @brief Prints all cards in the deck
 */
void printDeck(const CardDeck* deck)
{
    if (!deck) {
        printf("NULL deck\n");
        return;
    }

    printf("Deck has %d cards:\n", deck->size);
    for (int i = 0; i < deck->size; i++) {
        printf("%d: ", i);
        printCard(&deck->cards[i]);
        printf("\n");
    }
}