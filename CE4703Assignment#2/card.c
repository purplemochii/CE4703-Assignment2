/**
 * @file card.c
 * @brief Implementation of print and compare functions for Card.
 *
 * This file provides functions to convert Suit and Rank to
 * readable strings, a function to print a card, and a comparison
 * function that can be used when sorting cards.
 * These helper functions are used by the deck module and
 * by the game logic.
 *
 * @author Diana Adobovska
 * @date 24 November 2025
 */

#include <stdio.h>
#include "card.h"

const char* suitToString(Suit s)
{
    // Short text label for each suit.
    switch (s) {
    case CLUB:    return "Club";
    case SPADE:   return "Spade";
    case HEART:   return "Heart";
    case DIAMOND: return "Diamond";
    default:      return "UnknownSuit";
    }
}

const char* rankToString(Rank r)
{
    // Short text label for each rank.
    switch (r) {
    case TWO:   return "Two";
    case THREE: return "Three";
    case FOUR:  return "Four";
    case FIVE:  return "Five";
    case SIX:   return "Six";
    case SEVEN: return "Seven";
    case EIGHT: return "Eight";
    case NINE:  return "Nine";
    case TEN:   return "Ten";
    case JACK:  return "Jack";
    case QUEEN: return "Queen";
    case KING:  return "King";
    case ACE:   return "Ace";
    default:    return "UnknownRank";
    }
}

void printCard(const Card* c)
{
    // Simple safety check in case someone passes NULL by mistake.
    if (c == NULL) {
        printf("(null card)\n");
        return;
    }

    // Print suit first, then rank, for example: "Heart Queen".
    printf("%s %s\n", suitToString(c->suit), rankToString(c->rank));
}

int compareCards(const Card* a, const Card* b)
{
    // Handle NULL pointers first (just in case).
    if (a == NULL || b == NULL) {
        if (a == b) {
            return 0;
        }
        else if (a == NULL) {
            return -1;
        }
        else {
            return 1;
        }
    }

    // First compare by suit (CLUB < SPADE < HEART < DIAMOND).
    if (a->suit != b->suit) {
        return (int)a->suit - (int)b->suit;
    }

    // If suits are equal, compare by rank (Two..Ace).
    return (int)a->rank - (int)b->rank;
}
