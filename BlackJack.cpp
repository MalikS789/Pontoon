#include "Deck.h"
#include "Bank.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {

        /* keep track of each player's wins and losses */
        vector<bool> PlayersRoundsWon;
        vector<bool> BankRoundsWon;
    
        bool continuePlaying = true;
        /* we keep playing until the player wants to quit */
        while (continuePlaying) {
    
            /* Both player and bank are initialised */
            Player player;
            Bank bank;
    
            /* initialise a new deck */
            Deck deck;
    
            /* fill the deck with a standard set of 52 playing cards */
            for (int j = 1; j < 5; ++j) {
                string suit = "";
                if (j == 1)
                    suit = "Diamonds";
                else if (j == 2)
                    suit = "Hearts";
                else if (j == 3)
                    suit = "Spades";
                else if (j == 4)
                    suit = "Clubs";
                for (int i = 1; i < 14; ++i) {
                    string face = "";
                    if (i == 1)
                        face = "Ace";
                    else if (i == 2)
                        face = "Two";
                    else if (i == 3)
                        face = "Three";
                    else if (i == 4)
                        face = "Four";
                    else if (i == 5)
                        face = "Five";
                    else if (i == 6)
                        face = "Six";
                    else if (i == 7)
                        face = "Seven";
                    else if (i == 8)
                        face = "Eight";
                    else if (i == 9)
                        face = "Nine";
                    else if (i == 10)
                        face = "Ten";
                    else if (i == 11)
                        face = "Jack";
                    else if (i == 12)
                        face = "Queen";
                    else if (i == 13)
                        face = "King";
                    if (i >= 10) {
                        /* in this case, we want Ten, Jack, Queen and King to all
                         have a value of 10 regardless of what their face is */
                        int k = 10;
                        Card card(k, suit, face);
                        deck.AddCardToDeck(card);
                    } else {
                        Card card(i, suit, face);
                        deck.AddCardToDeck(card);
                    }
                }
            }
    
            /* shuffle the cards */
            deck.Shuffle();
    
            /* deal 2 cards to the bank */
            bank.AddToHand(deck.DealACard());
            bank.AddToHand(deck.DealACard());
    
            /* deal 2 cards to the player */
            player.AddToHand(deck.DealACard());
            player.AddToHand(deck.DealACard());
    
            bool playerChooseToStick = false;
            bool bankChooseToStick = false;
    
            while (true) {
    
                if (playerChooseToStick && bankChooseToStick) {
                    /*both player and bank choose to stick, so we now find out who 
                     got a higher value in hand*/
                    int playerTotal = 0;
                    int bankTotal = 0;
    
                    /* find total value in both player and bank's hand*/
                    for (int i = 0; i < player.getHandSize(); i++) {
                        playerTotal += player.ShowCard(i).getValue();
                    }
    
                    for (int i = 0; i < bank.getHandSize(); i++) {
                        bankTotal += bank.ShowCard(i).getValue();
                    }
    
                    if (playerTotal > bankTotal) {
                        //player wins as they have a higher value in hand
                        BankRoundsWon.push_back(false);
                        PlayersRoundsWon.push_back(true);
                        cout << "You win as you have higher value in your hand!" << endl;
                        cout << "" << endl;
                        break;
                    } else if (bankTotal > playerTotal) {
                        //bank wins as they have a higher value in hand
                        BankRoundsWon.push_back(true);
                        PlayersRoundsWon.push_back(false);
                        cout << "bank wins as it has higher value in its hand" << endl;
                        cout << "" << endl;
                        break;
                    } else {
                        /*both player and bank have equal value in hand */
                        if (player.getHandSize() > bank.getHandSize()) {
                            //player wins as they have more cards in their hand
                            BankRoundsWon.push_back(false);
                            PlayersRoundsWon.push_back(true);
                            cout << "both you and bank have same value in hand, but you have more cards so you win" << endl;
                            cout << "" << endl;
                            break;
                        } else if (bank.getHandSize() > player.getHandSize()) {
                            //bank wins as they have more cards in their hand
                            BankRoundsWon.push_back(true);
                            PlayersRoundsWon.push_back(false);
                            cout << "both you and bank have same value in hand, but bank has more cards so bank wins" << endl;
                            cout << "" << endl;
                            break;
                        } else {
                            //on the rare occasion that both players and bank have same number of cards and same total value
                            BankRoundsWon.push_back(true);
                            PlayersRoundsWon.push_back(false);
                            cout << "both you and bank have same value and number of cards in hand so bank wins according to default rules of pontoon" << endl;
                            cout << "" << endl;
                            break;
                        }
                    }
                }
    
                playerChooseToStick = false;
                bankChooseToStick = false;
                string choice = "";
                bool bust = false;
                bool bankBust = false;
                int total = 0;
                int bankTotal = 0;
                while (true) {
    
                    /* show the player their hand */
                    cout << "your hand is : " << endl;
                    cout << "" << endl;
                    total = 0;
                    for (int i = 0; i < player.getHandSize(); i++) {
    
                        /* print each card which appropriate formatting */
                        cout << player.ShowCard(i).getFace() << " of " << player.ShowCard(i).getSuit() << endl;
    
                        /* as we are print each card, add the value of that card to
                         the player's hands' total */
                        total += player.ShowCard(i).getValue();
                        if (total >= 21) {
                            /* as the value is 21 or more, the player is bust */
                            bust = true;
                        }
                    }
                    if (player.getHandSize() >= 5) {
                        /* if the player has 5 or more cards in their hand, they 
                         automatically lose*/
                        break;
                    }
                    if (bust) {
                        /* as the value is 21 or more, the player is bust */
                        cout << "BUST!!!" << endl;
                        cout << "" << endl;
                        break;
                    }
                    cout << "value = " << total << endl;
                    cout << "" << endl;
                    cout << "[s]tick or [t]wist?" << endl;
                    cout << "" << endl;
                    cin >> choice;
                    if (choice == "t") {
                        /* if they chose to twist, add a card to the hand and loop
                         go to the beginning of the loop */
                        player.AddToHand(deck.DealACard());
                    }
                    if (choice == "s") {
                        /* if they chose to stick, break out of the loop */
                        playerChooseToStick = true;
                        break;
                    }
                }
                if (bust || player.getHandSize() >= 5) {
                    /* one of the lose conditions is meet, so add the point for the
                     * round to the bank and also tell the player they lost */
                    BankRoundsWon.push_back(true);
                    PlayersRoundsWon.push_back(false);
                    cout << "Bad luck, the bank won." << endl;
                    cout << "" << endl;
                    break;
                }
                while (bankTotal < total) {
                    /* while the bank's hands' total is less then the player's hands' total: */
                    bankTotal = 0;
                    cout << "the banks hand is : " << endl;
                    cout << "" << endl;
                    for (int i = 0; i < bank.getHandSize(); i++) {
                        cout << bank.ShowCard(i).getFace() << " of " << bank.ShowCard(i).getSuit() << endl;
                        bankTotal += bank.ShowCard(i).getValue();
                        if (bankTotal >= 21) {
                            bankBust = true;
                        }
                    }
                    cout << "value = " << bankTotal << endl;
                    cout << "" << endl;
                    if (bank.getHandSize() >= 5) {
                        break;
                    }
                    if (bankBust) {
                        cout << "BUST!!!" << endl;
                        cout << "" << endl;
                        break;
                    }
                    choice = bank.getChoice(); //AI
                    if (choice == "t") {
                        cout << "the bank draws a card..." << endl;
                        cout << "" << endl;
                        Card card = deck.DealACard();
                        bank.AddToHand(card);
                    }
                    if (choice == "s") {
                        bankChooseToStick = true;
                        break;
                    }
                }
    
                if (bankBust || bank.getHandSize() >= 5) {
                    /* one of the lose conditions is meet, so add the point for the
                     *  round to the player and also tell the player the bank lost */
                    PlayersRoundsWon.push_back(true);
                    BankRoundsWon.push_back(false);
                    cout << "Well done, you won!!!" << endl;
                    cout << "" << endl;
                    break;
                }
            }
            string choice = "";
            while (choice != "y" && choice != "n") {
                /* this while loop does input validation as it will continuously 
                 * ask the play if they want to play again until they answer y or n*/
                cout << "do you want to play again ([y]es/[n]o)?" << endl;
                cout << "" << endl;
                cin >> choice;
                if (choice == "n") {
                    continuePlaying = false;
                }
            }
        }
        /* at the end of the game, print the statistics of the rounds */
        cout << "Rounds: " << PlayersRoundsWon.size() << endl;
        int RoundsWon = 0;
        int RoundsLost = 0;
        for (int i = 0; i < PlayersRoundsWon.size(); i++) {
            if (PlayersRoundsWon.at(i) == true) {
                RoundsWon++;
            } else if (PlayersRoundsWon.at(i) == false) {
                RoundsLost++;
            }
        }
        cout << "Won: " << RoundsWon << endl;
        cout << "Lost: " << RoundsLost << endl;
        cout << "-- " << endl;
        for (int i = 0; i < PlayersRoundsWon.size(); i++) {
            if (PlayersRoundsWon.at(i)) {
                cout << "Round " << i + 1 << ": won." << endl;
            } else if (BankRoundsWon.at(i)) {
                cout << "Round " << i + 1 << ": lost." << endl;
            }
        }
        cout << "" << endl;
        cout << "Thanks, bye!" << endl;


}