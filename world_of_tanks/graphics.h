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
	float time = 0;
	float interval = 0;
	sf::Clock* clock = nullptr;
public:
	Timer(): clock(new sf::Clock) {  };
	bool restart_clock();
	inline void set_interval_shot(float interval_) { interval = interval_;}
};



class Tanks: public sf::Drawable {                                                                         //abstract factory

public:
	virtual void shot() = 0;
	virtual void move_automatically(sf::Int64 time) = 0;
	virtual void get_damage(float get_damage) = 0;
	virtual bool destroy_object() = 0;
	virtual bool intersection(sf::Sprite& sprite) = 0;
	virtual Timer get_timer() = 0;
	virtual std::list<std::unique_ptr<Weapon>>& get_weapon() = 0;
	virtual sf::Sprite& get_sprite() = 0;
	virtual ~Tanks() { };
};

class Tanks_v1: public Tanks {
	sf::Sprite sprite;
	sf::Texture texture;
	Timer timer;
	RandomSelection random_selection;
	WeaponInitializer* weapon = nullptr;
	HealthBar* healthbar = nullptr;
	inline sf::Sprite& get_sprite() {  return sprite;  };
	inline Timer get_timer()override { return timer; };
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
	double get_angle();
	void rotation(sf::Int64 time);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
public:
	Tanks_v1(WeaponInitializer* weapon, HealthBar* healthbar);	
	std::list<std::unique_ptr<Weapon>>& get_weapon()override { return weapon->get_weapon();  };	
	void shot()                            override;
	void get_damage(float power_damage)    override;
	void move_automatically(sf::Int64 time)override;			
	bool destroy_object()                  override;
	bool intersection(sf::Sprite& spr)     override;	
};


class Tanks_v2 : public Tanks {
	sf::Sprite sprite;
	sf::Texture texture;
	Timer timer;
	RandomSelection random_selection; 
	WeaponInitializer* weapon = nullptr;
	HealthBar* healthbar = nullptr;
	inline sf::Sprite& get_sprite() {  return sprite; };
	inline Timer get_timer() override { return timer; };
	int multiplier_dictance = 5;
	bool moving_forward = true;
	double angle = 0.0;
	double current_angle = 0;
	double speed_movement = 0.2;
	double speed_rotate = 0.05;
	double radius_of_shot = 1000;
	double distance_to_point = 0;
	double current_position_x = 500;
	double current_position_y = 0;
	double generate_position_x = 0;
	double generate_position_y = 0;
	double get_angle();
	void rotation(sf::Int64 time);
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
public:
	Tanks_v2(WeaponInitializer* weapon,HealthBar* healthbar);	
	std::list<std::unique_ptr<Weapon>>& get_weapon()override { return weapon->get_weapon(); };	
	void shot()                            override;
	void get_damage(float power_damage)    override;
	void move_automatically(sf::Int64 time)override;		
	bool destroy_object()                  override;
	bool intersection(sf::Sprite& spr)     override;	
};




class TechnicFactory {

public:
	virtual std::unique_ptr<Tanks> create_tank_v1(WeaponInitializer* weapon_initializer,HealthBar* healbar_initializer) = 0;
	virtual std::unique_ptr<Tanks> create_tank_v2(WeaponInitializer* weapon_initializer,HealthBar* healbar_initializer) = 0;
	virtual ~TechnicFactory() { };
};

class TanksFactory: public TechnicFactory {

public:
	std::unique_ptr<Tanks>create_tank_v1(WeaponInitializer* weapon_initializer, HealthBar* healbar_initializer) {
		return std::unique_ptr<Tanks>(new Tanks_v1(weapon_initializer,healbar_initializer)); 
	}
	std::unique_ptr<Tanks>create_tank_v2(WeaponInitializer* weapon_initializer, HealthBar* healbar_initializer) {
		return std::unique_ptr<Tanks>(new Tanks_v2(weapon_initializer,healbar_initializer));
	}
};