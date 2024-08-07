
#pragma once

#include <iostream>

#include "Players/Player.h"
//#include "Events/Event.h"
#include "vector"
#include "memory"
#include "queue"

using std::queue;
using std::vector;
using std::shared_ptr;
using std::string;



class MatamStory{
private:
    queue<shared_ptr<Event>> Events;
    vector<shared_ptr<Player>> players;
    unsigned int m_turnIndex;
    size_t index;
    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player& player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;
    // Factory function to create events
//    shared_ptr<Event> createEvent(const string& eventType) {
//        if (eventType == "Slime") {
//            return shared_ptr<Event>(new Event(shared_ptr<Encounter>(new Slime())));
//        } else if (eventType == "Snail") {
//            return shared_ptr<Event>(new Event(shared_ptr<Encounter>(new Snail())));
//        }
//        // Add more event types as needed
//        return nullptr; // Return nullptr for unknown event types
//    }

public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);

    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();
};
