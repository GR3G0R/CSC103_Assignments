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
public:
    Card(const char s = 'S', const int n = 0) : m_char(s), m_num(n) {}  //Card class constructor
    friend ostream& operator<<(ostream&, const Card&);
    friend bool operator==(const Card& c, const Card& d);
    friend bool operator!=(const Card& a, const Card& b);
};
ostream& operator<<(ostream& o, const Card& c) {  //Overload extraction operator to produce card value
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

bool operator==(const Card& a, const Card& b) {
    return a == b;

}

bool operator!=(const Card& c, const Card& d) {
    return !(c == d);
}



class Player {  //Introduce Player class
    string m_name;
    vector<Card> m_deck;
public:
    vector <char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    Player(const string& n) : m_name(n) {m_deck.reserve(5); } //Player constructor
    void push_back(const Card& c) {m_deck.push_back(c); }
    friend ostream& operator<<(ostream&, const Player& p);
    // Card get_card(int index) { return m_deck[index]; }
    friend bool operator==(const Player& c, const Player& d);
    friend bool operator!=(const Player& a, const Player& b);
    Card pass_card(int index) {  //Returns card to be removed and removes card from player deck
        Card result = m_deck[index];
        m_deck.erase(m_deck.begin() + index); return result;
    }
    string get_name() const { return m_name; }
    vector<Card> get_hand() const { return m_deck; }
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

/*class Hint {
   Player p_name;
   Card passed_card;
   int index;
public:
    Hint(const Card c, const Player = p) passed_card(c), p_name(p) {}
    friend ostream& operator<<(ostream&, const Hint& h);
};
ostream& operator<<(ostream& o, const Hint& h) {

}*/
// void print_players(vector<Player>& players) {  //Print each payer and thier hand
// for (int i = 0, len = players.size(); i < len; ++i)
//     cout << players[i] << endl;
// }
void print_players(vector<Player>& players) {  //Print each payer and thier hand
    for (int i = 0, len = players.size(); i < len; ++i)
        cout << players[i] << endl;
    cout << endl;
}

void winner(vector<Card>& hand) {
/*for ( int i = 0, len = hand.size(); i < len; ++i) {
		if( hand[i] == hand[i+1] ) {
        cout << "True";
    }
    else {
        cout << "False";
    }
	}
}*/
    if (equal(hand.begin() + 1, hand.end(), hand.begin()) ) {
        cout << "True";
    }
    else if (!equal(hand.begin() + 1, hand.end(), hand.begin())) {
        cout << "False" << endl; }
    else {
        cout << "False" << endl;
    }
}

int main() {
    vector<Player> players;
    char user_input;

    vector<Card> deck; deck.reserve(52);  //Declare vector deck
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('S',i));  //push_back spades suit
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('C',i));  //push_back clubs suit
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('D',i));  //push_back diamonds suit
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('H',i));  //push_back clubs suit
    random_shuffle(deck.begin(),deck.end());  //Shuffle deck

    players.push_back(Player("Player1"));  //push_back players
    players.push_back(Player("Player2"));
    players.push_back(Player("Player3"));
    players.push_back(Player("Player4"));
    players.push_back(Player("Player5"));


    for (int i = 0, len = players.size(); i < len; ++i) {
        for (int j = 0; j < 7; ++j) {
            Card c = deck.back();
            players[i].push_back(c);
            deck.pop_back();
        }
    }

    vector<Card> player_hand;
    for (int i = 0, len = players.size(); i < len; ++i) {
        player_hand = players[0].get_hand();
        //for (int j = 0, len = player_hand.size(); j < len; ++j) {
                cout << player_hand[i] << endl;
        //}
    }
    //winner(player_hand);
    /*if (equal(player_hand.begin() + 1, player_hand.end(), player_hand.begin()) ) {
    cout << "True";
    }*/


    while(true) {
        for (int i = 0, len = players.size(); i < len; ++i) {
            cout << "Which one to replace? ";
            cin >> user_input;

            if (user_input == '?') {
                for (int i = 0, len = players.size(); i < len; ++i)
                    cout << "Hint: " << players[i].get_name() << " passed "
                        << "passed_card" << " to " << players[i + 1 ].get_name() << endl;
                    cout << endl;
                    continue;
            }

        int index = find(players[i].letters.begin(), players[i].letters.end(), user_input) - players[i].letters.begin();
        Card passed_card = players[i].pass_card(index);
        players[(i+1) % players.size()].push_back(passed_card);
        print_players(players);
    }
    }

    return 0;
}
