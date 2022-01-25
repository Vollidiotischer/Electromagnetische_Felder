#pragma once
#include <SFML/Graphics.hpp>

struct my_vect {
	float x, y; 
	double vx, vy; 

	my_vect(float x, float y, double vx, double vy) {
		this->x = x; 
		this->y = y; 
		this->vx = vx; 
		this->vy = vy; 
	}
};

struct Point_Charge {
	int x, y; 
	int charge; // number of electron charges (e)
	int radius; 

	Point_Charge(int x, int y, int charge, int radius) {
		this->x = x; 
		this->y = y; 
		this->charge = charge; 
		this->radius = radius;
	}

	bool hits(int x, int y) {

		int dx = this->x - x;
		int dy = this->y - y; 

		return sqrt(dx * dx + dy * dy) < this->radius;
	}

	static int calculate_circle_size(int x) {
		return floor(50 - 40 * pow(2.71, -0.006 * abs(x)));
	}
};

constexpr int screen_width = 500; 
constexpr int screen_height = 750; 

constexpr int points_per_row = 25; 
constexpr int num_rows = 40; 

constexpr int vector_length = 13; 
constexpr int vector_height = 3; 
constexpr int circle_size = 5; 

constexpr int max_charge = 10000; 
