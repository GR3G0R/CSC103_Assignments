//Gregory Delpe
//Assignment #4: My Ship Sails

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

class Card {  //Introduce Card Class
    char m_char;
    int m_num;
    vector<char> deck;
public:
    Card(const char s = 'S', const int n = 0) : m_char(s), m_num(n) {}  //Card class constructor
    friend ostream& operator<<(ostream&, const Card&);  //Friend insertion operator
    friend bool operator==(const Card& c, const Card& d);  //Friend equality operator
    friend bool operator!=(const Card& a, const Card& b);  //Friend not equal to operator
    friend bool operator<(const Card& c1, const Card& c2); //Friend less-than operator
    char getCard() const { return m_char; }  //Access private member m_char trough member function getCard
};
ostream& operator<<(ostream& o, const Card& c) {  //Overload extraction operator to produce higher order cards
    o << c.m_char;
    switch (c.m_num) {
    case 1: o << 'A'; break;
    case 11: o << 'J'; break;
    case 12: o << 'K'; break;
    case 13: o << 'Q'; break;
    default: o << c.m_num;
    }
    return o;
}

bool operator==(const Card& a, const Card& b) {  //Overload equality operator
    return a.m_char == b.m_char;

}

bool operator!=(const Card& c, const Card& d) { //Overload not equal to operator
    return !(c.m_char == d.m_char);
}

bool operator<(const Card& c1, const Card& c2) {  //Overload less-than operator
    return c1.getCard() < c2.getCard();
}




class Player {  //Introduce Player class

    string m_name;
    vector<Card> m_deck;
public:
    vector <char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};  //Vector of deck elements

    Player(const string& n) : m_name(n) {m_deck.reserve(5); } //Player constructor
    void push_back(const Card& c) {m_deck.push_back(c); }  //Define member function push_back - push cards onto player deck
    friend ostream& operator<<(ostream&, const Player& p);  //Friend insertion operator
    // Card get_card(int index) { return m_deck[index]; }
    friend bool operator==(const Player& c, const Player& d);  //Friend equality operator
    friend bool operator!=(const Player& a, const Player& b);  //Friend not equal to operator
    Card pass_card(int index) {  //Returns card to be removed and removes card from player deck
        Card result = m_deck[index];  //Assign returned card value to result variable
        m_deck.erase(m_deck.begin() + index); return result;  //Remove element of chosen index, reduce container size, and shift position of remaining vectors
    }
    string get_name() const { return m_name; }  //Access privat member m_name with member function
    vector<Card> get_hand() const { return m_deck; }  //Access private member m_deck with member function
};
// ostream& operator<<(ostream& o, const Player& p) {  //Extraction operator overloaded to print player name and hand
//     o << "Player: " << p.m_name << " has ";
//     for (int i = 0, len = p.m_deck.size(); i < len; ++i) {
//         o << p.m_deck[i] << " ";
//     }
//     return o;
// }
ostream& operator<<(ostream& o, const Player& p) {  //Extraction operator overloaded to print player name and hand
    //o << p.m_name << " ";
    for (int i = 0, len = p.m_deck.size(); i < len; ++i) {
        o << "(" << p.letters[i] << ") " << p.m_deck[i] << " ";
    }
    return o;
}

bool operator==(const Player& a, const Player& b) {
    return a.get_hand() == b.get_hand();

}

bool operator!=(const Player& c, const Player& d) {
    return !(c == d);
}

void print_players(vector<Player>& players) {  //Print each payer and thier hand
    for (int i = 0, len = players.size(); i < len; ++i)
        cout << players[i] << endl;
    cout << endl;
}

void shipSails(vector<Card> playerHand) {
    sort(playerHand.begin(), playerHand.end());
    Card &c1 = playerHand.front();
    Card &c2 = playerHand.back();
    if(c1 == c2) {
        cout << "True" << endl;
    }
    else { cout << "False" << endl; }
}


int main() {
    vector<Player> players;
    char user_input;
    vector<Card> playerHand, playerHand1, playerHand2, playerHand3, playerHand4;

    vector<Card> deck; deck.reserve(52);  //Declare vector deck
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('S',i));  //push_back spades suit
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('C',i));  //push_back clubs suit
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('D',i));  //push_back diamonds suit
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('H',i));  //push_back clubs suit
    random_shuffle(deck.begin(),deck.end());  //Shuffle deck

    //Add
    players.push_back(Player("Player0"));
    players.push_back(Player("Player1"));
    players.push_back(Player("Player2"));
    players.push_back(Player("Player3"));
    players.push_back(Player("Player4"));


    for (int i = 0, len = players.size(); i < len; ++i) {  //Deal 7 cards to each player
        for (int j = 0; j < 7; ++j) {
            Card c = deck.back();
            players[i].push_back(c);
            deck.pop_back();
        }
    }

    while(true) {
        for (int i = 0, len = players.size(); i < len; ++i) {

           cout <<  players[0] << endl << endl;

            cout << "Which one to replace? ";  //Promt user to pass unwanted card
            cin >> user_input;  //Get user input

            if (user_input == '?') {  //Hint - reveals all passed cards
                print_players(players);  //Print each player and their respective hand
                continue;
            }

            int index = find(players[i].letters.begin(), players[i].letters.end(), user_input) - players[i].letters.begin();  //Define variable for index of passed card
            Card passed_card = players[i].pass_card(index);  //variable passed_card is assigned returned card at index of card passed by user

            for (int i = 0, len = players.size(); i < len; ++i)
                cout << "Hint: " << players[i].get_name() << " passed "
                    << passed_card << " to " << players[i + 1 ].get_name() << endl;
                cout << endl;

            players[(i+1) % players.size()].push_back(passed_card);  //Push passed card onto next players deck

            for (int i = 0, len = 7; i < len; ++i) {
                playerHand = players[0].get_hand();  //Assign deck component of player to vector player_hand
                playerHand1 = players[1].get_hand();
                playerHand2 = players[2].get_hand();
                playerHand3 = players[3].get_hand();
                playerHand4 = players[4].get_hand();
                //for (int j = 0, len = player_hand.size(); j < len; ++j) {
                    cout << playerHand[i] << endl;
            //}
            }

            shipSails(playerHand); //Determine if players ship sails
        }
    }

    return 0;
}
