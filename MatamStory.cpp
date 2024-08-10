
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
int MatamStory::packAux(std::istream& eventsStream, std::string word, std::vector<std::shared_ptr<Encounter>>& g,
                        unsigned int counter, unsigned int pack_num);
void MatamStory::makePackEvent(std::string name, std::vector<std::shared_ptr<Encounter>>& e);






bool compare_players(const shared_ptr<Player>& player1 , const shared_ptr<Player>& player2 ){
    if (player1->getLevel() > player2->getLevel()) return true;
    if (player1->getLevel() < player2->getLevel()) return false;


    if (player1->getCoins() > player2->getCoins()) return true;
    if (player1->getCoins() < player2->getCoins()) return false;


    return player1->getName() < player2->getName();
}

//bool check_pack_recursive(vector<string>& pack, size_t& index) {
//    int count = 0;
//    for (index = 2; index <pack.size() ; ++index) {
//
//        if (pack[index] != "Snail" && pack[index] != "Slime" && pack[index] != "Balrog" && pack[index] != "Pack"){
//            return false;
//        }
//        count++;
//    }
//    if (count != stoi(pack[1])){
//        return false;
//    }
//    index = 2; // Reset index for nested pack checking
//    for (size_t i = 2; i < pack.size(); ++i) {
//        if (pack[i] == "Pack") {
//            size_t nestedIndex = i + 1; // Set the starting point for the nested pack
//            if (!check_pack_recursive(pack, nestedIndex)) {
//                return false; // Invalid nested pack
//            }
//            // Move the outer index to skip over the nested pack
//            index = nestedIndex; // Update the index to the position after the nested pack
//        }
//    }
//
//
//    return true;
//}

//bool checkevent(vector<string>& encounter){
//    if(encounter.size() < 1){
//        return false;
//    }
//    if(encounter[0] != "Snail" && encounter[0] != "Slime" &&
//    encounter[0] != "Balrog" && encounter[0] != "Pack" && encounter[0] != "SolarEclipse" && encounter[0] != "PotionsMerchant"){
//        return false;
//    }
//    if (encounter[0] != "Pack" && encounter.size() > 1){
//        return false;
//    }
//    if (encounter[0] == "Pack"  ){
//        size_t index = 2; // Start checking from the third element
//        return check_pack_recursive(encounter, index); // Check for valid pack
//    }
//    return true;
//}

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












//
//vector<string> getevent3(istringstream& eventstream);
//
//
//vector<string> getevent2(istringstream& eventstram) {
//    vector<string> event;
//    string event_type;
//    eventstram >> event_type;
//    if (eventstram.fail()) {
//        throw InvalidEventsFileException();
//    }
//    if (event_type == "Snail" || event_type == "Slime" || event_type == "Balrog" || event_type == "SolarEclipse"  || event_type == "PotionsMerchant") {
//        event.push_back(event_type);
//        return event;
//    }
//    if (event_type != "Pack") {
//        throw InvalidEventsFileException();
//    }
//    event.push_back(event_type); // should be pack
//    int count;
//    std::string input;
//
//    if (!(eventstram >> input)) {
//        throw InvalidEventsFileException();
//    }
//
//    try {
//        count = std::stoi(input);
//    } catch (const std::invalid_argument& e) {
//        throw InvalidEventsFileException();
//    } catch (const std::out_of_range& e) {
//        throw InvalidEventsFileException();
//    }
//
//    if (count <= 1) {
//        throw InvalidEventsFileException();
//    }
//
//    event.push_back(std::to_string(count));
//
//    for (int i = 0; i < count; i++) {
//        std::vector<string> monsterencounter = getevent3(eventstram);
//        for (const string& s : monsterencounter) {
//            event.push_back(s);
//        }
//    }
//
//    return event;
//}
//
//vector<string> getevent3(istringstream& eventstream) {
//    vector<string> event;
//    string name;
//    eventstream >> name;
//
//    if (eventstream.fail()) {
//        throw InvalidEventsFileException();
//    }
//    if (name == "Snail" || name == "Balrog" || name == "Slime") {
//        event.push_back(name);
//        return event;
//    }
//
//    if (name != "Pack") {
//        throw InvalidEventsFileException();
//    }
//    event.push_back(name); // should be pack
//    int count;
//    std::string input;
//
//    if (!(eventstream >> input)) {
//        throw InvalidEventsFileException();
//    }
//
//    try {
//        count = std::stoi(input);
//    } catch (const std::invalid_argument& e) {
//        throw InvalidEventsFileException();
//    } catch (const std::out_of_range& e) {
//        throw InvalidEventsFileException();
//    }
//
//    if (count <= 1) {
//        throw InvalidEventsFileException();
//    }
//
//    event.push_back(std::to_string(count));
//
//    for (int i = 0; i < count; i++) {
//        std::vector<string> monsterencounter = getevent3(eventstream);
//        for (const string& s : monsterencounter) {
//            event.push_back(s);
//        }
//    }
//
//    return event;
//}







std::string readNextWord(std::istringstream& stream) {
    std::string word;

    while (true) {
        stream >> std::ws; // Ignore leading whitespace and newlines
        if (stream >> word) { // Attempt to read the next word
            return word; // Return the valid word
        }
        // If the read fails, we loop back to skip additional whitespace
    }
}

// Function to read a count and ensure it's valid
int readCount(std::istringstream& stream) {
    std::string countStr = readNextWord(stream);
    int count;

    try {
        count = std::stoi(countStr); // Convert count to integer
    } catch (const std::invalid_argument&) {
        throw InvalidEventsFileException(); // Handle conversion error
    } catch (const std::out_of_range&) {
        throw InvalidEventsFileException(); // Handle out of range error
    }

    if (count <= 1) {
        throw InvalidEventsFileException();
    }

    return count;
}




std::vector<std::string> getevent2(std::istringstream& eventstream) {
    std::vector<std::string> event;
    std::string event_type = readNextWord(eventstream); // Read event type

    if (event_type == "Snail" || event_type == "Slime" || event_type == "Balrog" || event_type == "SolarEclipse" || event_type == "PotionsMerchant") {
        event.push_back(event_type);
        return event;
    }

    if (event_type != "Pack") {
        throw InvalidEventsFileException();
    }

    event.push_back(event_type); // should be Pack
int count;
std::string input;
    if (!(eventstream >> input)) {
        throw InvalidEventsFileException();
    }

    try {
        count = std::stoi(input);
    } catch (const std::invalid_argument& e) {
        throw InvalidEventsFileException();
    } catch (const std::out_of_range& e) {
        throw InvalidEventsFileException();
    }

    if (count <= 1) {
        throw InvalidCardsFile();
    }

    card.push_back(std::to_string(count));

    for (int i = 0; i < count; i++) {
        std::vector<std::string> monstercards = getCard3(deck);
        for (const std::string& s : monstercards) {
            card.push_back(s);
        }
    }

    return event;
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
//vector<string> get_card(ifstream& eventStream) {
//    vector<string> event;
//    string name;
//    eventStream >> name;
//    if (eventStream.fail()) {
//        throw InvalidEventsFileException();
//    }
//    if (name == "Snail" || name == "Slime" || name == "Balrog" || name == "SolarEclipse" || name == "PotionsMerchant") {
//        event.push_back(name);
//        return event;
//    }
//    if (name != "Pack") {
//        throw InvalidEventsFileException();
//    }
//    event.push_back(name); // should be pack
//    int count;
//    std::string input;
//
//    if (!(eventStream >> input)) {
//        throw InvalidEventsFileException();
//    }
//
//    try {
//        count = std::stoi(input);
//    } catch (const std::invalid_argument&) {
//        throw InvalidEventsFileException();
//    } catch (const std::out_of_range&) {
//        throw InvalidEventsFileException();
//    }
//
//    if (count <= 1) {
//        throw InvalidEventsFileException();
//    }
//
//    event.push_back(std::to_string(count));
//
//    for (int i = 0; i < count; i++) {
//        std::vector<string> monsterCards = get_card(eventStream);
//        event.insert(event.end(), monsterCards.begin(), monsterCards.end());
//    }
//    return event;
//}
//
bool isEvent(std::string name) const
{
    if (name == "PotionsMerchant")
    {
        return true;
    }
    if (name == "Snail")
    {
        return true;
    }
    if (name == "Slime")
    {
        return true;
    }
    if (name == "Balrog")
    {
        return true;
    }
    if (name == "SolarEclipse")
    {
        return true;
    }
    if (name == "Pack")
    {
        return true;
    }
    return false;
}
int MatamStory::packAux(std::istream& eventsStream, std::string word, std::vector<std::shared_ptr<Encounter>>& g,unsigned int counter, unsigned int pack_num){
    word = "";
    eventsStream >> word;
    for (unsigned int i = 0; i < word.size(); i++)
    {
        if (!isdigit(word[i]))
        {
            throw InvalidEventsFileException();
        }
    }
    unsigned int size_of_vector = std::stoi(word);
    if (size_of_vector < 2)
    {
        throw InvalidEventsFileException();
    }
    std::vector<int> helper;
    counter += size_of_vector;
    pack_num++;
    while (eventsStream >> word){
        if (!isEvent(word) || word == "PotionsMerchant" || word == "SolarEclipse")
        {
            throw EventsFileInvalid();
        }
        if (word != "Pack")
        {
            makePackEvent(word, g);
            helper.push_back(1);
        }
        else
        {
            if (word == "Pack")
            {
                packAux(eventsStream, word, g, counter, pack_num);
                helper.push_back(1);
            }
        }
        if (helper.size() >= size_of_vector)
        {
            break;
        }
    }
    if (helper.size() != size_of_vector)
    {
        throw InvalidEventsFileException();
    }
    return size_of_vector;
}

void MatamStory::makePackEvent(std::string name, std::vector<std::shared_ptr<Encounter>>& e)
{
    shared_ptr<Encounter> inthepack;
    if (name == "Snail")
    {
        inthepack = make_shared<Snail>();
    }
    if (name == "Slime")
    {
        inthepack = make_shared<Slime>();
    }
    if (name == "Balrog")
    {
        inthepack = make_shared<Balrog>();

    }
    e.push_back(inthepack);
}

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
    index = 0;
    string line;
    while (getline(eventsStream, line)) {
        // Trim leading and trailing whitespace (including newlines)
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

        // Skip empty lines
        if (line.empty()) {
            continue;
        }
//    string line;
//    while(getline(eventsStream,line)){

            std::istringstream eventStream(line);
            vector<string> event = getevent2(eventStream);



        shared_ptr<Encounter> encounter;
        if (event[0] == "Snail"){
            encounter = make_shared<Snail>();
        } else if (event[0] == "Slime"){
            encounter = make_shared<Slime>();
        } else if (event[0] == "Balrog"){
        encounter = make_shared<Balrog>();
        } else if (event[0] == "Pack"){
            int size = stoi(event[1]);
            int start = 1;
            vector<shared_ptr<Monsters>> monsters = getMonsters(event,start);
            encounter = make_shared<Pack>(monsters,size);
        } else if (event[0] == "SolarEclipse"){
            encounter = make_shared<SolarEclipse>();
        } else if (event[0] == "PotionsMerchant"){
            encounter = make_shared<PotionsMerchant>();
        } else {
            throw InvalidEventsFileException();
        }


        shared_ptr<Event> newEvent = make_shared<Event>(encounter);
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
    Events.pop();
    Events.push(event);
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
