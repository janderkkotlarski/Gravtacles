#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>
 
#include <SFML/Graphics.hpp>

class gravitor
{
	 
	const std::string m_file_name{"Field.png"};
	
	const float m_strength{1.0f};
	
	const sf::Color m_light_red{sf::Color(255, 63, 63, 255)};
	const sf::Color m_light_blue{sf::Color(63, 63, 255, 255)};
	 
	sf::Texture m_texture;	
	sf::Sprite m_sprite;
	 
	void set_texture()
	{
		
		assert(m_file_name != "");
		
		if (!m_texture.loadFromFile(m_file_name))
		{
				
			std::cout << m_file_name << " not found!\n";
				
		}
		 
	}
	
	void set_sprite_texture()
	{
		
		m_sprite.setTexture(m_texture);
		
	}
	
	void set_origin()
	{
		
		const sf::FloatRect m_image_bounds{m_sprite.getLocalBounds()};		
		m_sprite.setOrigin(0.5f*m_image_bounds.width, 0.5f*m_image_bounds.height);
		
	}
	
	void set_position(const sf::Vector2f& position)
	{
		
		m_sprite.setPosition(position);
		
	}
	
	void set_color()
	{
		
		int opaque{abs(static_cast<int>(m_strength*255.0f))};
		
		if (opaque > 255)
		{
			
			opaque = 255;
			
		}
		
		if (m_strength < 0.0f)
		{
			
			sf::Color light_red{m_light_red};			
			light_red.a = opaque;			
			m_sprite.setColor(light_red);
			
		}
		else
		{
			
			sf::Color light_blue{m_light_blue};			
			light_blue.a = opaque;			
			m_sprite.setColor(light_blue);
			
		}
		
	}
	
	public:
	
	void show_gravitor(sf::RenderWindow& window)
	{
		
		window.draw(m_sprite);
			
	}
	
	void set_spriterator()
	{
		
		set_texture();		
		set_sprite_texture();
		
	}
	
	gravitor(const float strength, const sf::Vector2f& position)
		: m_strength(strength), m_texture(), m_sprite()
	{
		
		set_texture();		
		set_sprite_texture();		
		set_origin();		
		set_position(position);		
		set_color();
		
	}
	
	~gravitor()
	{
		
	}	
	 
};

class cargo
{
	
	const std::string m_file_name{"Ball.png"};
	
	const sf::Color m_light_orange{sf::Color(255, 196, 63, 255)};
	
	sf::Vector2f m_posit{0.0f, 0.0f};
	sf::Vector2f m_speed{0.0f, 0.0f};
	sf::Vector2f m_accel{0.0f, 0.0f};
	
	sf::Texture m_texture;	
	sf::Sprite m_sprite;
	 
	void set_texture()
	{
		
		assert(m_file_name != "");
		
		if (!m_texture.loadFromFile(m_file_name))
		{
				
			std::cout << m_file_name << " not found!\n";
				
		}
		 
	}
	
	void set_sprite_texture()
	{
		
		m_sprite.setTexture(m_texture);
		
	}
	
	void set_origin()
	{
		
		const sf::FloatRect m_image_bounds{m_sprite.getLocalBounds()};		
		m_sprite.setOrigin(0.5f*m_image_bounds.width, 0.5f*m_image_bounds.height);
		
	}
	
	void set_color()
	{

		m_sprite.setColor(m_light_orange);
		
	}
	
	public:
	
	void set_position(const sf::Vector2f& position)
	{
		
		m_sprite.setPosition(position);
		
	}	
	
	void show_cargo(sf::RenderWindow& window)
	{
		
		window.draw(m_sprite);
			
	}
	
	void set_spriterator()
	{
		
		set_texture();		
		set_sprite_texture();
		
	}
	
	sf::Vector2f get_position()
	{
		
		return m_sprite.getPosition();
		
	}
	
	sf::FloatRect get_sizes()
	{
		
		return m_sprite.getLocalBounds();
		
	}
	
	cargo(const sf::Vector2f& position)
		: m_posit(position),
		  m_texture(), m_sprite()
	{
		
		set_texture();		
		set_sprite_texture();		
		set_origin();		
		set_position(m_posit);		
		set_color();
		
	}
	
	~cargo()
	{
		
	}
	
};

class pointer
{
	
	const sf::Color m_light_cyan{sf::Color(63, 255, 255, 63)};
	
	sf::ConvexShape m_polygon;
	
	void init_polygon(cargo& ball)
	{
				
		const sf::Vector2f position{ball.get_position()};
		
		const float mult{0.33f};
		
		const sf::FloatRect image_bounds{ball.get_sizes()};
		
			
		const float width{mult*image_bounds.width};
		const float height{mult*image_bounds.height};
		
		m_polygon.setPointCount(3);
		
		m_polygon.setPoint(0, position + sf::Vector2f(width, height));		
		m_polygon.setPoint(1, position + sf::Vector2f(width, -height));		
		m_polygon.setPoint(2, position + sf::Vector2f(-width, height));
		
		m_polygon.setFillColor(m_light_cyan);
		
	}
	
	public:
	
	void morph_polygon(sf::RenderWindow& window)
	{
		
		m_polygon.setPoint(0, static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));	
			
	}
	
	void show_polygon(sf::RenderWindow& window)
	{
		
		window.draw(m_polygon);
		
	}
	
	pointer(cargo& ball)
		: m_polygon()
	{
		
		init_polygon(ball);
		
	}
	
	~pointer()
	{
		
	}
	
};

class target
{
	
	const std::string m_file_name{"Ball.png"};
	
	const sf::Color m_light_purple{sf::Color(255, 63, 255, 255)};
	
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	
	void set_texture()
	{
		
		assert(m_file_name != "");
		
		if (!m_texture.loadFromFile(m_file_name))
		{
				
			std::cout << m_file_name << " not found!\n";
				
		}
		 
	}
	
	void set_sprite_texture()
	{
		
		m_sprite.setTexture(m_texture);
		
	}
	
	void set_origin()
	{
		
		const sf::FloatRect m_image_bounds{m_sprite.getLocalBounds()};		
		m_sprite.setOrigin(0.5f*m_image_bounds.width, 0.5f*m_image_bounds.height);
		
	}
	
	void set_color()
	{

		m_sprite.setColor(m_light_purple);
		
	}
	
	void set_position(const sf::Vector2f& position)
	{
		
		m_sprite.setPosition(position);
		
	}
	
	public:
	
	void show_target(sf::RenderWindow& window)
	{
		
		window.draw(m_sprite);
			
	}
	
	target(const sf::Vector2f& position)
		: m_texture(), m_sprite()
	{
		
		set_texture();		
		set_sprite_texture();		
		set_origin();		
		set_position(position);		
		set_color();
		
	}
	
	~target()
	{
		
	}
	
};



int main()
{
	 
	const std::string program_name{"Gravtacles V0.4"};
	
	assert(program_name != "");
	 
	const float delta_time{0.025f};
	 
	const float window_x{704.0f};
	const float window_y{704.0f};
	
	assert(window_x > 0.0f);
	assert(window_y > 0.0f);
	 
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

	const sf::Vector2f begin_posit{0.05f*window_sizes};
	const sf::Vector2f end_posit{0.95f*window_sizes};
	
	
	
	cargo ball{begin_posit};
	
	pointer triforce{ball};
	
	target goal{end_posit};
	
	std::vector <float> strengths{1.0f, -1.0f, 0.1f, -0.7f, 0.3f};	
	const int grav_number{static_cast<int>(strengths.size())};	
	
	std::vector <sf::Vector2f> pozitions{sf::Vector2f(0.1f*window_x, 0.9f*window_y),
										 sf::Vector2f(0.8f*window_x, 0.2f*window_y),
										 sf::Vector2f(0.7f*window_x, 0.5f*window_y),
										 sf::Vector2f(0.1f*window_x, 0.3f*window_y),
										 sf::Vector2f(0.9f*window_x, 0.8f*window_y)};
	
	std::vector <gravitor> gravs;
	
	for (int count{0}; count < grav_number; ++count)
	{
		
		gravs.push_back(gravitor (strengths[count], pozitions[count]));

	}
	
	for (int count{0}; count < grav_number; ++count)
	{
		
		gravs[count].set_spriterator();
		
	}
	 
	sf::RenderWindow window{sf::VideoMode(window_x, window_y), program_name, sf::Style::Default};
	 
	while (window.isOpen())
    {
		
		sf::Clock clock;
		
        sf::Event event;
        
        window.clear(black);
            
        for (int count{0}; count < grav_number; ++count)
		{
			
			gravs[count].show_gravitor(window);
			
		}
		
		ball.show_cargo(window);
		
		goal.show_target(window);
		
		triforce.show_polygon(window);
        
        window.display();
        
        triforce.morph_polygon(window);
        
        while(clock.getElapsedTime().asSeconds() < delta_time)
        {						

		}

                    
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
