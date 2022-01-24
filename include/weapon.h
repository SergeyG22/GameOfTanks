#pragma once
#include "../build/_deps/sfml-src/include/SFML/Graphics.hpp"
#include <iostream>
#include <list>
#include <cmath>

class Weapon {

public:
	virtual ~Weapon() = default;
	virtual sf::Sprite& get_sprite() = 0;
	virtual void bullet_movements(sf::Int64 time) = 0;
	virtual sf::Vector2i get_current_position() = 0;
	virtual sf::Vector2i get_coordinates_bullet() = 0;
	virtual float get_power_of_weapon() = 0;
};


class GunTypeA: public Weapon{
	sf::Sprite sprite;
	sf::Texture texture;
	float power_damage = 50;
	double speed_movement = 1.5;
	double distance_to_point = 0;	
	sf::Vector2f current_position;
	sf::Vector2f final_coordinates_bullet;
	sf::Sprite& get_sprite()override { return sprite; }
	void bullet_movements(sf::Int64 time)override;
	float get_power_of_weapon()          override { return power_damage; };
	sf::Vector2i get_current_position()  override { return (sf::Vector2i)current_position; };
	sf::Vector2i get_coordinates_bullet()override { return (sf::Vector2i)final_coordinates_bullet; };
public:
	GunTypeA(sf::Vector2f final_coordinates_bullet,sf::Vector2f current_position);			
};

class GunTypeB : public Weapon {
	sf::Sprite sprite;
	sf::Texture texture;
	float power_damage = 5;
	double speed_movement = 1.5;
	double distance_to_point = 0;
	sf::Vector2f current_position;
	sf::Vector2f final_coordinates_bullet;
	sf::Sprite& get_sprite()override { return sprite; }
	void bullet_movements(sf::Int64 time)override;
	float get_power_of_weapon()          override { return power_damage; };
	sf::Vector2i get_current_position()  override { return (sf::Vector2i)current_position; };
	sf::Vector2i get_coordinates_bullet()override { return (sf::Vector2i)final_coordinates_bullet; };
public:
	GunTypeB(sf::Vector2f final_coordinates_bullet, sf::Vector2f current_position);		
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