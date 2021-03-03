# Pontoon
A C++ implementation of the game Pontoon (a variation of Black Jack)

Features:
- The bank is an AI that uses probability to make intelligent guesses.
- The game makes good use of object orientated programming practises.

How to compile:
  The game utilises no libraries except the standard C++ ones. C++14 will work fine.
* C++ complier and version used:
  * C++ 11
  * C++ compiler: g++.exe (MinGW.org GCC-8.2.0-5) 8.2.0
  * Assembler: GNU assembler (GNU Binutils) 2.32
  * Make Tool: GNU Make 3.81

# Header files

* Bank.h
  * As the bank player header is an extension of the generic player class (Player.h), it inherits all functions a normal player would have. In addition to these functions, it has an additional function called “getChoice”. This returns a string value of either ‘t’ or ‘s’. This function has all the artificial intelligence inside it, it is easy to use for the game is it implemented for (Blackjack). The function uses a probability map, that uses simple risk analysis by using observation of previous cards observed in the round to guess which cards are most likely to appear next and thus which choice is the safest to make.
The algorithm works as follows:
    * All possible faces have a percentage probability of appearing (typically 4/52). However as faces Ten, Jack, Queen and King all have a value of 10, this makes the likelihood of getting a value of 10 4 x 4/52 = 16/52 at the beginning of the game.
    * The bank will then look at each card in their hand and reduce the likelihood of that face appearing again in the probability model for that face. E.g. if the hand contains a King and an Ace, both of their probabilities of appearing again would be 3/50 as we know we observed 1 instance of them, and 2 cards are no longer in the deck.
    * The bank totals the value of their hand and subtracts that from 21. This gives the value of cards that can be drawn from 1 to ? that wouldn’t make the bank go bust.
    * The bank sums all the cards that have a value greater than or equal to ? in values’ likelihood of appearing to get a percentage likelihood of going bust if twist is chosen
    * If this likelihood is above 50%, the bank sticks, otherwise it twists.
* Card.h
  * The card class is a generic class that can be used to represent a card in any game type. The suit and face are strings therefore have theoretically infinite different assignment possibilities. The value of each card is an integer as a card typically is either a whole value. This value is assigned to the card manually, so that the freedom of games types the card class is used for is large.
* Deck.h
  * This class uses an instance of the Stack class to emulate a deck of cards. This decided as typically you can only remove cards from the top of a deck of cards. This however added complications to having a method to shuffling it. Therefore to shuffle the cards, I temporarily copy all the cards into a vector and shuffle the vector. This vector then gets it’s content copied back to the stack.
The stack functions are hidden to anyone using an instance of the Deck, and instead I give the game 4 methods. isEmpty to see if the deck is empty, AddCardToDeck to allow the game to add a card to
the deck, Shuffle to shuffle the deck and DealACard to give a card to the game and also remove it form the stack.
* Player.h
  * This class is a generic player class that can be used to represent a player. It creates a vector of cards when the player is first created. This class has 4 basic functions, AddToHand which adds a card to the vector of cards, ShowCard to allow the card to be observed, GiveCard which does the same thing as ShowCard but also removes the card from the vector and getHandSize which returns the number of cards in the player’s hand.
* Stack.h
  * This is a template class that takes a deque (of any type) and restricts it’s functions to emulate a real stack. These functions include top(), push(), pop(), isEmpty() to see if the stack is empty and size() to return the size of the stack.

# <i>the algorithm used to shuffle the cards</i>
The algorithm used to the shuffle the cards is known as std::shuffle. This method of randomising was more secure then std::shuffle_random, and so the security of the shuffling algorithm was very good, as its purpose is to mix the cards around to make it very hard to predict what card will appear when. Also as by default the std::shuffle will give the same result everytime the program is initialised, the system epoch was used to generate a seed to ensure that this would not be the case.
Also, as a true stack cannot have it’s ordering modified directly, It was decided that copying the contents of stack to a vector first, shuffling the vector and finally copying this shuffled vector back to the stack.
# <i>how the cards/deck classes are reused and how they can be reused for other card games</i>
Both the Card and Deck classes are reused in both the card guessing game aswell as the Blackjack game. This is because the Card class was designed in such a way as to allow for any card to have any value assigned to it. This de-coupled nature of the value of the card compared to it’s face may seem more tedious but it allows for custom rule games such as the version of blackjack (which makes Ten, Jack, Queen and King all equal 10).
The Deck class can have any number of cards assigned to it, and has functions that are basic deck functions. This means if a special type of deck were to be implemented, it could simply inherit from this Deck and add it’s own functions.
# <i>what the data structure you used for representing the cards/deck and why</i>
For a card, a header file was used as this made the most sense. This allows for someone to either directly add functions/attributes for the card or even extends functionality using inheritance.
The deck uses a deque data structure, however the deque is specifically restricted to act as a stack as a stack is the closest resemblance to a deck of cards in real life. This is because typically a deck of cards gets accessed from the top.
<i>how polymorphism is implemented</i>
The Stack header file used uses polymorphism, even though it restricts the deque to behave like a stack. It still allows the “Stack” to be filled by any datatype that you want. Therefore, by extending it to a deck class I was able to utilise it to store a custom class called Card.
# <i>what custom template used and why</i>
A custom template was used for the Stack class as to allow it to be used with any type of data when being used in the Deck class. This was important as it was going to be used with the Card class instances.
