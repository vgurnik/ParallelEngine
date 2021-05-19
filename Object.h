#pragma once
#include <SFML/Graphics.hpp>
#include "Linalg.h"

enum class Type {
	CUBE,
	CUBOID,
	SPHERE,
};

//The class implements shapes such as cuboid, cube, and sphere.
class Object {
private:
	Type shape;
	sf::Vector3f position;
	double length;
	double width;
	double height;
public:
	Object(Type T, sf::Vector3f pos, double side, ...) {
		shape = T;
		position = pos;
		double* a = &side;
		switch (T) {
		case Type::CUBOID:
			length = *a;
			a++;
			width = *a;
			a++;
			height = *a;
			break;
		default:
			length = *a;
			width = 0;
			height = 0;
			break;
		}
	}

	//Calculates the distance from the observer to the shape.
	double distance(sf::Vector3f dot) {
		switch (shape) {
		case Type::SPHERE:
			return sqrt((dot.x - position.x) * (dot.x - position.x) + (dot.y - position.y) * (dot.y - position.y) + (dot.z - position.z) * (dot.z - position.z)) - length;
			break;
		case Type::CUBE:
			sf::Vector3f dist(abs(dot.x - position.x) - length, abs(dot.y - position.y) - length, abs(dot.z - position.z) - length);
			double d = sqrt(dist.x * dist.x + dist.y * dist.y + dist.z * dist.z);
			if (dist.x < 0 && dist.y < 0 && dist.z < 0) return -d;
			return d;
			break;
		case Type::CUBOID:
			sf::Vector3f dist(abs(dot.x - position.x) - length, abs(dot.y - position.y) - height, abs(dot.z - position.z) - width);
			double d = sqrt(dist.x * dist.x + dist.y * dist.y + dist.z * dist.z);
			if (dist.x < 0 && dist.y < 0 && dist.z < 0) return -d;
			return d;
			break;
		default:
			break;
		}
	}

	//Unit normal to the shape.
	sf::Vector3f normal(sf::Vector3f dot) {
		switch (shape) {
		case Type::SPHERE:
			return normalize(position - dot);
			break;
		case Type::CUBE:
			sf::Vector3f dist(abs(dot.x - position.x) - length, abs(dot.y - position.y) - length, abs(dot.z - position.z) - length);
			if (dist.x < dist.y && dist.x < dist.z) {
				dist.x = 1;
				dist.y = 0;
				dist.z = 0;
				if (position.x < dot.x) dist.x *= (-1);
				return dist;
			}
			else if (dist.y < dist.z) {
				dist.x = 0;
				dist.y = 1;
				dist.z = 0;
				if (position.y < dot.y) dist.y *= (-1);
				return dist;
			}
			else {
				dist.x = 0;
				dist.y = 0;
				dist.z = 1;
				if (position.z < dot.z) dist.z *= (-1);
				return dist;
			}
			break;
		case Type::CUBOID:
			sf::Vector3f dist(abs(dot.x - position.x) - length, abs(dot.y - position.y) - height, abs(dot.z - position.z) - width);
			if (dist.x < dist.y && dist.x < dist.z) {
				dist.x = 1;
				dist.y = 0;
				dist.z = 0;
				if (position.x < dot.x) dist.x *= (-1);
				return dist;
			}
			else if (dist.y < dist.z) {
				dist.x = 0;
				dist.y = 1;
				dist.z = 0;
				if (position.y < dot.y) dist.y *= (-1);
				return dist;
			}
			else {
				dist.x = 0;
				dist.y = 0;
				dist.z = 1;
				if (position.z < dot.z) dist.z *= (-1);
				return dist;
			}
			break;
		default:
			break;
		}
	}
};

/*
1. Add a rotation of the shapes.
2. Add interaction with objects (addition, subtraction, and so on (specify)).
*/