/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Deck.h
 * Author: Malik
 *
 * Created on 15 February 2020, 11:33
 */

#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "Stack.h"
#include <algorithm>    // std::shuffle
#include <vector>       // std::vector
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

class Deck {
    /* used a stack to emulate how a deck of cards works */

public:

    /* determine whether Deck is empty */
    bool isEmpty() const {
        return stack.isEmpty();
    }

    /* add card to the top of the deck */
    void AddCardToDeck(Card &card) {
        stack.push(card);
    }

    /* Shuffle all values in the Deck */
    void Shuffle() {
        /* as we cannot reorder in a stack, copy all contents of stack into a 
         vector. As we do so, we ensure the card is removed from the stack */
        std::vector<Card> order;
        while (!stack.isEmpty()) {
            order.push_back(DealACard());
        }
        /* re-order all cards randomly in the vector */
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng(seed);
        std::shuffle(std::begin(order), std::end(order), rng);

        /* add the cards from the shuffled vector back into the deck */
        for (size_t i = 0; i < order.size(); i++) {
            AddCardToDeck(order.at(i));
        }
    }

    /* return the card from the top of the deck (removing it from the deck
     in the process) */
    Card DealACard() {
        Card cardd = stack.top();
        stack.pop();
        return cardd;
    }

private:
    /* We are using an instance of stack (which is a restricted deque) */
    Stack<Card> stack;
};

#endif /* DECK_H */