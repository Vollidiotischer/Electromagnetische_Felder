#pragma once
#include <SFML/Graphics.hpp>

struct my_vect {
	int x, y; 
	double vx, vy; 

	my_vect(int x, int y, double vx, double vy) {
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
		return floor(25 - 15 * pow(2.71, -0.1 * abs(x)));
	}
};

constexpr int screen_width = 500; 
constexpr int screen_height = 750; 

void initSFML(sf::RenderWindow*);