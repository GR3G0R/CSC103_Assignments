//Gregory Delpe
//Implementation of Typing Lesson

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

static const char a_car[] = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char car[] = "*&^%$#@!";
static const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static const char num[] = "0123456789";

char RNG() {
    int stringLength = sizeof(a_car) -1;
    return a_car[rand() % stringLength];
}


int main() {
srand(time(0));
int man_allow = 1000;
char ranCar = RNG();

while (true) {

cout << "Your current points " << man_allow << ", just type -> ";



for (int a = 1; a<=8;++a) {
for (int i= 0;i<sizeof(a_car)-1;++i) {
  char ranCar = RNG();
  if (ranCar  == num[i]) {
    cout << "[0-9]";
    break;
  }
  else if (ranCar  == alpha[i]) {
    cout << ranCar;
    break;
  }
  else if (ranCar == car[i]) {
    cout << "[%-&]";
    break;
  }
  else {
    continue;
  }
 }
}

cout <<  ": ";

char usr_input[7];

chrono::steady_clock::time_point begin = chrono::steady_clock::now();
cin >> usr_input;
chrono::steady_clock::time_point end= chrono::steady_clock::now();
int inSpeed = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

char ranCar_collect[7];
for (int i = 0; i < 7; ++i) {
ranCar_collect[i] = ranCar;
break;
}



if (inSpeed >= 7000) {
  man_allow -= (inSpeed - 7000);
  cout << inSpeed << " milliseconds, you *failed* it within the interval of 7000..."
    << endl << "String offset is ";
    
for (int i =  0;i<sizeof(usr_input);++i) {
    int offset = ranCar_collect[i] - usr_input[i];
    cout <<  offset;
    break;
}
    cout << ", your total penalty is " << (inSpeed - 7000)
    << "..." << endl << endl;
    continue;
}
else if (inSpeed <= 7000) {
  for (int i = 0; i<=7;++i){
    for (int j = 0; i<=7;++j){
    if (ranCar_collect[i] == usr_input[j]) {
     man_allow += 500;
     break;
    }
    else if (ranCar_collect[i] != usr_input[j]) {
    int offset = ranCar_collect[i] - usr_input[j];
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
if (man_allow<=0) {
  cout << "Bye..." << endl;
  break;
}

}

}
