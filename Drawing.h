#pragma once

namespace Drawing {
	void init_SFML(sf::RenderWindow**); 

	
	void draw_screen(sf::RenderWindow* rw, std::vector<Point_Charge*>& point_charges, std::array<std::array<my_vect*, points_per_row>, num_rows>& vectors);
	
}