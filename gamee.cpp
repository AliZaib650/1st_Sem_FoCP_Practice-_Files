#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <chrono>
#include <windows.h>

using namespace std;

// Helper function to print messages letter-by-letter
void printSlowly(const string& text, int delay_ms = 30) {
    for (char c : text) {
        cout << c << flush;
        Sleep(delay_ms);
    }
}

void runGameSimulator(int &currentposition, int& target);
int rolldice();
int turnplay(int dice, int& currentposition);

int main()
{
    srand(time(0));
    int currentposition = 0;
    int target = 100;
    int n;
    cout << endl;
    cout << endl;
    printSlowly("==================================================\n", 10);
    printSlowly("========= WELCOME TO ROLL DICE SIMULATOR =========\n", 10);
    printSlowly("==================================================\n", 10);
    cout << endl;
    
    printSlowly("Enter 1 to continue to game, 0 to exit from game: ");
    cin >> n;
    
    while(n != 0)
    {
        if (n == 1)
        {
            printSlowly("WELCOME TO GAME!!!!\n");
            runGameSimulator(currentposition, target);
            if(currentposition == target)
            {
                currentposition = 0;
                printSlowly("Press 1 to replay game, 0 to exit from game: ");
                cin >> n;
            }
        }
        else
        {
            printSlowly("You entered an invalid input, Please choose from given options!!!\n");
            printSlowly("Enter 1 to continue to game, 0 to exit from game: ");
            cin >> n;
        }
    }
    
    printSlowly("You exited the game successfully!\n");
    printSlowly("Have a nice day!!\n");

    return 0;
}

int rolldice()
{
    return 1 + rand() % 6;
}

void runGameSimulator(int &currentposition, int& target)
{
    while(currentposition < target)
    {
        int dice;
        char random;
        printSlowly("Please press any character and then ENTER to roll dice : ");
        cin >> random;
        dice = rolldice();
        currentposition = turnplay(dice, currentposition);
        if(currentposition == target)
        {
            printSlowly("You won the Game!!!!\n");
            printSlowly("Congratulations \n");
        }
    }
}

int turnplay(int dice, int& currentposition)
{
    currentposition += dice;
    if(dice == 6)
    {
        printSlowly("Wow!! You rolled a 6, you will get a bonus of 2.\n");
        currentposition += 2;
        if(currentposition > 100) { currentposition = 100; }
        printSlowly("your current position is now: " + to_string(currentposition) + "\n");
    }
    
    if(currentposition % 9 == 0)
    {
        printSlowly("You rolled a " + to_string(dice) + "\n");
        printSlowly("OOOPS! you landed at a trap. HAHAHAHA..........\n");
        currentposition -= 15;
        if(currentposition < 0) { currentposition = 0; }
        printSlowly("your current position is reseted again to " + to_string(currentposition) + "\n");
    }
    else if(currentposition % 20 == 0 && currentposition < 80)
    {
        currentposition += 10;
        if(currentposition > 100) { currentposition = 100; }
        printSlowly("Congratulations!!!!! You unlocked a treasure box!\n");
        printSlowly("Your currentposition boosted to " + to_string(currentposition) + "\n");
    }
    else
    {
        printSlowly("You rolled a " + to_string(dice) + "\n");
        if(currentposition > 100) { currentposition = 100; }
        printSlowly("Your current position is " + to_string(currentposition) + "\n");
    }
    return currentposition;
}
