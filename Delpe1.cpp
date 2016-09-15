#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

int toss()            //Iplement function for die throw
{
    return rand() % 6 + 1;
}

int high_throw (int a, int b, int c) {      //Function hight_throw ->  determines greatest of three die thrown
    if((a >= b) && (a >= c)) {
      return a;
    }
    else if ((b >= a) && (b >= c)) {
      return b;
    }
    else {
      return c;
    }
}

int high_throw2 (int x, int y) {        //Function high_throw2 -> determines greatest of two die thrown
    if(x > y) {
      return x;
    }
    else {
      return y;
    }
}


int main() {
  cout << "Hello!" << endl << endl;                  //Going to Boston game intro
  cout << "Let's play a game..." << endl << endl;
  cout << "__GOING TO BOSTON__" << endl << endl;
  cout << "[Round 1]" << endl << endl;

  int man_allow = 1000, mac_allow = 1000;            //Declare variables for machine and player allowance -> assign each a value of $1000

  while(true) {

        int mac_throw1 = toss();                      //Declare variable for each throw of dice
        int mac_throw2 = toss();
        int mac_throw3 = toss();

        int man_throw1 = toss();
        int man_throw2 = toss();
        int man_throw3 = toss();


        cout << "You rolled (" << man_throw1 << "," << man_throw2 << 
          ",?), machine rolled (" << mac_throw1 << "," << mac_throw2 
          << "," << "?)" << endl;

        cout << "How much are you going to bet (Bet $1 - $10): ";        //Promt player to raise wager
        int wager;
        cin >> wager;
        cout << endl;

        if(wager>10 || wager<0) {                                         //Indicate an error for wagers made out of bounds ($1 - $10)
          cout << "Your bet must be between $1 and $10, type again: " << endl << endl;
          continue;
        }

       if (man_throw1==man_throw2==man_throw3) {                          //Test for "Big Fish"
          man_allow += wager*50;
          mac_allow -= wager*50;
          cout << "You had (" << man_throw1 << "," << man_throw2 <<
            "," << man_throw3 << ") ... Big Fish!!!" << endl;
          cout << "Machine had (" << mac_throw1 << "," << mac_throw2 
            << "," << mac_throw3 << ")" << endl;
          cout << "-> Machine rolled (" << mac_throw2 << "," << mac_throw3 <<
           ") and then rolled ("; 
          int r1_total = high_throw(mac_throw1,mac_throw2,mac_throw3);

          int mac_throw4 = toss();
          int mac_throw5 = toss();

          int r2_total = high_throw2(mac_throw4,mac_throw5);

          int mac_throw6 = toss();
          int mac_score = r1_total + r2_total + mac_throw6; 
         cout << mac_throw6 << ") -> Machine scored " << mac_score
            << endl;
         cout << "You won :) You have $" << man_allow << " machine has $" 
           << mac_allow;
         break;
          }
       else if (mac_throw1==mac_throw2==mac_throw3) {
          mac_allow += wager*50;
          man_allow -= wager*50;
          cout << "You lost. Machine had (" << mac_throw1 << "," << 
          mac_throw2 << "," << mac_throw3 << ") ... Big Fish!!!"
           << endl;
          break;
          }

       cout << "You rolled (" << man_throw1 << "," << man_throw2 <<                     //Reveal results of player and machine die throws
         "," << man_throw3 << "), machine rolled (" << mac_throw1 << "," << mac_throw2 << 
         "," << mac_throw3 <<  ")..." << endl << "How much are you going to bet: ";
       cin >> wager;
       cout << endl;

       if(wager>10 || wager<0) {                                                      //Indicate and error for wagers mad out of bounds ($1 - $10)
          cout << "Your bet must be between $1 and $10, type again: " << endl << endl;
          break;
        }
         cout << "You had (" << man_throw1 << "," << man_throw2 <<                     //Reveal results of machine and player die throws
            "," << man_throw3 << ") -> You rolled (";
         int man_throw4 = toss();
         int man_throw5 = toss();
         cout <<  man_throw3 << "," << man_throw4 << ") and then rolled (";
         int man_throw6 = toss();
         cout << man_throw6 << ") -> You score ";
         int man_score = high_throw(man_throw1,man_throw2,man_throw3) +
                    high_throw2(man_throw4,man_throw5) + man_throw6;
         cout << man_score << endl;
         cout << "Machine had (" << mac_throw1 << "," << mac_throw2 << "," 
           << mac_throw3 << ") -> Machine rolled ("; 

       int r1_total = high_throw(mac_throw1,mac_throw2,mac_throw3);

       int mac_throw4 = toss();
       int mac_throw5 = toss();

      cout << mac_throw4 << "," << mac_throw5 << ") and then rolled (";
       int mac_throw6 = toss();
      cout << mac_throw6 << ")";

       int r2_total = high_throw2(mac_throw4,mac_throw5);
       int mac_score = r1_total + r2_total + mac_throw6;
      cout  << " -> Machine scored " << mac_score
         << endl << endl;

      if (man_score > mac_score) {                  //Determine winner of round and establish allowance of player/machine
       cout << "You won :) You have $";
       man_allow += (man_score - mac_score)*wager;
       mac_allow -= (man_score - mac_score)*wager;
       cout << man_allow << ", machine has $" <<
         mac_allow << "..." << endl;
       if (mac_allow <= 0) {
        break;
       }
      }
      else if (mac_score > man_score) {
       cout << "You lost :( You have $";
       man_allow -= (mac_score - man_score)*wager;
       mac_allow += (mac_score - man_score)*wager;
       cout << man_allow << ", machine has $" <<
         mac_allow << "..." << endl << endl;
       if (man_allow <=0) { 
         break;
       }
      }
       else {
       cout << "Tied..." << endl << endl;
      }

      for(int i=0;man_allow != 0 && mac_allow != 0; ++i) {              //Count ronund of game -> end if player or machine allowance >= 0
        int a = a + 1;
        cout << "[Round " << a + 1 << "]" << endl << endl;
          break;
        }
  }
}
