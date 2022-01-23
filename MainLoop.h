#pragma once
#include "Declarations.h"

namespace MainLoop {
	void run(); 

	template<typename T>
	void free_vec(std::vector<T*>&); 

	void free_2d_array(std::array<std::array<my_vect*, points_per_row>, num_rows>&);
}