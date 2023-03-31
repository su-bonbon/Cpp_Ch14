/// @file Container_test.cpp
/// @author Sujin Lee
/// @date 2022-03-11
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief using a class Container, this program generates
///        five unique random digits in the range of [0..9]
/// 2022-03-02: Sujin created

#include <iostream>
#include <initializer_list>
#include <cstdlib>
#include <ctime>
#include "Container.hpp"
using namespace std;
/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
    bool flag1 = false;
    bool flag2 = false;
    string flag3 = "";
    int count = 0;
    int money = 0;
    Container<int> lottery;
    Container<int> user;
    Container<int>::pointer ptr = nullptr;
    string errormsg = "ERROR_ERROR";
    std::srand(std::time(nullptr));
    do{
        do{
            try {
                cout << "Enter five unique lottery digits: ";
                cin >> num1 >> num2 >> num3 >> num4 >> num5;
                user = { num1, num2, num3, num4, num5 };

                for (auto i = user.begin(); i < user.end(); i++) {
                   ptr = user.find(*i, i + 1);
                   if(ptr != user.end()) {
                       throw errormsg;
                   }
                }
                flag1 = false;
            }
            catch(string) {
                cout << "Sorry, you cannot enter duplicates." << endl;
                flag1 = true;
            }

        } while(flag1);

        // rand()%(low+high)+low+1
        for (int i = 0; i < 5; i++) {
            int number;
            number = rand() % (9) + 1;
            while (lottery.find(number) != lottery.end()) {
                number = rand() % (9) + 1;
            }
            lottery.push_back(number);
        }

        for (auto item1 : lottery) {
            for (auto item2 : user) {
                if (item1 == item2) {
                    count++;
                }
            }
        }

        flag2 = std::equal(lottery.begin(), lottery.end(), user.begin(), user.end());

        if (flag2) {
            money = 10000;
        }
        else if (count == 5) {
            money = 3000;
        }
        else if (count == 4) {
            money = 500;
        }

        cout << endl;
        cout << "Congratulations! You matched " << count << " digits!" << endl;
        cout << "Your prize is $" << money << endl << endl;

        cout << "Winning numbers: " << lottery << endl;
        cout << "Your picks:      " << user << endl << endl;

        cout << "Play again (yes/no)? ";
        cin >> flag3;
        user.clear();
        lottery.clear();
        count = 0;
        money = 0;

        if (flag3 == "no") {
            cout << "Good bye." << endl;
        }
    } while(flag3 != "no");


    return EXIT_SUCCESS;
}
