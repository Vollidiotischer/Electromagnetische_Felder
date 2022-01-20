#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Declarations.h"


namespace Events {

	void handle_events(sf::RenderWindow* rw, std::vector<Point_Charge*>* point_charges) {

		sf::Event events;

		while (rw->pollEvent(events)) {
			if (events.type == sf::Event::Closed) {
				rw->close();
			}

			if (events.type == sf::Event::MouseButtonPressed) {

				// create Point charge

				bool charge_is_positive = events.mouseButton.button == sf::Mouse::Left;

				int mox = sf::Mouse::getPosition(*rw).x;
				int moy = sf::Mouse::getPosition(*rw).y;

				int charge_ammount = charge_is_positive ? 10 : -10;

				point_charges->push_back(new Point_Charge(mox, moy, charge_ammount, Point_Charge::calculate_circle_size(charge_ammount)));

			}

			if (events.type == sf::Event::MouseWheelMoved) {

				int mox = sf::Mouse::getPosition(*rw).x;
				int moy = sf::Mouse::getPosition(*rw).y;

				for (int i = 0; i < point_charges->size(); i++) {
					if ((*point_charges)[i]->hits(mox, moy)) {

						if (abs((*point_charges)[i]->charge + events.mouseWheel.delta) > 25) {
							continue; 
						}

						(*point_charges)[i]->charge += events.mouseWheel.delta;
						(*point_charges)[i]->radius = Point_Charge::calculate_circle_size((*point_charges)[i]->charge);
						std::cout << (*point_charges)[i]->charge << " " << (*point_charges)[i]->radius << std::endl;

					}
				}
			}

		}

	}
}


/*

int x = 0

if (abs(x) > 25) 
	x -= x/abs(x); 

if (x > 25)	
	x = 25
if (x < -25)
	x = -25

*/