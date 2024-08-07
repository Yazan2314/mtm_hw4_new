#include "Event.h"

// Encounter constructor



// Monsters constructor
Monsters::Monsters( int force, int loot, int damage)
        :  combatPower(force), loot(loot), damage(damage) {}

//// Increase combat power
//void Monsters::increaseCombatPower() {
//    combatPower += 2;
//}
//
//// Snail constructor
//Snail::Snail() : Monsters("Snail", 5, 2, 10) {}
//
//// Get type for Snail
//string Snail::getType() const {
//    return "Snail";
//}
//
//// Get description for Snail
//string Snail::getDescription() const {
//    return getType() + " (power " + std::to_string(getcombatPower())
//           + ", loot " + std::to_string(getloot()) + ", damage " + std::to_string(getdamage()) + ")";
//}
//
//// Slime constructor
//Slime::Slime() : Monsters("Slime", 12, 5, 25) {}
//
//// Get type for Slime
//string Slime::getType() const {
//    return "Slime";
//}
//
//// Get description for Slime
//string Slime::getDescription() const {
//    return getType() + " (power " + std::to_string(getCombatPower())
//           + ", loot " + std::to_string(getLoot()) + ", damage " + std::to_string(getDamage()) + ")";
//}
//
//// Balrog constructor
//Balrog::Balrog() : Monsters("Balrog", 15, 100, 9001) {}
//
//// Get type for Balrog
//string Balrog::getType() const {
//    return "Balrog";
//}
//
//// Get description for Balrog
//string Balrog::getDescription() const {
//    return getType() + " (power " + std::to_string(getCombatPower())
//           + ", loot " + std::to_string(getLoot()) + ", damage " + std::to_string(getDamage()) + ")";
//}
//
//// Pack constructor
//Pack::Pack(const vector<shared_ptr<Monsters>>& monsters, int size)
//        : Monsters("Pack", 0, 0, 0), size(size) {
//    for (const auto& monster : monsters) {
//        combatPower += monster->getCombatPower();
//        loot += monster->getLoot();
//        damage += monster->getDamage();
//    }
//}
//
//// Get type for Pack
//string Pack::getType() const {
//    return "Pack";
//}
//
//// Get description for Pack
//string Pack::getDescription() const {
//    return "Pack of " + std::to_string(size) + " (power " + std::to_string(getCombatPower())
//           + ", loot " + std::to_string(getLoot()) + ", damage " + std::to_string(getDamage()) + ")";
//}
//
//// Get type for SolarEclipse
//string SolarEclipse::getType() const {
//    return "Solar Eclipse";
//}
//
//// Get description for SolarEclipse
//string SolarEclipse::getDescription() const {
//    return "Solar Eclipse";
//}
//
//// Get type for PotionsMerchant
//string PotionsMerchant::getType() const {
//    return "Potions Merchant";
//}
//
//// Get description for PotionsMerchant
//string PotionsMerchant::getDescription() const {
//    return "Potions Merchant";
//}
//
//// Event constructor
//Event::Event(const shared_ptr<Encounter>& encounter)
//        : type(encounter->getType()), encounter(encounter) {}
//
//// Get description of Event
//string Event::getDescription() const {
//    return encounter->getDescription();
//}
//
//// Get type of Event
//string Event::getType() const {
//    return type;
//}
//
//// Get encounter of Event
//shared_ptr<Encounter> Event::getEncounter() const {
//    return encounter;
//}
