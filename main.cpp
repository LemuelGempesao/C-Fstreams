#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_PLAYERS = 100;

struct Player {
    string name;
    int score;
    bool l1_finished;
    bool l2_finished;
    bool l3_finished;
};

int numPlayers = 0;
Player players[MAX_PLAYERS];

void addNewPlayer() {
    if (numPlayers >= MAX_PLAYERS) {
        cout << "Maximum number of players reached." << endl;
        return;
    }

    cout << "Enter player name: ";
    cin >> players[numPlayers].name;
    players[numPlayers].score = 0;
    players[numPlayers].l1_finished = false;
    players[numPlayers].l2_finished = false;
    players[numPlayers].l3_finished = false;
    numPlayers++;
}

void savePlayersToFile() {
    ofstream outputFile("player_data.txt");
    if (!outputFile) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    for (int i = 0; i < numPlayers; i++) {
        outputFile << players[i].name << " " << players[i].score << " "
                   << players[i].l1_finished << " " << players[i].l2_finished << " "
                   << players[i].l3_finished << endl;
    }

    outputFile.close();
}

void loadPlayersFromFile() {
    numPlayers = 0;

    ifstream inputFile("player_data.txt");
    if (!inputFile) {
        cerr << "No existing player data found. Starting with empty player list." << endl;
        return;
    }
    inputFile.seekg(0, ios::end);
    if (inputFile.tellg() == 0) {
        cerr << "Notice: Player data file is empty." << endl;
        return;
    }
    inputFile.seekg(0, ios::beg);

    while (numPlayers < MAX_PLAYERS &&
           inputFile >> players[numPlayers].name >> players[numPlayers].score
                     >> players[numPlayers].l1_finished >> players[numPlayers].l2_finished
                     >> players[numPlayers].l3_finished) {
        numPlayers++;
    }

    inputFile.close();
}

Player* findPlayerByName(const string& playerName) {
    for (int i = 0; i < numPlayers; i++) {
        if (players[i].name == playerName) {
            return &players[i];
        }
    }
    cout << "Player not found. Creating a new player with default values." << endl;
    if (numPlayers < MAX_PLAYERS) {
        Player* newPlayer = &players[numPlayers++];
        newPlayer->name = playerName;
        newPlayer->score = 0;
        newPlayer->l1_finished = false;
        newPlayer->l2_finished = false;
        newPlayer->l3_finished = false;
        return newPlayer;
    } else {
        cout << "Cannot create a new player. Maximum number of players reached." << endl;
        return nullptr;
    }
}

int main() {
    loadPlayersFromFile();

    string choice;
    string playerName;

    do {
        cout << "\n\n1. Add new player\n";
        cout << "2. Play game\n";
        cout << "3. Save and exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice == "1") {
            addNewPlayer();
        }
        else if(choice == "2") {
            cout << "Enter player name: ";
            cin >> playerName;
            Player* currentPlayer = findPlayerByName(playerName);
            if (currentPlayer) {
                cout << "Player score: " << currentPlayer->score+2 << endl;
                cout << "Current player: " << playerName << endl;
            }
        }
        else if(choice == "3") {
            savePlayersToFile();
            cout << "Player data saved. Exiting...\n";
        }
        else {
            cout << "Invalid choice\n";
        }
    } while (choice != "4");

    return 0;
}
