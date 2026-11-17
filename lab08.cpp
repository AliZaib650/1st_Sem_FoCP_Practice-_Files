#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Enumeration for grid contents
enum TileType { EMPTY, REWARD, CHALLENGE, EXIT };

// Structure to manage the player's status and inventory
struct Player {
    int health;
    int maxHealth;
    int attack;
    int gold;
    int score;
    int level;
    int x, y; // Player position on the grid
    vector<string> items;
};

// Structure to define grid tiles
struct Tile {
    TileType type;
    string description;
    bool visited;
};

// Global Constants for Map Dimensions
const int MAP_SIZE = 5;

// Function Declarations
void initializePlayer(Player& player);
void generateLevel(vector<vector<Tile>>& map, int level);
void displayHUD(const Player& player);
void displayMap(const vector<vector<Tile>>& map, const Player& player);
void handleTileAction(Player& player, Tile& tile);
bool processMovement(Player& player, char direction);

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    cout << "==================================================\n";
    cout << "        WELCOME TO THE PROCEDURAL DUNGEON         \n";
    cout << "==================================================\n";
    
    Player player;
    initializePlayer(player);
    
    bool gameRunning = true;
    
    while (gameRunning) {
        // Setup the level map
        vector<vector<Tile>> map(MAP_SIZE, vector<Tile>(MAP_SIZE));
        generateLevel(map, player.level);
        
        // Reset player coordinates to start of the level
        player.x = 0;
        player.y = 0;
        map[player.y][player.x].visited = true;
        
        cout << "\n--- ENTERING LEVEL " << player.level << " ---\n";
        cout << "Find the EXIT (E) to progress. Watch out for traps!\n";
        
        bool levelActive = true;
        while (levelActive) {
            displayHUD(player);
            displayMap(map, player);
            
            cout << "\nMove (W = Up, S = Down, A = Left, D = Right, Q = Quit): ";
            char choice;
            cin >> choice;
            choice = toupper(choice);
            
            if (choice == 'Q') {
                cout << "\nYou abandoned the quest. Final Score: " << player.score << "\n";
                gameRunning = false;
                break;
            }
            
            if (processMovement(player, choice)) {
                Tile& currentTile = map[player.y][player.x];
                currentTile.visited = true;
                
                // Handle challenges, rewards, or exits
                if (currentTile.type == EXIT) {
                    cout << "\n[!] You found the Exit portal! Progressing to next level...\n";
                    player.level++;
                    player.score += 50; // Level completion bonus
                    levelActive = false; // Exits current loop to generate next level
                } else {
                    handleTileAction(player, currentTile);
                    currentTile.type = EMPTY; // Clear the tile after interacting
                }
            } else {
                cout << "[!] Invalid move or boundary hit. Try again.\n";
            }
            
            // Check Lose Condition
            if (player.health <= 0) {
                cout << "\n==================================================\n";
                cout << "       GAME OVER - YOU DIED IN THE DUNGEON        \n";
                cout << "==================================================\n";
                cout << "Final Stats:\n";
                cout << "Level Reached: " << player.level << "\n";
                cout << "Total Gold:    " << player.gold << "\n";
                cout << "Final Score:   " << player.score << "\n";
                gameRunning = false;
                break;
            }
        }
    }
    
    cout << "\nThank you for playing!\n";
    return 0;
}

// Generates randomized, scalable starting player attributes
void initializePlayer(Player& player) {
    player.maxHealth = 80 + (rand() % 41); // Random health between 80 and 120
    player.health = player.maxHealth;
    player.attack = 10 + (rand() % 6);     // Random base attack between 10 and 15
    player.gold = 0;
    player.score = 0;
    player.level = 1;
    player.items.push_back("Rusty Dagger");
}

// Procedurally generates challenge and reward locations based on current level scaling
void generateLevel(vector<vector<Tile>>& map, int level) {
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            map[y][x].type = EMPTY;
            map[y][x].visited = false;
        }
    }
    
    // Always fix the exit at the bottom right corner for navigation logic
    map[MAP_SIZE - 1][MAP_SIZE - 1].type = EXIT;
    
    // Scale challenge distribution frequency based on higher progression levels
    int challengeChance = 25 + (level * 5); // Level 1 = 30%, Level 2 = 35% etc.
    int rewardChance = 20;
    
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            // Skip the starting zone and exit tile initialization
            if ((x == 0 && y == 0) || (x == MAP_SIZE - 1 && y == MAP_SIZE - 1)) {
                continue;
            }
            
            int roll = rand() % 100;
            if (roll < challengeChance) {
                map[y][x].type = CHALLENGE;
            } else if (roll < (challengeChance + rewardChance)) {
                map[y][x].type = REWARD;
            }
        }
    }
}

// Prints user-friendly inventory metrics and stats dashboard
void displayHUD(const Player& player) {
    cout << "\n==================================================\n";
    cout << " LVL: " << player.level 
         << " | HP: " << player.health << "/" << player.maxHealth 
         << " | ATK: " << player.attack 
         << " | Gold: " << player.gold 
         << " | Score: " << player.score << "\n";
    cout << " Inventory: ";
    if (player.items.empty()) {
        cout << "Empty";
    } else {
        for (size_t i = 0; i < player.items.size(); ++i) {
            cout << "[" << player.items[i] << "] ";
        }
    }
    cout << "\n==================================================\n";
}

// Renders visual ASCII environment grid tracking visited locations and entities
void displayMap(const vector<vector<Tile>>& map, const Player& player) {
    cout << " Dungeon Layout:\n";
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            if (x == player.x && y == player.y) {
                cout << " [P] "; // Player Location
            } else if (!map[y][x].visited) {
                cout << " [?] "; // Unexplored Fog of war
            } else {
                switch (map[y][x].type) {
                    case EMPTY:     cout << " [.] "; break;
                    case REWARD:    cout << " [$] "; break;
                    case CHALLENGE: cout << " [X] "; break;
                    case EXIT:      cout << " [E] "; break;
                }
            }
        }
        cout << "\n";
    }
}

// Handles input movement actions and verifies structural boundary collision rules
bool processMovement(Player& player, char direction) {
    int targetX = player.x;
    int targetY = player.y;
    
    switch (direction) {
        case 'W': targetY--; break; // Up
        case 'S': targetY++; break; // Down
        case 'A': targetX--; break; // Left
        case 'D': targetX++; break; // Right
        default: return false;      // Invalid Command input
    }
    
    // Bounds Checking
    if (targetX >= 0 && targetX < MAP_SIZE && targetY >= 0 && targetY < MAP_SIZE) {
        player.x = targetX;
        player.y = targetY;
        return true;
    }
    return false;
}

// Evaluates procedural interactions, resolving rewards or dynamic scaling penalties
void handleTileAction(Player& player, Tile& tile) {
    if (tile.type == REWARD) {
        int rewardRoll = rand() % 3;
        if (rewardRoll == 0) {
            int goldFound = 10 + (rand() % 21);
            player.gold += goldFound;
            player.score += goldFound * 2;
            cout << "\n[+] Reward! You opened a chest and found " << goldFound << " Gold coins!\n";
        } else if (rewardRoll == 1) {
            int healAmount = 15 + (rand() % 16);
            player.health = min(player.maxHealth, player.health + healAmount);
            cout << "\n[+] Reward! You found a glowing Health Elixir and healed for " << healAmount << " HP.\n";
        } else {
            string weapons[] = {"Iron Sword", "Steel Shield", "Magic Ring", "Elven Bow"};
            string newWeapon = weapons[rand() % 4];
            player.items.push_back(newWeapon);
            player.attack += 3;
            player.score += 30;
            cout << "\n[+] Reward! Found loot: " << newWeapon << "! (Attack boosted by +3)\n";
        }
    } 
    else if (tile.type == CHALLENGE) {
        // Difficulty modifiers scale up based on the current level progression tier
        int baseMonsterHP = 20 + (player.level * 10);
        int monsterAttack = 8 + (player.level * 4);
        
        cout << "\n[!] Ambush! A level " << player.level << " Monster blocks your path!\n";
        cout << "Monster stats -> HP: " << baseMonsterHP << ", ATK: " << monsterAttack << "\n";
        
        // Simulating text interaction combat
        cout << "Engaging in combat using your active inventory tools...\n";
        
        int damageTaken = max(5, monsterAttack - (int)(player.items.size() * 2));
        player.health -= damageTaken;
        player.score += baseMonsterHP;
        
        cout << "[-] Penalty: You defeated the monster but suffered " << damageTaken << " damage points.\n";
    } 
    else {
        cout << "\n[.] The room is quiet and empty. Safe for now.\n";
    }
}
