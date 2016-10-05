//Gregory Delpe
//Assignment 3: Animal Quz

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
using namespace std;


vector<string> pushtoken (string l) {  //Fucntion pushes user input to vector string object for collection
    vector<string> tok;
    string token;
    bool found = false;
    for (int i = 0; i < l.length(); ++i) {
        if (!isspace(l[i])) {  //If user input is not a blank space push string elements onto stack
            token += l[i];
            found = true;
            continue;
        }
        if (!found) continue;  //If blank space is detected return to loop
        tok.push_back(token);  //End of word reached -> stack padded with spaces
        token = "";
        found = false;
    }
    if (found) tok.push_back(token);      //If word detected -> pushed onto stack
    return tok;
}

// void game_init () {
//   shuffle(tokens.begin(),tokens.end());
//   int num_animals = uniform_int_distribution <int> (1,3) rand();
//   for (int i = 0; i < num_animals; i++) choice.push_back(i);
//   shuffle(choice.begin(),choice.end());
//
// }

void print_animals(vector <string> animals) {
    for (int i = 0; i < animals.size(); ++i) {
        cout << i + 1 << ": " << animals[i] << endl;
    }
}

string scramble (vector <string> capture,int& num_animals){  //Generate randomly shuffled string
    srand(time(0));
    string challenge;
    vector <string> challenges;
    random_shuffle(capture.begin(), capture.end());
    num_animals = rand() % 3 + 1;  // num_animals in the range 1 to 3
    for (int i = 0; i < num_animals; i++) challenges.push_back(capture[i]);
    for_each(challenges.begin(), challenges.end(), [&](string &piece){ challenge += piece; });  //Construct string from vector
    random_shuffle(challenge.begin(), challenge.end());  //Scramble string
    return challenge;
}

int main() {
    vector <string> tokens, guess;
    string usr_input, input,  guess_word;
    int num_animals;

    cout << "Enter at least five animal names, e.g., cat, dog, etc..." << endl;
    while (true) {
        // if (usr_input == "?") {
        //     print_animals(tokens);
        //     usr_input = "";
        //     continue;
        // }
        cout << "> ";
        getline(cin, usr_input); //Get user input
        vector<string> tok = pushtoken(usr_input); //Assign returned user input to local vector
        tokens.insert(tokens.end(), tok.begin(), tok.end());  //Push returned user input onto stack
        guess_word = scramble(tokens, num_animals);
        if (usr_input == "") break;  // QUIT

    }

    print_animals(tokens);
    cout << endl;
    assert (tokens.size() >= 5);  //Assert vector is at least five elements
    cout << "What are 2 animals in \"" << guess_word << "\" ? ";
    
    for (int i = 0; i < num_animals; ++i) {
        getline(cin, input);
        if (input == "Quit") return 0;
        if (input == "?") print_animals(tokens);
        guess.push_back(input);
    }

   /* for (int i = 0; i < tokens.size(); ++i) {
        cout << tokens[i];

    }*/
}


