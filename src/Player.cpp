#include "../include/Player.h"
#include "../include/Commands.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void Player::runCharacterCreation(const bool DEBUG)
{
    // If debug is turned on, skip character setup for testing other things
    if(!DEBUG)
    {
        cout << "Welcome to Escape the Vault.\n";
        cout << "You wake up, cold and confused. You start to remember who you are...\n";

        string input;
        cout << "Who am I?\n";
        cin >> input;
        setName(input);
        bool goodAge = false;
        while(!goodAge)
        {
            goodAge = true;
            cout << "How old am I?\n";
            cin >> input;
            for(unsigned int i = 0; i < input.size(); i++)
            {
                if(!isdigit(input[i]))
                    goodAge = false;
            }
            if(!goodAge)
                cout << "Error: invalid age\n";
        }
        setAge(stoi(input));
        cout << "What am I skilled in?\n";
        cout << "In strength, perception, endurance, charisma, intelligence, agility, luck?\n";
        cout << "(5 points to each by default)\n";
        int pointsLeft = 5;
        cout << pointsLeft << " points left to assign. Current distribution:\n\tStrength: " << getStrength() << " Perception: " << getPerception() << " Endurance: " << getEndurance() << " Charisma: " << getCharisma() << "\n\tIntelligence: " << getIntelligence() << " Agility: " << getAgility() << " Luck: " << getLuck() << endl;
        while(pointsLeft > 0)
        {
            cin >> input;
            for(unsigned int i = 0; i < input.size(); i++)
            {
                input[i] = tolower(input[i]);
            }
            if(input == "strength" || input == "s")
            {
                setStrength(getStrength()+1);
                pointsLeft--;
            }
            else if(input == "perception" || input == "p")
            {
                setPerception(getPerception()+1);
                pointsLeft--;
            }
            else if(input == "endurance" || input == "e")
            {
                setEndurance(getEndurance()+1);
                pointsLeft--;
            }
            else if(input == "charisma" || input == "c")
            {
                setCharisma(getCharisma()+1);
                pointsLeft--;
            }
            else if(input == "intelligence" || input == "i")
            {
                setIntelligence(getIntelligence()+1);
                pointsLeft--;
            }
            else if(input == "agility" || input == "a")
            {
                setAgility(getAgility()+1);
                pointsLeft--;
            }
            else if(input == "luck" || input == "l")
            {
                setLuck(getLuck()+1);
                pointsLeft--;
            }
            else
                cout << "Please try again.\n";
            cout << pointsLeft << " points left to assign. Current distribution:\n\tStrength: " << getStrength() << " Perception: " << getPerception() << " Endurance: " << getEndurance() << " Charisma: " << getCharisma() << "\n\tIntelligence: " << getIntelligence() << " Agility: " << getAgility() << " Luck: " << getLuck() << endl;
        }

        cout << "\nYou clamber out of the cryochamber and start your journey out of the vault...\n";
        system(pauseCommand.c_str());
        system(clsCommand.c_str());
    }
    else
    {
        setName("Vault Boy");
        setAge(17);
        setStrength(getStrength()+2);
        setEndurance(getEndurance()+1);
        setAgility(getAgility()+1);
        setIntelligence(getIntelligence()+1);
    }
}

void Player::displayInventory()
{
    vector<Item> displayOnce;
    for(int i = 0; i < inventory.getNumItems(); i++)
    {
        Item currentItem = inventory[i];
        int numSame = inventory.count(currentItem);
        if(numSame == 1)
        {
            cout << "\t" << i+1 << ". " << inventory[i] << endl;
        }
        else if(find(displayOnce.begin(), displayOnce.end(), currentItem) == displayOnce.end())
        {
            displayOnce.push_back(currentItem);
            cout << "\t" << i+1 << ". " << inventory[i] << " (x" << numSame << ")" << endl;
        }
    }
}

//to be used for demonstration to show that crafting works , will fill inventory with items including crafting reagents
void Player::fillInventory()
{
    for(int i = 0; i < 3; i++)
    {
        addToInventory(Item("Blood Pack"));
        addToInventory(Item("Steel"));
        addToInventory(Item("Leather"));
        addToInventory(Item("Claw"));
        addToInventory(Item("Buckles"));
    }
    addToInventory(Item("Mini Nuke"));
    addToInventory(Item("Heavy Armor"));
    addToInventory(Item("Stimpak"));
}

bool Player::use(int idx)
{
    Item toUse = inventory[idx];

    if(toUse.itemType == "RECOVERY")
    {
        hp += toUse.hpRestore;
        removeFromInventory(toUse);
        cout << "Restored " << toUse.hpRestore << " hp.\n";
        system(pauseCommand.c_str());
        return true;
    }
    else
        return false;
}

void Player::printSPECIAL()
{
    cout << "\tS: " << getStrength() << " P: " << getPerception() << " E: " << getEndurance() << " C: " << getCharisma() << " I: " << getIntelligence() << " A: " << getAgility() << " L: " << getLuck() << endl;
}
