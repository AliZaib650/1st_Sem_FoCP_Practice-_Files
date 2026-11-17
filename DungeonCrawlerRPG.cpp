#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main() {
    srand(time(0));

    int playerRow = 0;
    int playerCol = 0;
    int exitRow = 0;
    int exitCol = 0;
    
    int hp = 0;
    int maxHp = 0;
    int gold = 0;
    int winGold = 0;
    int keys = 0;
    
    int trapMinDamage = 0;
    int trapMaxDamage = 0;
    int minGoldReward = 0;
    int maxGoldReward = 0;
    int mapSize = 0;
    int difficultyChoice = 0;

    int map[8][8]; 
    bool revealed[8][8];

    cout << "=========================================\n";
    cout << "      THE CHRONICLES OF OBLIVION         \n";
    cout << "=========================================\n";
    cout << "Select Matrix Difficulty:\n";
    cout << "1. Initiate   (5x5 Arena, 100 HP, 1 Key Needed)\n";
    cout << "2. Vanguard   (6x6 Arena,  80 HP, 2 Keys Needed)\n";
    cout << "3. Overlord   (8x8 Arena,  60 HP, 3 Keys Needed)\n";
    cout << "Your decree (1-3): ";
    cin >> difficultyChoice;

    while (difficultyChoice < 1 || difficultyChoice > 3) {
        cout << "Invalid protocol. Choose 1-3: ";
        cin >> difficultyChoice;
    }

    if (difficultyChoice == 1) {
        mapSize = 5;
        hp = 100;
        maxHp = 100;
        winGold = 150;
        trapMinDamage = 10;
        trapMaxDamage = 20;
        minGoldReward = 15;
        maxGoldReward = 30;
    } else if (difficultyChoice == 2) {
        mapSize = 6;
        hp = 80;
        maxHp = 80;
        winGold = 250;
        trapMinDamage = 15;
        trapMaxDamage = 30;
        minGoldReward = 20;
        maxGoldReward = 45;
    } else {
        mapSize = 8;
        hp = 60;
        maxHp = 60;
        winGold = 400;
        trapMinDamage = 25;
        trapMaxDamage = 45;
        minGoldReward = 30;
        maxGoldReward = 60;
    }

    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            map[i][j] = 0; 
            revealed[i][j] = false;
        }
    }

    playerRow = rand() % mapSize;
    playerCol = rand() % mapSize;
    revealed[playerRow][playerCol] = true;

    do {
        exitRow = rand() % mapSize;
        exitCol = rand() % mapSize;
    } while (exitRow == playerRow && exitCol == playerCol);
    map[exitRow][exitCol] = 5; 

    int requiredKeys = (difficultyChoice == 1) ? 1 : (difficultyChoice == 2) ? 2 : 3;
    int keysPlaced = 0;
    while (keysPlaced < requiredKeys) {
        int r = rand() % mapSize;
        int c = rand() % mapSize;
        if (map[r][c] == 0 && !(r == playerRow && c == playerCol)) {
            map[r][c] = 4; 
            keysPlaced++;
        }
    }

    int totalCells = mapSize * mapSize;
    int trapCount = totalCells * 0.25; 
    int rewardCount = totalCells * 0.25; 
    int merchantCount = (difficultyChoice == 3) ? 1 : 2;

    int placed = 0;
    while (placed < trapCount) {
        int r = rand() % mapSize;
        int c = rand() % mapSize;
        if (map[r][c] == 0 && !(r == playerRow && c == playerCol)) {
            map[r][c] = 1; 
            placed++;
        }
    }

    placed = 0;
    while (placed < rewardCount) {
        int r = rand() % mapSize;
        int c = rand() % mapSize;
        if (map[r][c] == 0 && !(r == playerRow && c == playerCol)) {
            map[r][c] = 2; 
            placed++;
        }
    }

    placed = 0;
    while (placed < merchantCount) {
        int r = rand() % mapSize;
        int c = rand() % mapSize;
        if (map[r][c] == 0 && !(r == playerRow && c == playerCol)) {
            map[r][c] = 3; 
            placed++;
        }
    }

    bool gameRunning = true;
    string statusMessage = "You awake in the cold, dynamic labyrinth.";

    while (gameRunning) {
        cout << "\033[2J\033[1;1H"; 
        cout << "==================================================\n";
        cout << " STATUS: HP [" << hp << "/" << maxHp << "] | GOLD [" << gold << "/" << winGold << "] | KEYS [" << keys << "/" << requiredKeys << "]\n";
        cout << "==================================================\n\n";

        for (int i = 0; i < mapSize; i++) {
            cout << "  ";
            for (int j = 0; j < mapSize; j++) {
                if (i == playerRow && j == playerCol) {
                    cout << "🤖 ";
                } else if (revealed[i][j]) {
                    if (map[i][j] == 0) cout << ".  ";
                    else if (map[i][j] == 1) cout << "X  ";
                    else if (map[i][j] == 2) cout << "$  ";
                    else if (map[i][j] == 3) cout << "M  ";
                    else if (map[i][j] == 4) cout << "K  ";
                    else if (map[i][j] == 5) cout << "E  ";
                } else {
                    cout << "#  ";
                }
            }
            cout << "\n";
        }
        
        cout << "\nLOG: " << statusMessage << "\n\n";
        cout << "ACTIONS:\n";
        cout << "  [W] Move Up    | [A] Move Left | [S] Move Down | [D] Move Right\n";
        cout << "  [M] Store Panel | [P] Forfeit Run\n";
        cout << "Input Command: ";
        
        char action;
        cin >> action;
        action = toupper(action);

        statusMessage = "";

        if (action == 'P') {
            gameRunning = false;
            statusMessage = "Forfeited the matrix run.";
            break;
        }

        if (action == 'M') {
            bool inStore = true;
            while (inStore) {
                cout << "\033[2J\033[1;1H";
                cout << "=========================================\n";
                cout << "       NEXUS INTERCOMMERCE TERMINAL      \n";
                cout << "=========================================\n";
                cout << " Current Wealth: " << gold << " Gold\n";
                cout << " Current Health: " << hp << " / " << maxHp << " HP\n\n";
                cout << "1. Nano-Heal Infusion (+30 HP)       - 40 Gold\n";
                cout << "2. Vitality Core Upgrade (+20 MaxHP) - 75 Gold\n";
                cout << "3. Structural Shielding (-5 Trap Dmg)- 100 Gold\n";
                cout << "4. Disconnect Terminal\n";
                cout << "Selection: ";
                int storeChoice;
                cin >> storeChoice;

                if (storeChoice == 1) {
                    if (gold >= 40) {
                        gold -= 40;
                        hp = (hp + 30 > maxHp) ? maxHp : hp + 30;
                        statusMessage = "Infusion successful. Health restored.";
                    } else {
                        statusMessage = "Insufficient liquid capital.";
                    }
                    inStore = false;
                } else if (storeChoice == 2) {
                    if (gold >= 75) {
                        gold -= 75;
                        maxHp += 20;
                        hp += 20;
                        statusMessage = "Core modified. Max capacity amplified.";
                    } else {
                        statusMessage = "Insufficient liquid capital.";
                    }
                    inStore = false;
                } else if (storeChoice == 3) {
                    if (gold >= 100) {
                        gold -= 100;
                        trapMinDamage = (trapMinDamage - 5 < 0) ? 0 : trapMinDamage - 5;
                        trapMaxDamage = (trapMaxDamage - 5 < 5) ? 5 : trapMaxDamage - 5;
                        statusMessage = "Shield structures upgraded permanently.";
                    } else {
                        statusMessage = "Insufficient liquid capital.";
                    }
                    inStore = false;
                } else {
                    inStore = false;
                    statusMessage = "Exited terminal connection.";
                }
            }
            continue;
        }

        int targetRow = playerRow;
        int targetCol = playerCol;

        if (action == 'W') targetRow--;
        else if (action == 'S') targetRow++;
        else if (action == 'A') targetCol--;
        else if (action == 'D') targetCol++;
        else {
            statusMessage = "Invalid navigation key syntax.";
            continue;
        }

        if (targetRow < 0 || targetRow >= mapSize || targetCol < 0 || targetCol >= mapSize) {
            statusMessage = "Navigation blocked: Peripheral boundaries reached.";
            continue;
        }

        playerRow = targetRow;
        playerCol = targetCol;
        revealed[playerRow][playerCol] = true;

        int tileType = map[playerRow][playerCol];

        if (tileType == 0) {
            statusMessage = "Sector clear. No anomalies detected.";
        } 
        else if (tileType == 1) {
            int dmg = trapMinDamage + (rand() % (trapMaxDamage - trapMinDamage + 1));
            hp -= dmg;
            statusMessage = "WARNING: Triggered environmental anomaly! Sustained " + to_string(dmg) + " damage.";
            map[playerRow][playerCol] = 0; 
        } 
        else if (tileType == 2) {
            int currentReward = minGoldReward + (rand() % (maxGoldReward - minGoldReward + 1));
            gold += currentReward;
            statusMessage = "SECURED: Extracted " + to_string(currentReward) + " gold assets from sector.";
            map[playerRow][playerCol] = 0; 
        } 
        else if (tileType == 3) {
            statusMessage = "MERCHANT SIGNAL: Access the [M] system to deploy operations.";
        } 
        else if (tileType == 4) {
            keys++;
            statusMessage = "KEY ACQUIRED: Validation signature stored.";
            map[playerRow][playerCol] = 0; 
        } 
        else if (tileType == 5) {
            if (keys >= requiredKeys) {
                cout << "\033[2J\033[1;1H";
                cout << "=========================================\n";
                cout << "            GRID EXTRACTION SUCCESS      \n";
                cout << "=========================================\n";
                cout << "Systems verified. Escape portal active.\n";
                cout << "Final Matrix Inventory: " << gold << " Gold | " << hp << " HP Remaining.\n";
                gameRunning = false;
                break;
} 
else
 {
 statusMessage = "ACCESS DENIED: Missing " + to_string(requiredKeys - keys) + " cryptographic keys to crack terminal.";
}
}
if (hp <= 0) {
cout << "\033[2J\033[1;1H";
cout << "=========================================\n";
cout << "              MATRIX TERMINATION         \n";
cout << "=========================================\n";
cout << "Vital signs ceased. Biological frame destroyed.\n";
cout << "Data Lost. Score: " << gold << " Gold collected.\n";
gameRunning = false;
}
else if (gold >= winGold) {
cout << "\033[2J\033[1;1H";
cout << "=========================================\n";
cout << "        ECONOMIC INDEPENDENCE ACHIEVED   \n";
cout << "=========================================\n";
cout << "Wealth thresholds exceeded requirement profiles.\n";
cout << "Final Assets Secured: " << gold << " Gold.\n";
gameRunning = false;
}
}
return 0;
}