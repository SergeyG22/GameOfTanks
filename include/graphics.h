#pragma once
#include "../build/_deps/sfml-src/include/SFML/Graphics.hpp"
#include <iostream>
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
	virtual void shot() { };
	virtual void shot_with_keyboard(sf::Event& event) { };
	virtual void move_automatically(sf::Int64 time) { };
	virtual void keyboard_control(sf::Int64 time)   { };
	virtual void get_damage(float get_damage) = 0;
	virtual bool destroy_object() = 0;
	virtual bool intersection(sf::Sprite& sprite) = 0;
	virtual Timer get_timer() = 0;
	virtual std::list<std::unique_ptr<Weapon>>& get_weapon() = 0;
	virtual sf::Sprite& get_sprite() = 0;
	virtual ~Tanks() = default;
};

class TankVersion1: public Tanks {
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
	TankVersion1(WeaponInitializer* weapon, HealthBar* healthbar);	
	std::list<std::unique_ptr<Weapon>>& get_weapon()override { return weapon->get_weapon();  };	
	void shot()                            override;
	void get_damage(float power_damage)    override;
	void move_automatically(sf::Int64 time)override;
	bool destroy_object()                  override;
	bool intersection(sf::Sprite& spr)     override;	
};

class TankVersion1_ForThePlayer: public Tanks {
	sf::Sprite sprite;
	sf::Texture texture;
	Timer timer;
	RandomSelection random_selection;
	WeaponInitializer* weapon = nullptr;
	HealthBar* healthbar = nullptr;
	inline sf::Sprite& get_sprite() { return sprite; };
	inline Timer get_timer()override { return timer; };
	int multiplier_dictance = 5;
	bool moving_forward = true;
	double angle = 0.0;
	double current_angle = 0;
	double speed_rotate = 0.05;
	double speed_movement = 0.1;
	double radius_of_shot = 1000;
	double distance_to_point = 0;
	double current_position_x = 1000;
	double current_position_y = 500;
	double generate_position_x = 0;
	double generate_position_y = 0;
	double get_angle();
	void generate_point();
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
public:
	TankVersion1_ForThePlayer(WeaponInitializer* weapon, HealthBar* healthbar);
	std::list<std::unique_ptr<Weapon>>& get_weapon()override { return weapon->get_weapon(); };
	void shot_with_keyboard(sf::Event& )   override;
	void get_damage(float power_damage)    override;
	void keyboard_control(sf::Int64 time)  override;
	bool destroy_object()                  override;
	bool intersection(sf::Sprite& spr)     override;
};




class TankVersion2 : public Tanks {
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
	TankVersion2(WeaponInitializer* weapon,HealthBar* healthbar);	
	std::list<std::unique_ptr<Weapon>>& get_weapon()override { return weapon->get_weapon(); };	
	void shot()                            override;
	void get_damage(float power_damage)    override;
	void move_automatically(sf::Int64 time)override;		
	bool destroy_object()                  override;
	bool intersection(sf::Sprite& spr)     override;	
};




class TechnicFactory {

public:
	virtual std::unique_ptr<Tanks> create_tank_version_1(WeaponInitializer* weapon_initializer,HealthBar* healbar_initializer) = 0;
	virtual std::unique_ptr<Tanks> create_tank_version_2(WeaponInitializer* weapon_initializer,HealthBar* healbar_initializer) = 0;
	virtual std::unique_ptr<Tanks> create_tank_version_1_for_player(WeaponInitializer* weapon_initializer, HealthBar* healbar_initializer) = 0;
	virtual ~TechnicFactory() = default;
};

class TanksFactory: public TechnicFactory {

public:
	std::unique_ptr<Tanks>create_tank_version_1(WeaponInitializer* weapon_initializer, HealthBar* healbar_initializer) {
		return std::unique_ptr<Tanks>(new TankVersion1(weapon_initializer,healbar_initializer)); 
	}
	std::unique_ptr<Tanks>create_tank_version_2(WeaponInitializer* weapon_initializer, HealthBar* healbar_initializer) {
		return std::unique_ptr<Tanks>(new TankVersion2(weapon_initializer,healbar_initializer));
	}
	std::unique_ptr<Tanks>create_tank_version_1_for_player(WeaponInitializer* weapon_initializer, HealthBar* healbar_initializer) {
		return std::unique_ptr<Tanks>(new TankVersion1_ForThePlayer(weapon_initializer, healbar_initializer));
	}
};