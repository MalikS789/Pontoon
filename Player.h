/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: Malik
 *
 * Created on 22 February 2020, 15:29
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <iostream>
#include <vector>
#include <algorithm>

class Player {
    /* a generic Player class */

public:
    /* add a new card to the player's hand */
    void AddToHand(Card card) {
        hand.push_back(card);
    }

    /* returns the card at the index of the hand's vector */
    Card ShowCard(int index) {
        return hand[index];
    }

    /* return the card at the index of the hand's vector, and also removes
     it from the hand */
    Card GiveCard(int index) {
        Card card = hand[index];
        hand.erase(hand.begin() + index);
        return card;
    }

    /* returns the number of cards in the player's hand */
    int getHandSize() {
        return hand.size();
    }

private:
    std::vector<Card> hand;
};

#endif /* PLAYER_H */