#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <array>
#include "Declarations.h"

namespace Drawing {

	namespace {
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

		void draw_arrow(sf::RenderWindow* rw, double x, double y, double w, double h) {
			static sf::RectangleShape line({ vector_length, vector_height });
			static sf::CircleShape triangle(circle_size, 3); // TRIANGLE

			line.setFillColor(sf::Color::Black);
			triangle.setFillColor(sf::Color::Black);

			float angle = atan(h / w) / 3.1415 * 180;

			if (w <= 0) {
				angle += 180.0;
			}

			

			int x_triangle = x + cos(angle / 180.0 * 3.1415) * vector_length;
			int y_triangle = y + sin(angle / 180.0 * 3.1415) * vector_length + vector_height / 2.0;

			triangle.setOrigin(circle_size, circle_size);
			triangle.setRotation(angle + 90);
			triangle.setPosition(x_triangle, y_triangle);

			line.setOrigin(0, vector_height / 2.0);

			line.setRotation(angle);
			line.setPosition(x, y);


			rw->draw(line);
			rw->draw(triangle);
		}
	}

	void init_SFML(sf::RenderWindow** rw) {

		*rw = new sf::RenderWindow(sf::VideoMode(screen_width, screen_height), "Elektromagnetische Felder");

		(*rw)->setKeyRepeatEnabled(false);

	}

	void draw_screen(sf::RenderWindow* rw, std::vector<Point_Charge*>& point_charges, std::array<std::array<my_vect*, points_per_row>, num_rows>& vectors) {

		rw->clear(sf::Color::White); 

		sf::CircleShape circle(10, 10); // radius = 10, Number of Points = 10
		
		// draw vectors
		for (int i = 0; i < vectors.size(); i++) {
			for (int i2 = 0; i2 < vectors[i].size(); i2++) {
				draw_arrow(rw, vectors[i][i2]->x, vectors[i][i2]->y, vectors[i][i2]->vx, vectors[i][i2]->vy);

			}
		}

		// draw point charges & Point charge Symbols (+ or -)
		for (int i = 0; i < point_charges.size(); i++) {
			Point_Charge* pc = point_charges[i]; 
			circle.setOrigin(pc->radius, pc->radius); 
			circle.setPosition(pc->x, pc->y); 
			circle.setRadius(pc->radius);

			circle.setFillColor(pc->charge > 0 ? sf::Color::Red : pc->charge == 0 ? sf::Color::Black : sf::Color::Blue); // blue: negative charge, red: positive charge

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