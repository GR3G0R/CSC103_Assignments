//Gregory Delpe
//Implementation of Typing Lesson

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

static const char a_car[] = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
string car = "*&^%$#@!";
string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
string num = "0123456789";


int main() {
srand(time(0));
int man_allow = 1000;
//string word;
while (true) {
string word;
cout << "Your current points " << man_allow << ", just type -> ";

for (int i = 0; i<7; ++i) word += a_car[rand() % 70];


for (int i = 0;i<word.length(); i++) {
  //char inWord = word;
  if (isdigit(word[i])) {
   cout << "[0-9]";
  }
  else if (isalpha(word[i])) {
   cout << word[i];
  }
  else {
   cout << "[%-&]";
   continue;
  }
}



cout <<  ": ";

char usr_input[7];

chrono::steady_clock::time_point begin = chrono::steady_clock::now();
cin >> usr_input;
chrono::steady_clock::time_point end= chrono::steady_clock::now();
int inSpeed = chrono::duration_cast<chrono::milliseconds>(end - begin).count();



if (inSpeed >= 7000) {
  man_allow -= (inSpeed - 7000);
  cout << inSpeed << " milliseconds, you *failed* it within the interval of 7000...";
   cout << endl << "String offset is ";
  
int offset;

for (int i=0;i<word.length(); ++i) {
    offset += word[i] - usr_input[i];
}

  cout << offset <<  ", your total penalty is " << (inSpeed - 7000) + offset
    << "..." << endl << endl;
  if (man_allow<=0) {
     cout << endl << endl << "Bye..." << endl;
     break;
  }
    continue;
}
else if (inSpeed <= 7000) {
  for (int i = 0; i<=7;++i){
    for (int j = 0; i<=7;++j){
    if (word[i] == usr_input[j]) {
     man_allow += 500;
     break;
    }
    else if (word[i] != usr_input[j]) {
    int offset = word[i] - usr_input[j];
    man_allow -= offset;
    break;
    }
    else {
    break;
    }
  }
}
  cout << inSpeed << " millisecond, you made it within the interval of 7000..."
    << endl << endl;
  continue;
}
else {
continue;
}
}

}
