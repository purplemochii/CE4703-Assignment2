/**
 * @file deck.c
 * @brief Implementation of CardDeck operations
 *
 * This file implements all the CardDeck functions declared in deck.h.
 * The deck uses a singly linked list with head and tail pointers.
 *
 * @author Shrestha Dey
 * @date 25 November 2025
 */
#include "deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARDS_PER_PACK 52

 /**
 * @brief Helper function to create a new node
 *
 * Allocates memory for a new node and initializes it with the given card.
 *
 * @param card The card to store in the node
 * @return Pointer to the new node, or NULL on allocation failure
 */
static CardNode* createNode(Card card)
{
    CardNode* node = malloc(sizeof(CardNode));
    if (!node) {
        return NULL;
    }
    node->card = card;
    node->next = NULL;
    return node;
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

    deck->head = NULL;
    deck->tail = NULL;
    deck->size = 0;

    /// Fill the deck with complete packs
    for (int pack = 0; pack < num_packs; pack++) {
        for (Suit s = CLUB; s <= DIAMOND; s++) {
            for (Rank r = TWO; r <= ACE; r++) {
                Card c = { s, r };
                if (!addCardToEnd(deck, c)) {
                    // Memory allocation failed, clean up
                    freeDeck(deck);
                    return NULL;
                }
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
    if (!deck) {
        return;
    }

    /// Free all nodes in the linked list
    CardNode* current = deck->head;
    while (current) {
        CardNode* next = current->next;
        free(current);
        current = next;
    }

    /// Free the deck structure itself
    free(deck);
}

/**
 * @brief Shuffles the deck randomly
 */
void shuffleDeck(CardDeck* deck)
{
    if (!deck || deck->size <= 1) {
        return;
    }

    /// Convert linked list to array for shuffling
    Card* temp_array = malloc(deck->size * sizeof(Card));
    if (!temp_array) {
        return;
    }

    /// Copy cards to array
    CardNode* current = deck->head;
    for (int i = 0; i < deck->size; i++) {
        temp_array[i] = current->card;
        current = current->next;
    }

    /// Fisher-Yates shuffle
    for (int i = deck->size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = temp_array[i];
        temp_array[i] = temp_array[j];
        temp_array[j] = temp;
    }

    /// Copy shuffled cards back to linked list
    current = deck->head;
    for (int i = 0; i < deck->size; i++) {
        current->card = temp_array[i];
        current = current->next;
    }

    free(temp_array);
}
/**
 *@brief Adds a card to the beginning of the deck
 */
bool addCard(CardDeck* deck, Card card)
{
    if (!deck) {
        return false;
    }

    CardNode* new_node = createNode(card);
    if (!new_node) {
        return false;
    }

    /// Add to the beginning (head)
    new_node->next = deck->head;
    deck->head = new_node;

    /// If deck was empty, this is also the tail
    if (!deck->tail) {
        deck->tail = new_node;
    }

    deck->size++;
    return true;
}

/**
 * @brief Removes and returns the top card from the deck
 */
bool removeTopCard(CardDeck* deck, Card* out_card)
{
    if (!deck || !out_card || !deck->head) {
        return false;
    }

    // Store the card from the head node
    *out_card = deck->head->card;

    // Remove the head node
    CardNode* old_head = deck->head;
    deck->head = deck->head->next;

    // If we just removed the last card, update tail
    if (!deck->head) {
        deck->tail = NULL;
    }

    free(old_head);
    deck->size--;
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

    /// Special case: removing from position 0 (head)
    if (position == 0) {
        return removeTopCard(deck, out_card);
    }

    /// Traverse to the node before the target position
    CardNode* current = deck->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }

    /// Remove the node at position
    CardNode* to_remove = current->next;
    *out_card = to_remove->card;
    current->next = to_remove->next;

    /// If we removed the tail, update tail pointer
    if (!current->next) {
        deck->tail = current;
    }

    free(to_remove);
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
    CardNode* current = deck->head;
    int index = 0;
    while (current) {
        printf("%d: ", index++);
        printCard(&current->card);
        printf("\n");
        current = current->next;
    }
}