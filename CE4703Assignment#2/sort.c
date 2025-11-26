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
//sortdeck is treating the deck like an array but we're using linked lists, which need nodes, not indexing
void sortDeck(CardDeck* deck)
{
    //replace array indexing with node pointers and nested loops to walk through the list
    for (int i = 0; i < 52; i++) { // sorting must use deck -> size, hardcoding doesnt work in this instance since the players choose the deck size they want
        for (int j = i + 1; j < 52; j++) {
            if (compareCards(deck[i], deck[j]) > 0)//compareCards expects pointers, not values (hence the error)
                cardSwap(deck[i], deck[j]);//we're swapping the actual card values inside the nodes, not the nodes themselves
        }
    }

    //to make things easier, you can look up bubble sort / selection sort using linked-lists specifically
}