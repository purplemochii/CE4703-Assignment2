// WORK STILL IN PROGRESS

/**
 * @file sort.c
 * @brief Implementation of sortDeck function
 *
 * This file implements the sortDeck function declared in sort.h.
 * The function uses the compareCards function from card.c.
 *
 * @author Méabh McCarthy
 * @date 25 November 2025
 */

#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

void cardSwap(Card* a, Card* b)
{
    Card blank;
    blank = *a;
    *a = *b;
    *b = blank;
}

/**
 * @brief Sorts deck of cards based on suit and rank
 */
void sortDeck(CardDeck* deck)
{
    for (int i = 0; i < 52; i++) {
        for (int j = i + 1; j < 52; j++) {
            if (compareCards(deck[i], deck[j]) > 0)
                cardSwap(deck[i], deck[j]);
        }
    }
}