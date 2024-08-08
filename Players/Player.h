#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <string>
#include "memory"
#include "algorithm"
#include "./Events/Event.h"
using std::string;

class Encounter;

//class PlayerStrategy {
//public:
//    virtual string getStrategy() = 0;
//};
//
//// Concrete Strategy for Close Fighting
//class CloseFighter : public PlayerStrategy {
//public:
//    string getStrategy() override {
//        return "CloseFighter";
//    }
//};
//
//// Concrete Strategy for Distance Fighting
//class DistanceFighter : public PlayerStrategy {
//public:
//    string getStrategy() override {
//        return "DistanceFighter";
//    }
//
//};

class Character {
public:
    virtual string getCharacter()=0;
};

class Responsible : public Character {
    string getCharacter() override {
        return "Responsible";
    }
};
class RiskTaking : public Character {
    string getCharacter() override{
        return "RiskTaking";
    }
};



class Jop {
//protected:
//    std::unique_ptr<PlayerStrategy> strategy;
public:
    virtual string getJob()=0;
    virtual string getstrategy() = 0;
    virtual bool usingMagic() = 0;
};
class Warrior : public Jop{
    string getJob() override {
        return "Warrior";
    }
    string getstrategy() override {
        return "CloseFighter";
    }
    bool usingMagic() override {
        return false;
    }

};
class Archer : public Jop{
    string getJob() override {
        return "Archer";
    }
    string getstrategy() override {
        return "DistanceFighter";
    }
    bool usingMagic() override {
        return false;
    }
};
class Magician : public Jop{
    string getJob() override {
        return "Magician";
    }
    string getstrategy() override {
        return "DistanceFighter";
    }
    bool usingMagic() override {
        return true;
    }
};





class Player {
protected:
    string name;
    int level;
    int Force;
    int current_HP;
    int Max_HP;
    int coins;

    std::shared_ptr<Jop> job;
    std::shared_ptr<Character> character;


public:
    /// constructor ///
    Player(string& name1 , std::shared_ptr<Jop>& job1 , std::shared_ptr<Character>& character1);


    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;

    int getCompetPower();


    void updateForce();

    int payhealth();
    string playEncounter(const std::shared_ptr<Encounter>& clash);



};


#endif // PLAYER_H