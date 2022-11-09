#include <iostream>
#include <SFML/Graphics.hpp> //Библиотека SFML;
#define NUM_RAIN 100
using namespace std;
using namespace sf; // Пространство имён SFML;
unsigned short WIDTH = 1900, HEIGHT = 1000;
float SPEED = 100;

vector <Color> COLOR_LIB = {Color(186, 220, 255)
						   };

RenderWindow window(VideoMode(WIDTH, HEIGHT), "Rain", Style::Default, ContextSettings(0,0,8));


class Rain{
	public:
		float screen_pos[2]; //x=0 y=1
		float vel;
		Color color;
		float size = 2;
		
		void update();
		void draw();
		void get_pos();
		void Rotar(float ang);
		Rain();
};

Rain::Rain(){ // get_pos3d()
	Rain::get_pos();
	
	float a = rand();
	vel = (a/RAND_MAX) * 0.08 + 0.01;
	color = COLOR_LIB[rand() % COLOR_LIB.size()];
}

void Rain::get_pos(){
	screen_pos[0] = rand()%WIDTH;
	screen_pos[1] = -size*4;
}



void Rain::update(){
	screen_pos[1] = screen_pos[1] + vel * SPEED;
	if (screen_pos[1] > HEIGHT + size*4)
		Rain::get_pos();
}

void Rain::draw(){
	CircleShape rain(size);  
	
    rain.setPosition(screen_pos[0], screen_pos[1]);
	rain.setFillColor(color);  
 
	window.draw(rain);	 
}

class RainField{
	public:
		Rain rains[NUM_RAIN];
		void run();
};


void RainField::run(){
	for(int i=0; i<NUM_RAIN;i++)
		rains[i].update();
		
	for(int i=0; i<NUM_RAIN;i++)
		rains[i].draw();
}

int main()
{
    window.setFramerateLimit(120);
       
    RectangleShape fon(Vector2f(WIDTH, HEIGHT));  
    fon.setFillColor(Color(0, 0, 32, 20));  
    
    RainField rnfd;
    
    window.clear(Color::Black);
    
   	RectangleShape aa(Vector2f(WIDTH, HEIGHT));  
	aa.setFillColor(Color(128, 128, 128)); 
	window.draw(aa); 
	
	Clock time;
	bool fl = true;
    
    while(window.isOpen()) 
    {
        Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close(); 
        }
		
		if(fl)
			if(time.getElapsedTime().asMilliseconds() >= 100){
				time.restart();
				fl = false;
				window.draw(aa); 
			}
		
		window.draw(fon);	  
		
		rnfd.run();
        
        window.display();
    }
    return 0; 
}