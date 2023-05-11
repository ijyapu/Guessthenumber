
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

//Player Class
class Player {
public:
    Player(string name) : name(name), wins(0) {}
    virtual int getGuess(int max, int min) { return 0; }        //Virtual function to get the player's guess
    virtual int checkMin(int guess, int answer, int min) = 0;   // pure virtual function to check the min value for the guess
    virtual int checkMax(int guess, int answer, int max) = 0;   // pure virtual function to check the max value for the guess
    int getWins() { return wins; }
    string getName() { return name; }
    void setName(string newName) { name = newName; }
    void setWins(int newWin) { wins = newWin; }

private:
    string name;
    int wins;
};


//HumanPlayer class inherited from the Player Class
class HumanPlayer : public Player {
public:
    int getGuess(int max, int min)override {    //override the getGUess function to take user input as guess
        int input;
        cout << "Please enter your guess [0 - 100]: ";
        cin >> input;
        return input;
    }
    HumanPlayer(string name) : Player(name) {}
    virtual int checkMin(int guess, int answer, int min)override {      //override to update the min value for the guess
        if (guess < answer)
            min = guess + 1;
        return min;
    }
    virtual int checkMax(int guess, int answer, int max)override {      //override to update the min value for the guess
        if (guess > answer)
            max = guess - 1;
        return max;
    }
};


//CompterPlayer class inherited from the Player Class
class ComputerPlayer : public Player {
public:
    ComputerPlayer(string name) : Player(name) {}
    int getGuess(int min, int max) { return rand() % 100; }     // override the getGuess function to generate a random number as the guess
    virtual int checkMin(int guess, int answer, int min)override {      
        if (guess < answer)
            min = guess + 1;
        return min;
    }
    virtual int checkMax(int guess, int answer, int max)override {      
        if (guess > answer)
            max = guess - 1;
        return max;
    }
};

bool checkForWin(int guess, int answer) {
    cout << "You guessed " << guess << ". \n";
    if (answer == guess) {
        cout << "You're right! You win!" << endl; // guessed right
        return true;
    }
    else if (answer < guess) {
        cout << "Your guess was too high.\n" << endl;
    }
    else {
        cout << "Your guess was too low.\n" << endl;
    }
    return false; //check if the guess is too high or low and return true if its right, else return false
}

void play(Player& player1, Player& player2) {
    int answer = 0, guess = 0;
    srand((int)time(0));
    answer = rand() % 100;
    bool win = false;
    int max = 100;
    int min = 0;
    while (!win) {
        cout << player1.getName() << "'s turn to guess:" << endl;
        guess = player1.getGuess(max, min);
        win = checkForWin(guess, answer);
        max = player1.checkMax(guess, answer, max);
        min = player1.checkMin(guess, answer, min);
        if (win) {
            player1.setWins(player1.getWins() + 1);
            return;
        }
        cout << player2.getName() << "'s turn to guess:" << endl;
        guess = player2.getGuess(max, min);
        max = player2.checkMax(guess, answer, max);
        min = player2.checkMin(guess, answer, min);
        win = checkForWin(guess, answer);
        if (win) {
            player2.setWins(player2.getWins() + 1);
        }
    }
}

int main() {
    HumanPlayer human1("Player 1"), human2("Player 2");
    ComputerPlayer computer1("Computer Player 1"), computer2("Computer Player 2");

    cout << "Select the game type (1-3) from the menu:" << endl
        << "1. Human vs. Human" << endl
        << "2. Human vs. Computer" << endl
        << "3. Computer vs. Computer" << endl
        << "Enter any other key to end the game." << endl;
    cout << "#";
    int input = 0;
    cin >> input;                       //User's menu selection 
    while (input < 4 && input > 0)
    {
        if (input == 1)
        {
            play(human1, human2);
        }
        else if (input == 2)
        {
            play(human1, computer2);
        }
        else
        {
            play(computer1, computer2);
        }
        cout << "\nSelect the game type (1-3) from the menu, any other number to quit" << endl
            << "1. Human vs. Human" << endl
            << "2. Human vs. Computer" << endl
            << "3. Computer vs. Computer" << endl;
        cout << "#";
        cin >> input;

    }

    cout << "\n** GAME OVER **" << endl;

}
