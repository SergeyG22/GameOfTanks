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



const double PI = 3.14159265;

class RandomSelection {

public:
	double generate_number(int range_min, int range_max);
};

class Timer {

public:
	void add(std::chrono::milliseconds delay, std::function<void()> callback, bool asynchronous = true);
};


class Tanks {                                                                         //abstract factory

public:
	virtual ~Tanks() { };
	virtual sf::Sprite& get_sprite() = 0;
	virtual void move_automatically(sf::Int64 time) = 0;
	virtual void move_with_keyboard(sf::Event event, sf::Int64 time) = 0;
	virtual void shot() = 0;
	virtual std::list<std::unique_ptr<Weapon>>& get_weapon() =0;
};

class Tanks_v1: public Tanks {
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
	std::list<std::unique_ptr<Weapon>>weapon;
public:
	Tanks_v1();	
	sf::Sprite& get_sprite()override { return sprite; }
	std::list<std::unique_ptr<Weapon>>&get_weapon()override { return weapon; };	
	void move_automatically(sf::Int64 time)override;
	void move_with_keyboard(sf::Event event, sf::Int64 time)override;
	void rotation(sf::Int64 time);
	void shot()override;
	double get_angle();
};


class Tanks_v2 : public Tanks {
	sf::Sprite sprite;
	sf::Texture texture;
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
	std::list<std::unique_ptr<Weapon>>weapon;
public:
	Tanks_v2();
	sf::Sprite& get_sprite()override { return sprite; }
	void move_automatically(sf::Int64 time)override;
	void move_with_keyboard(sf::Event event, sf::Int64 time)override {};
	void rotation(sf::Int64 time);
	double get_angle();
	void shot()override {};
	std::list<std::unique_ptr<Weapon>>& get_weapon()override { return weapon; };
};




class TechnicFactory {

public:
	virtual std::unique_ptr<Tanks> create_tank_v1() = 0;
	virtual std::unique_ptr<Tanks> create_tank_v2() = 0;
	virtual ~TechnicFactory() { };
};

class TanksFactory: public TechnicFactory {

public:
	std::unique_ptr<Tanks>create_tank_v1() {
		return std::unique_ptr<Tanks>(new Tanks_v1);
	}
	std::unique_ptr<Tanks>create_tank_v2() {
		return std::unique_ptr<Tanks>(new Tanks_v2);
	}
};