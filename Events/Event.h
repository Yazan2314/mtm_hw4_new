#ifndef EVENT_H
#define EVENT_H
    #pragma once

    #include "../Players/Player.h"
    #include "vector"
    #include "memory"
    #include "string"



    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;








    class Encounter {
    public:
//        virtual ~Encounter() = default;
        virtual string getDescription() = 0;
        virtual string getType() = 0;
        virtual int getcombatPower(){
            return 0;
        }
        virtual int getloot(){
            return 0;
        }
        virtual int getdamage() {
            return 0;
        }


    };
//////////////////////////// monster ///////////////////////////////////////////////////////
    class Monsters : public Encounter{
    protected:
        int combatPower;
        int loot;
        int damage;
    public:
//        Monsters(int force, int loot, int damage);
        void increaseCombatPower(){
            combatPower += 2;
        }

    };
    ////////////////////////////////// Snail /////////////////////////////
    class Snail : public Monsters {
    public:
    Snail(){
        combatPower = 5;
        loot = 2;
        damage = 10;
    }
//Snail() : Monsters(5,2,10){}
    string getType() override{
        return "Snail";
    }


        int getcombatPower() override {
            return combatPower;
        }
        int getloot() override {
            return loot;
        }
        int getdamage() override {
            return damage;
        }
        string getDescription() override {
            return getType() + " (power " + std::to_string( getcombatPower())
            + ", loot " + std::to_string(getloot()) + ", damage " + std::to_string(getdamage()) + ")";
        }


    };
    ///////////////////////////////////// Slime /////////////////////////////////////////
    class Slime : public Monsters {
    public:


        string getType() override{
            return "Slime";
        }
        int getcombatPower() override {
            return combatPower;
        }
        int getloot() override {
            return loot;
        }
        int getdamage() override {
            return damage;
        }
        string getDescription() override {
            return getType() + " (power " + std::to_string( getcombatPower())
                   + ", loot " + std::to_string(getloot()) + ", damage " + std::to_string(getdamage()) + ")";
        }


        Slime(){
            combatPower = 12;
            loot = 5;
            damage = 25;
        }
    };
    class Balrog : public Monsters {
    public:
        Balrog(){
            combatPower = 15;
            loot = 100;
            damage = 9001;
        }


        string getType() override {
            return "Balrog";
        }
        int getcombatPower() override {
            return combatPower;
        }
        int getloot() override {
            return loot;
        }
        int getdamage() override {
            return damage;
        }
        string getDescription() override {
            return getType() + " (power " + std::to_string( getcombatPower())
                   + ", loot " + std::to_string(getloot()) + ", damage " + std::to_string(getdamage()) + ")";
        }

    };
    class Pack : public Monsters {
    protected:

        size_t size;
        std::vector<std::shared_ptr<Monsters>> monsters;
    public:
//        Pack(const std::vector<std::shared_ptr<Monsters>>& monsters)
//            : Monsters(0, 0, 0), size(monsters.size()), monsters(monsters) {
//
//                // Initialize combatPower, loot, and damage based on the monsters in the pack
//                for (const auto& monster : monsters) {
//                    combatPower += monster->getcombatPower();
//                    loot += monster->getloot();
//                    damage += monster->getdamage();
//                }
//            }

       Pack( vector <shared_ptr<Monsters>> & monsters , int size ) {
            combatPower = 0;
            loot = 0;
            damage = 0;
            this->size = size;
            for (auto &monster: monsters) {
                combatPower += monster->getcombatPower();
                loot += monster->getloot();
                damage += monster->getdamage();
            }
        }
        std::vector<std::shared_ptr<Monsters>> getMonsters() const {
            return monsters;
        }

                string getType() override {
            return "Pack";
        }
        int getcombatPower() override {
            return combatPower;
        }
        int getloot() override {
            return loot;
        }
        int getdamage() override {
            return damage;
        }
        string getDescription() override {
            return "Pack of " + std::to_string(size) + " members" + " (power " + std::to_string( getcombatPower())
                   + ", loot " + std::to_string(getloot()) + ", damage " + std::to_string(getdamage()) + ")";
        }

    };

///////////////// specialevent /////////////////////////////////////////////
    class SpecialEvent : public Encounter {

    };

    class SolarEclipse : public SpecialEvent  {
        string getType() override {
            return "SolarEclipse";
        }
        string getDescription() override{
            return "SolarEclipse";
        }

    };
    class PotionsMerchant : public SpecialEvent {
        string getType() override {
            return "PotionsMerchant";
        }
        string getDescription() override{
            return "PotionsMerchant";
        }
    };
    class Event {
protected:
    string Type;
    shared_ptr<Encounter> encounter;
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */


    Event(const shared_ptr<Encounter>& encounter1){
        this->Type = encounter1->getType();
        this->encounter = encounter1;
    }

    string getDescription() const {
        return encounter->getDescription();
    }
    string getType() {
        return Type;
    }

    shared_ptr<Encounter> getEncounter(){
        return encounter;
    }




};

#endif // EVENT_H
