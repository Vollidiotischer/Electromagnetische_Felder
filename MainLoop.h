#pragma once
#include <vector>

namespace MainLoop {
	void run(); 

	template<typename T>
	void free_vec(std::vector<T*>*); 
}