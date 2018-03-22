#include "../include/Character.h"
#include "../include/Commands.h"
#include <iostream>
using namespace std;

Character::Character(int startingX, int startingY, int startingZ)
{
    alive = true;
    hp = 100;
    age = 0;
    name = "Undefined";
    strength = 5;
    perception = 5;
    endurance = 5;
    charisma = 5;
    age = 5;
    intelligence = 5;
    agility = 5;
    luck = 5;
    x = startingX;
    y = startingY;
    z = startingZ;
    enemiesKilled = 0;
    shouldOutput = false;
}

void Character::use(string name)
{
    for(unsigned int i = 0; i < inventory.items.size(); i++)
    {
        if(inventory.items[i].itemName == name)
        {
            if(name == "healthKit")
            {
                //Assuming the player has a maximum of hp of 100 and the health kit is worth 20
                int hp = getHP();
                if(hp <= 80 && hp >= 1)//the players hp cant be not less than or equal to 0
                    hp = hp + 20;
                if(hp >= 81 && hp >= 100)
                    hp = 100 - hp;
                setHP(hp);
            }

            inventory.remove(inventory.items[i]);
        }
    }
}

void Character::moveUp()
{
    y--;
}

void Character::moveDown()
{
    y++;
}

void Character::moveLeft()
{
    x--;
}

void Character::moveRight()
{
    x++;
}

void Character::goUpFloor()
{
    z--;
}

void Character::goDownFloor()
{
    z++;
}

int Character::getX()
{
    return x;
}

int Character::getY()
{
    return y;
}

int Character::getZ()
{
    return z;
}

int Character::getHP()
{
    return hp;
}

int Character::getAge()
{
    return age;
}

string Character::getName()
{
    return name;
}

int Character::getStrength()
{
    return strength;
}

int Character::getPerception()
{
    return perception;
}

int Character::getEndurance()
{
    return endurance;
}

int Character::getCharisma()
{
    return charisma;
}

int Character::getIntelligence()
{
    return intelligence;
}

int Character::getAgility()
{
    return agility;
}

int Character::getLuck()
{
    return luck;
}

void Character::setLoc(int x_, int y_)
{
    x = x_;
    y = y_;
}

void Character::setHP(int hp_)
{
    hp = hp_;
}

void Character::setAge(int age_)
{
    age = age_;
}

void Character::setName(string name_)
{
    name = name_;
}

void Character::setStrength(int strength_)
{
    strength = strength_;
}

void Character::setPerception(int perception_)
{
    perception = perception_;
}

void Character::setEndurance(int endurance_)
{
    endurance = endurance_;
}

void Character::setCharisma(int charisma_)
{
    charisma = charisma_;
}

void Character::setIntelligence(int intelligence_)
{
    intelligence = intelligence_;
}

void Character::setAgility(int agility_)
{
    agility = agility_;
}

void Character::setLuck(int luck_)
{
    luck = luck_;
}

void Character::equip(int i)
{
    Item item = inventory[i];
    if(item.itemType == "RANGED WEAPON" || item.itemType == "MELEE WEAPON")
    {
        equippedWeapon = item;
    }
    else if(item.itemType == "ARMOR")
    {
        equippedArmor = item;
    }
    else
    {
        cout << "Can't equip that.\n";
        system(pauseCommand.c_str());
    }
}

void Character::unequip(int choice)
{
    if(choice == 0)
    {
        equippedWeapon = defaultWeapon;
    }
    else if(choice == 1)
    {
        equippedArmor = defaultArmor;
    }
}

int Character::takeDamage(int dam, bool ignoreArmor)
{
    int damageCount = dam;
    if(!ignoreArmor)
        damageCount -= equippedArmor.damageResistance;
    if(damageCount < 0)
    {
        damageCount = 0;
    }
    hp -= damageCount;
    if(hp <= 0)
    {
        alive = false;
        hp = 0;
    }
    return damageCount;
}

int Character::takeDamageFrom(Item& i, bool kill, int damageModifier)
{
    int damageCount = i.damage;
    damageCount += damageModifier;
    damageCount -= equippedArmor.damageResistance;
    damageCount -= (endurance*2)+luck;
    if(damageCount < 0)
    {
        damageCount = 0;
    }
    if(kill)
        damageCount = 999999;
    if(!kill && i.itemType == "RANGED WEAPON")
        i.ammoCount--;
    hp -= damageCount;
    if(hp <= 0)
    {
        alive = false;
        hp = 0;
    }
    return damageCount;
}

// returns damage done
int Character::attack(Character& e, bool kill)
{
    int damageModifier;
    if(equippedWeapon.getItemType()=="MELEE WEAPON")
    {
        damageModifier=(strength*2)+luck;
    }
    if(equippedWeapon.getItemType()=="RANGED WEAPON")
    {
        damageModifier=(perception*4)+luck;
    }
    int dam = e.takeDamageFrom(equippedWeapon, kill, damageModifier);

    if (name == "Grognak The Destroyer")
        cout << name + ": \"Grogogo I am going to destroy you!\"\n";
    else if (name == "Deathclaw")
        cout << name + ": \"Ain't no ravenclaw. This ain't Harry Potter no mo\"\n";
    else if (name == "Radscorpion")
        cout << name + ": \"Wesley Snipes ain't got nothing on me sucka!\"\n";
    else if (name == "Raider Clasher")
        cout << name + ": \"I am part of Raider Nation!\"\n";
    else if (name == "Ghoul")
        cout << name + ": \"I am part of the ghoulish Army that will stop you!\"\n";
    else if (name == "Rabid Dog")
        cout << name + ": \"Grr I will bite your face off!\"\n";
    else if (name == "Super Mutant")
        cout << name + ": \"X-MEN once hit me up, but Wolverine was not down...\"\n";
    else if (name == "Yao Guai")
        cout << name + ": \"This ain't no ying and yang in this game!\"\n";
    else if (name == "Assaultron")
        cout << name + ": \"Transformers, robots in disguise...oh wait wrong series\"\n";
    else if (name == "Mobile Turret")
        cout << name + ": \"Rattatatat!\"\n";

    if(shouldOutput)
        cout << "Dealt " << dam << " damage to " << e.name << endl;
    if(!e.isAlive())
    {
        int caps = e.inventory.getCaps();
        if(shouldOutput)
            cout << e.name << " died.\nCollected " << caps << " caps.\n";
        inventory.addCaps(caps);
        enemiesKilled++;
    }
    system(pauseCommand.c_str());
    return dam;
}
