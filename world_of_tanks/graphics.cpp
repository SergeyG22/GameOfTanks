#include "graphics.h"


double RandomSelection::generate_number(int min, int max) {
	std::random_device random;
	std::mt19937 mt(random());
	std::uniform_real_distribution<double>range(min, max);
	return range(mt);
}

bool Timer::restart_clock() {
	time = clock->getElapsedTime().asSeconds();
	if (time > interval) {
		clock->restart();
		return true;
	}
	return false;
};






Tanks_v1::Tanks_v1(WeaponInitializer* weapon_initializer, HealthBar* healthbar_initializer):weapon(weapon_initializer),healthbar(healthbar_initializer) {
	if (!texture.loadFromFile("teñhniñ/tank_v1.png")) {
		std::cout << "error\n";
	}
	timer.set_interval_shot(0.5);           //sets the time between shots
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2  );
	generate_position_x = random_selection.generate_number(150, 1130);
	generate_position_y = random_selection.generate_number(150, 874);
    sprite.setRotation(get_angle());
	angle = get_angle();
}


void Tanks_v1::move_automatically(sf::Int64 time) {

	if (moving_forward) {
		distance_to_point = sqrt((generate_position_x - current_position_x) * (generate_position_x - current_position_x) + (generate_position_y - current_position_y) * (generate_position_y - current_position_y));
		if (distance_to_point > 1) {
			sprite.setPosition(current_position_x, current_position_y);
			current_position_x += speed_movement * time * (generate_position_x - current_position_x) / distance_to_point;
			current_position_y += speed_movement * time * (generate_position_y - current_position_y) / distance_to_point;
			healthbar->set_position(current_position_x,current_position_y);
		}
		else {
			generate_position_x = random_selection.generate_number(150, 1130);
			generate_position_y = random_selection.generate_number(150, 874);
			current_angle = get_angle();
			moving_forward = false;	
		}
	}
	else {
		if (!moving_forward) {
			rotation(time);			
		}
	}	
}





void Tanks_v1::rotation(sf::Int64 time) {
	if (angle < current_angle) {
		angle += speed_rotate * time;
		sprite.setRotation(angle);
		if (angle > current_angle) {
			moving_forward = true;
		}
	}
	else if (angle > current_angle) {
		angle -= speed_rotate * time;
		sprite.setRotation(angle);
		if (angle < current_angle) {
			moving_forward = true;		
		}
	}
}

void Tanks_v1::shot() {
	sf::Vector2f final_coordinates_bullet;
	sf::Vector2f current_position_techniks;	
	current_position_techniks.x = current_position_x;
	current_position_techniks.y = current_position_y;
	double x = (radius_of_shot / 2 * multiplier_dictance) * -cos(sprite.getRotation() * PI / 180);
	double y = (radius_of_shot / 2 * multiplier_dictance) * -sin(sprite.getRotation() * PI / 180);
	final_coordinates_bullet.x = x + current_position_x;
	final_coordinates_bullet.y = y + current_position_y;
	weapon->add_weapon(final_coordinates_bullet,current_position_techniks);
}

void Tanks_v1::get_damage(float power_damage){
	healthbar->change_healthbar(power_damage);
}

bool Tanks_v1::destroy_object(){
	if (healthbar->get_healthbar_rectangle()[1]->getSize().x == 0) {
		return true;
	}
		return false;	
}

bool Tanks_v1::intersection(sf::Sprite& spr){
	for (const auto& it : get_weapon()) {
		if (!sprite.getGlobalBounds().intersects(it->get_sprite().getGlobalBounds()) && it->get_sprite().getGlobalBounds().intersects(spr.getGlobalBounds())) {
			return true;
		}
	}
	return false;
}


double Tanks_v1::get_angle() {
	double delta_x = current_position_x - generate_position_x;
	double delta_y = current_position_y - generate_position_y;
	double angle = (atan2(delta_y, delta_x)) * 180 / PI;
	return angle;
}

void Tanks_v1::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
	for (const auto& it : healthbar->get_healthbar_rectangle()) {
		target.draw(*it, states);
	}
}



Tanks_v2::Tanks_v2(WeaponInitializer* weapon_initializer,HealthBar* healthbar_initializer):weapon(weapon_initializer),healthbar(healthbar_initializer) {
	if (!texture.loadFromFile("teñhniñ/tank_v2.png")) {
		std::cout << "error\n";
	}
	timer.set_interval_shot(0.2);           //sets the time between shots
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	generate_position_x = random_selection.generate_number(150, 1130);
	generate_position_y = random_selection.generate_number(150, 874);
	sprite.setRotation(get_angle());
	angle = get_angle();
}

void Tanks_v2::move_automatically(sf::Int64 time) {

	if (moving_forward) {
		distance_to_point = sqrt((generate_position_x - current_position_x) * (generate_position_x - current_position_x) + (generate_position_y - current_position_y) * (generate_position_y - current_position_y));
		if (distance_to_point > 1) {
			sprite.setPosition(current_position_x, current_position_y);
			current_position_x += speed_movement * time * (generate_position_x - current_position_x) / distance_to_point;
			current_position_y += speed_movement * time * (generate_position_y - current_position_y) / distance_to_point;
			healthbar->set_position(current_position_x, current_position_y);
		}
		else {
			generate_position_x = random_selection.generate_number(150, 1130);
			generate_position_y = random_selection.generate_number(150, 874);
			current_angle = get_angle();
			moving_forward = false;
		}
	}
	else {
		if (!moving_forward) {
			rotation(time);
		}
	}

}

void Tanks_v2::get_damage(float power_damage) {
	healthbar->change_healthbar(power_damage);
}


void Tanks_v2::shot() {
	sf::Vector2f final_coordinates_bullet;
	sf::Vector2f current_position_techniks;
	current_position_techniks.x = current_position_x;
	current_position_techniks.y = current_position_y;
	double x = (radius_of_shot / 2 * multiplier_dictance) * -cos(sprite.getRotation() * PI / 180);
	double y = (radius_of_shot / 2 * multiplier_dictance) * -sin(sprite.getRotation() * PI / 180);
	final_coordinates_bullet.x = x + current_position_x;
	final_coordinates_bullet.y = y + current_position_y;
	weapon->add_weapon(final_coordinates_bullet, current_position_techniks);
}

bool Tanks_v2::destroy_object() {
	if (healthbar->get_healthbar_rectangle()[1]->getSize().x == 0) {
		return true;
	}
	    return false;
}

bool Tanks_v2::intersection(sf::Sprite& spr) {
	for (const auto& it : get_weapon()) {
		if (!sprite.getGlobalBounds().intersects(it->get_sprite().getGlobalBounds()) && it->get_sprite().getGlobalBounds().intersects(spr.getGlobalBounds())) {
			return true;
		}
	}
	return false;
};


void Tanks_v2::rotation(sf::Int64 time) {
	if (angle < current_angle) {
		angle += speed_rotate * time;
		sprite.setRotation(angle);
		if (angle > current_angle) {
			moving_forward = true;
		}
	}
	else if (angle > current_angle) {
		angle -= speed_rotate * time;
		sprite.setRotation(angle);
		if (angle < current_angle) {
			moving_forward = true;
		}
	}
}




double Tanks_v2::get_angle() {
	double delta_x = current_position_x - generate_position_x;
	double delta_y = current_position_y - generate_position_y;
	double angle = (atan2(delta_y, delta_x)) * 180 / PI;
	return angle;
}

void Tanks_v2::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
	for (const auto& it : healthbar->get_healthbar_rectangle()) {
		target.draw(*it, states);
	}
}
