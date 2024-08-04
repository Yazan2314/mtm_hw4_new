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
        virtual string getDescription() = 0;
        virtual string getTupe() = 0;
        virtual int getcombatPower() = 0;
        virtual int getloot() = 0;
        virtual int getdamage() = 0;


    };
//////////////////////////// monster ///////////////////////////////////////////////////////
    class Monsters : public Encounter{
    protected:
        int combatPower;
        int loot;
        int damage;
    public:
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
        string getTupe() override{
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
            return getTupe() + " (power " + std::to_string( getcombatPower())
            + ", loot " + std::to_string(getloot()) + ", damage " + std::to_string(getdamage());
        }


    };
    ///////////////////////////////////// Slime /////////////////////////////////////////
    class Slime : public Monsters {
Slime(){
    combatPower = 12;
    loot = 5;
    damage = 25;
}
        string getTupe() override{
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
            return getTupe() + " (power " + std::to_string( getcombatPower())
                   + ", loot " + std::to_string(getloot()) + ", damage " + std::to_string(getdamage());
        }
    };
    class Balrorg : public Monsters {
    public:
        Balrorg(){
            combatPower = 15;
            loot = 100;
            damage = 9001;
        }

        string getTupe() override {
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
            return getTupe() + " (power " + std::to_string( getcombatPower())
                   + ", loot " + std::to_string(getloot()) + ", damage " + std::to_string(getdamage());
        }

    };
    class Pack : public Monsters {
    private:
        vector<shared_ptr<Monsters>> monsters;
        vector<shared_ptr<Pack>> packs;
        size_t size;

    public:
        Pack(vector<shared_ptr<Monsters>>& monsterList, vector<shared_ptr<Pack>>& packList, size_t packSize)
                : monsters(monsterList), packs(packList), size(packSize) {
            combatPower = 0;
            loot = 0;
            damage = 0;

            for (const auto& monster : monsters) {
                combatPower += monster->getcombatPower();
                loot += monster->getloot();
                damage += monster->getdamage();
            }

            for (const auto& pack : packs) {
                combatPower += pack->getcombatPower();
                loot += pack->getloot();
                damage += pack->getdamage();
            }
        }
        string getTupe() override {
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
            return "Pack of " + std::to_string(size)  + " (power " + std::to_string( getcombatPower())
                   + ", loot " + std::to_string(getloot()) + ", damage " + std::to_string(getdamage());
        }

    };

///////////////// specialevent /////////////////////////////////////////////
    class specialevent : public Encounter {
    };

    class SolarEclips : public specialevent {
        string getTupe() override {
            return "SolarEclips";
        }
        string getDescription() override{
            return "SolarEclips";
        }

    };
    class PotionsMerchant : public specialevent {
        string getTupe() override {
            return "PotionsMerchant";
        }
        string getDescription() override{
            return "PotionsMerchant";
        }
    };
    class Event {
protected:
    string Tupe;
    shared_ptr<Encounter> encounter;
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    string getDescription() const {
        return encounter->getDescription();
    }
    string getTupe() {
        return Tupe;
    }
    Event(const shared_ptr<Encounter>& encounter1){
        this->Tupe = encounter1->getTupe();
        this->encounter = encounter1;
    }
    shared_ptr<Encounter> getEncounter(){
        return encounter;
    }




};

#endif // EVENT_H