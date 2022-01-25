#pragma once

namespace Calculations {

	void init_lists(std::array<std::array<my_vect*, points_per_row>, num_rows>&); 

	void calculate_frame(std::vector<Point_Charge*>&, std::array<std::array<my_vect*, points_per_row>, num_rows>&);

	double calculate_vector_length(my_vect*); 

}