#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include "graphics.h"








int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "World of tanks");

   std::list<std::unique_ptr<Tanks>>techniks;
   TechnicFactory* tanks_factory = new TanksFactory;
   techniks.emplace_back(std::unique_ptr<Tanks>(tanks_factory->create_tank_v1()));
 //  techniks.emplace_back(std::unique_ptr<Tanks>(tanks_factory->create_tank_v2()));


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
                it->move_with_keyboard(event, time);
            }



            if (event.type == sf::Event::Closed)
                window.close();
        }

                
        window.clear();
        for (const auto& it : techniks) {          
            window.draw(it->get_sprite());
              it->move(time);
            for (const auto& iter : it->get_weapon()) {
                window.draw(iter->get_sprite());
                  iter->bullet_movements(time);
                  if (iter->get_current_position() == iter->get_coordinates_bullet()) {
                      std::cout << it->get_weapon().size()<<'\n';
                  }
            }
        }
        
        for (auto it = techniks.begin(); it != techniks.end();++it) {
            for (auto iter = (*it)->get_weapon().begin(); iter != (*it)->get_weapon().end();) {
                if ((*iter)->get_current_position() == (*iter)->get_coordinates_bullet()) {
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