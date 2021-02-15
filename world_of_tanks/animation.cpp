#include "animation.h"

Explosion_A::Explosion_A(sf::Vector2f position) {
	if (!texture.loadFromFile("animation/explosion_a.png")) {
		std::cout << "error\n";
	}
	sprite.setTexture(texture);
	sprite.setPosition(position);
}


void Explosion_A::play(sf::Int64 time) {	
		current_frame += 0.05 * time;
		if (play_back) {
			if (current_frame > 20) {
				current_frame -= 20;
				play_back = false;
			}
		}
		 sprite.setTextureRect(sf::IntRect(50 * int(current_frame), 0, 51, 50));		
}

void Explosion_A::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}