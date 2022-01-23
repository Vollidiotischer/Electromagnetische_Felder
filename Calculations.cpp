#include <iostream>
#include <array>

#include "Declarations.h"

namespace Calculations {

	namespace {

		double f_e(double r, double q) {

			double new_charge = q * 1.6022 * 100000000;// *pow(10, -7);

			double e = (1.0 / (4.0 * 3.1415 * 8.85)) * (new_charge / ((double) r * r));

			return e; 

		}

		void calculate_field(my_vect* vect, std::vector<Point_Charge*>& point_charges) {

			for (int i = 0; i < point_charges.size(); i++) {
				double dx = (double)vect->x - point_charges[i]->x; 
				double dy = (double)vect->y - point_charges[i]->y;

				double r = sqrt(dx * dx + dy * dy); 


				double e = f_e(r, point_charges[i]->charge); 

				double qx = (dx / (abs(dx + dy))) * e; 
				double qy = (dy / (abs(dx + dy))) * e; 

				vect->vx += qx; 
				vect->vy += qy; 
			}

		}
	}

	void init_lists(std::array<std::array<my_vect*, points_per_row>, num_rows>& vectors) {

		float dist_x = (float)screen_width / points_per_row; 
		float dist_y = (float)screen_height / num_rows; 

		for (int i = 0; i < num_rows; i++) {
			for (int i2 = 0; i2 < points_per_row; i2++) {
				vectors[i][i2] = new my_vect(i2 * dist_x, i * dist_y, 0, 0);
			}
		}
	}

	

	void calculate_frame(std::vector<Point_Charge*>& point_charges, std::array<std::array<my_vect*, points_per_row>, num_rows>& vectors) {
		for (int i = 0; i < vectors.size(); i++) {
			for (int i2 = 0; i2 < vectors[i].size(); i2++) {
				vectors[i][i2]->vx = 0;
				vectors[i][i2]->vy = 0;
				calculate_field(vectors[i][i2], point_charges); 
			}
		}

	}

}

/*

width: 500
height: 750

points_per_row: 50
num_rows: 75

dist_x = width / points_per_row
dist_y = height / num_rows

*/