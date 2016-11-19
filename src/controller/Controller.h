//
// Created by Valentin on 28/10/2016.
//

#ifndef PACMAN_CONTROLLER_H
#define PACMAN_CONTROLLER_H

#include <SFML/Window/Event.hpp>
#include "../model/Model.h"

class Controller {
private:
	sf::RenderWindow &window;
	Model *model;
    int compteur = 0;
public:

	Controller(sf::RenderWindow &window, Model *model);

	void ActionEvent(sf::Time time);

	void MoveKeyPressed(sf::Event event, float myftime);

	void ramassePiece(int x, int y);

	~Controller();
};


#endif //PACMAN_CONTROLLER_H
