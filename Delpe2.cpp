//Gregory Delpe
//Implementation of Typing Lesson

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cassert>
using namespace std;

static const char a_car[] = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'\0'";
static const char car[] = "*&^%$#@!'\0'";
static const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'\0'";
static const char num[] = "0123456789'\0'";
//static const char alphanum[] = "0123456789" "!@#$%^&*" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";

char genRandom() {
    int stringLength = sizeof(a_car) -1;
    return a_car[rand() % stringLength];
}

int main() {
srand(time(0));
int mac_allow = 1000, man_allow = 1000;

//while (true) {
  cout << "Your current points 1000, just type -> ";


or (int a = 1; a<=7;++a) {
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


}

#if 0
//<<  ": ";

//string usr_input;

//clock_t begin = clock();
/*chrono::steady_clock::time_point begin = chrono::steady_clock::now();
cin >> usr_input;
chrono::steady_clock::time_point end= chrono::steady_clock::now();
cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;*/
#endif
}
