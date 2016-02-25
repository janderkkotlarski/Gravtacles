 #include <iostream>
 #include <cassert>
 #include <string>
 #include <vector>
 #include <cmath>
 
 #include <SFML/Graphics.hpp>
 
 
 
 int main()
 {
	 
	const std::string program_name{"Gravtacles V0.1"};
	 
	const float delta_time{0.025f};
	 
	const float window_x{704.0f};
	const float window_y{640.0f};
	 
	const sf::Vector2f window_sizes{window_x, window_y};
	 
	const sf::Color white{sf::Color(255, 255, 255)};    
    const sf::Color black{sf::Color(0, 0, 0)};    
    const sf::Color orange{sf::Color(255, 127, 0)};    
    const sf::Color purple{sf::Color(127, 0, 255)};    
    const sf::Color cyan{sf::Color(127, 255, 255)};
    const sf::Color red{sf::Color(255, 0, 0)};
    const sf::Color yellow{sf::Color(255, 255, 0)};
    const sf::Color green{sf::Color(0, 255, 0)};
    const sf::Color blue{sf::Color(127, 127, 255)};
	 
	sf::Color change{sf::Color(127, 0, 63)};
	
	const float radius{50.0f};
	
	sf::CircleShape circle{radius};
	
	circle.setOrigin(radius, radius);
	
	circle.setPosition(0.5f*window_sizes);
	
	circle.setFillColor(change);
	
	sf::Vector2f moving{0.0000004f*window_sizes};
	
	sf::Vector2f posit{circle.getPosition()};
	 
	sf::RenderWindow window{sf::VideoMode(window_x, window_y), program_name, sf::Style::Default};
	 
	while (window.isOpen())
    {
		
		sf::Clock clock;
		
        sf::Event event;
        
        window.clear(black);
        
        window.draw(circle);
        
        window.display();
        
        change.g = ((change.g + 1) % 256);
                
        circle.setFillColor(change);
        
        while(clock.getElapsedTime().asSeconds() < delta_time)
        {						
			
			posit = posit + moving;
			
			
			if ((posit.x < radius) ||
			    (posit.x + radius > window_x))
			{
				
				moving.x *= -1;
				
			}
			
			if ((posit.y < radius) ||
			    (posit.y + radius > window_y))
			{
				
				moving.y *= -1;
				
			}
			
		}
		
		circle.setPosition(posit);
                    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            
            window.close();
                    
            return 1;
                    
        }    
        
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
            {
                
                window.close();
                
                return 2;
                
            }
        
        }
            

    }
	 
	return 0;	 
	 
 }
