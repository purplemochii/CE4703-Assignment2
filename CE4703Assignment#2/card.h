/**
 * @file card.h
 * @brief Card type: Suit enum, Rank enum, Card struct and basic operations.
 *
 * This file defines the data type for a single playing card.
 * A card has a suit (Club, Spade, Heart, Diamond)
 * and a rank (Two through Ace). It also declares helper
 * functions to print and compare cards.
 * This type will be used in the card game program.
 *
 * @author Diana Adobovska
 * @date 24 November 2025
 */

#ifndef CARD_H
#define CARD_H

 /** @brief Enum for all four suits (Club, Spade, Heart, Diamond). */
typedef enum {
    CLUB,
    SPADE,
    HEART,
    DIAMOND
} Suit;

/** @brief Enum for all 13 ranks in a standard deck (Two–Ace). */
typedef enum {
    TWO = 2,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
} Rank;

/**
 * @brief Structure representing a single playing card.
 *
 * A card is defined by its suit and rank.
 */
typedef struct {
    Suit suit; /**< Suit of the card. */
    Rank rank; /**< Rank of the card. */
} Card;

/**
 * @brief Prints a card in human-readable form (for example "Heart Queen").
 *
 * This is mainly used for showing cards to the user.
 *
 * @param c Pointer to the card to print. Should not be NULL.
 */
void printCard(const Card* c);

/**
 * @brief Compares two cards by suit first, then by rank.
 *
 * This function can be used when sorting cards.
 * Suits are compared using their enum order (CLUB, SPADE, HEART, DIAMOND),
 * and if suits are the same, ranks are compared (Two is lowest, Ace highest).
 *
 * @param a Pointer to the first card.
 * @param b Pointer to the second card.
 * @return Negative value if a < b, positive value if a > b, 0 if equal.
 */
int compareCards(const Card* a, const Card* b);

/**
 * @brief Converts a Suit value to a string.
 * @param s Suit value.
 * @return Constant string representing the suit (for example "Heart").
 */
const char* suitToString(Suit s);

/**
 * @brief Converts a Rank value to a string.
 * @param r Rank value.
 * @return Constant string representing the rank (for example "Queen").
 */
const char* rankToString(Rank r);

#endif /* CARD_H */
