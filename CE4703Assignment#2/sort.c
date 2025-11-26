// WORK STILL IN PROGRESS

/**
 * @file sort.c
 * @brief Implementation of sortDeck function
 *
 * This file implements the sortDeck function declared in sort.h.
 * The function uses the compareCards function from card.c.
 *
 * @author Méabh McCarthy
 * @date 26 November 2025
 */

#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Sorts deck of cards based on suit and rank
 */
void sortDeck(CardDeck* deck) 
{
    if (deck == NULL || deck->head == NULL) return;
    CardNode* i;
    CardNode* j;
    Card blank;
    for (i = deck->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (compareCards(&(i->card), &(j->card)) > 0) {
                blank = i->card;
                i->card = j->card;
                j->card = blank;
            }
        }
    }
}
