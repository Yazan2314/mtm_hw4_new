#include "Player.h"
#include "exception"
Player::Player(std::string& name1, std::shared_ptr<Jop> &job1, std::shared_ptr<Character> &character1) :name(std::move(name1))
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
    + " character" + "(level " +std::to_string(level) +", force" + std::to_string(Force)  +")";
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
    if (job->getJob() == "Magician"){
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
    std::string clashking = clash->getTupe();
    std::string jobTupe = job->getJob();
    std::string charecterTupe = character->getCharacter();

    int combatpower = getCompetPower();
    if (clashking == "Snail" || clashking == "Slime" || clashking == "Balrog" || clashking == "Pack") {

        if (combatpower > clash->getcombatPower()) {
            level++;
            coins += clash->getloot();
            if (jobTupe == "Warrior") {
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
                auto pack = std::dynamic_pointer_cast<Pack>(clash); // Dynamic cast
                if (pack) {
                    for (const auto &monster: pack->getMonsters()) {
                        if (monster->getTupe() == "Balrog") {
                            auto balrog = std::dynamic_pointer_cast<Balrog>(monster); // Dynamic cast
                            if (balrog) {
                                balrog->increaseCombatPower();
                            }
                        }
                    }
                }
            }
            return "Won";
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
                auto pack = std::dynamic_pointer_cast<Pack>(clash); // Dynamic cast
                if (pack) {
                    for (const auto &monster: pack->getMonsters()) {
                        if (monster->getTupe() == "Balrog") {
                            auto balrog = std::dynamic_pointer_cast<Balrog>(monster); // Dynamic cast
                            if (balrog) {
                                balrog->increaseCombatPower();
                            }
                        }
                    }
                }
            }
            return "Lost";
        }
    } else if (clashking == "SolarEclips") {
        int prev = Force;
        updateForce();
        return std::to_string(Force - prev);

    } else if (clashking == "PotionsMerchant") {
        int amount = payhealth();
        return std::to_string(amount);
    }
    return "";

}

std::shared_ptr<Jop> Player::createJob(const std::string& jobType) {
    if (jobType == "Warrior") {
        return std::make_shared<Warrior>();
    } else if (jobType == "Archer") {
        return std::make_shared<Archer>();
    } else if (jobType == "Magician") {
        return std::make_shared<Magician>();
    }
    throw std::invalid_argument("Invalid job type");
}

// Factory method for creating characters
std::shared_ptr<Character> Player::createCharacter(const std::string& characterType) {
    if (characterType == "Responsible") {
        return std::make_shared<Responsible>();
    } else if (characterType == "RiskTaking") {
        return std::make_shared<RiskTaking>();
    }
    throw std::invalid_argument("Invalid character type");
}
