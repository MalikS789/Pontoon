/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Card.h
 * Author: Malik
 *
 * Created on 15 February 2020, 16:40
 */

#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:

    /* A generic card class that can be used to represent a card in a variety
     of games */
    Card(int &valuee, std::string &suitt, std::string &facee) :
    value(valuee), suit(suitt), face(facee) {
    }

    std::string getFace() {
        return face;
    }

    void setFace(std::string &facee) {
        face = facee;
    }

    std::string getSuit() {
        return suit;
    }

    void setSuit(std::string &suitt) {
        suit = suitt;
    }

    int getValue() {
        return value;
    }

    void setValue(int &valuee) {
        value = valuee;
    }

private:
    int value;
    std::string face;
    std::string suit;
};

#endif /* CARD_H */