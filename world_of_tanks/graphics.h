#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <thread>
#include <memory>
#include <random>
#include <chrono>
#include <list>
#include <cmath>
#include "weapon.h"
#include "healthbar.h"



const double PI = 3.14159265;

class RandomSelection {

public:
	double generate_number(int range_min, int range_max);
};



class Timer {
	sf::Clock* clock = nullptr;
	float interval = 0;
	float time = 0;
public:
	Timer(): clock(new sf::Clock) { 
	};
	float get_elapsed_time() { return clock->getElapsedTime().asSeconds(); };
	bool restart_clock() {
		time = clock->getElapsedTime().asSeconds();
		if (time > interval) {
			clock->restart();
			return true;
		}
		return false;
	};
	void set_interval_shot(float interval_) {
		interval = interval_;
	}
};



class Tanks {                                                                         //abstract factory

public:
	virtual ~Tanks() { };
	virtual sf::Sprite& get_sprite() = 0;
	virtual void shot() = 0;
	virtual void move_automatically(sf::Int64 time) = 0;
	virtual Timer get_timer() = 0;
	virtual std::list<std::unique_ptr<Weapon>>& get_weapon() =0;
};

class Tanks_v1 : public Tanks {
	sf::Sprite sprite;
	sf::Texture texture;
	Timer timer;
	RandomSelection random_selection;
	int multiplier_dictance = 5;
	bool moving_forward = true;
	double angle = 0.0;
	double current_angle = 0;	
	double speed_rotate = 0.05;
	double speed_movement = 0.1;
	double radius_of_shot = 1000;
	double distance_to_point = 0;	
	double current_position_x = 500;
	double current_position_y = 500;
	double generate_position_x = 0;
	double generate_position_y = 0;	
  //std::list<std::unique_ptr<Weapon>>weapon;
	WeaponInitializer* weapon = nullptr;
public:
	Tanks_v1(WeaponInitializer* weapon);
	sf::Sprite& get_sprite()override { return sprite; }
	std::list<std::unique_ptr<Weapon>>&get_weapon()override { return weapon->get_weapon(); };
	Timer get_timer()override { return timer; };
	void move_automatically(sf::Int64 time)override;
	void rotation(sf::Int64 time);
	void shot()override;
	double get_angle();
};


class Tanks_v2 : public Tanks {
	sf::Sprite sprite;
	sf::Texture texture;
	Timer timer;
	RandomSelection random_selection;
	bool moving_forward = true;
	double angle = 0.0;
	double current_angle = 0;
	double speed_movement = 0.2;
	double speed_rotate = 0.05;
	double distance_to_point = 0;
	double current_position_x = 500;
	double current_position_y = 0;
	double generate_position_x = 0;
	double generate_position_y = 0;
	//std::list<std::unique_ptr<Weapon>>weapon;
	WeaponInitializer* weapon = nullptr;
public:
	Tanks_v2(WeaponInitializer* weapon);
	sf::Sprite& get_sprite()override { return sprite; }
	Timer get_timer()override { return timer; };
	void move_automatically(sf::Int64 time)override;
	void rotation(sf::Int64 time);
	double get_angle();
	void shot()override {};
	std::list<std::unique_ptr<Weapon>>& get_weapon()override { return weapon->get_weapon(); };
};




class TechnicFactory {

public:
	virtual std::unique_ptr<Tanks> create_tank_v1(WeaponInitializer* weapon_initializer) = 0;
	virtual std::unique_ptr<Tanks> create_tank_v2(WeaponInitializer* weapon_initializer) = 0;
	virtual ~TechnicFactory() { };
};

class TanksFactory: public TechnicFactory {

public:
	std::unique_ptr<Tanks>create_tank_v1(WeaponInitializer* weapon_initializer) {
		return std::unique_ptr<Tanks>(new Tanks_v1(weapon_initializer)); 
	}
	std::unique_ptr<Tanks>create_tank_v2(WeaponInitializer* weapon_initializer) {
		return std::unique_ptr<Tanks>(new Tanks_v2(weapon_initializer));
	}
};