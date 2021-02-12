#include "weapon.h"


GunTypeA::GunTypeA(sf::Vector2f final_coordinates_bullet_, sf::Vector2f current_position_techniks){

	final_coordinates_bullet = final_coordinates_bullet_;
	current_position = current_position_techniks;
	current_position.x -= texture.getSize().x/2;
	current_position.y -= texture.getSize().y/2;
	if (!texture.loadFromFile("weapon/weapon_a.png")) {
		std::cout << "error\n";
	}
	sprite.setTexture(texture);
	sprite.setPosition(current_position.x, current_position.y);
}

void GunTypeA::bullet_movements(sf::Int64 time) {	
	distance_to_point = sqrt((final_coordinates_bullet.x - current_position.x) * (final_coordinates_bullet.x - current_position.x) + (final_coordinates_bullet.y - current_position.y) * (final_coordinates_bullet.y - current_position.y));
	if (distance_to_point > 1) {		
		current_position.x += speed_movement * time * (final_coordinates_bullet.x - current_position.x) / distance_to_point;
		current_position.y += speed_movement * time * (final_coordinates_bullet.y - current_position.y) / distance_to_point;
		sprite.setPosition(current_position.x - texture.getSize().x / 2, current_position.y - texture.getSize().y / 2);
	}
}



GunTypeB::GunTypeB(sf::Vector2f final_coordinates_bullet_, sf::Vector2f current_position_techniks) {

	final_coordinates_bullet = final_coordinates_bullet_;
	current_position = current_position_techniks;
	current_position.x -= texture.getSize().x / 2;
	current_position.y -= texture.getSize().y / 2;
	if (!texture.loadFromFile("weapon/weapon_b.png")) {
		std::cout << "error\n";
	}
	sprite.setTexture(texture);
	sprite.setPosition(current_position.x, current_position.y);
}

void GunTypeB::bullet_movements(sf::Int64 time) {
	distance_to_point = sqrt((final_coordinates_bullet.x - current_position.x) * (final_coordinates_bullet.x - current_position.x) + (final_coordinates_bullet.y - current_position.y) * (final_coordinates_bullet.y - current_position.y));
	if (distance_to_point > 1) {
		current_position.x += speed_movement * time * (final_coordinates_bullet.x - current_position.x) / distance_to_point;
		current_position.y += speed_movement * time * (final_coordinates_bullet.y - current_position.y) / distance_to_point;
		sprite.setPosition(current_position.x - texture.getSize().x / 2, current_position.y - texture.getSize().y / 2);
	}
}