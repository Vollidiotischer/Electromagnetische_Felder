#include <SFML/Graphics.hpp>
#include <iostream>

#include "Declarations.h"

namespace Drawing {
	void init_SFML(sf::RenderWindow** rw) {

		*rw = new sf::RenderWindow(sf::VideoMode(screen_width, screen_height), "Elektromagnetische Felder");

		(*rw)->setKeyRepeatEnabled(false);

	}

	void draw_plus(sf::RenderWindow* rw, int x, int y, int r) {
		sf::RectangleShape rect({ (float)(r * 1.75), (float)r / 4 });
		rect.setFillColor(sf::Color::Black);
		rect.setPosition(x - r * 1.75 / 2, y - r / 8);
		rw->draw(rect);

		rect.setSize({ (float)(r / 4.0), (float)(r * 1.75) });
		rect.setPosition((float)(x - r / 8.0), y - r * 1.75 / 2);
		rw->draw(rect);

	}

	void draw_minus(sf::RenderWindow* rw, int x, int y, int r) {
		sf::RectangleShape rect({ (float)(r * 1.75), (float)r / 4 });
		rect.setPosition(x - r * 1.75 / 2, y - r / 8);
		rect.setFillColor(sf::Color::Black); 
		rw->draw(rect); 
	}

	void draw_screen(sf::RenderWindow* rw, std::vector<Point_Charge*>* point_charges, std::vector<my_vect*>* vectors) {

		rw->clear(sf::Color::White); 

		sf::CircleShape circle(10, 10); // radius = 10, Number of Points = 10
		
		// draw vectors

		// draw point charges & Point charge Symbols (+ or -)
		for (int i = 0; i < point_charges->size(); i++) {
			Point_Charge* pc = (*point_charges)[i]; 
			circle.setOrigin(pc->radius, pc->radius); 
			circle.setPosition(pc->x, pc->y); 
			circle.setRadius(pc->radius);

			circle.setFillColor(pc->charge > 0 ? sf::Color::Blue : pc->charge == 0 ? sf::Color::Black : sf::Color::Red); // blue: positive charge, red: negative charge

			rw->draw(circle); 

			if (pc->charge == 0) {
				continue; 
			}

			if (pc->charge > 0) {
				draw_plus(rw, pc->x, pc->y, pc->radius); 
			}
			else {
				draw_minus(rw, pc->x, pc->y, pc->radius); 
			}
		}


		rw->display(); 
	}
}