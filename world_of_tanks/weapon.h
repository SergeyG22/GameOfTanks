#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

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

class GunTypeB : public Weapon {
	sf::Sprite sprite;
	sf::Texture texture;
	double speed_movement = 0.5;
	double distance_to_point = 0;
	sf::Vector2f current_position;
	sf::Vector2f final_coordinates_bullet;
public:
	GunTypeB(sf::Vector2f final_coordinates_bullet, sf::Vector2f current_position);
	sf::Sprite& get_sprite()override { return sprite; }
	void bullet_movements(sf::Int64 time)override;
	sf::Vector2i get_current_position()override { return (sf::Vector2i)current_position; };
	sf::Vector2i get_coordinates_bullet()override { return (sf::Vector2i)final_coordinates_bullet; };
};











class WeaponInitializer {                                           //strategy
	
public:
	virtual void add_weapon(sf::Vector2f,sf::Vector2f) = 0;
	virtual std::list<std::unique_ptr<Weapon>>& get_weapon() = 0;
	virtual ~WeaponInitializer() { };
};

class GunTypeA_Initializer: public WeaponInitializer {
	 std::list<std::unique_ptr<Weapon>>weapon;
public:
	void add_weapon(sf::Vector2f final_coordinates_bullet,sf::Vector2f current_position_techniks)override {
		weapon.emplace_back(std::unique_ptr<Weapon>(new GunTypeA(final_coordinates_bullet, current_position_techniks)));
	}
	std::list<std::unique_ptr<Weapon>>& get_weapon()override { return weapon; };
};

class GunTypeB_Initializer: public WeaponInitializer {
	std::list<std::unique_ptr<Weapon>>weapon;
public:
	void add_weapon(sf::Vector2f final_coordinates_bullet, sf::Vector2f current_position_techniks)override {
		weapon.emplace_back(std::unique_ptr<Weapon>(new GunTypeB(final_coordinates_bullet, current_position_techniks)));
	}
	std::list<std::unique_ptr<Weapon>>& get_weapon()override { return weapon; };
};