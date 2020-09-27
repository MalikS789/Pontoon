/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bank.h
 * Author: Malik
 *
 * Created on 23 February 2020, 14:02
 */

#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include "Player.h"
#include "Card.h"

class Bank : public Player {
    /* the AI bank player that extends from the generic Player class */

public:

    /* use a probability model to make the Bank either 't' or 's' */
    std::string getChoice() {
        /* This vector will hold the likelyhood of which value will appear
         * next time a card is drawn from the deck */
        std::vector<double> likelyhoodOfFaceAppearing;
        /* In this case the possible values are from 1 to 10*/
        for (int i = 0; i < 10; i++) {
            if (i < 9) {
                /* There are 4 suits, each with a card of the same value (4/52) */
                likelyhoodOfFaceAppearing.push_back(4.0);
            } else {
                /* as Ten, Jack, Queen & King all have the value of 10, this 
                 means 4 x 4/52 = 16/52 */
                likelyhoodOfFaceAppearing.push_back(16.0);
            }
        }
        int Total = 0;
        for (int i = 0; i < getHandSize(); i++) {
            /* for each card in the bank's hand: */
            /* get the card value */
            int index = ShowCard(i).getValue();
            /* as we know this value has already been removed from the deck,
               we take 1 away from the value in the probability map*/
            likelyhoodOfFaceAppearing[index]--;
            /* add the value to the total to get the total value in the hand*/
            Total += index;
        }

        for (int i = 0; i < likelyhoodOfFaceAppearing.size(); i++) {
            /* convert each value in the probability map into a percentage 
             likelyhood of appearing next */
            likelyhoodOfFaceAppearing[i] /= ((52.0 - getHandSize()) / 100.0);
        }

        /* Leway = The values from 1 up to ? that we can afford to draw and not 
         * go bust */
        double leway = 21 - Total;
        double LikelyhoodToGoBust = 0.0;
        for (int i = leway - 1; i < likelyhoodOfFaceAppearing.size(); i++) {
            /* for every value that can cause the bank to go bust, add the 
             likelyhood of that value appearing to the total likelyhood of 
             going bust */
            LikelyhoodToGoBust += likelyhoodOfFaceAppearing[i];
        }

        /* choose the likelyhood threshold for which to either twist or stick */
        if (LikelyhoodToGoBust < 50.0) {
            return "t";
        } else {
            return "s";
        }
    }

};

#endif /* BANK_H */