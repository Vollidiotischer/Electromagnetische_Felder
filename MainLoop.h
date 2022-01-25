#pragma once
#include "Declarations.h"

namespace MainLoop {
	void run(); 

	void free_vec(std::vector<Point_Charge*>&); 

	void free_2d_array(std::array<std::array<my_vect*, points_per_row>, num_rows>&);
}