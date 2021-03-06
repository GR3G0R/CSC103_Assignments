//Gregory Delpe
//Assignment 3: Animal Quz

#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <set>
#include <unordered_set>
#include <random>
#include <chrono>
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
    if (found) tok.push_back(token);  //If word detected -> pushed onto stack
    return tok;
}

void print_animals(vector<string> animals) {  //Print list of animals names chosen by user
    for (int i = 0; i < animals.size(); ++i) {
        cout << i + 1 << ": " << animals[i] << endl;
    }
    cout << endl;
}


string scramble (vector<string> capture, vector<string>& challenge_words, int& num_animals){  //Generate randomly shuffled string
    string challenge;
    set<string> cw;
    default_random_engine generator ((unsigned int)time(0));  //Construct random generator engine
    uniform_int_distribution<int> distribution(1,3);  //num_animals in the range 1 to 3
    num_animals = distribution(generator);  //Assign num_animals with random int in range of 1 to 3
    random_shuffle(capture.begin(), capture.end());  //Shuffle list of animals chosen by user
    for (int i = 0; i < num_animals; ++i) cw.insert(capture[i]);
    challenge_words.assign(cw.begin(), cw.end());
    for_each(challenge_words.begin(), challenge_words.end(), [&](string &piece){ challenge += piece; });  //Construct string from vector
    random_shuffle(challenge.begin(), challenge.end());  //Scramble string
    return challenge;
}

void success(int& successes, int& fails, int& scount) {  //Track successful guesses
    fails = 0;
    successes += 1;
    if (successes >= 2) {
        scount += 1;
        successes = 0;
        }
    cout << "Yes!\n" << endl;
    if (successes % 2 == 0) {
        cout << "Succeeded two consecutive times, challenge goes up!\n"<< endl;
    }
}

void fail(int& successes, int& fails,int& scount) {  //Track unseccessful guesses
    successes = 0;
    fails += 1;
    if (fails >= 2) {
        scount -= 1;
        fails = 0;
        }
    if (scount < 0) scount = 0;
    cout << "Nope!\n"  << endl;
    if (fails % 2 == 0) {
        cout << "Missed two consecutive times, challenge goes down!\n" << endl;
    }
}

int main() {
    vector<string> tokens, challenge_words, guess_words;
    string usr_input, input, guess_word;
    int num_animals, successes = 0, fails = 0, scount = 0;

    cout << "Enter at least five animal names, e.g., cat, dog, etc..." << endl;  //Promt user for to input 5 animals
    while (true) {
        cout << "> ";
        getline(cin, usr_input); //Get user input
        vector<string> tok = pushtoken(usr_input); //Assign returned user input to local vector
        tokens.insert(tokens.end(), tok.begin(), tok.end());  //Push returned user input onto stack
        if (usr_input == "") break;  //Register usr_input

    }

    print_animals(tokens);
    assert (tokens.size() >= 5);  //Assert vector is at least five elements


    while(true) {
        guess_word = scramble(tokens, challenge_words, num_animals);  //Assign scrambled word to local string guess_word

        for (int i = 0; i < scount; ++i) {  //Regulate strikes
            while(true) {
                int index = rand() % guess_word.length();
                if (guess_word[index] == '_') continue;
                    guess_word[index] = '_';
                    break;
                }
        }

        cout << "What are " << num_animals << " animals in \"" << guess_word << "\" ? ";  //Promt user to guess animals in guess_word
        getline(cin, input);
        //guess_words = pushtoken(input);  //Push guess_word response onto guess stack

        if (input == "quit") {
            cout << "Bye..";
            return 0;  //QUIT game
        }
        else if (input == "?") {  //Print list of animal names chosen by user
            print_animals(tokens);
            continue;
        }
        else {
            guess_words = pushtoken(input);
        }

        if (guess_words.size() < challenge_words.size()) {  //Promt user for additional input
            cout << "Your number of input is incorrect. Enter again: ";
            guess_words.clear();
            getline(cin, input);
            if (input == "quit") {
                cout << "Bye..";
                return 0;  //QUIT game
            }
            else if (input == "?") {  //Print list of animal names chosen by user
                print_animals(tokens);
                continue;
            }
            guess_words = pushtoken(input);  //Push guess_word response onto guess stack
        }

        unordered_set<string> set_guess_words(guess_words.begin(), guess_words.end());  //Convert guess_words vector to set
        unordered_set<string> set_challenge_words(challenge_words.begin(), challenge_words.end());  //Convert challange_words vector to set

        if (set_guess_words == set_challenge_words) { //Set comparator determines if guess == scrambled word
            success(successes, fails, scount);
        }
        if (set_guess_words != set_challenge_words) {
            fail(successes, fails, scount);
        }
    }
}
