#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Weapon {

public:
	virtual ~Weapon() { };
	virtual sf::Sprite& get_sprite() = 0;
	virtual void bullet_movements(sf::Int64 time) = 0;
	virtual sf::Vector2i get_current_position() = 0;
	virtual sf::Vector2i get_coordinates_bullet() = 0;
};

class GunTypeA: public Weapon{
	sf::Sprite sprite;
	sf::Texture texture;
	double speed_movement = 1.5;
	double distance_to_point = 0;
	sf::Vector2f current_position;
	sf::Vector2f final_coordinates_bullet;
public:
	GunTypeA(sf::Vector2f final_coordinates_bullet,sf::Vector2f current_position);
	sf::Sprite& get_sprite()override { return sprite; }
	void bullet_movements(sf::Int64 time)override;
	sf::Vector2i get_current_position()override { return (sf::Vector2i)current_position; };
	sf::Vector2i get_coordinates_bullet()override { return (sf::Vector2i)final_coordinates_bullet; };
};