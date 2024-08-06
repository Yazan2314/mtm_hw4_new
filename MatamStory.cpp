
#include "MatamStory.h"
#include "Utilities.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
#include <memory>


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



bool checkpleayer(const string& line){

}




























std::vector<std::string> getEventData(std::istringstream& iss) {
    std::vector<std::string> eventData;
    std::string token;

    // Extract tokens from the stream until a newline or end of stream
    while (iss >> token) {
        eventData.push_back(token);
    }

    return eventData; // Return the vector containing parsed event data
}


MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
std::string line;
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



    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/

    /*============================================*/


    this->m_turnIndex = 1;
}

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

    for (int i = 0; i < sortedplayers.size(); ++i) {
        printLeaderBoardEntry(i+1, *sortedplayers[i]);
    }

    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    int player_died = 0;

    for (const auto & player : players) {
        if(player->getHealthPoints() == 0){
            player_died++;
        }
    }
    if(player_died == players.size()){
        return true;
    }
    for (int i = 0; i < players.size(); ++i) {
        if (players[i]->getLevel() == 10){
            return true;
        }
    }
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