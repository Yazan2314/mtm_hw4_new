
#include "MatamStory.h"
#include "Utilities.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
#include <memory>
#include <cctype>



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

bool compare_players(const shared_ptr<Player>& player1 , const shared_ptr<Player>& player2 );
bool cheack_Player(const std::string& line);
std::string readNextWord(std::istringstream& stream);
int readCount(std::istringstream& stream);
std::vector<std::string> parsePackEvents(std::istringstream& stream, int count);
std::vector<std::string> getevent2(std::istringstream& eventstream);
vector<shared_ptr<Monsters>> getMonsters(vector<string>& event, int &start);






bool compare_players(const shared_ptr<Player>& player1 , const shared_ptr<Player>& player2 ){
    if (player1->getLevel() > player2->getLevel()) return true;
    if (player1->getLevel() < player2->getLevel()) return false;


    if (player1->getCoins() > player2->getCoins()) return true;
    if (player1->getCoins() < player2->getCoins()) return false;


    return player1->getName() < player2->getName();
}



bool checkevent(vector<string>& encounter){
    if(encounter.size() < 1){
        return false;
    }
    if(encounter[0] != "Snail" && encounter[0] != "Slime" &&
    encounter[0] != "Balrog" && encounter[0] != "Pack" && encounter[0] != "SolarEclipse" && encounter[0] != "PotionsMerchant"){
        return false;
    }
    if (encounter[0] != "Pack" && encounter.size() > 1){
        return false;
    }

    return true;
}

bool cheack_Player(const std::string& line){
    std::istringstream iss(line);
    std::vector<std::string > playerdata;
    std::string word;
    while(iss >> word){
        playerdata.push_back(word);
    }
    if (playerdata.size() != 3){
        return false;
    }
    if (playerdata[0].size() < 3 || playerdata[0].size() > 15){
        return false;
    }
    // Check if name consists only of alphabetic characters
    for (char c : playerdata[0]) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    if (playerdata[1] != "Warrior" && playerdata[1] != "Magician" && playerdata[1] != "Archer"){
        return false;
    }
    if (playerdata[2]  != "RiskTaking" && playerdata[2] != "Responsible" ){
        return false;
    }
    return true;
}
bool check_player_valid(const vector<string>& playerData) {
    if (playerData.size() != 3) {
        return false; // Invalid number of fields
    }

    const string& name = playerData[0];
    const string& job = playerData[1];
    const string& character = playerData[2];

    if (name.empty() || !std::all_of(name.begin(), name.end(), ::isalpha)) {
        return false; // Name must be non-empty and consist only of alphabetic characters
    }

    if (job != "Warrior" && job != "Archer" && job != "Magician") {
        return false;
    }

    if (character != "Responsible" && character != "RiskTaking") {
        return false;
    }

    return true;
}








vector<shared_ptr<Monsters>> getMonsters(vector<string>& event, int &start) {
    vector<shared_ptr<Monsters>> monsters;
    size_t size = stoi(event[start]);
    size_t i = start + 1;

    while (i < start + 1 + size && i < event.size()) {
        if (event[i] == "Pack") {
            int size_2 = stoi(event[i + 1]);
            int nested_start = i + 2;
            vector<shared_ptr<Monsters>> gm = getMonsters(event, nested_start);
            i = nested_start - 1;
            shared_ptr<Monsters> m = make_shared<Pack>(gm, size_2);
            monsters.push_back(m);
        } else {
            if (event[i] == "Slime") {
                shared_ptr<Monsters> m = make_shared<Slime>();
                monsters.push_back(m);
            } else if (event[i] == "Snail") {
                shared_ptr<Monsters> m = make_shared<Snail>();
                monsters.push_back(m);
            } else {
                shared_ptr<Monsters> m = make_shared<Balrog>();
                monsters.push_back(m);
            }
        }
        i++;
    }

    start = i;
    return monsters;
}








bool is_event(const std::string& word) {
    return word == "PotionsMerchant" || word == "Snail" ||
           word == "Slime" || word == "Balrog" ||
           word == "SolarEclipse" || word == "Pack";
}









void makePackEvent(const std::string& name, std::vector<std::shared_ptr<Monsters>>& e) {
    if (name == "Snail") {
        e.push_back(std::make_shared<Snail>());
    } else if (name == "Slime") {
        e.push_back(std::make_shared<Slime>());
    } else if (name == "Balrog") {
        e.push_back(std::make_shared<Balrog>());
    }
}

// Recursive function to handle nested packs
int packAux(std::istream& eventsStream, std::string& word, std::vector<std::shared_ptr<Monsters>>& g,
            unsigned int counter, unsigned int pack_num ,std::string size_of_word) {
    // Read the size of the pack
    word = size_of_word;
    for (char c : word) {
        if (!isdigit(c)) {
            throw InvalidEventsFileException();
        }
    }
    unsigned int size_of_vector = std::stoi(word);
    if (size_of_vector < 2) {
        throw InvalidEventsFileException();
    }

    std::vector<int> helper;
    counter += size_of_vector;
    pack_num++;

    while (eventsStream >> word) {
        if (!is_event(word) || word == "PotionsMerchant" || word == "SolarEclipse") {
            throw InvalidEventsFileException();
        }

        if (word != "Pack") {
            makePackEvent(word, g); // Pass the monsters vector
            helper.push_back(1);
        } else {
            string  size_of_pack;
            eventsStream >> size_of_pack;
            packAux(eventsStream, word, g, counter, pack_num,size_of_pack);
            helper.push_back(1);
        }

        if (helper.size() >= size_of_vector) {
            break;
        }
    }

    if (helper.size() != size_of_vector) {
        throw InvalidEventsFileException();
    }
    return size_of_vector;
}


MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
    index = 0;
    std::string word;

    while (eventsStream >> word) {
        if (!is_event(word)) {
            throw InvalidEventsFileException();
        }

        std::shared_ptr<Encounter> encounter;

        if (word == "Snail") {
            encounter = std::make_shared<Snail>();
        } else if (word == "Slime") {
            encounter = std::make_shared<Slime>();
        } else if (word == "Balrog") {
            encounter = std::make_shared<Balrog>();
        } else if (word == "PotionsMerchant") {
            encounter = std::make_shared<PotionsMerchant>();
        } else if (word == "SolarEclipse") {
            encounter = std::make_shared<SolarEclipse>();
        } else if (word == "Pack") {
            string size_of_pack;
            eventsStream >> size_of_pack;

            if (stoi(size_of_pack) < 2) {
                throw InvalidEventsFileException();
            }
            std::vector<std::shared_ptr<Monsters>> monsters; // Changed to Monsters
            try {
                packAux(eventsStream, word, monsters, 0, 0,size_of_pack);
                encounter = std::make_shared<Pack>(monsters, stoi(size_of_pack)); // Use size of the vector
            } catch (...) {
                throw InvalidEventsFileException();
            }
        }

        std::shared_ptr<Event> newEvent = std::make_shared<Event>(encounter);
        this->Events.push(newEvent);
    }


////// todo: read players from the stream

    string line1;
    while (getline(playersStream, line1)) {
        // Trim leading and trailing whitespace (including newlines)
        line1.erase(0, line1.find_first_not_of(" \t\n\r\f\v"));
        line1.erase(line1.find_last_not_of(" \t\n\r\f\v") + 1);

        // Skip empty lines
        if (line1.empty()) {
            continue;
        }

        if (!cheack_Player(line1)) {
            throw InvalidPlayersFileException();
        }

        std::istringstream iss(line1);
        string name, job, character;
        if (!(iss >> name >> job >> character)) {
            throw InvalidPlayersFileException();
        }

        shared_ptr<Jop> playerjob;
        if (job == "Warrior") {
            playerjob = make_shared<Warrior>();
        } else if (job == "Archer") {
            playerjob = make_shared<Archer>();
        } else if (job == "Magician") {
            playerjob = make_shared<Magician>();
        } else {
            throw InvalidPlayersFileException();
        }

        shared_ptr<Character> playercharacter;
        if (character == "Responsible") {
            playercharacter = make_shared<Responsible>();
        } else if (character == "RiskTaking") {
            playercharacter = make_shared<RiskTaking>();
        } else {
            throw InvalidPlayersFileException();
        }

        shared_ptr<Player> newPlayer = make_shared<Player>(name, playerjob, playercharacter);
        players.push_back(newPlayer);
    }

    if (players.size() < 2 || players.size() > 6){
        throw InvalidPlayersFileException();
    }



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
    ////////// anthor solition i can search for player in players with for and play it //////
std::shared_ptr<Event> event = Events.front();
    Events.pop();
    Events.push(event);
    printTurnDetails(m_turnIndex,*players[index],*event);
    string result = (*players[index]).playEncounter(event->getEncounter());
    if(result == "win"){
       result = getEncounterWonMessage(*players[index],event->getEncounter()->getloot());
    }else if (result == "Lost"){
      result =   getEncounterLostMessage(*players[index] , event->getEncounter()->getdamage());
    } else if (event->getEncounter()->getType() == "SolarEclipse"){
       result = getSolarEclipseMessage(*players[index], stoi(result));
    } else if (event->getEncounter()->getType() == "PotionsMerchant") {
        result = getPotionsPurchaseMessage(*players[index] , stoi(result));
    }
    printTurnOutcome(result);
    m_turnIndex++;

}

void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/
    for (index = 0 ; index < players.size(); ++index) {

        if(players[index]->getHealthPoints() == 0){
            continue;
        }else {
            playTurn(*players[index]);
        }
    }

    index = 0;

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
