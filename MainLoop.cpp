#include <iostream>
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include "Declarations.h"

#include "MainLoop.h"
#include "Drawing.h"
#include "Events.h"
#include "Calculations.h"

/*

CONTROLS: 
	m_left -> point_charge (positive) 
	m_right -> point_charge (negative) 
	mouse_wheel (scroll) -> resize charge of point_charge
	mouse_wheel (press) -> move around in the screen

	key_D -> delete point_charge


MAINLOOP: 
	clean main loop up a little

DECLARATIONS: 
	set point density & make it work


EVENTS: 


CALCULATION: 
	calculate vector of each point
		- (struct with x, y, vx, vy coponent) (my_vect struct) 
		- calculate
		- save in according list (vectors) 


DRAWING: 
	draw all vectors (with according lengths) 
		- get access to vector list in draw
*/

namespace MainLoop {

	void run() {
		
		// create variables
		std::vector<Point_Charge*> point_charges;
		std::array<std::array<my_vect*, points_per_row>, num_rows> vectors;

		sf::RenderWindow* rw; 

		// initialize variables
		Drawing::init_SFML(&rw); 
		Calculations::init_lists(vectors); 


		// main loop
		while (rw->isOpen()) {

			Events::handle_events(rw, point_charges);

			Calculations::calculate_frame(point_charges, vectors); 

			Drawing::draw_screen(rw, point_charges, vectors); 

		}

		// cleanup
		free_vec(point_charges); 
		free_2d_array(vectors);

		delete rw; 
	}

	void free_vec(std::vector<Point_Charge*>& vec) {

		for (int i = 0; i < vec.size(); i++) {
			delete vec[i]; 
		}

		vec.clear();
	}

	void free_2d_array(std::array<std::array<my_vect*, points_per_row>, num_rows>& arr) {

		for (int i = 0; i < num_rows; i++) {
			for (int i2 = 0; i2 < points_per_row; i2++) {
				delete arr[i][i2]; 
			}
		}

		
	}

}