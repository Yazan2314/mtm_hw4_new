
#include "MatamStory.h"

#include "Utilities.h"



bool compare_player(const shared_ptr<Player>& player1 , const shared_ptr<Player>& player2 ){
    if (player1->getLevel() > player2->getLevel()) return true;
    if (player1->getLevel() < player2->getLevel()) return false;


    if (player1->getCoins() > player2->getCoins()) return true;
    if (player1->getCoins() < player2->getCoins()) return false;


    return player1->getName() < player2->getName();
}





























MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    /*===== TODO: Open and read events file =====*/


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

    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/

    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
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

    /*========================================================================*/
}
////////