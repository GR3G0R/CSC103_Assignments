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

class Player {  //Introduce Player class
    string m_name;
    vector <Card> m_deck;
public:
    vector <char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    Player(const string& n) : m_name(n) {m_deck.reserve(5); } //Player constructor
    void push_back(const Card& c) {m_deck.push_back(c); }
    friend ostream& operator<<(ostream&, const Player& p);
    // Card get_card(int index) { return m_deck[index]; }
    Card pass_card(int index) {
        Card result = m_deck[index];
        m_deck.erase(m_deck.begin() + index);
        return result;
    }
};
// ostream& operator<<(ostream& o, const Player& p) {  //Extraction operator overloaded to print player name and hand
//     o << "Player: " << p.m_name << " has ";
//     for (int i = 0, len = p.m_deck.size(); i < len; ++i) {
//         o << p.m_deck[i] << " ";
//     }
//     return o;
// }
ostream& operator<<(ostream& o, const Player& p) {  //Extraction operator overloaded to print player name and hand
    o << p.m_name << " ";
    for (int i = 0, len = p.m_deck.size(); i < len; ++i) {
        o << "(" << p.letters[i] << ") " << p.m_deck[i] << " ";
    }
    return o;
}

// void print_players(vector<Player>& players) {  //Print each payer and thier hand
// for (int i = 0, len = players.size(); i < len; ++i)
//     cout << players[i] << endl;
// }
void print_players(vector<Player>& players) {  //Print each payer and thier hand
    for (int i = 0, len = players.size(); i < len; ++i)
        cout << players[i] << endl;
    cout << endl;
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

    print_players(players);
    for (int i = 0, len = players.size(); i < len; ++i) {
        cout << "Which one to replace? ";
        cin >> user_input;
        int index = find(players[i].letters.begin(), players[i].letters.end(), user_input) - players[i].letters.begin();
        Card passed_card = players[i].pass_card(index);
        players[(i+1) % players.size()].push_back(passed_card);
        print_players(players);
    }

    return 0;
}
