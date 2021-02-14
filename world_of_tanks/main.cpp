#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "graphics.h"








int main()
{
   sf::RenderWindow window(sf::VideoMode(1280, 1024), "World of tanks");
   std::list<std::unique_ptr<Tanks>>techniks;
   TechnicFactory* tanks_factory = new TanksFactory;
   WeaponInitializer* weapon_b = new GunTypeB_Initializer;
   HealthBar* healthbar_a = new HealthBarTypeA;
   WeaponInitializer* weapon_a = new GunTypeA_Initializer;
   HealthBar* healthbar_b = new HealthBarTypeA;

   WeaponInitializer* weapon_c = new GunTypeB_Initializer;
   HealthBar* healthbar_c = new HealthBarTypeA;


   
   techniks.emplace_back(std::unique_ptr<Tanks>(tanks_factory->create_tank_v1(weapon_a,healthbar_a)));
   techniks.emplace_back(std::unique_ptr<Tanks>(tanks_factory->create_tank_v2(weapon_b,healthbar_b)));
   techniks.emplace_back(std::unique_ptr<Tanks>(tanks_factory->create_tank_v2(weapon_c, healthbar_c)));


    sf::Clock clock;

  


    while (window.isOpen())
    {

        auto time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;



        sf::Event event;
        while (window.pollEvent(event))
        {


            




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