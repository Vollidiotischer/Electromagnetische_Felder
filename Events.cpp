#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Declarations.h"


namespace Events {

	namespace {
		void delete_point_charge(sf::RenderWindow* rw, std::vector<Point_Charge*>& point_charges) {

			int mox = sf::Mouse::getPosition(*rw).x;
			int moy = sf::Mouse::getPosition(*rw).y;

			for (int i = 0; i < point_charges.size(); i++) {
				if (point_charges[i]->hits(mox, moy)) {
					delete point_charges[i];
					point_charges.erase(point_charges.begin() + i);
				}
			}
		}

		void create_point_charge(sf::RenderWindow* rw, sf::Event& events, std::vector<Point_Charge*>& point_charges) {
			// create Point charge

			bool charge_is_positive = events.mouseButton.button == sf::Mouse::Left;

			int mox = sf::Mouse::getPosition(*rw).x;
			int moy = sf::Mouse::getPosition(*rw).y;

			int charge_ammount = charge_is_positive ? starting_charge : -1 * starting_charge;

			point_charges.push_back(new Point_Charge(mox, moy, charge_ammount, Point_Charge::calculate_circle_size(charge_ammount)));

		}

		void resize_point_charge(sf::RenderWindow* rw, sf::Event& events, std::vector<Point_Charge*>& point_charges) {

			int mox = sf::Mouse::getPosition(*rw).x;
			int moy = sf::Mouse::getPosition(*rw).y;

			for (int i = 0; i < point_charges.size(); i++) {
				if (point_charges[i]->hits(mox, moy)) {

					if (abs(point_charges[i]->charge + events.mouseWheel.delta) > max_charge) {
						continue;
					}

					point_charges[i]->charge += events.mouseWheel.delta;
					point_charges[i]->radius = Point_Charge::calculate_circle_size(point_charges[i]->charge);

				}
			}
		}

		void move_screen(sf::RenderWindow* rw, std::vector<Point_Charge*>& point_charges, int& old_x, int& old_y) {
			int mox = sf::Mouse::getPosition(*rw).x;
			int moy = sf::Mouse::getPosition(*rw).y;

			int dx = mox - old_x; 
			int dy = moy - old_y; 

			for (int i = 0; i < point_charges.size(); i++) {
				point_charges[i]->x += dx; 
				point_charges[i]->y += dy; 
			}

			old_x = mox; 
			old_y = moy; 
		}
	}

	void handle_events(sf::RenderWindow* rw, std::vector<Point_Charge*>& point_charges) {

		static bool screen_moving = false; 
		static int old_x = 0; 
		static int old_y = 0; 

		if (screen_moving) {
			move_screen(rw, point_charges, old_x, old_y); 
		}

		sf::Event events;

		while (rw->pollEvent(events)) {
			if (events.type == sf::Event::Closed) {
				rw->close();
			}

			if (events.type == sf::Event::KeyPressed) {
				if (events.key.code == sf::Keyboard::D) {
					delete_point_charge(rw, point_charges); 
				}
			}

			if (events.type == sf::Event::MouseButtonPressed) {
				if (events.key.code == sf::Mouse::Middle) {
					old_x = sf::Mouse::getPosition(*rw).x; 
					old_y = sf::Mouse::getPosition(*rw).y; 
					screen_moving = true; 
				}
				else {
					create_point_charge(rw, events, point_charges);
				}
			}

			if (events.type == sf::Event::MouseWheelMoved) {
				resize_point_charge(rw, events, point_charges); 
			}

			if (events.type == sf::Event::MouseButtonReleased) {
				if (events.key.code == sf::Mouse::Middle) {
					screen_moving = false;
				}
			}

		}

	}
}