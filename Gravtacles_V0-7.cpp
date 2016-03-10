#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>
#include <random>
 
#include <SFML/Graphics.hpp>

float absuvect(const sf::Vector2f& vecator)
{
	
	return std::sqrt(vecator.x*vecator.x + vecator.y*vecator.y);
	
}

class gravitor
{
	 
	const std::string m_file_name{"Field.png"};
	
	float m_radius{0.0f};
	
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
		m_radius = 0.25f*(m_image_bounds.width + m_image_bounds.height);
		
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
	
	float show_radius()
	{
		
		return m_radius;
		
	}
	
	float show_strength()
	{
		
		return m_strength;
		
	}
	
	sf::Vector2f get_position()
	{
		
		return m_sprite.getPosition();
		
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
	
	float m_radius{0.0f};
	
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
		m_radius = 0.25f*(m_image_bounds.width + m_image_bounds.height);
		
	}
	
	void set_color()
	{

		m_sprite.setColor(m_light_orange);
		
	}
	
	public:
	
	
	
	void set_position()
	{
		
		m_sprite.setPosition(m_posit);
		
	}
	
	void reset_speed()
	{
		
		m_speed = sf::Vector2f(0.0f, 0.0f);
		
	}
	
	void set_position(const sf::Vector2f& position)
	{
		
		
		m_posit = position;
		
		set_position();
		
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
	
	void reset_accel()
	{
		
		m_accel = sf::Vector2f(0.0f, 0.0f);
		
	}
	
	void set_click_speed(sf::RenderWindow& window)
	{
		
		const float mult{300.0f};

		const sf::Vector2f direction{static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) - m_posit};
		
		m_speed = mult*direction/absuvect(direction);

	}
	
	void add_accel(const sf::Vector2f& accel)
	{
		
		m_accel = m_accel + accel;
		
	}
	
	void speed_add_accel(const float delta_time)
	{
		
		m_speed = m_speed + delta_time*m_accel;
		
	}
	
	void posit_add_speed(const float delta_time)
	{
		
		m_posit = m_posit + delta_time*m_speed;
		
	}
	
	void decrease_speed()
	{
		
		m_speed *= 0.9999f;
		
	}
	
	void bounce(const sf::Vector2f& window_sizes)
	{
		
		if (m_posit.x < 0.0f)
		{
			
			m_speed.x = -m_speed.x;			
			m_posit.x = -m_posit.x;
			
		}
		
		if (m_posit.x > window_sizes.x)
		{
			
			m_speed.x = -m_speed.x;			
			m_posit.x = window_sizes.x + window_sizes.x - m_posit.x;
			
		}
		
		if (m_posit.y < 0.0f)
		{
			
			m_speed.y = -m_speed.y;			
			m_posit.y = -m_posit.y;
			
		}
		
		if (m_posit.y > window_sizes.y)
		{
			
			m_speed.y = -m_speed.y;			
			m_posit.y = window_sizes.y + window_sizes.y - m_posit.y;
			
		}
		
		set_position();
		
	}
	
	
	float show_radius()
	{
		
		return m_radius;
		
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
	
	float m_radius{0.0f};
	
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
		m_radius = 0.25f*(m_image_bounds.width + m_image_bounds.height);
		
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
	
	float show_radius()
	{
		
		return m_radius;
		
	}
	
	sf::Vector2f get_position()
	{
		
		return m_sprite.getPosition();
		
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

class score
{
	
	
	
};

sf::Vector2f gravector(const sf::Vector2f& distance, const float dist, const float radius,
					   const float strength)
{
	
	const float mult{-20000.0f};	
	assert(mult < 0.0f);
	
	const sf::Vector2f gravecs{(mult*strength*(radius - dist)*(radius - dist)/(radius*radius*dist))*distance};
	
	return gravecs;
	
}

void gravitas(cargo& ball, gravitor& grav)
{
	
	const sf::Vector2f distance{ball.get_position() - grav.get_position()};
	
	const float dist{absuvect(distance) + 0.0001f};
		
	if (dist < grav.show_radius())
	{
		
		ball.add_accel(gravector(distance, dist, grav.show_radius(), grav.show_strength()));
		
	}
		
}

bool cargo_reach_target(cargo& ball, target& goal)
{
	
	const float dist{absuvect(ball.get_position() - goal.get_position())};
	
	const float radius{ball.show_radius() + goal.show_radius()};
	
	if (dist <= radius)
	{
		
		return true;
		
	}
	
	return false;
	
}

float random_fraction()
{
	
	unsigned int max_unsigned {static_cast<unsigned int>(-1)};
	
	std::random_device rand;
	
	return static_cast<float>(rand())/static_cast<float>(max_unsigned);
	
}

float random_strength()
{
	
	return -1.0f + 2.0f*random_fraction();
		
}

sf::Vector2f random_posit(const sf::Vector2f& window_sizes)
{
	
	const float boundary{0.1f};
	
	const float range{1.0f - 2.0f*boundary};	
	
	return sf::Vector2f(window_sizes.x*(boundary + range*random_fraction()),
						window_sizes.y*(boundary + range*random_fraction()));
	
}



int main()
{
	

	
	const std::string program_name{"Gravtacles V0.7"};
	
	assert(program_name != "");
	
	const float delta_delta_time{0.001f};
	 
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
	
	std::vector <float> strengths{-0.25f};
	std::vector <sf::Vector2f> pozitions{sf::Vector2f(0.5f*window_x, 0.5f*window_y)};
										
	std::vector <gravitor> gravs;
	
	int grav_number{1};
	
	gravs.push_back(gravitor (strengths[grav_number - 1], pozitions[grav_number - 1]));
	gravs[grav_number - 1].set_spriterator();

		

	sf::RenderWindow window{sf::VideoMode(window_x, window_y), program_name, sf::Style::Default};
	
	const int max_level{10000};
	
	int current_level{1};
	 
	while (window.isOpen())
    {
				
		while (current_level <= max_level)
		{
			
			bool stay_in_level{true};			
			bool show_triforce{true};			
			bool move_in_level{false};
			
			ball.set_position(begin_posit);
			ball.reset_speed();
			
			while (stay_in_level)
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
				
				if (show_triforce)
				{
					
					triforce.show_polygon(window);
					
				}
				
				window.display();
				
				triforce.morph_polygon(window);
				
				bool cargo_target{false}; 
				
				while ((clock.getElapsedTime().asSeconds() < delta_time) &&
					   !cargo_target)
				{
					
					sf::Clock delta_clock;
					
					while (delta_clock.getElapsedTime().asSeconds() < delta_delta_time)
					{
												
					}
					
					if (move_in_level)
					{
						
						const float delta_temp{delta_clock.getElapsedTime().asSeconds()};
						
						ball.reset_accel();
						
						for (int count{0}; count < grav_number; ++count)
						{
							
							gravitas(ball, gravs[count]);
							
						}
						
						ball.speed_add_accel(delta_temp);
						ball.decrease_speed();
						ball.posit_add_speed(delta_temp);						
						ball.set_position();
						ball.bounce(window_sizes);
						
						
						if (!show_triforce &&
							cargo_reach_target(ball, goal))
						{
							
							cargo_target = true;
							
							stay_in_level = false;
							
						}

					}					
					
				}
				
				
				
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && show_triforce)
				{
					
					
					show_triforce = false;					
					move_in_level = true;
					
					ball.set_click_speed(window);
					
				}
				
				if (!show_triforce &&
					sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
				
					stay_in_level = false;
					
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
			
			++current_level;
			
			++grav_number;
				
			gravs.push_back(gravitor (random_strength(), random_posit(window_sizes)));
			
			for (int count{0}; count < grav_number; ++count)
			{
				
				gravs[count].set_spriterator();
				
			}
			
		}
		
		window.close();                

    }
	 
	return 0;	 
	 
}
