//#include "Event.h"
//
//// Encounter methods
//int Encounter::getCombatPower() { return 0; }
//int Encounter::getLoot() { return 0; }
//int Encounter::getDamage() { return 0; }
//
//// Monsters methods
//Monsters::Monsters(int force, int loot, int damage)
//        : combatPower(force), loot(loot), damage(damage) {}
//
//void Monsters::increaseCombatPower() {
//    combatPower += 2;
//}
//
//// Snail methods
//Snail::Snail() : Monsters(5, 2, 10) {}
//
//string Snail::getType() {
//    return "Snail";
//}
//
//int Snail::getCombatPower() {
//    return combatPower;
//}
//
//int Snail::getLoot() {
//    return loot;
//}
//
//int Snail::getDamage() {
//    return damage;
//}
//
//string Snail::getDescription() {
//    return getType() + " (power " + std::to_string(getCombatPower())
//           + ", loot " + std::to_string(getLoot()) + ", damage " + std::to_string(getDamage()) + ")";
//}
//
//// Slime methods
//Slime::Slime() : Monsters(12, 5, 25) {}
//
//string Slime::getType() {
//    return "Slime";
//}
//
//int Slime::getCombatPower() {
//    return combatPower;
//}
//
//int Slime::getLoot() {
//    return loot;
//}
//
//int Slime::getDamage() {
//    return damage;
//}
//
//string Slime::getDescription() {
//    return getType() + " (power " + std::to_string(getCombatPower())
//           + ", loot " + std::to_string(getLoot()) + ", damage " + std::to_string(getDamage()) + ")";
//}
//
//// Balrog methods
//Balrog::Balrog() : Monsters(15, 100, 9001) {}
//
//string Balrog::getType() {
//    return "Balrog";
//}
//
//int Balrog::getCombatPower() {
//    return combatPower;
//}
//
//int Balrog::getLoot() {
//    return loot;
//}
//
//int Balrog::getDamage() {
//    return damage;
//}
//
//string Balrog::getDescription() {
//    return getType() + " (power " + std::to_string(getCombatPower())
//           + ", loot " + std::to_string(getLoot()) + ", damage " + std::to_string(getDamage()) + ")";
//}
//
//// Pack methods
//Pack::Pack(const vector<shared_ptr<Monsters>>& monsters)
//        : Monsters(0, 0, 0), size(monsters.size()), monsters(monsters) {
//    for (const auto& monster : monsters) {
//        combatPower += monster->getCombatPower();
//        loot += monster->getLoot();
//        damage += monster->getDamage();
//    }
//}
//
//vector<shared_ptr<Monsters>> Pack::getMonsters() const {
//    return monsters;
//}
//
//string Pack::getType() {
//    return "Pack";
//}
//
//int Pack::getCombatPower() {
//    return combatPower;
//}
//
//int Pack::getLoot() {
//    return loot;
//}
//
//int Pack::getDamage() {
//    return damage;
//}
//
//string Pack::getDescription() {
//    return "Pack of " + std::to_string(size) + " members" + " (power " + std::to_string(getCombatPower())
//           + ", loot " + std::to_string(getLoot()) + ", damage " + std::to_string(getDamage()) + ")";
//}
//
//// SolarEclipse methods
//string SolarEclipse::getType() {
//    return "SolarEclipse";
//}
//
//string SolarEclipse::getDescription() {
//    return "SolarEclipse";
//}
//
//// PotionsMerchant methods
//string PotionsMerchant::getType() {
//    return "PotionsMerchant";
//}
//
//string PotionsMerchant::getDescription() {
//    return "PotionsMerchant";
//}
//
////// EncounterFactory methods
////shared_ptr<Encounter> EncounterFactory::createEncounter(const string& type) {
////    if (type == "Snail") {
////        return make_shared<Snail>();
////    } else if (type == "Slime") {
////        return make_shared<Slime>();
////    } else if (type == "Balrog") {
////        return make_shared<Balrog>();
////    } else if (type == "SolarEclipse") {
////        return make_shared<SolarEclipse>();
////    } else if (type == "PotionsMerchant") {
////        return make_shared<PotionsMerchant>();
////    }
////    return nullptr;
////}
////
////// Event methods
////Event::Event(const string& type) {
////    this->type = type;
////    this->encounter = EncounterFactory::createEncounter(type);
////}
//
//string Event::getDescription() const {
//    return encounter->getDescription();
//}
//
//string Event::getType() {
//    return type;
//}
//
//shared_ptr<Encounter> Event::getEncounter() {
//    return encounter;
//}
