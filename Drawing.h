#pragma once

namespace Drawing {
	void init_SFML(sf::RenderWindow**); 

	void draw_screen(sf::RenderWindow*, std::vector<Point_Charge*>*, std::vector<my_vect*>*); 

}