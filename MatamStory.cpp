
#include "MatamStory.h"
#include "Utilities.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
#include <memory>

using std::make_shared;
using namespace std;

class InvalidPlayersFileException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid Players File";
    }
};

class InvalidEventsFileException  : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid Events File";
    }
};


bool compare_players(const shared_ptr<Player>& player1 , const shared_ptr<Player>& player2 ){
    if (player1->getLevel() > player2->getLevel()) return true;
    if (player1->getLevel() < player2->getLevel()) return false;


    if (player1->getCoins() > player2->getCoins()) return true;
    if (player1->getCoins() < player2->getCoins()) return false;


    return player1->getName() < player2->getName();
}

bool check_pack_recursive(vector<string>& pack, size_t& index) {
    int count = 0;
    for (index = 2; index <pack.size() ; ++index) {

        if (pack[index] != "Snail" && pack[index] != "Slime" && pack[index] != "Balrorg" && pack[index] != "Pack"){
            return false;
        }
        count++;
    }
    if (count != stoi(pack[1])){
        return false;
    }
    index = 2; // Reset index for nested pack checking
    for (size_t i = 2; i < pack.size(); ++i) {
        if (pack[i] == "Pack") {
            size_t nestedIndex = i + 1; // Set the starting point for the nested pack
            if (!check_pack_recursive(pack, nestedIndex)) {
                return false; // Invalid nested pack
            }
            // Move the outer index to skip over the nested pack
            index = nestedIndex; // Update the index to the position after the nested pack
        }
    }


    return true;
}

bool checkevent(vector<string>& encounter){
    if(encounter.size() < 1){
        return false;
    }
    if(encounter[0] != "Snail" && encounter[0] != "Slime" &&
    encounter[0] != "Balrorg" && encounter[0] != "Pack" && encounter[0] != "SolarEclips" && encounter[0] != "PotionsMerchant"){
        return false;
    }
    if (encounter[0] != "Pack" && encounter.size() > 1){
        return false;
    }
    if (encounter[0] == "Pack"  ){
        size_t index = 2; // Start checking from the third element
        return check_pack_recursive(encounter, index); // Check for valid pack
    }
    return true;

}



vector<string> getevent(const string& line) {
    vector<string> event;
    istringstream iss(line);
    string temp;

    while (iss >> temp) {
        event.push_back(temp);
    }

    return event;
}
vector<string> getEventData(std::istringstream& iss) {
    std::vector<std::string> eventData;
    std::string token;
    while (iss >> token) {
        eventData.push_back(token);
    }
    return eventData;
}


//bool checkpleayer(const string& line){
//
//}




























std::vector<std::string> parseLine(const std::string& line) {
    std::vector<std::string> tokens; // Vector to hold the parsed tokens
    std::istringstream iss(line); // Create a string stream from the line
    std::string token;

    // Extract each word (token) from the line
    while (iss >> token) {
        tokens.push_back(token); // Add each token to the vector
    }

    return tokens; // Return the vector of tokens
}


MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/
//    while (getline(eventsStream,line)){
//        istringstream iss(line);
//        vector<string> event = getEventData(iss);
//
//        if(event[0] == "Slime"){
//            shared_ptr<Encounter> slimeevent (new Slime());
//            shared_ptr<Event> ev (new Event(slimeevent));
//            this->Events.push(ev);
//        } else if (event[0] == "Snail"){
//            shared_ptr<Encounter> snailevent  (new Snail());
//            shared_ptr<Event> ev (new Event(snailevent));
//            this->Events.push(ev);
//        }
//    }

    string line;

    // Read events from the events stream
    while (getline(eventsStream, line)) {
        vector<string> event = parseLine(line); // Ensure parseLine is correctly implemented
        if (!checkevent(event)) { // Validate the event
            throw InvalidEventsFileException();
        }

        // Create events based on type using make_shared
        if (event[0] == "Slime") {
            Events.push(make_shared<Event>(make_shared<Slime>()));
        } else if (event[0] == "Snail") {
            Events.push(make_shared<Event>(make_shared<Snail>()));
        } else if (event[0] == "Balrorg") {
            Events.push(make_shared<Event>(make_shared<Balrorg>()));
        } else if (event[0] == "SolarEclipse") {
            Events.push(make_shared<Event>(make_shared<SolarEclips>()));
        } else if (event[0] == "PotionsMerchant") {
            Events.push(make_shared<Event>(make_shared<PotionsMerchant>()));
        } else if (event[0] == "Pack") {
            // Check the number of monsters in the pack
            if (event.size() < 3) {
                throw InvalidEventsFileException(); // Ensure there's a pack size defined
            }
            vector<shared_ptr<Encounter>> packMembers;
            for (size_t i = 2; i < event.size(); ++i) {
                if (event[i] == "Slime") {
                    packMembers.push_back(make_shared<Slime>());
                } else if (event[i] == "Snail") {
                    packMembers.push_back(make_shared<Snail>());
                } else if (event[i] == "Balrorg") {
                    packMembers.push_back(make_shared<Balrorg>());
                } else {
                    throw InvalidEventsFileException(); // Invalid monster type in the pack
                }
            }
            Events.push(make_shared<Event>(make_shared<Pack>(vector<Monsters> (vector<Encounter> packMembers))));
        } else {
            throw InvalidEventsFileException(); // Unknown event type
        }
    }
    while (std::getline(players, line1)) {
        if (!checkIsPlayerValid(line1)) {
            throw InvalidPlayersFile();
        }

        std::istringstream iss(line1); // Define std::istringstream inside the loop
        std::string name, job, behavior;

        if (!(iss >> name >> job >> behavior)) {
            throw InvalidPlayersFileException();
        }

        std::shared_ptr<Jop> jobPtr;
        if (job == "Warrior") {
            jobPtr = std::make_shared<Warrior>();
        } else if (job == "Archer") {
            jobPtr = std::make_shared<Archer>();
        }else if ( job == "Magician"){
            jobPtr = make_shared<Magician>();
        } else {
            throw InvalidPlayersFileException();
        }

        std::shared_ptr<Character> behaviorPtr;
        if (behavior == "Responsible") {
            behaviorPtr = std::make_shared<Responsible>();
        } else if (behavior == "RiskTaking") {
            behaviorPtr = std::make_shared<RiskTaking>();
        } else {
            throw InvalidPlayersFileException();
        }

        std::shared_ptr<Player> playerPtr = std::make_shared<Player>(name, jobPtr, behaviorPtr);
        players.push_back(playerPtr);
    }

    players.close();

    if (players.size() > 6 || players.size() < 2) {
        throw InvalidPlayersFileException();
    }
    // Read players from the players stream
//    while (getline(playersStream, line)) {
//        istringstream iss(line);
//        string name, job, character;
//        iss >> name >> job >> character;
//
//        // Validate player attributes
//        if (name.length() < 3 || name.length() > 15 ||
//            (job != "Warrior" && job != "Magician" && job != "Archer") ||
//            (character != "Responsible" && character != "RiskTaking")) {
//            throw InvalidPlayersFileException();
//        }
//
//        // Create job and character based on the string values
//        std::shared_ptr<Jop> jobPtr;
//        if (job == "Warrior") {
//            jobPtr = make_shared<Warrior>();
//        } else if (job == "Magician") {
//            jobPtr = make_shared<Magician>();
//        } else if (job == "Archer") {
//            jobPtr = make_shared<Archer>();
//        }
//
//        std::shared_ptr<Character> characterPtr;
//        if (character == "Responsible") {
//            characterPtr = make_shared<Responsible>();
//        } else if (character == "RiskTaking") {
//            characterPtr = make_shared<RiskTaking>();
//        }
//
//        // Create a new player and add it to the players list
//        shared_ptr<Player> player = make_shared<Player>(name, jobPtr, characterPtr);
//        players.push_back(player);
//    }
    this->m_turnIndex = 1; // Initialize turn index
}

    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/

    /*============================================*/


//    this->m_turnIndex = 1;
//}

void MatamStory::playTurn(Player& player) {

    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */
std::shared_ptr<Event> event = Events.front();
Events.pop();
Events.push(event);
    printTurnDetails(m_turnIndex,*players[index],*event);
    string result = (*players[index]).playEncounter(event->getEncounter());
    if(result == "Won"){
       result = getEncounterLostMessage(*players[index],event->getEncounter()->getloot());
    }else if (result == "Lose"){
      result =   getEncounterLostMessage(*players[index] , event->getEncounter()->getdamage());
    } else if (event->getEncounter()->getTupe() == "SolarEclips"){
       result = getSolarEclipseMessage(*players[index],stoi(result));
    } else {
        result = getPotionsPurchaseMessage(*players[index] ,stoi(result));
    }
    printTurnOutcome(result);
    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/
    for ( ; index < players.size(); ++index) {

        if(players[index]->getHealthPoints() == 0){
            continue;
        }else {
            playTurn(*players[index]);
        }
    }

    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
    vector<shared_ptr<Player>> sortedplayers = players;
    sort(sortedplayers.begin(),sortedplayers.end(), compare_players);

    for (size_t i = 0; i < sortedplayers.size(); ++i) {
        printLeaderBoardEntry(i+1, *sortedplayers[i]);
    }

    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    size_t player_died = 0;

    for (const auto & player : players) {
        if(player->getHealthPoints() == 0){
            player_died++;
        }
    }
    if(player_died == players.size()){
        return true;
    }
    for (const auto  & player :players) {
        if (player->getLevel() == 10){
            return true;
        }
    }
//    for (int i = 0; i < players.size(); ++i) {
//        if (players[i]->getLevel() == 10){
//            return true;
//        }
//    }
    return false; // Replace this line
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/
    for (size_t i = 0; i < players.size() ; i++) {
        printStartPlayerEntry(i+1,*players[i]);
    }

    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/
vector<shared_ptr<Player>> sortedplayer = players;
    sort(sortedplayer.begin(),sortedplayer.end(), compare_players);
    if (sortedplayer[0]->getLevel()!= 10){
        printNoWinners();
    } else {
        printWinner(*sortedplayer[0]);
    }
    /*========================================================================*/
}
////////