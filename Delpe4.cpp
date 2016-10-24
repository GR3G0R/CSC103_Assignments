//Gregory Delpe
//Assignment #4: My Ship Sails

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
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
    void push_ship(const bool& b) { deck.push_back(b); }
    char getSuit(const Card& c) { return c.getCard(); }
    int getNum() const { return m_num; }

};
ostream& operator<<(ostream& o, const Card& c) {  //Overload extraction operator to produce higher order cards
    o << c.m_char;
    switch (c.m_num) {
    case 1: o  << 'A'; break;
    case 11: o << 'J'; break;
    case 12: o << 'K'; break;
    case 13: o << 'Q'; break;
    default: o << c.m_num;
    }
    return o;
}

bool operator==(const Card& a, const Card& b) {  //Overload equality operator
    //return a.m_char == b.m_char;
    return a.m_num == b.m_num;
}

bool operator!=(const Card& c, const Card& d) { //Overload not equal to operator
    //return !(c.m_char == d.m_char);
    return !(c.m_num == d.m_num);
}

bool operator<(const Card& c1, const Card& c2) {  //Overload less-than operator
    //return c1.m_char < c2.m_char;
    return c1.m_num < c2.m_num;
}




class Player: public Card {  //Introduce Player class

    string m_name;
    vector<Card> m_deck;
public:
    vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};  //Vector of deck elements

    Player(const string& n) : m_name(n) {m_deck.reserve(5); } //Player constructor
    void push_back(const Card& c) { m_deck.push_back(c); }  //Define member function push_back - push cards onto player deck
    void push_ship(const bool& b) { m_deck.push_back(b); }
    void push_char(const char& e) { m_deck.push_back(e); }
    friend ostream& operator<<(ostream&, const Player& p);  //Friend insertion operator
    friend bool operator==(const Player& c, const Player& d);  //Friend equality operator
    friend bool operator!=(const Player& a, const Player& b);  //Friend not equal to operator
    friend bool operator<(const Player& c1, const Player& c2); //Friend less-than operator
    char get_card(const Card& a) { return a.getCard(); }  //Access private member m_char trough member function getCard
    Card pass_card(int index) {  //Returns card to be removed and removes card from player deck
        Card result = m_deck[index];  //Assign returned card value to result variable
        m_deck.erase(m_deck.begin() + index);  //Remove element of chosen index, reduce container size, and shift position of remaining vectors
        return result;
    }
    string get_name() const { return m_name; }  //Access privat member m_name with member function
    vector<Card> get_hand() const { return m_deck; }  //Access private member m_deck with member function
    char get_Suit(const Card& c) { return c.getCard(); }
};

ostream& operator<<(ostream& o, const Player& p) {  //Extraction operator overloaded to print player name and hand
    //o << p.m_name << " ";
    for (int i = 0, len = p.m_deck.size(); i < len; ++i) {
        o << "(" << p.letters[i] << ") " << p.m_deck[i] << " ";
    }
    return o;
}

bool operator==(const Player& a, const Player& b) {  //Overload equality operator
    return a.get_hand() == b.get_hand();

}

bool operator!=(const Player& c, const Player& d) {  //Overload not equal to operator
    return !(c == d);
}

bool operator<(const Player& c1, const Player& c2) {  //Overload less-than operator
    return c1.get_hand() < c2.get_hand();
}


void print_players(vector<Player>& players) {  //Print each payer and thier hand
    for (int i = 0, len = players.size(); i < len; ++i)
        cout << players[i].get_name() << " " << players[i] << endl;
    cout << endl;
}

bool shipSails(vector<Card> playerHand) {  //Fuction determines if playrs ship has sailed
    sort(playerHand.begin(), playerHand.end());  //Sort player hand
    Card &c1 = playerHand.front();  //Access value of first vector elements by reference
    Card &c2 = playerHand.back();  //Access value of last vector element by reference
    if(c1 == c2) {  //Test for parity between fisrt and last element of sorted vector
        return true;  //Return boolean
    }
    else {
        return false;  //Return boolean
    }
}

void finalDistro(vector<Player> players) {  //Print final distribution
    for (int i = 0; i < 6; ++i) {
        cout << players[i].get_name() << " " <<  players[i] << endl;  //Print player name and hand
    }
}

void passCard(vector<Card> hand, vector<Card>& suitCount , vector<Player>& players, int i, vector<Card>& pCards) {  //Function controls passing scheme and mac intelligence
    Card cCard, sCard, hCard, dCard;
    int sCount = 0, cCount = 0, dCount = 0, hCount =0;
    int c_index, h_index, d_index, s_index;
    for (int i = 0; i < 7; ++i) {
        if (hand[i].getCard() == 'S') {  //Check for prsence of spade in player hand
            ++sCount;  //increment spade counter if instance of spade discovered
            sCard = hand[i];  //Copy card
            s_index = i;  //Capy card index
        }
        if (hand[i].getCard() == 'H') {  //Chaeck for presence of hearts in player hand
            ++hCount;  //increment heart counter if instance of heart disovered
            hCard = hand[i];  //Copy Card
            h_index = i; //Copy card index
        }
        if (hand[i].getCard() == 'C') {
            ++cCount;
            cCard = hand[i];
            c_index = i;
        }
        if (hand[i].getCard() == 'D') {
            ++dCount;
            dCard = hand[i];
            d_index = i;
        }
    }

    //Push objects of card suit and count onto vector suitCount
    if (sCount > 0) suitCount.push_back(Card('S', sCount));
    if (hCount > 0) suitCount.push_back(Card('H', hCount));
    if (dCount > 0) suitCount.push_back(Card('D', dCount));
    if (cCount > 0) suitCount.push_back(Card('C', cCount));

    Card least;
    sort(suitCount.begin(), suitCount.end());  //Sort vector suitCount
    for (int j = 0; j < suitCount.size(); ++j) {  //Identify least common suit
        if (suitCount[j].getNum() == '1') {
            least = suitCount[j];
        }
        else { least = suitCount.front(); }
    }

    if (least.getCard() == 'S') {  //Check for least common suit
        Card player_pass = players[i].pass_card(s_index);  //Assign card of least common suit to pass variable
        pCards.push_back(player_pass);  //Push card into pass card tracking vector
        players[(i+1) % players.size()].push_back(player_pass);  //Pass card to next player and remove from hand
    }
    else if (least.getCard() == 'H') {
        Card player_pass = players[i].pass_card(h_index);
        pCards.push_back(player_pass);
        players[(i+1) % players.size()].push_back(player_pass);
    }
    if (least.getCard() == 'D') {
        Card player_pass = players[i].pass_card(d_index);
        pCards.push_back(player_pass);
        players[(i+1) % players.size()].push_back(player_pass);
    }
    else if (least.getCard() == 'C') {
        Card player_pass = players[i].pass_card(c_index);
        pCards.push_back(player_pass);
        players[(i+1) % players.size()].push_back(player_pass);
    }


    suitCount.clear();  //Clear counter vector
}


int main() {
    vector<Player> players;
    char user_input;
    vector<Card> playerHand, playerHand1, playerHand2, playerHand3, playerHand4, suitCount, pCards;
    vector<bool> shipStatus;
    vector<Card> test = {'a','a','a','a'};  //Test variable

    for (int i = 0, len = suitCount.size(); i < len; ++i) { suitCount[i] = 0; }

    vector<Card> deck; deck.reserve(52);  //Declare vector deck
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('S',i));  //push_back spades suit
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('C',i));  //push_back clubs suit
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('D',i));  //push_back diamonds suit
    for (int i = 1; i <= 13; ++i) deck.push_back(Card('H',i));  //push_back clubs suit

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));  //Shuffle deck


    //Add contestants to vector players
    players.push_back(Player("Player 0"));
    players.push_back(Player("Player 1"));
    players.push_back(Player("Player 2"));
    players.push_back(Player("Player 3"));
    players.push_back(Player("Player 4"));
    //players.push_back(Player("Test"));  //Test player



    for (int i = 0, len = players.size(); i < len; ++i) {  //Deal 7 cards to each player
        for (int j = 0; j < 7; ++j) {
            Card c = deck.back();  //Assign reference to last elemement in vector deck to vriable c
            players[i].push_back(c);  //Push reference to card onto players vector
            deck.pop_back();  //Remove last element pushed to vector players from vector deck
        }
    }

    while(true) {
        for (int i = 0, len = players.size(); i < len; ++i) {

            cout <<  players[0] << endl << endl;  //Print deck and chracter reference for "Player 0"

            cout << "Which one to replace? ";  //Promt user to pass unwanted card
            cin >> user_input;  //Get user input
            cout << endl << endl;

            if (user_input == '?') {  //Hint - reveals all passed cards
                print_players(players);  //Print each player and their respective hand
                continue;
            }

            int index = find(players[0].letters.begin(), players[0].letters.end(), user_input) - players[0].letters.begin();  //Define variable for index of passed card
            Card passed_card = players[0].pass_card(index);  //variable passed_card is assigned returned card at index of card passed by user

            pCards.push_back(passed_card);  //Push user slected pass card to tracking vector

            players[(1) % players.size()].push_back(passed_card);  //Push passed card onto next players deck

            for (int i = 0, len = 7; i < len; ++i) {
                playerHand  = players[0].get_hand();  //Assign deck component of player to independent vector playerHand*
                playerHand1 = players[1].get_hand();
                playerHand2 = players[2].get_hand();
                playerHand3 = players[3].get_hand();
                playerHand4 = players[4].get_hand();
               //cout << playerHand[i] << endl << endl;  //Test - view independent playerHand
            }

            //void passCard(vector<Player> hand, vector<Card>& suitCount , vector<Player> players, int i) {
            passCard(playerHand1, suitCount, players, 1, pCards);
            passCard(playerHand2, suitCount, players, 2, pCards);
            passCard(playerHand3, suitCount, players, 3, pCards);
            passCard(playerHand4, suitCount, players, 4, pCards);

            for (int i = 0, len = players.size(); i < len; ++i)  //Produce user hint
                cout << "Hint: " << players[i].get_name() << " passed "
                    << pCards[i] << setw(5) << left << " to "
                    << right << players[(i+1) % players.size()].get_name() << endl;
                cout << endl;

            pCards.clear();  //Clear tracking vector

            //Build vector of booleans for status of
            //players with/without sailed ship
            shipStatus.push_back(shipSails(playerHand));
            shipStatus.push_back(shipSails(playerHand1));
            shipStatus.push_back(shipSails(playerHand2));
            shipStatus.push_back(shipSails(playerHand3));
            shipStatus.push_back(shipSails(playerHand4));
            //shipStatus.push_back(shipSails(test));  //Test shipSails method

            if (find(shipStatus.begin(), shipStatus.end(), true) != shipStatus.end()) {  //Search for any intance of sailed ship evaluated to 1
                for (int i = 0, len = shipStatus.size(); i < len; ++i) {  //Iterate over shipStatus
                    if(shipStatus[i] == 1) {  //Check if element returned true
                        cout << "My Ship Sails! --- " << players[i].get_name() << " Won..."  //Print name of players with sailed ship
                            << endl << endl;
                    }
                }
                finalDistro(players);  //Print final distribution
                return 0;  //End game
            }
            else {
                shipStatus.clear();  //Claer shipStatus
            }

            for (int i = 0, len = shipStatus.size(); i < len; ++i) {  //Test - view vector shipStatus
                cout << shipStatus[i] << endl << endl;
            }
        }
    }

    return 0;
}
