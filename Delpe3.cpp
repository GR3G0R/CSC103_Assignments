//Gregory Delpe
//Assignment 3: Animal Quz

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;


vector<string> pushtoken (string l) { //Fucntion pushes user input to vector string object for collection
  vector<string> tok;
  string token;
  bool found = false;
  for (int i = 0; i < l.length(); ++i) {
      if (!isspace(l[i])) { //If user input is not a blank space push string elements onto stack
          token += l[i];
          found = true;
          continue;
      }
      if (!found) continue; //If blank space is detected return to loop
      tok.push_back(token); //End of word reached -> stack padded with spaces
      token = "";
      found = false;
  }
  if (found) tok.push_back(token);  //If word detected -> pushed onto stack
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

int main() {
    srand(time(0));
    vector <string> tokens;
    string usr_input;
    string guess_word;

    cout << "Enter at least five animal names, e.g., cat, dog, etc..." << endl;
    while (true) {
        cout << "> ";
        getline(cin, usr_input); //Get user input
        if (usr_input == "") break; // QUIT

        vector<string> tok = pushtoken(usr_input); //Assign returned user input to local vector
        // TODO assert vector is at least five elements
        tokens.insert(tokens.end(), tok.begin(), tok.end());  //Push returned user input onto stack
        print_animals(tokens);

        random_shuffle(tokens.begin(), tokens.end());
        int num_animals = rand() % 3 + 1; // num_animals in the range 1 to 3
        vector <string> challenges;
        for (int i = 0; i < num_animals; i++) challenges.push_back(tokens[i]);
        string challenge;
        for_each(challenges.begin(), challenges.end(), [&](string &piece){ challenge += piece; });
        random_shuffle(challenge.begin(), challenge.end());
        cout << challenge << endl;
    }

}


