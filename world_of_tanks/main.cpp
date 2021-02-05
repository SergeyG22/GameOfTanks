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
   techniks.emplace_back(std::unique_ptr<Tanks>(tanks_factory->create_tank_v2()));


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
            window.draw(it->get_sprite());
            it->move(time);
        }


        window.display();       
    }

    return 0;
}