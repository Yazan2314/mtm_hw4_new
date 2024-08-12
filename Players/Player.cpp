#include "Player.h"

Player::Player(std::string& name1, std::shared_ptr<Jop>& job1, std::shared_ptr<Character>& character1)
{
    this->name = name1;
    this->job = job1;
    this->character = character1;
    if (job1->getJob() == "Archer"){
        this->coins = 20;
    }else {
        this->coins = 10;
    }
    if(job1->getJob() == "Warrior"){
        this->Max_HP = 150;

    }else {
        this->Max_HP = 100;

    }
    this->current_HP = Max_HP;
    this->level = 1;
    this->Force = 5;
}

string Player::getDescription() const {
    return name + ", " + this->job->getJob() + " with " + this->character->getCharacter()
    + " character " + "(level " +std::to_string(level) +", force " + std::to_string(Force)  +")";
}

string Player::getName() const {
    return name;
}

int Player::getLevel() const {
    return level;
}

int Player::getForce() const {
    return Force;
}

int Player::getHealthPoints() const {
    return current_HP;
}
int Player::getCoins() const {
    return coins;
}

int Player::getCompetPower() {
    if(job->getJob() == "Warrior") {
        return Force * 2 + level;
    }
    return Force + level;
}

void Player::updateForce() {
    if (job->usingMagic()){
        Force++;
    }else{
        Force--;
        Force = std::max(0,Force);
    }
}

int Player::payhealth() {
    int amount = 0;
    if (character->getCharacter() == "Responsible"){
        while (current_HP < 100 && coins >= 5){
            coins -= 5;
            current_HP += 10;
           current_HP = std::min(100 , current_HP);
            amount++;
        }
    } else {
        if(getHealthPoints() < 50 && coins >= 5){
            coins -= 5;
            current_HP += 10;
            amount++;
        }
    }
    return amount;
}

///////////////////////// if the monster is balrog we need to increa the competpower by 2 for each round" //////
string Player::playEncounter(const std::shared_ptr<Encounter>& clash) {
    std::string clashking = clash->getType();
    std::string jobTupe = job->getJob();
    std::string  strategy = job->getstrategy();
    std::string charecterTupe = character->getCharacter();

    int combatpower = getCompetPower();
    if (clashking == "Snail" || clashking == "Slime" || clashking == "Balrog" || clashking == "Pack") {

        if (combatpower > clash->getcombatPower()) {
            level++;
            coins += clash->getloot();
            if (strategy == "CloseFighter") {
                current_HP -= 10;
                current_HP = std::max(0, current_HP);
            }



            if (clashking == "Balrog") {
                auto balrog = std::dynamic_pointer_cast<Balrog>(clash); // Dynamic cast
                if (balrog) {
                    balrog->increaseCombatPower();
                }
            }

            if (clashking == "Pack") {
                auto pack = std::dynamic_pointer_cast<Pack>(clash); // Dynamic cast to Pack
                if (pack) {
                    int balrogCount = 0;

                    // Count the number of Balrog monsters in the pack
                    for (const auto &monster : pack->getMonsters()) {
                        if (monster->getType() == "Balrog") {
                            ++balrogCount;
                        }
                    }

                    // Increase the combat power of the Pack based on the number of Balrogs
                    if (balrogCount > 0) {
                        pack->increaseCombatPower( balrogCount );
                    }
                }
            }
            return "win";

        } else {
            current_HP -= clash->getdamage();
            current_HP = std::max(0, current_HP);
            if (clashking == "Balrog") {
                auto balrog = std::dynamic_pointer_cast<Balrog>(clash); // Dynamic cast
                if (balrog) {
                    balrog->increaseCombatPower();
                }
            }

            if (clashking == "Pack") {
                auto pack = std::dynamic_pointer_cast<Pack>(clash); // Dynamic cast to Pack
                if (pack) {
                    int balrogCount = 0;

                    // Count the number of Balrog monsters in the pack
                    for (const auto &monster : pack->getMonsters()) {
                        if (monster->getType() == "Balrog") {
                            ++balrogCount;
                        }
                    }

                    // Increase the combat power of the Pack based on the number of Balrogs
                    if (balrogCount > 0) {
                        pack->increaseCombatPower( balrogCount);
                    }
                }
            }
            return "Lost";
        }
    } else if (clashking == "SolarEclipse") {
        int prev = Force;
        updateForce();
        return std::to_string(Force - prev);

    } else if (clashking == "PotionsMerchant") {
        int amount = payhealth();
        return std::to_string(amount);
    }
    return ""; // test

}


