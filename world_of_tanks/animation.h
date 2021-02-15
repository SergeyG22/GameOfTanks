#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Explosion: public sf::Drawable {

public:
	virtual ~Explosion(){ };
	virtual void play(sf::Int64 time) = 0;
	virtual bool get_state() = 0;
};

class Explosion_A: public Explosion {	
	sf::Sprite sprite;
	sf::Texture texture;
	float current_frame = 0;
	bool play_back = true;
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
public:
	Explosion_A(sf::Vector2f position);
	void play(sf::Int64 time)override;
	bool get_state()override { return play_back; };
};

