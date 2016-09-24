//Gregory Delpe
//Implementation of Typing Lesson

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cassert>
using namespace std;

static const char a_car[] = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char car[] = "*&^%$#@!";
static const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
static const char num[] = "0123456789";
//"!@#$%^&*" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
int stringLength = sizeof(a_car) -1;

char genRandom() {
    return a_car[rand() % stringLength];
}

int main() {
srand(time(0));
int mac_allow = 1000, man_allow = 1000;
cout << "Your current points 1000, just type -> " <<  ": ";
string usr_input;
//clock_t begin = clock();
chrono::steady_clock::time_point begin = chrono::steady_clock::now();
cin >> usr_input;
chrono::steady_clock::time_point end= chrono::steady_clock::now();
cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;
/*for (int i = 0;i<7;++i) {
genRandom();
}*/
//while(true) {
for(int a = 1; a<=7;++a) {
for (int i = 0;i<sizeof(a_car)-1;++i) {
  char g = genRandom();
  if (g  == num[i]) {
    cout << "[0-9]";
    break;
  }
  else if (g  == alpha[i]) {
    cout << g;
    break;
  }
  else if (g == car[i]) {
    cout << "[%-&]"; 
    break;
  }
  else {
    continue;
  }
}
//}
}
//clock_t end = clock();
//double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//cout << elapsed_secs << endl;
}
