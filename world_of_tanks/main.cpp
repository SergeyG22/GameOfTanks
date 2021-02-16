#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "graphics.h"
#include "animation.h"







int main()
{
   sf::RenderWindow window(sf::VideoMode(1280, 1024), "World of tanks");
   std::list<std::unique_ptr<Tanks>>techniks;
   std::list<std::unique_ptr<Explosion>>explosion;

   TechnicFactory* tanks_factory = new TanksFactory;
   WeaponInitializer* weapon_b = new GunTypeA_Initializer;
   HealthBar* healthbar_a = new HealthBarTypeA;
   WeaponInitializer* weapon_a = new GunTypeB_Initializer;
   HealthBar* healthbar_b = new HealthBarTypeA;
   WeaponInitializer* weapon_c = new GunTypeB_Initializer;
   HealthBar* healthbar_c = new HealthBarTypeA;

   WeaponInitializer* weapon_d = new GunTypeB_Initializer;
   HealthBar* healthbar_d = new HealthBarTypeA;
   
   techniks.emplace_back(std::unique_ptr<Tanks>(tanks_factory->create_tank_version_2(weapon_b,healthbar_a)));
   techniks.emplace_back(std::unique_ptr<Tanks>(tanks_factory->create_tank_version_2(weapon_b,healthbar_b)));
   techniks.emplace_back(std::unique_ptr<Tanks>(tanks_factory->create_tank_version_2(weapon_c,healthbar_c)));
   techniks.emplace_back(std::unique_ptr<Tanks>(tanks_factory->create_tank_version_1_for_player(weapon_d,healthbar_d)));

   sf::Clock clock;




    while (window.isOpen())
    {

        auto time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;



        sf::Event event;
        while (window.pollEvent(event))
        {
            for (const auto& it : techniks) {
                it->shot_with_keyboard(event);
            }
            




            if (event.type == sf::Event::Closed)
                window.close();
        }

                
        window.clear();

        

        





        for (const auto& it : techniks) {            
            if (it->get_timer().restart_clock()) {            //fire a shot if returned true                
                it->shot();
            }          
              window.draw(*it);
              it->move_automatically(time);
              it->keyboard_control(time);
            for (const auto& iter : it->get_weapon()) {
                window.draw(iter->get_sprite());
                  iter->bullet_movements(time);
                  it->get_weapon();
            }
        }


        for (auto it1 = techniks.begin(); it1 != techniks.end(); ++it1) {
            for (auto it2 = techniks.begin(); it2 != techniks.end(); ++it2) {
                if ((*it1)->intersection((*it2)->get_sprite())) {
                    for (auto it3 = (*it1)->get_weapon().begin(); it3 != (*it1)->get_weapon().end();) {
                        if ((*it1)->intersection((*it2)->get_sprite())) {

                         
                            (*it2)->get_damage((*it3)->get_power_of_weapon());
                            explosion.emplace_back(std::unique_ptr<Explosion>(new Explosion_A(sf::Vector2f((*it3)->get_current_position()))));                           
                            it3 = (*it1)->get_weapon().erase(it3);
                        }
                        else {
                            ++it3;
                        }
                    }
                       
                  
                }
            }
        }
        
        for (auto it = techniks.begin(); it != techniks.end(); ) {
            if ((*it)->destroy_object()) {
                it = techniks.erase(it);
            } 
            else{
                ++it;
            }
        }
        
        for (auto it = explosion.begin(); it != explosion.end(); ) {
            if (!(*it)->get_state()) {
                it = explosion.erase(it);
            } 
            else {
                ++it;
            }
            
        }

        for (const auto& it : explosion) {
            it->play(time);
            window.draw(*it);
        }

   

        
        for (auto it = techniks.begin(); it != techniks.end(); ++it) {                 //deletes objects when a point is reached
            for (auto iter = (*it)->get_weapon().begin(); iter != (*it)->get_weapon().end();) {               
                if ((*iter)->get_current_position() == (*iter)->get_coordinates_bullet()) {
                        iter = (*it)->get_weapon().erase(iter);
                    }
                else {
                    ++iter;
                }
            }
        }
        
        for (auto it = techniks.begin(); it != techniks.end(); ++it) {                 // deletes an object off-screen
            for (auto iter = (*it)->get_weapon().begin(); iter != (*it)->get_weapon().end();) {            
                if ((*iter)->get_sprite().getPosition().x <=0 || (*iter)->get_sprite().getPosition().x >= window.getSize().x
                   || (*iter)->get_sprite().getPosition().y <= 0 || (*iter)->get_sprite().getPosition().y >= window.getSize().y                    
                    ) {
                    iter = (*it)->get_weapon().erase(iter);                   
                }
                else {
                    ++iter;
                }
                
            }
        }
        
        





        window.display();       
    }

    return 0;
}