#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "MainLoop.h"
#include "Declarations.h"
#include "Drawing.h"
#include "Events.h"
#include "Calculations.h"

/*

MAINLOOP: 
	clean main loop up a little

DECLARATIONS: 
	set point density & make it work


EVENTS: 
	implement being able to change point_charge-charge using themouse wheel


CALCULATION: 
	calculate vector of each point
		- (struct with x, y, vx, vy coponent) 
		- calculate
		- save in according list


DRAWING: 
	draw all point charges
		- get access to point charges list
	draw all vectors
		- get access to vector list in draw
*/

namespace MainLoop {

	void run() {
		
		// create variables
		std::vector<Point_Charge*> point_charges;
		std::vector<my_vect*> vectors;

		sf::RenderWindow* rw; 

		// initialize variables
		Drawing::init_SFML(&rw); 


		// main loop
		while (rw->isOpen()) {

			Events::handle_events(rw, &point_charges);

			Calculations::calculate_frame(); 

			Drawing::draw_screen(rw, &point_charges, &vectors); 

		}

		// cleanup
		free_vec<Point_Charge>(&point_charges); 
		free_vec<my_vect>(&vectors); 

		delete rw; 
	}

	template<typename T>
	void free_vec(std::vector<T*>* vec) {

		for (int i = 0; i < vec->size(); i++) {
			delete (*vec)[i]; 
		}

		vec->clear();
	}

}